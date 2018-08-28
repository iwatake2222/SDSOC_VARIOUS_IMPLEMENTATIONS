#ifndef MYIP_PARTITION_H_
#define MYIP_PARTITION_H_

#include <stdint.h>
#include "common.h"

#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum/8], src[0:BLOCK_SIZE*blockNum/8])
void myIP_partition_0_pipe_mask_64(uint64_t* dst, uint64_t* src, int blockNum);

#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum/8], src[0:BLOCK_SIZE*blockNum/8])
void myIP_partition_2_pipe_mask_64(uint64_t* dst, uint64_t* src, int blockNum);

#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum/8], src[0:BLOCK_SIZE*blockNum/8])
void myIP_partition_4_pipe_mask_64(uint64_t* dst, uint64_t* src, int blockNum);

#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum/8], src[0:BLOCK_SIZE*blockNum/8])
void myIP_partition_0_df_mask_64(uint64_t* dst, uint64_t* src, int blockNum);

#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum/8], src[0:BLOCK_SIZE*blockNum/8])
void myIP_partition_2_df_mask_64(uint64_t* dst, uint64_t* src, int blockNum);

#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum/8], src[0:BLOCK_SIZE*blockNum/8])
void myIP_partition_4_df_mask_64(uint64_t* dst, uint64_t* src, int blockNum);


#endif	// MYIP_PARTITION_H_
