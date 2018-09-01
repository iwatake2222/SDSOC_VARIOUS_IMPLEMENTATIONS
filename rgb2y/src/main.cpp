#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sds_utils.h"
#include "sds_lib.h"
#include "common.h"
#include "convRGB2Y.h"

static void readFile(const char* filename, uint8_t *data, uint32_t size)
{
	FILE *fd = fopen(filename, "rb");
	fread(data, 1, size, fd);
	fclose(fd);
}

static void writeFile(const char* filename, uint8_t *data, uint32_t size)
{
	FILE *fd = fopen(filename, "wb");
	fwrite(data, 1, size, fd);
	fclose(fd);
}

void verifyGrayscaleImage(uint8_t* ref, uint8_t* target, int width, int height, int refStride, int targetStride)
{
#define MAX_DIFF 10
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			uint8_t yRef = *(ref + x);
			uint8_t yTarget = *(target + x);
			if (abs(yRef-yTarget) > MAX_DIFF) {
				printf("  Incorrect conversion at (%d, %d). ref = %d, target = %d\n", x, y, yRef, yTarget);
				return;
			}
		}
		ref += refStride;
		target += targetStride;
	}
	printf("  OK\n");
}

void convRGB2Y_CPU(uint8_t* dst, uint8_t* src, int width, int height, int dstStride, int srcStride)
{
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			uint8_t r = *(src + x * 3 + 0);
			uint8_t g = *(src + x * 3 + 1);
			uint8_t b = *(src + x * 3 + 2);
			*(dst + x) = (uint8_t)(0.299f * r + 0.587f * g + 0.114f * b);
		}
		dst += dstStride;
		src += srcStride;
	}
}

int main()
{
	sds_utils::perf_counter counter;

	/*** CPU implementation ***/
	uint8_t* imgSrc = (uint8_t*)malloc(WIDTH_MAX * HEIGHT_MAX * 3);
	uint8_t* imgDst = (uint8_t*)malloc(WIDTH_MAX * HEIGHT_MAX);
	readFile("org.raw", imgSrc, STRIDE_RGB * HEIGHT);
	counter.reset();
	for (int i = 0; i < TEST_NUM; i++) {
		counter.start();
		convRGB2Y_CPU(imgDst, imgSrc, WIDTH, HEIGHT, STRIDE_Y, STRIDE_RGB);
		counter.stop();
	}
	printf("convRGB2Y_CPU: %.3f [msec]\n", counter.avg_time() * 1000);
	writeFile("gray_cpu.raw", imgDst, STRIDE_Y * HEIGHT);


	/*** HW implementation ***/
	uint8_t* imgSrc8 = (uint8_t*)sds_alloc_non_cacheable(WIDTH_MAX * HEIGHT_MAX * 3);
	uint8_t* imgDst8 = (uint8_t*)sds_alloc_non_cacheable(WIDTH_MAX * HEIGHT_MAX);
	uint64_t* imgSrc64 = (uint64_t*)sds_alloc_non_cacheable(WIDTH_MAX * HEIGHT_MAX * 3);
	uint64_t* imgDst64 = (uint64_t*)sds_alloc_non_cacheable(WIDTH_MAX * HEIGHT_MAX);

	readFile("org.raw", imgSrc8, STRIDE_RGB * HEIGHT);
	counter.reset();
	for (int i = 0; i < TEST_NUM; i++) {
		counter.start();
		convRGB2Y_hw0(imgDst8, imgSrc8, WIDTH, HEIGHT, STRIDE_Y, STRIDE_RGB);
		counter.stop();
	}
	printf("convRGB2Y_hw0: %.3f [msec]\n", counter.avg_time() * 1000);
	writeFile("gray_hw0.raw", imgDst8, STRIDE_Y * HEIGHT);

	readFile("org.raw", (uint8_t*)imgSrc64, STRIDE_RGB * HEIGHT);
	counter.reset();
	for (int i = 0; i < TEST_NUM; i++) {
		counter.start();
		convRGB2Y_hw1(imgDst64, imgSrc64, WIDTH, HEIGHT, STRIDE_Y, STRIDE_RGB);
		counter.stop();
	}
	printf("convRGB2Y_hw1: %.3f [msec]\n", counter.avg_time() * 1000);
	writeFile("gray_hw1.raw", (uint8_t*)imgDst64, STRIDE_Y * HEIGHT);


	sds_free(imgSrc8);
	sds_free(imgDst8);
	sds_free(imgSrc64);
	sds_free(imgDst64);

	free(imgSrc);
	free(imgDst);
}
