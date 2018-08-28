#ifndef MYIP_BUFF_PIPE_H_
#define MYIP_BUFF_PIPE_H_

#include <stdint.h>
#include "common.h"

/*** バッファ1つ ***/
#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum], src[0:BLOCK_SIZE*blockNum])
void myIP_buff1_pipe_8(uint8_t* dst, uint8_t* src, int blockNum);

#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum/8], src[0:BLOCK_SIZE*blockNum/8])
void myIP_buff1_pipe_64(uint64_t* dst, uint64_t* src, int blockNum);

/* バッファ1つ others */
#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum/8], src[0:BLOCK_SIZE*blockNum/8])
void myIP_buff1_pipe_64_a(uint64_t* dst, uint64_t* src, int blockNum);

#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum/8], src[0:BLOCK_SIZE*blockNum/8])
void myIP_buff1_pipe_64_b(uint64_t* dst, uint64_t* src, int blockNum);

#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum/8], src[0:BLOCK_SIZE*blockNum/8])
void myIP_buff1_pipe_64_c(uint64_t* dst, uint64_t* src, int blockNum);

/*** バッファ2つ ***/
#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum/8], src[0:BLOCK_SIZE*blockNum/8])
void myIP_buff2_pipe_64(uint64_t* dst, uint64_t* src, int blockNum);

#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum/8], src[0:BLOCK_SIZE*blockNum/8])
void myIP_buff2_pipe_mask_64(uint64_t* dst, uint64_t* src, int blockNum);

#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum/8], src[0:BLOCK_SIZE*blockNum/8])
void myIP_buff2_pipe_cast_64(uint64_t* dst, uint64_t* src, int blockNum);

#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum/8], src[0:BLOCK_SIZE*blockNum/8])
void myIP_buff2_pipe_cast_64_a(uint64_t* dst, uint64_t* src, int blockNum);


/*** 関数化 ***/
#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum/8], src[0:BLOCK_SIZE*blockNum/8])
void myIP_buff2_pipe_cast_noinline_64(uint64_t* dst, uint64_t* src, int blockNum);

#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum/8], src[0:BLOCK_SIZE*blockNum/8])
void myIP_buff2_pipe_cast_inline_64(uint64_t* dst, uint64_t* src, int blockNum);

#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum/8], src[0:BLOCK_SIZE*blockNum/8])
void myIP_buff2_pipe_cast_copyfunc_64(uint64_t* dst, uint64_t* src, int blockNum);


#endif	// MYIP_BUFF_PIPE_H_
