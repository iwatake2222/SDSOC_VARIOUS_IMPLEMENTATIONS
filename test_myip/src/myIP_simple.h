#ifndef MYIP_SIMPLE_H_
#define MYIP_SIMPLE_H_

#include <stdint.h>
#include "common.h"

/*** simple ***/
#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum], src[0:BLOCK_SIZE*blockNum])
void myIP_simple_8(uint8_t* dst, uint8_t* src, int blockNum);

#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum/4], src[0:BLOCK_SIZE*blockNum/4])
void myIP_simple_32(uint32_t* dst, uint32_t* src, int blockNum);

#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum/8], src[0:BLOCK_SIZE*blockNum/8])
void myIP_simple_64(uint64_t* dst, uint64_t* src, int blockNum);


/*** pipeline ***/
#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum], src[0:BLOCK_SIZE*blockNum])
void myIP_simple_pipe_8(uint8_t* dst, uint8_t* src, int blockNum);

#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum/4], src[0:BLOCK_SIZE*blockNum/4])
void myIP_simple_pipe_32(uint32_t* dst, uint32_t* src, int blockNum);

#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum/8], src[0:BLOCK_SIZE*blockNum/8])
void myIP_simple_pipe_64(uint64_t* dst, uint64_t* src, int blockNum);


/*** pipeline others ***/
#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum/8], src[0:BLOCK_SIZE*blockNum/8])
void myIP_simple_pipe_64_a(uint64_t* dst, uint64_t* src, int blockNum);

#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum/8], src[0:BLOCK_SIZE*blockNum/8])
void myIP_simple_pipe_64_b(uint64_t* dst, uint64_t* src, int blockNum);

#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum/8], src[0:BLOCK_SIZE*blockNum/8])
void myIP_simple_pipe_64_c(uint64_t* dst, uint64_t* src, int blockNum);

#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum/8], src[0:BLOCK_SIZE*blockNum/8])
void myIP_simple_pipe_64_tripcount(uint64_t* dst, uint64_t* src, int blockNum);


#endif	// MYIP_SIMPLE_H_
