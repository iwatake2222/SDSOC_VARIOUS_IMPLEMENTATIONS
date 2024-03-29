#include <string.h>
#include "myIP_buff_df.h"

void myIP_buff2_df_cast_64(uint64_t* dst, uint64_t* src, int blockNum)
{
	for (int i = 0; i < blockNum; i++) {
#pragma HLS DATAFLOW
		uint64_t buffSrc[BLOCK_SIZE / 8];
		uint64_t buffDst[BLOCK_SIZE / 8];
		uint8_t* buffSrc8 = (uint8_t*)buffSrc;
		memcpy(buffSrc, src + i * BLOCK_SIZE / 8, BLOCK_SIZE);
		for (int j = 0; j < BLOCK_SIZE / 8; j++) {
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
		memcpy((dst + i * BLOCK_SIZE / 8), buffDst, BLOCK_SIZE);
	}
}

void myIP_buff2_df_cast_pipe_64(uint64_t* dst, uint64_t* src, int blockNum)
{
	for (int i = 0; i < blockNum; i++) {
#pragma HLS DATAFLOW
		uint64_t buffSrc[BLOCK_SIZE / 8];
		uint64_t buffDst[BLOCK_SIZE / 8];
		uint8_t* buffSrc8 = (uint8_t*)buffSrc;
		memcpy(buffSrc, src + i * BLOCK_SIZE / 8, BLOCK_SIZE);
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
		memcpy((dst + i * BLOCK_SIZE / 8), buffDst, BLOCK_SIZE);
	}
}

void myIP_buff2_df_cast_pipe_64_a(uint64_t* dst, uint64_t* src, int blockNum)
{
	uint64_t buffSrc[BLOCK_SIZE / 8];
	uint64_t buffDst[BLOCK_SIZE / 8];
	for (int i = 0; i < blockNum; i++) {
#pragma HLS DATAFLOW
		uint8_t* buffSrc8 = (uint8_t*)buffSrc;
		memcpy(buffSrc, src + i * BLOCK_SIZE / 8, BLOCK_SIZE);
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
		memcpy((dst + i * BLOCK_SIZE / 8), buffDst, BLOCK_SIZE);
	}
}


static uint8_t getData(uint64_t *buff, int index)
{
#pragma HLS INLINE
	return (buff[index / 8] >> (8 * (index % 8))) & 0xFF;
}

void myIP_buff2_df_mask_pipe_64(uint64_t* dst, uint64_t* src, int blockNum)
{
	for (int i = 0; i < blockNum; i++) {
#pragma HLS DATAFLOW
		uint64_t buffSrc[BLOCK_SIZE / 8];
		uint64_t buffDst[BLOCK_SIZE / 8];
		memcpy(buffSrc, src + i * BLOCK_SIZE / 8, BLOCK_SIZE);
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
		memcpy((dst + i * BLOCK_SIZE / 8), buffDst, BLOCK_SIZE);
	}
}


/*** �֐��� ***/
static void process_64(uint64_t *buffDst, uint64_t *buffSrc)
{
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

static void process_inline_64(uint64_t *buffDst, uint64_t *buffSrc)
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


static void read_64(uint64_t *buff, uint64_t* src)
{
	for (int i = 0; i < BLOCK_SIZE / 8; i++) {
#pragma HLS PIPELINE
		*buff++ = *src++;
	}
}

static void writ_64(uint64_t *dst, uint64_t* buff)
{
	for (int i = 0; i < BLOCK_SIZE / 8; i++) {
#pragma HLS PIPELINE
		*dst++ = *buff++;
	}
}

void myIP_buff2_df_cast_noinline_64(uint64_t* dst, uint64_t* src, int blockNum)
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

void myIP_buff2_df_cast_inline_64(uint64_t* dst, uint64_t* src, int blockNum)
{
	for (int i = 0; i < blockNum; i++) {
#pragma HLS DATAFLOW
		uint64_t buffSrc[BLOCK_SIZE / 8];
		uint64_t buffDst[BLOCK_SIZE / 8];
		memcpy(buffSrc, src + i * BLOCK_SIZE / 8, BLOCK_SIZE);
		process_inline_64(buffDst, buffSrc);
		memcpy((dst + i * BLOCK_SIZE / 8), buffDst, BLOCK_SIZE);
	}
}

void myIP_buff2_df_cast_copyfunc_64(uint64_t* dst, uint64_t* src, int blockNum)
{
	for (int i = 0; i < blockNum; i++) {
#pragma HLS DATAFLOW
		uint64_t buffSrc[BLOCK_SIZE / 8];
		uint64_t buffDst[BLOCK_SIZE / 8];
		read_64(buffSrc, src + i * BLOCK_SIZE / 8);
		process_64(buffDst, buffSrc);
		writ_64(dst + i * BLOCK_SIZE / 8, buffDst);
	}
}

