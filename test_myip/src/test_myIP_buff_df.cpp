#include <iostream>
#include <string.h>
#include <stdint.h>
#include <cstdio>
#include <stdlib.h>
#include <stdio.h>
#include "sds_utils.h"
#include "sds_lib.h"
#include "myIP_buff_df.h"

extern void verifyResult(uint8_t *dst, uint8_t *src, int blockNum);

void test_myIP_buff_df(int blockNum)
{
	sds_utils::perf_counter counter;

	uint64_t *src64 = (uint64_t*)sds_alloc_non_cacheable(BLOCK_SIZE * blockNum);
	uint64_t *dst64 = (uint64_t*)sds_alloc_non_cacheable(BLOCK_SIZE * blockNum);
	for(int i = 0; i < BLOCK_SIZE * blockNum; i++) {
		((uint8_t*)src64)[i] = i % 256;
	}

	memset(dst64, 0, BLOCK_SIZE * blockNum);
	counter.reset();
	for (int i = 0; i < TEST_NUM; i++) {
		counter.start();
		myIP_buff2_df_cast_64(dst64, src64, blockNum);
		counter.stop();
	}
	std::cout << "myIP_buff2_df_cast_64" << ": " << counter.avg_time() * 1000  << " msec" << std::endl;
	verifyResult((uint8_t*)dst64, (uint8_t*)src64, blockNum);

	memset(dst64, 0, BLOCK_SIZE * blockNum);
	counter.reset();
	for (int i = 0; i < TEST_NUM; i++) {
		counter.start();
		myIP_buff2_df_cast_pipe_64(dst64, src64, blockNum);
		counter.stop();
	}
	std::cout << "myIP_buff2_df_cast_pipe_64" << ": " << counter.avg_time() * 1000  << " msec" << std::endl;
	verifyResult((uint8_t*)dst64, (uint8_t*)src64, blockNum);

	memset(dst64, 0, BLOCK_SIZE * blockNum);
	counter.reset();
	for (int i = 0; i < TEST_NUM; i++) {
		counter.start();
		myIP_buff2_df_cast_pipe_64_a(dst64, src64, blockNum);
		counter.stop();
	}
	std::cout << "myIP_buff2_df_cast_pipe_64_a" << ": " << counter.avg_time() * 1000  << " msec" << std::endl;
	verifyResult((uint8_t*)dst64, (uint8_t*)src64, blockNum);

	memset(dst64, 0, BLOCK_SIZE * blockNum);
	counter.reset();
	for (int i = 0; i < TEST_NUM; i++) {
		counter.start();
		myIP_buff2_df_mask_pipe_64(dst64, src64, blockNum);
		counter.stop();
	}
	std::cout << "myIP_buff2_df_mask_pipe_64" << ": " << counter.avg_time() * 1000  << " msec" << std::endl;
	verifyResult((uint8_t*)dst64, (uint8_t*)src64, blockNum);

	/*** ŠÖ”‰» ***/
	memset(dst64, 0, BLOCK_SIZE * blockNum);
	counter.reset();
	for (int i = 0; i < TEST_NUM; i++) {
		counter.start();
		myIP_buff2_df_cast_noinline_64(dst64, src64, blockNum);
		counter.stop();
	}
	std::cout << "myIP_buff2_df_cast_noinline_64" << ": " << counter.avg_time() * 1000  << " msec" << std::endl;
	verifyResult((uint8_t*)dst64, (uint8_t*)src64, blockNum);

	memset(dst64, 0, BLOCK_SIZE * blockNum);
	counter.reset();
	for (int i = 0; i < TEST_NUM; i++) {
		counter.start();
		myIP_buff2_df_cast_inline_64(dst64, src64, blockNum);
		counter.stop();
	}
	std::cout << "myIP_buff2_df_cast_inline_64" << ": " << counter.avg_time() * 1000  << " msec" << std::endl;
	verifyResult((uint8_t*)dst64, (uint8_t*)src64, blockNum);

	memset(dst64, 0, BLOCK_SIZE * blockNum);
	counter.reset();
	for (int i = 0; i < TEST_NUM; i++) {
		counter.start();
		myIP_buff2_df_cast_copyfunc_64(dst64, src64, blockNum);
		counter.stop();
	}
	std::cout << "myIP_buff2_df_cast_copyfunc_64" << ": " << counter.avg_time() * 1000  << " msec" << std::endl;
	verifyResult((uint8_t*)dst64, (uint8_t*)src64, blockNum);


	sds_free(src64);
	sds_free(dst64);
}


