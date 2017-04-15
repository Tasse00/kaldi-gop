// gop/gop-wrapper-impl.h

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

#ifndef KALDI_GOP_WRAPPER_IMPL_H_
#define KALDI_GOP_WRAPPER_IMPL_H_ 1

#include <vector>
#include <string>
#include "gop/gmm-gop.h"

class GopImpl {
public:
  GopImpl() {}
  void Init(std::string &model_pathname);
  void Compute(std::string &wav_filename, std::string text_string);
  std::vector<float>& Result();

private:
  kaldi::GmmGop gmmgop_;
  fst::SymbolTable *word_syms_;
  std::vector<float> result_;
};

#endif  // KALDI_GOP_WRAPPER_IMPL_H_
