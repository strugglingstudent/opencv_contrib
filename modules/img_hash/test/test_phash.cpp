/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//
//                        Intel License Agreement
//                For Open Source Computer Vision Library
//
// Copyright (C) 2000, Intel Corporation, all rights reserved.
// Third party copyrights are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistribution's of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//   * Redistribution's in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//   * The name of Intel Corporation may not be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
// This software is provided by the copyright holders and contributors "as is" and
// any express or implied warranties, including, but not limited to, the implied
// warranties of merchantability and fitness for a particular purpose are disclaimed.
// In no event shall the Intel Corporation or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
//
//M*/

#include "test_precomp.hpp"

using namespace cv;

class CV_PHashTest : public cvtest::BaseTest
{
public:
    CV_PHashTest();
    ~CV_PHashTest();
protected:
    void run(int /* idx */);
};

CV_PHashTest::CV_PHashTest(){}
CV_PHashTest::~CV_PHashTest(){}

void CV_PHashTest::run(int )
{
    cv::Mat input(32, 32, CV_8U);
    cv::Mat hash;

    uchar value = 0;
    uchar *inPtr = input.ptr<uchar>(0);
    for(size_t i = 0; i != 32*32; ++i)
    {
        inPtr[i] = value++;
    }

    cv::ihash::pHash(input, hash);
    uchar const expectResult[] =
    {
        13, 15, 14, 15, 15, 15, 14, 15,
        15, 15, 14, 15, 15, 15, 14, 15
    };
    uchar const *hashPtr = hash.ptr<uchar>(0);
    for(int i = 0; i != 16; ++i)
    {
        if(hashPtr[i] != expectResult[i])
        {
            ts->printf(cvtest::TS::LOG, "Wrong hash value \n");
            ts->set_failed_test_info(cvtest::TS::FAIL_INVALID_TEST_DATA);
            return;
        }
    }
}

TEST(average_phash_test, accuracy) { CV_PHashTest test; test.safe_run(); }