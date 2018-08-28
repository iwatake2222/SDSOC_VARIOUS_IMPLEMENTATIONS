#include <iostream>
#include <string.h>
#include <stdint.h>
#include <cstdio>
#include <stdlib.h>
#include <stdio.h>
#include "sds_utils.h"
#include "sds_lib.h"
#include "common.h"

int main(int argc, char **argv)
{
	std::cout << "Hello world" << std::endl;
	int blockNum = 512;

	extern void test_myIP_cpu(int blockNum);
	test_myIP_cpu(blockNum);

	extern void test_myIP_simple(int blockNum);
	test_myIP_simple(blockNum);

	extern void test_myIP_buff_pipe(int blockNum);
	test_myIP_buff_pipe(blockNum);

	extern void test_myIP_buff_df(int blockNum);
	test_myIP_buff_df(blockNum);

	extern void test_myIP_partition(int blockNum);
	test_myIP_partition(blockNum);

	extern void test_myIP_stream(int blockNum);
	test_myIP_stream(blockNum);

	extern void test_myIP_dma(int blockNum);
	test_myIP_dma(blockNum);

	extern void test_myIP_var(int blockNum);
	test_myIP_var(blockNum);

	std::cout << "Done" << std::endl;
}


void verifyResult(uint8_t *dst, uint8_t *src, int blockNum)
{
	for(int i = 0; i < BLOCK_SIZE * blockNum; i++) {
		if ((uint8_t)(src[i] * 2) != dst[i]) {
			printf("   error at index(%d). src = %d, dst = %d\n", i, src[i], dst[i]);
			break;
		}
	}
}
