#include <string.h>
#include <hls_stream.h>
#include "myIP_dma.h"

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

static void read_64(uint64_t *buff, uint64_t* src)
{
	for (int i = 0; i < BLOCK_SIZE / 8; i++) {
#pragma HLS PIPELINE
		*buff++ = *src++;
	}
}

static void write_64(uint64_t *dst, uint64_t* buff)
{
	for (int i = 0; i < BLOCK_SIZE / 8; i++) {
#pragma HLS PIPELINE
		*dst++ = *buff++;
	}
}



void myIP_dma_simple_pipe_64(uint64_t* dst, uint64_t* src, int blockNum)
{
	for (int i = 0; i < BLOCK_SIZE * blockNum / 8; i++) {
#pragma HLS PIPELINE
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

void myIP_dma_pipe_cast_64(uint64_t* dst, uint64_t* src, int blockNum)
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

void myIP_dma_df_cast_64(uint64_t* dst, uint64_t* src, int blockNum)
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


void myIP_dma_pipe_copyfunc_64(uint64_t* dst, uint64_t* src, int blockNum)
{
	for (int i = 0; i < blockNum; i++) {
#pragma HLS PIPELINE
		uint64_t buffSrc[BLOCK_SIZE / 8];
		uint64_t buffDst[BLOCK_SIZE / 8];

		read_64(buffSrc, src + i * BLOCK_SIZE / 8);
		process_64(buffDst, buffSrc);
		write_64((dst + i * BLOCK_SIZE / 8), buffDst);
	}
}


void myIP_dma_df_copyfunc_64(uint64_t* dst, uint64_t* src, int blockNum)
{
	for (int i = 0; i < blockNum; i++) {
#pragma HLS DATAFLOW
		uint64_t buffSrc[BLOCK_SIZE / 8];
		uint64_t buffDst[BLOCK_SIZE / 8];

		read_64(buffSrc, src + i * BLOCK_SIZE / 8);
		process_64(buffDst, buffSrc);
		write_64((dst + i * BLOCK_SIZE / 8), buffDst);
	}
}

