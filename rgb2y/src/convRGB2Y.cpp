#include <string.h>
#include "convRGB2Y.h"

void convRGB2Y_hw0(uint8_t* dst, uint8_t* src, int width, int height, int dstStride, int srcStride)
{
	for (int y = 0; y < height; y++) {
#pragma HLS LOOP_TRIPCOUNT min=1280 max=1280
		for (int x = 0; x < width; x++) {
#pragma HLS LOOP_TRIPCOUNT min=1920 max=1920
			uint8_t r = *(src + x * 3 + 0);
			uint8_t g = *(src + x * 3 + 1);
			uint8_t b = *(src + x * 3 + 2);
			*(dst + x) = (uint8_t)(0.299f * r + 0.587f * g + 0.114f * b);
		}
		dst += dstStride;
		src += srcStride;
	}
}

enum {
	RED = 0,
	GREEN = 1,
	BLUE = 2,
};
static uint8_t getPixel(uint64_t* lineBuf, int col, int rgb)
{
#pragma HLS INLINE
	int index = col * 3 + rgb;
	return (lineBuf[index / 8] >> (8 * (index % 8))) & 0xFF;
}

static uint8_t convPixelRGB2YgetPixel(uint8_t r, uint8_t g, uint8_t b)
{
#pragma HLS INLINE
	return (uint8_t)(0.299f * r + 0.587f * g + 0.114f * b);
}

void convRGB2Y_hw1(uint64_t* dst, uint64_t* src, int width, int height, int dstStride, int srcStride)
{
	uint64_t lineBuffSrc[WIDTH_MAX * 3];
	uint64_t lineBuffDst[WIDTH_MAX];
	for (int y = 0; y < height; y++) {
#pragma HLS PIPELINE
#pragma HLS LOOP_TRIPCOUNT min=1280 max=1280
		memcpy(lineBuffSrc, src + y * srcStride / 8, width * 3);
		for (int x = 0; x < width / 8; x++) {
#pragma HLS LOOP_TRIPCOUNT min=1920/8 max=1920/8
			/* 入出力は64-bitなので、8pixel単位で処理してまとめて出力する */
			uint8_t y8pixel[8];
			for (int i = 0; i < 8; i++) {
#pragma HLS LOOP_TRIPCOUNT min=8 max=8
				y8pixel[i] = convPixelRGB2YgetPixel(getPixel(lineBuffSrc, x * 8 + i, RED), getPixel(lineBuffSrc, x * 8 + i, GREEN), getPixel(lineBuffSrc, x * 8 + i, BLUE));
			}
			*(lineBuffDst + x) = ((uint64_t)y8pixel[7] << (8 * 7)) | ((uint64_t)y8pixel[6] << (8 * 6)) | ((uint64_t)y8pixel[5] << (8 * 5)) | ((uint64_t)y8pixel[4] << (8 * 4))
				| ((uint64_t)y8pixel[3] << (8 * 3)) | ((uint64_t)y8pixel[2] << (8 * 2)) | ((uint64_t)y8pixel[1] << (8 * 1)) | ((uint64_t)y8pixel[0] << (8 * 0));
		}
		memcpy(dst + y * dstStride / 8, lineBuffDst, width);
	}
}


