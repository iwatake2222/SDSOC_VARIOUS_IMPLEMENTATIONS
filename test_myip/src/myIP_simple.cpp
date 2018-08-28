#include "myIP_simple.h"

/*** simple ***/
void myIP_simple_8(uint8_t* dst, uint8_t* src, int blockNum)
{
	for (int i = 0; i < BLOCK_SIZE * blockNum; i++) {
		uint8_t temp = *(src + i);
		temp *= 2;
		*(dst + i) = temp;
	}
}

void myIP_simple_32(uint32_t* dst, uint32_t* src, int blockNum)
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

void myIP_simple_64(uint64_t* dst, uint64_t* src, int blockNum)
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

/*** pipeline ***/
void myIP_simple_pipe_8(uint8_t* dst, uint8_t* src, int blockNum)
{
	for (int i = 0; i < BLOCK_SIZE * blockNum; i++) {
#pragma HLS PIPELINE
		uint8_t temp = *(src + i);
		temp *= 2;
		*(dst + i) = temp;
	}
}

void myIP_simple_pipe_32(uint32_t* dst, uint32_t* src, int blockNum)
{
	for (int i = 0; i < BLOCK_SIZE * blockNum / 4; i++) {
#pragma HLS PIPELINE
		uint32_t temp = *(src + i);
		uint8_t *pTemp8 = (uint8_t *)&temp;
		*(pTemp8 + 0) *= 2;
		*(pTemp8 + 1) *= 2;
		*(pTemp8 + 2) *= 2;
		*(pTemp8 + 3) *= 2;
		*(dst + i) = temp;
	}
}

void myIP_simple_pipe_64(uint64_t* dst, uint64_t* src, int blockNum)
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

/*** pipeline others ***/
void myIP_simple_pipe_64_a(uint64_t* dst, uint64_t* src, int blockNum)
{
	for (int i = 0; i < BLOCK_SIZE * blockNum / 8; i++) {
#pragma HLS PIPELINE
		uint64_t temp = src[i];
		uint8_t *pTemp8 = (uint8_t *)&temp;
		pTemp8[0] *= 2;
		pTemp8[1] *= 2;
		pTemp8[2] *= 2;
		pTemp8[3] *= 2;
		pTemp8[4] *= 2;
		pTemp8[5] *= 2;
		pTemp8[6] *= 2;
		pTemp8[7] *= 2;
		dst[i] = temp;
	}
}

void myIP_simple_pipe_64_b(uint64_t* dst, uint64_t* src, int blockNum)
{
	for (int i = 0; i < BLOCK_SIZE * blockNum / 8; i++) {
#pragma HLS PIPELINE
		uint64_t temp = *src;
		uint8_t *pTemp8 = (uint8_t *)&temp;
		pTemp8[0] *= 2;
		pTemp8[1] *= 2;
		pTemp8[2] *= 2;
		pTemp8[3] *= 2;
		pTemp8[4] *= 2;
		pTemp8[5] *= 2;
		pTemp8[6] *= 2;
		pTemp8[7] *= 2;
		*dst = temp;
		src++;
		dst++;
	}
}

void myIP_simple_pipe_64_c(uint64_t* dst, uint64_t* src, int blockNum)
{
	for (int i = 0; i < BLOCK_SIZE * blockNum / 8; i++) {
#pragma HLS PIPELINE
		uint64_t temp = *src;
		uint8_t *pTemp8 = (uint8_t *)&temp;
		*pTemp8 *= 2;	pTemp8++;
		*pTemp8 *= 2;	pTemp8++;
		*pTemp8 *= 2;	pTemp8++;
		*pTemp8 *= 2;	pTemp8++;
		*pTemp8 *= 2;	pTemp8++;
		*pTemp8 *= 2;	pTemp8++;
		*pTemp8 *= 2;	pTemp8++;
		*pTemp8 *= 2;
		*dst = temp;
		src++;
		dst++;
	}
}


void myIP_simple_pipe_64_tripcount(uint64_t* dst, uint64_t* src, int blockNum)
{
	for (int i = 0; i < BLOCK_SIZE * blockNum / 8; i++) {
#pragma HLS PIPELINE
#pragma HLS LOOP_TRIPCOUNT min=1024*512/8 max=1024*512/8
//#pragma HLS LOOP_TRIPCOUNT min = BLOCK_SIZE * 512 / 8 max = BLOCK_SIZE * 512 / 8

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
