// gopbin/gop-wrapper-test.cc

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
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURSE.  See the
// GNU General Public License for more details.

#include <iostream>
#include <string>
#include "gop/gop-wrapper.h"
using namespace std;

int main(int argc, char *argv[]) {
  const char *usage =
      "Compute GOP with GMM-based models.\n"
      "Usage:   gop-wrapper-test [options] <model-pathname> <wav-filename> <text-string>\n"
      "e.g.: \n"
      " gop-wrapper-test ./model 1.wav \"good morning\" 1.txt\n";

  if (argc < 3) {
    cout << usage << endl;
    return 0;
  }

  string model_pathname(argv[1]);
  string wav_filename(argv[2]);
  string text_string(argv[3]);

  Gop gop;
  gop.Init(model_pathname);

  gop.Compute(wav_filename, text_string);
  auto result = gop.Result();

  return 0;
}
