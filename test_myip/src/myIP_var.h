#ifndef MYIP_VAR_H_
#define MYIP_VAR_H_

#include <stdint.h>
#include "common.h"


#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum/8], src[0:BLOCK_SIZE*blockNum/8])
void myIP_buff2_pipe_cast_inline_var_64(uint64_t* dst, uint64_t* src, int blockNum, int blockSize);

#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum/8], src[0:BLOCK_SIZE*blockNum/8])
void myIP_buff2_df_cast_inline_var_64(uint64_t* dst, uint64_t* src, int blockNum, int blockSize);


#endif	// MYIP_VAR_H_
