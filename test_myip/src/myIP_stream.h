#ifndef MYIP_STREAM_H_
#define MYIP_STREAM_H_

#include <stdint.h>
#include "common.h"


#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum/8], src[0:BLOCK_SIZE*blockNum/8])
void myIP_stream_df_64(uint64_t* dst, uint64_t* src, int blockNum);

#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum/8], src[0:BLOCK_SIZE*blockNum/8])
void myIP_stream_df_all_64(uint64_t* dst, uint64_t* src, int blockNum);

#endif	// MYIP_STREAM_H_
