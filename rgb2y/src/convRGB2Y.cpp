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
	uint64_t lineBuffSrc[WIDTH_MAX / 8 * 3];
	uint64_t lineBuffDst[WIDTH_MAX / 8];
	for (int y = 0; y < height; y++) {
#pragma HLS PIPELINE
#pragma HLS LOOP_TRIPCOUNT min=1280 max=1280
		memcpy(lineBuffSrc, src + y * srcStride / 8, width * 3);
		for (int x = 0; x < width / 8; x++) {
#pragma HLS LOOP_TRIPCOUNT min=1920/8 max=1920/8
			/* 入出力は64-bitなので、8pixel単位で処理してまとめて出力する */
			uint8_t y0 = convPixelRGB2YgetPixel(getPixel(lineBuffSrc, x * 8 + 0, RED), getPixel(lineBuffSrc, x * 8 + 0, GREEN), getPixel(lineBuffSrc, x * 8 + 0, BLUE));
			uint8_t y1 = convPixelRGB2YgetPixel(getPixel(lineBuffSrc, x * 8 + 1, RED), getPixel(lineBuffSrc, x * 8 + 1, GREEN), getPixel(lineBuffSrc, x * 8 + 1, BLUE));
			uint8_t y2 = convPixelRGB2YgetPixel(getPixel(lineBuffSrc, x * 8 + 2, RED), getPixel(lineBuffSrc, x * 8 + 2, GREEN), getPixel(lineBuffSrc, x * 8 + 2, BLUE));
			uint8_t y3 = convPixelRGB2YgetPixel(getPixel(lineBuffSrc, x * 8 + 3, RED), getPixel(lineBuffSrc, x * 8 + 3, GREEN), getPixel(lineBuffSrc, x * 8 + 3, BLUE));
			uint8_t y4 = convPixelRGB2YgetPixel(getPixel(lineBuffSrc, x * 8 + 4, RED), getPixel(lineBuffSrc, x * 8 + 4, GREEN), getPixel(lineBuffSrc, x * 8 + 4, BLUE));
			uint8_t y5 = convPixelRGB2YgetPixel(getPixel(lineBuffSrc, x * 8 + 5, RED), getPixel(lineBuffSrc, x * 8 + 5, GREEN), getPixel(lineBuffSrc, x * 8 + 5, BLUE));
			uint8_t y6 = convPixelRGB2YgetPixel(getPixel(lineBuffSrc, x * 8 + 6, RED), getPixel(lineBuffSrc, x * 8 + 6, GREEN), getPixel(lineBuffSrc, x * 8 + 6, BLUE));
			uint8_t y7 = convPixelRGB2YgetPixel(getPixel(lineBuffSrc, x * 8 + 7, RED), getPixel(lineBuffSrc, x * 8 + 7, GREEN), getPixel(lineBuffSrc, x * 8 + 7, BLUE));
			*(lineBuffDst + x) = ((uint64_t)y7 << (8 * 7)) | ((uint64_t)y6 << (8 * 6)) | ((uint64_t)y5 << (8 * 5)) | ((uint64_t)y4 << (8 * 4))
				| ((uint64_t)y3 << (8 * 3)) | ((uint64_t)y2 << (8 * 2)) | ((uint64_t)y1 << (8 * 1)) | ((uint64_t)y0 << (8 * 0));
		}
		memcpy(dst + y * dstStride / 8, lineBuffDst, width);
	}
}

