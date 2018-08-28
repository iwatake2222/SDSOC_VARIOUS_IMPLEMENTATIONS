#include <iostream>
#include <string.h>
#include <stdint.h>
#include <cstdio>
#include <stdlib.h>
#include <stdio.h>
#include "sds_utils.h"
#include "sds_lib.h"
#include "common.h"

extern void verifyResult(uint8_t *dst, uint8_t *src, int blockNum);

void myIP_cpu_8(uint8_t* dst, uint8_t* src, int blockNum)
{
	for (int i = 0; i < BLOCK_SIZE * blockNum; i++) {
		uint8_t temp = *(src + i);
		temp *= 2;
		*(dst + i) = temp;
	}
}

void myIP_cpu_32(uint32_t* dst, uint32_t* src, int blockNum)
{
	for (int i = 0; i < BLOCK_SIZE * blockNum / 4; i++) {
		uint32_t temp = *(src + i);
		uint8_t *pTemp8 = (uint8_t *)&temp;
		*(pTemp8 + 0) *= 2;
		*(pTemp8 + 1) *= 2;
		*(pTemp8 + 2) *= 2;
		*(pTemp8 + 3) *= 2;
		*(dst + i) = temp;
	}
}

void myIP_cpu_64(uint64_t* dst, uint64_t* src, int blockNum)
{
	for (int i = 0; i < BLOCK_SIZE * blockNum / 8; i++) {
		uint64_t temp = *(src + i);
		uint8_t *pTemp8 = (uint8_t *)&temp;
		*(pTemp8 + 0) *= 2;
		*(pTemp8 + 1) *= 2;
		*(pTemp8 + 2) *= 2;
		*(pTemp8 + 3) *= 2;
		*(pTemp8 + 4) *= 2;
		*(pTemp8 + 5) *= 2;
		*(pTemp8 + 6) *= 2;
		*(pTemp8 + 7) *= 2;
		*(dst + i) = temp;
	}
}

void test_myIP_cpu(int blockNum)
{
	sds_utils::perf_counter counter;

	uint8_t *src8 = (uint8_t*)malloc(BLOCK_SIZE * blockNum);
	uint8_t *dst8 = (uint8_t*)malloc(BLOCK_SIZE * blockNum);
	uint32_t *src32 = (uint32_t*)malloc(BLOCK_SIZE * blockNum);
	uint32_t *dst32 = (uint32_t*)malloc(BLOCK_SIZE * blockNum);
	uint64_t *src64 = (uint64_t*)malloc(BLOCK_SIZE * blockNum);
	uint64_t *dst64 = (uint64_t*)malloc(BLOCK_SIZE * blockNum);
	for(int i = 0; i < BLOCK_SIZE * blockNum; i++) {
		src8[i] = i % 255;
		((uint8_t*)src32)[i] = i % 256;
		((uint8_t*)src64)[i] = i % 256;
	}

	memset(dst8, 0, BLOCK_SIZE * blockNum);
	counter.reset();
	for (int i = 0; i < TEST_NUM; i++) {
		counter.start();
		myIP_cpu_8(dst8, src8, blockNum);
		counter.stop();
	}
	std::cout << "myIP_cpu_8" << ": " << counter.avg_time() * 1000  << " msec" << std::endl;
	verifyResult((uint8_t*)dst8, (uint8_t*)src8, blockNum);

	memset(dst32, 0, BLOCK_SIZE * blockNum);
	counter.reset();
	for (int i = 0; i < TEST_NUM; i++) {
		counter.start();
		myIP_cpu_32(dst32, src32, blockNum);
		counter.stop();
	}
	std::cout << "myIP_cpu_32" << ": " << counter.avg_time() * 1000  << " msec" << std::endl;
	verifyResult((uint8_t*)dst32, (uint8_t*)src32, blockNum);
	memset(dst64, 0, BLOCK_SIZE * blockNum);
	counter.reset();
	for (int i = 0; i < TEST_NUM; i++) {
		counter.start();
		myIP_cpu_64(dst64, src64, blockNum);
		counter.stop();
	}
	std::cout << "myIP_cpu_64" << ": " << counter.avg_time() * 1000  << " msec" << std::endl;
	verifyResult((uint8_t*)dst64, (uint8_t*)src64, blockNum);

	free(src8);
	free(dst8);
	free(src32);
	free(dst32);
	free(src64);
	free(dst64);
}


