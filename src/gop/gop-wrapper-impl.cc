// gop/gop-wrapper-impl.cc

// Copyright 2016-2017  Junbo Zhang

// This program based on Kaldi (https://github.com/kaldi-asr/kaldi).
// However, this program is NOT UNDER THE SAME LICENSE of Kaldi's.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// version 2 as published by the Free Software Foundation;
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

#include "fstext/fstext-lib.h"
#include "feat/wave-reader.h"
#include "feat/feature-mfcc.h"
#include "gop/gop-wrapper.h"
#include "gop/gop-wrapper-impl.h"
#include "gop/gmm-gop.h"

using namespace kaldi;

void GopImpl::Init(std::string &model_pathname) {
  std::string tree_in_filename = model_pathname + "/tree";
  std::string model_in_filename = model_pathname + "/final.mdl";
  std::string lex_in_filename = model_pathname + "/L.fst";
  std::string word_symbol_filename = model_pathname + "/words.txt";
  std::string phone_symbol_filename = model_pathname + "/phones.txt";
  gmmgop_.Init(tree_in_filename, model_in_filename, lex_in_filename);
  word_syms_ = fst::SymbolTable::ReadText(word_symbol_filename);
  phone_syms_ = fst::SymbolTable::ReadText(phone_symbol_filename);
}

void GopImpl::Compute(std::string &wav_filename, std::string text_string) {
  std::ifstream is(wav_filename);
  KALDI_ASSERT(is.is_open());
  WaveData wave_data;
  wave_data.Read(is);
  is.close();
  KALDI_ASSERT(wave_data.Data().NumRows() == 1);

  MfccOptions mfcc_opts;
  Mfcc mfcc(mfcc_opts);
  Matrix<BaseFloat> mfcc_feats;
  SubVector<BaseFloat> waveform(wave_data.Data(), 0);
  mfcc.Compute(waveform, 1, &mfcc_feats, NULL);

  DeltaFeaturesOptions delta_opts;
  delta_opts.order = 2;
  delta_opts.window = 3;
  Matrix<BaseFloat> delta_feats;
  ComputeDeltas(delta_opts, mfcc_feats, &delta_feats);

  SlidingWindowCmnOptions cmvn_opts;
  cmvn_opts.cmn_window = 300;
  cmvn_opts.normalize_variance = false;
  cmvn_opts.center = true;
  Matrix<BaseFloat> features(delta_feats.NumRows(), delta_feats.NumCols(), kUndefined);
  SlidingWindowCmn(cmvn_opts, delta_feats, &features);

  std::istringstream iss(text_string);
  std::vector<int32> transcript;
  while (iss) {
    std::string sub;
    iss >> sub;
    int32 word_id = word_syms_->Find(sub);
    if (word_id > 0)
      transcript.push_back(word_id);
  }

  gmmgop_.Compute(features, transcript);
  auto &gop_result = gmmgop_.Result();
  auto &phones = gmmgop_.Phonemes();
  KALDI_ASSERT(gop_result.Dim() == phones.size());
  result_.clear();
  for (size_t i = 0; i < gop_result.Dim(); i++) {
    std::string phone = phone_syms_->Find(phones[i]);
    float score = gop_result(i);
    result_.push_back(std::pair<std::string, float>(phone, score));
  }
}

std::vector<std::pair<std::string, float> >& GopImpl::Result() {
  return result_;
}
