#ifndef MYIP_BUFF_DF_H_
#define MYIP_BUFF_DF_H_

#include <stdint.h>
#include "common.h"

/*** バッファ2つ ***/
#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum], src[0:BLOCK_SIZE*blockNum])
void myIP_buff2_df_cast_64(uint64_t* dst, uint64_t* src, int blockNum);

#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum/8], src[0:BLOCK_SIZE*blockNum/8])
void myIP_buff2_df_cast_pipe_64(uint64_t* dst, uint64_t* src, int blockNum);

#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum/8], src[0:BLOCK_SIZE*blockNum/8])
void myIP_buff2_df_cast_pipe_64_a(uint64_t* dst, uint64_t* src, int blockNum);

#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum/8], src[0:BLOCK_SIZE*blockNum/8])
void myIP_buff2_df_mask_pipe_64(uint64_t* dst, uint64_t* src, int blockNum);

/*** 関数化 ***/
#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum/8], src[0:BLOCK_SIZE*blockNum/8])
void myIP_buff2_df_cast_noinline_64(uint64_t* dst, uint64_t* src, int blockNum);

#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum/8], src[0:BLOCK_SIZE*blockNum/8])
void myIP_buff2_df_cast_inline_64(uint64_t* dst, uint64_t* src, int blockNum);

#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum/8], src[0:BLOCK_SIZE*blockNum/8])
void myIP_buff2_df_cast_copyfunc_64(uint64_t* dst, uint64_t* src, int blockNum);

#endif	// MYIP_BUFF_DF_H_
