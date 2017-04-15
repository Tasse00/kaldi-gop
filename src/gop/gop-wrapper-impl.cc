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
#include "gop/gop-wrapper.h"
#include "gop/gop-wrapper-impl.h"
#include "gop/gmm-gop.h"

using namespace kaldi;

void GopImpl::Init(std::string &model_pathname) {
  std::string tree_in_filename = model_pathname + "/tree";
  std::string model_in_filename = model_pathname + "/final.mdl";
  std::string lex_in_filename = model_pathname + "/L.fst";
  std::string word_symbol_filename = model_pathname + "/words.txt";
  gmmgop_.Init(tree_in_filename, model_in_filename, lex_in_filename);
  word_syms_ = fst::SymbolTable::ReadText(word_symbol_filename);
}

void GopImpl::Compute(std::string &wav_filename, std::string text_string) {
  const Matrix<BaseFloat> features;

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
  Vector<BaseFloat> &result = gmmgop_.Result();
  result_.clear();
  for (size_t i = 0; i < result.Dim(); i++) {
    result_.push_back(result(i));
  }
}

std::vector<float>& GopImpl::Result() {
  return result_;
}
