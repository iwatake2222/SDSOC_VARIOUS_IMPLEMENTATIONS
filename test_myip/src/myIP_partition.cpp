#include <string.h>
#include "myIP_partition.h"

static uint8_t getData(uint64_t *buff, int index)
{
#pragma HLS INLINE
	return (buff[index / 8] >> (8 * (index % 8))) & 0xFF;
}

#if 1
static void process_64(uint64_t *buffDst, uint64_t *buffSrc)
{
#pragma HLS INLINE
	for (int j = 0; j < BLOCK_SIZE / 8; j++) {
#pragma HLS PIPELINE
		uint8_t d0 = getData(buffSrc, j * 8 + 0) * 2;
		uint8_t d1 = getData(buffSrc, j * 8 + 1) * 2;
		uint8_t d2 = getData(buffSrc, j * 8 + 2) * 2;
		uint8_t d3 = getData(buffSrc, j * 8 + 3) * 2;
		uint8_t d4 = getData(buffSrc, j * 8 + 4) * 2;
		uint8_t d5 = getData(buffSrc, j * 8 + 5) * 2;
		uint8_t d6 = getData(buffSrc, j * 8 + 6) * 2;
		uint8_t d7 = getData(buffSrc, j * 8 + 7) * 2;
		buffDst[j] = ((uint64_t)d7 << (8 * 7)) | ((uint64_t)d6 << (8 * 6)) | ((uint64_t)d5 << (8 * 5)) | ((uint64_t)d4 << (8 * 4))
				| ((uint64_t)d3 << (8 * 3)) | ((uint64_t)d2 << (8 * 2)) | ((uint64_t)d1 << (8 * 1)) | ((uint64_t)d0 << (8 * 0));
	}
}
#else
//ERROR: [XFORM 203-103] unsupported array access (reinterpret, etc.)
static void process_64(uint64_t *buffDst, uint64_t *buffSrc)
{
#pragma HLS INLINE
	uint8_t* buffSrc8 = (uint8_t*)buffSrc;
	for (int j = 0; j < BLOCK_SIZE / 8; j++) {
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
#endif

void myIP_partition_0_pipe_mask_64(uint64_t* dst, uint64_t* src, int blockNum)
{
	for (int i = 0; i < blockNum; i++) {
#pragma HLS PIPELINE
		uint64_t buffSrc[BLOCK_SIZE / 8];
		uint64_t buffDst[BLOCK_SIZE / 8];

		memcpy(buffSrc, src + i * BLOCK_SIZE / 8, BLOCK_SIZE);
		process_64(buffDst, buffSrc);
		memcpy((dst + i * BLOCK_SIZE / 8), buffDst, BLOCK_SIZE);
	}
}


void myIP_partition_2_pipe_mask_64(uint64_t* dst, uint64_t* src, int blockNum)
{
	for (int i = 0; i < blockNum; i++) {
#pragma HLS PIPELINE
		uint64_t buffSrc[BLOCK_SIZE / 8];
		uint64_t buffDst[BLOCK_SIZE / 8];
		#pragma HLS ARRAY_PARTITION variable=buffSrc block factor=2
		#pragma HLS ARRAY_PARTITION variable=buffDst block factor=2

		memcpy(buffSrc, src + i * BLOCK_SIZE / 8, BLOCK_SIZE);
		process_64(buffDst, buffSrc);
		memcpy((dst + i * BLOCK_SIZE / 8), buffDst, BLOCK_SIZE);
	}
}

void myIP_partition_4_pipe_mask_64(uint64_t* dst, uint64_t* src, int blockNum)
{
	for (int i = 0; i < blockNum; i++) {
#pragma HLS PIPELINE
		uint64_t buffSrc[BLOCK_SIZE / 8];
		uint64_t buffDst[BLOCK_SIZE / 8];
		#pragma HLS ARRAY_PARTITION variable=buffSrc block factor=4
		#pragma HLS ARRAY_PARTITION variable=buffDst block factor=4

		memcpy(buffSrc, src + i * BLOCK_SIZE / 8, BLOCK_SIZE);
		process_64(buffDst, buffSrc);
		memcpy((dst + i * BLOCK_SIZE / 8), buffDst, BLOCK_SIZE);
	}
}

void myIP_partition_0_df_mask_64(uint64_t* dst, uint64_t* src, int blockNum)
{
	for (int i = 0; i < blockNum; i++) {
#pragma HLS DATAFLOW
		uint64_t buffSrc[BLOCK_SIZE / 8];
		uint64_t buffDst[BLOCK_SIZE / 8];

		memcpy(buffSrc, src + i * BLOCK_SIZE / 8, BLOCK_SIZE);
		process_64(buffDst, buffSrc);
		memcpy((dst + i * BLOCK_SIZE / 8), buffDst, BLOCK_SIZE);
	}
}
void myIP_partition_2_df_mask_64(uint64_t* dst, uint64_t* src, int blockNum)
{
	for (int i = 0; i < blockNum; i++) {
#pragma HLS DATAFLOW
		uint64_t buffSrc[BLOCK_SIZE / 8];
		uint64_t buffDst[BLOCK_SIZE / 8];
		#pragma HLS ARRAY_PARTITION variable=buffSrc block factor=2
		#pragma HLS ARRAY_PARTITION variable=buffDst block factor=2

		memcpy(buffSrc, src + i * BLOCK_SIZE / 8, BLOCK_SIZE);
		process_64(buffDst, buffSrc);
		memcpy((dst + i * BLOCK_SIZE / 8), buffDst, BLOCK_SIZE);
	}
}

void myIP_partition_4_df_mask_64(uint64_t* dst, uint64_t* src, int blockNum)
{
	for (int i = 0; i < blockNum; i++) {
#pragma HLS DATAFLOW
		uint64_t buffSrc[BLOCK_SIZE / 8];
		uint64_t buffDst[BLOCK_SIZE / 8];
		#pragma HLS ARRAY_PARTITION variable=buffSrc block factor=4
		#pragma HLS ARRAY_PARTITION variable=buffDst block factor=4

		memcpy(buffSrc, src + i * BLOCK_SIZE / 8, BLOCK_SIZE);
		process_64(buffDst, buffSrc);
		memcpy((dst + i * BLOCK_SIZE / 8), buffDst, BLOCK_SIZE);
	}
}
