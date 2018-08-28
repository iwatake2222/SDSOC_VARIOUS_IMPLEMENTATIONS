#include <iostream>
#include <string.h>
#include <stdint.h>
#include <cstdio>
#include <stdlib.h>
#include <stdio.h>
#include "sds_utils.h"
#include "sds_lib.h"
#include "myIP_buff_pipe.h"

extern void verifyResult(uint8_t *dst, uint8_t *src, int blockNum);

void test_myIP_buff_pipe(int blockNum)
{
	sds_utils::perf_counter counter;

	uint8_t *src8 = (uint8_t*)sds_alloc_non_cacheable(BLOCK_SIZE * blockNum);
	uint8_t *dst8 = (uint8_t*)sds_alloc_non_cacheable(BLOCK_SIZE * blockNum);
	uint64_t *src64 = (uint64_t*)sds_alloc_non_cacheable(BLOCK_SIZE * blockNum);
	uint64_t *dst64 = (uint64_t*)sds_alloc_non_cacheable(BLOCK_SIZE * blockNum);
	for(int i = 0; i < BLOCK_SIZE * blockNum; i++) {
		src8[i] = i % 255;
		((uint8_t*)src64)[i] = i % 256;
	}

	/*** バッファ1つ ***/
	memset(dst8, 0, BLOCK_SIZE * blockNum);
	counter.reset();
	for (int i = 0; i < TEST_NUM; i++) {
		counter.start();
		myIP_buff1_pipe_8(dst8, src8, blockNum);
		counter.stop();
	}
	std::cout << "myIP_buff1_pipe_8" << ": " << counter.avg_time() * 1000  << " msec" << std::endl;
	verifyResult((uint8_t*)dst8, (uint8_t*)src8, blockNum);

	memset(dst64, 0, BLOCK_SIZE * blockNum);
	counter.reset();
	for (int i = 0; i < TEST_NUM; i++) {
		counter.start();
		myIP_buff1_pipe_64(dst64, src64, blockNum);
		counter.stop();
	}
	std::cout << "myIP_buff1_pipe_64" << ": " << counter.avg_time() * 1000  << " msec" << std::endl;
	verifyResult((uint8_t*)dst64, (uint8_t*)src64, blockNum);

	/* バッファ1つ others */
	memset(dst64, 0, BLOCK_SIZE * blockNum);
	counter.reset();
	for (int i = 0; i < TEST_NUM; i++) {
		counter.start();
		myIP_buff1_pipe_64_a(dst64, src64, blockNum);
		counter.stop();
	}
	std::cout << "myIP_buff1_pipe_64_a" << ": " << counter.avg_time() * 1000  << " msec" << std::endl;
	verifyResult((uint8_t*)dst64, (uint8_t*)src64, blockNum);

	memset(dst64, 0, BLOCK_SIZE * blockNum);
	counter.reset();
	for (int i = 0; i < TEST_NUM; i++) {
		counter.start();
		myIP_buff1_pipe_64_b(dst64, src64, blockNum);
		counter.stop();
	}
	std::cout << "myIP_buff1_pipe_64_b" << ": " << counter.avg_time() * 1000  << " msec" << std::endl;
	verifyResult((uint8_t*)dst64, (uint8_t*)src64, blockNum);

	memset(dst64, 0, BLOCK_SIZE * blockNum);
	counter.reset();
	for (int i = 0; i < TEST_NUM; i++) {
		counter.start();
		myIP_buff1_pipe_64_c(dst64, src64, blockNum);
		counter.stop();
	}
	std::cout << "myIP_buff1_pipe_64_c" << ": " << counter.avg_time() * 1000  << " msec" << std::endl;
	verifyResult((uint8_t*)dst64, (uint8_t*)src64, blockNum);

	/*** バッファ2つ ***/
	memset(dst64, 0, BLOCK_SIZE * blockNum);
	counter.reset();
	for (int i = 0; i < TEST_NUM; i++) {
		counter.start();
		myIP_buff2_pipe_64(dst64, src64, blockNum);
		counter.stop();
	}
	std::cout << "myIP_buff2_pipe_64" << ": " << counter.avg_time() * 1000  << " msec" << std::endl;
	verifyResult((uint8_t*)dst64, (uint8_t*)src64, blockNum);

	memset(dst64, 0, BLOCK_SIZE * blockNum);
	counter.reset();
	for (int i = 0; i < TEST_NUM; i++) {
		counter.start();
		myIP_buff2_pipe_mask_64(dst64, src64, blockNum);
		counter.stop();
	}
	std::cout << "myIP_buff2_pipe_mask_64" << ": " << counter.avg_time() * 1000  << " msec" << std::endl;
	verifyResult((uint8_t*)dst64, (uint8_t*)src64, blockNum);

	memset(dst64, 0, BLOCK_SIZE * blockNum);
	counter.reset();
	for (int i = 0; i < TEST_NUM; i++) {
		counter.start();
		myIP_buff2_pipe_cast_64(dst64, src64, blockNum);
		counter.stop();
	}
	std::cout << "myIP_buff2_pipe_cast_64" << ": " << counter.avg_time() * 1000  << " msec" << std::endl;
	verifyResult((uint8_t*)dst64, (uint8_t*)src64, blockNum);

	memset(dst64, 0, BLOCK_SIZE * blockNum);
	counter.reset();
	for (int i = 0; i < TEST_NUM; i++) {
		counter.start();
		myIP_buff2_pipe_cast_64_a(dst64, src64, blockNum);
		counter.stop();
	}
	std::cout << "myIP_buff2_pipe_cast_64_a" << ": " << counter.avg_time() * 1000  << " msec" << std::endl;
	verifyResult((uint8_t*)dst64, (uint8_t*)src64, blockNum);

	/*** 関数化 ***/
	memset(dst64, 0, BLOCK_SIZE * blockNum);
	counter.reset();
	for (int i = 0; i < TEST_NUM; i++) {
		counter.start();
		myIP_buff2_pipe_cast_noinline_64(dst64, src64, blockNum);
		counter.stop();
	}
	std::cout << "myIP_buff2_pipe_cast_noinline_64" << ": " << counter.avg_time() * 1000  << " msec" << std::endl;
	verifyResult((uint8_t*)dst64, (uint8_t*)src64, blockNum);

	memset(dst64, 0, BLOCK_SIZE * blockNum);
	counter.reset();
	for (int i = 0; i < TEST_NUM; i++) {
		counter.start();
		myIP_buff2_pipe_cast_inline_64(dst64, src64, blockNum);
		counter.stop();
	}
	std::cout << "myIP_buff2_pipe_cast_inline_64" << ": " << counter.avg_time() * 1000  << " msec" << std::endl;
	verifyResult((uint8_t*)dst64, (uint8_t*)src64, blockNum);

	memset(dst64, 0, BLOCK_SIZE * blockNum);
	counter.reset();
	for (int i = 0; i < TEST_NUM; i++) {
		counter.start();
		myIP_buff2_pipe_cast_copyfunc_64(dst64, src64, blockNum);
		counter.stop();
	}
	std::cout << "myIP_buff2_pipe_cast_copyfunc_64" << ": " << counter.avg_time() * 1000  << " msec" << std::endl;
	verifyResult((uint8_t*)dst64, (uint8_t*)src64, blockNum);

	sds_free(src8);
	sds_free(dst8);
	sds_free(src64);
	sds_free(dst64);
}


