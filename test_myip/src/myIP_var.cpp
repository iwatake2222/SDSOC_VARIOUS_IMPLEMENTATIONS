#include <string.h>
#include "myIP_var.h"


static void process_inline_64(uint64_t *buffDst, uint64_t *buffSrc, int blockSize)
{
#pragma HLS INLINE
	uint8_t* buffSrc8 = (uint8_t*)buffSrc;
	for (int j = 0; j < blockSize / 8; j++) {
#pragma HLS PIPELINE
		uint8_t d0 = buffSrc8[j * 8 + 0] * 2;
		uint8_t d1 = buffSrc8[j * 8 + 1] * 2;
		uint8_t d2 = buffSrc8[j * 8 + 2] * 2;
		uint8_t d3 = buffSrc8[j * 8 + 3] * 2;
		uint8_t d4 = buffSrc8[j * 8 + 4] * 2;
		uint8_t d5 = buffSrc8[j * 8 + 5] * 2;
		uint8_t d6 = buffSrc8[j * 8 + 6] * 2;
		uint8_t d7 = buffSrc8[j * 8 + 7] * 2;
		buffDst[j] = ((uint64_t)d7 << (8 * 7)) | ((uint64_t)d6 << (8 * 6)) | ((uint64_t)d5 << (8 * 5)) | ((uint64_t)d4 << (8 * 4))
				| ((uint64_t)d3 << (8 * 3)) | ((uint64_t)d2 << (8 * 2)) | ((uint64_t)d1 << (8 * 1)) | ((uint64_t)d0 << (8 * 0));
	}
}

void myIP_buff2_pipe_cast_inline_var_64(uint64_t* dst, uint64_t* src, int blockNum, int blockSize)
{
	for (int i = 0; i < blockNum; i++) {
#pragma HLS PIPELINE
		uint64_t buffSrc[BLOCK_SIZE / 8];
		uint64_t buffDst[BLOCK_SIZE / 8];
		memcpy(buffSrc, src + i * blockSize / 8, blockSize);
		process_inline_64(buffDst, buffSrc, blockSize);
		memcpy((dst + i * blockSize / 8), buffDst, blockSize);
	}
}

void myIP_buff2_df_cast_inline_var_64(uint64_t* dst, uint64_t* src, int blockNum, int blockSize)
{
	for (int i = 0; i < blockNum; i++) {
#pragma HLS DATAFLOW
		uint64_t buffSrc[BLOCK_SIZE / 8];
		uint64_t buffDst[BLOCK_SIZE / 8];
		memcpy(buffSrc, src + i * blockSize / 8, blockSize);
		process_inline_64(buffDst, buffSrc, blockSize);
		memcpy((dst + i * blockSize / 8), buffDst, blockSize);
	}
}

















