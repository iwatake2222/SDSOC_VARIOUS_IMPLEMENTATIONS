#ifndef CONV_RGB2Y_H_
#define CONV_RGB2Y_H_

#include <stdint.h>
#include "common.h"

#pragma SDS data zero_copy(dst[0:dstStride*height], src[0:srcStride*height])
void convRGB2Y_hw0(uint8_t* dst, uint8_t* src, int width, int height, int dstStride, int srcStride);

#pragma SDS data zero_copy(dst[0:dstStride*height/8], src[0:srcStride*height/8])
void convRGB2Y_hw1(uint64_t* dst, uint64_t* src, int width, int height, int dstStride, int srcStride);

#endif	// CONV_RGB2Y_H_
