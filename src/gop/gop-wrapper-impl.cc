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

#include "gop/gop-wrapper.h"
#include "gop/gop-wrapper-impl.h"


void GopImpl::Init(std::string &model_pathname) {
}

void GopImpl::Compute(std::string &wav_filename, std::string text_string) {
}

std::vector<float>& GopImpl::Result() {
  std::vector<float> result;
  return result;
}