void convRGB2Y_hw2(uint64_t* dst, uint64_t* src, int width, int height, int dstStride, int srcStride)
{
	uint64_t lineBuffSrc[WIDTH_MAX / 8 * 3];
	uint64_t lineBuffDst[WIDTH_MAX / 8];
//#pragma HLS ARRAY_PARTITION variable=lineBuffSrc cyclic factor=3
//#pragma HLS ARRAY_PARTITION variable=lineBuffSrc block factor=8

	for (int y = 0; y < height; y++) {
#pragma HLS DATAFLOW
#pragma HLS LOOP_TRIPCOUNT min=1280 max=1280
		memcpy(lineBuffSrc, src + y * srcStride / 8, WIDTH * 3);
		for (int x = 0; x < WIDTH / 8; x++) {
#pragma HLS PIPELINE
#pragma HLS LOOP_TRIPCOUNT min=1920/8 max=1920/8
			/* 入出力は64-bitなので、8pixel単位で処理してまとめて出力する */
			uint8_t y0 = convPixelRGB2YgetPixel(getPixel(lineBuffSrc, x * 8 + 0, RED), getPixel(lineBuffSrc, x * 8 + 0, GREEN), getPixel(lineBuffSrc, x * 8 + 0, BLUE));
			uint8_t y1 = convPixelRGB2YgetPixel(getPixel(lineBuffSrc, x * 8 + 1, RED), getPixel(lineBuffSrc, x * 8 + 1, GREEN), getPixel(lineBuffSrc, x * 8 + 1, BLUE));
			uint8_t y2 = convPixelRGB2YgetPixel(getPixel(lineBuffSrc, x * 8 + 2, RED), getPixel(lineBuffSrc, x * 8 + 2, GREEN), getPixel(lineBuffSrc, x * 8 + 2, BLUE));
			uint8_t y3 = convPixelRGB2YgetPixel(getPixel(lineBuffSrc, x * 8 + 3, RED), getPixel(lineBuffSrc, x * 8 + 3, GREEN), getPixel(lineBuffSrc, x * 8 + 3, BLUE));
			uint8_t y4 = convPixelRGB2YgetPixel(getPixel(lineBuffSrc, x * 8 + 4, RED), getPixel(lineBuffSrc, x * 8 + 4, GREEN), getPixel(lineBuffSrc, x * 8 + 4, BLUE));
			uint8_t y5 = convPixelRGB2YgetPixel(getPixel(lineBuffSrc, x * 8 + 5, RED), getPixel(lineBuffSrc, x * 8 + 5, GREEN), getPixel(lineBuffSrc, x * 8 + 5, BLUE));
			uint8_t y6 = convPixelRGB2YgetPixel(getPixel(lineBuffSrc, x * 8 + 6, RED), getPixel(lineBuffSrc, x * 8 + 6, GREEN), getPixel(lineBuffSrc, x * 8 + 6, BLUE));
			uint8_t y7 = convPixelRGB2YgetPixel(getPixel(lineBuffSrc, x * 8 + 7, RED), getPixel(lineBuffSrc, x * 8 + 7, GREEN), getPixel(lineBuffSrc, x * 8 + 7, BLUE));
			*(lineBuffDst + x) = ((uint64_t)y7 << (8 * 7)) | ((uint64_t)y6 << (8 * 6)) | ((uint64_t)y5 << (8 * 5)) | ((uint64_t)y4 << (8 * 4))
				| ((uint64_t)y3 << (8 * 3)) | ((uint64_t)y2 << (8 * 2)) | ((uint64_t)y1 << (8 * 1)) | ((uint64_t)y0 << (8 * 0));
		}
		memcpy(dst + y * dstStride / 8, lineBuffDst, WIDTH);
	}
}


void convRGB2Y_hw3(uint8_t* dst, uint8_t* src, int width, int height, int dstStride, int srcStride)
{
	uint8_t lineBuffSrc[WIDTH_MAX * 3];
	uint8_t lineBuffDst[WIDTH_MAX];
//#pragma HLS ARRAY_PARTITION variable=lineBuffSrc cyclic factor=3
//#pragma HLS ARRAY_PARTITION variable=lineBuffSrc block factor=8

	for (int y = 0; y < height; y++) {
#pragma HLS DATAFLOW
#pragma HLS LOOP_TRIPCOUNT min=1280 max=1280
		memcpy(lineBuffSrc, src + y * srcStride, WIDTH * 3);
		for (int x = 0; x < WIDTH; x++) {
#pragma HLS PIPELINE
#pragma HLS LOOP_TRIPCOUNT min=1920 max=1920
			/* 入出力は64-bitなので、8pixel単位で処理してまとめて出力する */
			uint8_t y = convPixelRGB2YgetPixel(lineBuffSrc[x * 3 + 0], lineBuffSrc[x * 3 + 1], lineBuffSrc[x * 3 + 2]);
			*(lineBuffDst + x) = y;
		}
		memcpy(dst + y * dstStride, lineBuffDst, WIDTH);
	}
}


