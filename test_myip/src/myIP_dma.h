#ifndef MYIP_DMA_H_
#define MYIP_DMA_H_

#include <stdint.h>
#include "common.h"


//#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum/8], src[0:BLOCK_SIZE*blockNum/8])
#pragma SDS data copy(dst[0:BLOCK_SIZE*blockNum/8], src[0:BLOCK_SIZE*blockNum/8])
#pragma SDS data access_pattern(dst:SEQUENTIAL, src:SEQUENTIAL)
#pragma SDS data data_mover(dst:AXIDMA_SIMPLE, src:AXIDMA_SIMPLE)
void myIP_dma_simple_pipe_64(uint64_t* dst, uint64_t* src, int blockNum);

//#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum/8], src[0:BLOCK_SIZE*blockNum/8])
#pragma SDS data copy(dst[0:BLOCK_SIZE*blockNum/8], src[0:BLOCK_SIZE*blockNum/8])
#pragma SDS data access_pattern(dst:SEQUENTIAL, src:SEQUENTIAL)
#pragma SDS data data_mover(dst:AXIDMA_SIMPLE, src:AXIDMA_SIMPLE)
void myIP_dma_pipe_cast_64(uint64_t* dst, uint64_t* src, int blockNum);

//#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum/8], src[0:BLOCK_SIZE*blockNum/8])
#pragma SDS data copy(dst[0:BLOCK_SIZE*blockNum/8], src[0:BLOCK_SIZE*blockNum/8])
#pragma SDS data access_pattern(dst:SEQUENTIAL, src:SEQUENTIAL)
#pragma SDS data data_mover(dst:AXIDMA_SIMPLE, src:AXIDMA_SIMPLE)
void myIP_dma_df_cast_64(uint64_t* dst, uint64_t* src, int blockNum);

//#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum/8], src[0:BLOCK_SIZE*blockNum/8])
#pragma SDS data copy(dst[0:BLOCK_SIZE*blockNum/8], src[0:BLOCK_SIZE*blockNum/8])
#pragma SDS data access_pattern(dst:SEQUENTIAL, src:SEQUENTIAL)
#pragma SDS data data_mover(dst:AXIDMA_SIMPLE, src:AXIDMA_SIMPLE)
void myIP_dma_pipe_copyfunc_64(uint64_t* dst, uint64_t* src, int blockNum);

//#pragma SDS data zero_copy(dst[0:BLOCK_SIZE*blockNum/8], src[0:BLOCK_SIZE*blockNum/8])
#pragma SDS data copy(dst[0:BLOCK_SIZE*blockNum/8], src[0:BLOCK_SIZE*blockNum/8])
#pragma SDS data access_pattern(dst:SEQUENTIAL, src:SEQUENTIAL)
#pragma SDS data data_mover(dst:AXIDMA_SIMPLE, src:AXIDMA_SIMPLE)
void myIP_dma_df_copyfunc_64(uint64_t* dst, uint64_t* src, int blockNum);


#endif	// MYIP_DMA_H_
