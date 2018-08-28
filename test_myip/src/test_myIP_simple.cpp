#include <iostream>
#include <string.h>
#include <stdint.h>
#include <cstdio>
#include <stdlib.h>
#include <stdio.h>
#include "sds_utils.h"
#include "sds_lib.h"
#include "myIP_simple.h"


extern void verifyResult(uint8_t *dst, uint8_t *src, int blockNum);

void test_myIP_simple(int blockNum)
{
	sds_utils::perf_counter counter;

	uint8_t *src8 = (uint8_t*)sds_alloc_non_cacheable(BLOCK_SIZE * blockNum);
	uint8_t *dst8 = (uint8_t*)sds_alloc_non_cacheable(BLOCK_SIZE * blockNum);
	uint32_t *src32 = (uint32_t*)sds_alloc_non_cacheable(BLOCK_SIZE * blockNum);
	uint32_t *dst32 = (uint32_t*)sds_alloc_non_cacheable(BLOCK_SIZE * blockNum);
	uint64_t *src64 = (uint64_t*)sds_alloc_non_cacheable(BLOCK_SIZE * blockNum);
	uint64_t *dst64 = (uint64_t*)sds_alloc_non_cacheable(BLOCK_SIZE * blockNum);
	for(int i = 0; i < BLOCK_SIZE * blockNum; i++) {
		src8[i] = i % 255;
		((uint8_t*)src32)[i] = i % 256;
		((uint8_t*)src64)[i] = i % 256;
	}

	/*** myIP_simple ***/
	memset(dst8, 0, BLOCK_SIZE * blockNum);
	counter.reset();
	for (int i = 0; i < TEST_NUM; i++) {
		counter.start();
		myIP_simple_8(dst8, src8, blockNum);
		counter.stop();
	}
	std::cout << "myIP_simple_8" << ": " << counter.avg_time() * 1000  << " msec" << std::endl;
	verifyResult((uint8_t*)dst8, (uint8_t*)src8, blockNum);

	memset(dst32, 0, BLOCK_SIZE * blockNum);
	counter.reset();
	for (int i = 0; i < TEST_NUM; i++) {
		counter.start();
		myIP_simple_32(dst32, src32, blockNum);
		counter.stop();
	}
	std::cout << "myIP_simple_32" << ": " << counter.avg_time() * 1000  << " msec" << std::endl;
	verifyResult((uint8_t*)dst32, (uint8_t*)src32, blockNum);

	memset(dst64, 0, BLOCK_SIZE * blockNum);
	counter.reset();
	for (int i = 0; i < TEST_NUM; i++) {
		counter.start();
		myIP_simple_64(dst64, src64, blockNum);
		counter.stop();
	}
	std::cout << "myIP_simple_64" << ": " << counter.avg_time() * 1000  << " msec" << std::endl;
	verifyResult((uint8_t*)dst64, (uint8_t*)src64, blockNum);

	memset(dst8, 0, BLOCK_SIZE * blockNum);
	counter.reset();
	for (int i = 0; i < TEST_NUM; i++) {
		counter.start();
		myIP_simple_pipe_8(dst8, src8, blockNum);
		counter.stop();
	}
	std::cout << "myIP_simple_pipe_8" << ": " << counter.avg_time() * 1000  << " msec" << std::endl;
	verifyResult((uint8_t*)dst8, (uint8_t*)src8, blockNum);

	memset(dst32, 0, BLOCK_SIZE * blockNum);
	counter.reset();
	for (int i = 0; i < TEST_NUM; i++) {
		counter.start();
		myIP_simple_pipe_32(dst32, src32, blockNum);
		counter.stop();
	}
	std::cout << "myIP_simple_pipe_32" << ": " << counter.avg_time() * 1000  << " msec" << std::endl;
	verifyResult((uint8_t*)dst32, (uint8_t*)src32, blockNum);

	memset(dst64, 0, BLOCK_SIZE * blockNum);
	counter.reset();
	for (int i = 0; i < TEST_NUM; i++) {
		counter.start();
		myIP_simple_pipe_64(dst64, src64, blockNum);
		counter.stop();
	}
	std::cout << "myIP_simple_pipe_64" << ": " << counter.avg_time() * 1000  << " msec" << std::endl;
	verifyResult((uint8_t*)dst64, (uint8_t*)src64, blockNum);

	memset(dst64, 0, BLOCK_SIZE * blockNum);
	counter.reset();
	for (int i = 0; i < TEST_NUM; i++) {
		counter.start();
		myIP_simple_pipe_64_a(dst64, src64, blockNum);
		counter.stop();
	}
	std::cout << "myIP_simple_pipe_64_a" << ": " << counter.avg_time() * 1000  << " msec" << std::endl;
	verifyResult((uint8_t*)dst64, (uint8_t*)src64, blockNum);

	memset(dst64, 0, BLOCK_SIZE * blockNum);
	counter.reset();
	for (int i = 0; i < TEST_NUM; i++) {
		counter.start();
		myIP_simple_pipe_64_b(dst64, src64, blockNum);
		counter.stop();
	}
	std::cout << "myIP_simple_pipe_64_b" << ": " << counter.avg_time() * 1000  << " msec" << std::endl;
	verifyResult((uint8_t*)dst64, (uint8_t*)src64, blockNum);

	memset(dst64, 0, BLOCK_SIZE * blockNum);
	counter.reset();
	for (int i = 0; i < TEST_NUM; i++) {
		counter.start();
		myIP_simple_pipe_64_c(dst64, src64, blockNum);
		counter.stop();
	}
	std::cout << "myIP_simple_pipe_64_c" << ": " << counter.avg_time() * 1000  << " msec" << std::endl;
	verifyResult((uint8_t*)dst64, (uint8_t*)src64, blockNum);

	memset(dst64, 0, BLOCK_SIZE * blockNum);
	counter.reset();
	for (int i = 0; i < TEST_NUM; i++) {
		counter.start();
		myIP_simple_pipe_64_tripcount(dst64, src64, blockNum);
		counter.stop();
	}
	std::cout << "myIP_simple_pipe_64_tripcount" << ": " << counter.avg_time() * 1000  << " msec" << std::endl;
	verifyResult((uint8_t*)dst64, (uint8_t*)src64, blockNum);




	sds_free(src8);
	sds_free(dst8);
	sds_free(src32);
	sds_free(dst32);
	sds_free(src64);
	sds_free(dst64);
}


