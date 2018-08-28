#include <string.h>
#include <hls_stream.h>
#include "myIP_stream.h"


static void process_64(hls::stream<uint64_t> &fifoSrc, hls::stream<uint64_t> &fifoDst)
{
	for (int i = 0; i < BLOCK_SIZE / 8; i++) {
#pragma HLS PIPELINE
		uint64_t temp;
        fifoSrc >> temp;
        uint8_t* buffSrc8 = (uint8_t*)&temp;
		uint8_t d0 = buffSrc8[0] * 2;
		uint8_t d1 = buffSrc8[1] * 2;
		uint8_t d2 = buffSrc8[2] * 2;
		uint8_t d3 = buffSrc8[3] * 2;
		uint8_t d4 = buffSrc8[4] * 2;
		uint8_t d5 = buffSrc8[5] * 2;
		uint8_t d6 = buffSrc8[6] * 2;
		uint8_t d7 = buffSrc8[7] * 2;
		temp = ((uint64_t)d7 << (8 * 7)) | ((uint64_t)d6 << (8 * 6)) | ((uint64_t)d5 << (8 * 5)) | ((uint64_t)d4 << (8 * 4))
				| ((uint64_t)d3 << (8 * 3)) | ((uint64_t)d2 << (8 * 2)) | ((uint64_t)d1 << (8 * 1)) | ((uint64_t)d0 << (8 * 0));
        fifoDst << temp;
	}
}

static void read_64(hls::stream<uint64_t> &fifoSrc, uint64_t* src)
{
	for (int i = 0; i < BLOCK_SIZE / 8; i++) {
#pragma HLS PIPELINE
		fifoSrc << *src;
		src++;
	}
}

static void write_64(hls::stream<uint64_t> &fifoDst, uint64_t* dst)
{
	for (int i = 0; i < BLOCK_SIZE / 8; i++) {
#pragma HLS PIPELINE
		fifoDst >> *dst;
        dst++;
	}
}


static void process_all_64(hls::stream<uint64_t> &fifoSrc, hls::stream<uint64_t> &fifoDst, int blockNum)
{
	for (int i = 0; i < BLOCK_SIZE * blockNum / 8; i++) {
#pragma HLS PIPELINE
		uint64_t temp;
        fifoSrc >> temp;
        uint8_t* buffSrc8 = (uint8_t*)&temp;
		uint8_t d0 = buffSrc8[0] * 2;
		uint8_t d1 = buffSrc8[1] * 2;
		uint8_t d2 = buffSrc8[2] * 2;
		uint8_t d3 = buffSrc8[3] * 2;
		uint8_t d4 = buffSrc8[4] * 2;
		uint8_t d5 = buffSrc8[5] * 2;
		uint8_t d6 = buffSrc8[6] * 2;
		uint8_t d7 = buffSrc8[7] * 2;
		temp = ((uint64_t)d7 << (8 * 7)) | ((uint64_t)d6 << (8 * 6)) | ((uint64_t)d5 << (8 * 5)) | ((uint64_t)d4 << (8 * 4))
				| ((uint64_t)d3 << (8 * 3)) | ((uint64_t)d2 << (8 * 2)) | ((uint64_t)d1 << (8 * 1)) | ((uint64_t)d0 << (8 * 0));
        fifoDst << temp;
	}
}

static void read_all_64(hls::stream<uint64_t> &fifoSrc, uint64_t* src, int blockNum)
{
	for (int i = 0; i < BLOCK_SIZE * blockNum / 8; i++) {
#pragma HLS PIPELINE
		fifoSrc << *src;
		src++;
	}
}

static void write_all_64(hls::stream<uint64_t> &fifoDst, uint64_t* dst, int blockNum)
{
	for (int i = 0; i < BLOCK_SIZE * blockNum / 8; i++) {
#pragma HLS PIPELINE
		fifoDst >> *dst;
        dst++;
	}
}


#if 0
void myIP_stream_none_64(uint64_t* dst, uint64_t* src, int blockNum)
{
	hls::stream<uint64_t> fifoSrc;
	hls::stream<uint64_t> fifoDst;

	read_64(fifoSrc, src, blockNum);
	process_64(fifoSrc, fifoDst, blockNum);
	write_64(fifoDst, dst, blockNum);
}

void myIP_stream_pipe_64(uint64_t* dst, uint64_t* src, int blockNum)
{
	hls::stream<uint64_t> fifoSrc;
	hls::stream<uint64_t> fifoDst;

#pragma HLS PIPELINE
	read_64(fifoSrc, src, blockNum);
	process_64(fifoSrc, fifoDst, blockNum);
	write_64(fifoDst, dst, blockNum);
}
#endif

void myIP_stream_df_64(uint64_t* dst, uint64_t* src, int blockNum)
{
	hls::stream<uint64_t> fifoSrc;
	hls::stream<uint64_t> fifoDst;

	for (int i = 0; i < blockNum; i++) {
#pragma HLS DATAFLOW
		read_64(fifoSrc, src);
		process_64(fifoSrc, fifoDst);
		write_64(fifoDst, dst);
	}
}

void myIP_stream_df_all_64(uint64_t* dst, uint64_t* src, int blockNum)
{
	hls::stream<uint64_t> fifoSrc;
	hls::stream<uint64_t> fifoDst;

#pragma HLS DATAFLOW
	read_all_64(fifoSrc, src, blockNum);
	process_all_64(fifoSrc, fifoDst, blockNum);
	write_all_64(fifoDst, dst, blockNum);
}


