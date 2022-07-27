// GRR20196992 Lucas Alionco


#ifndef WAVE_STRUCT
#define WAVE_STRUCT

#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <string.h>

typedef struct Wave_t {
	char ChunkID[4];
	uint32_t ChunkSize;
	char Format[4];
	char SubChunk1ID[4];
	uint32_t SubChunk1Size;
	uint16_t AudioFormat;
	uint16_t NumberOfChannels;
	uint32_t SampleRate;
	uint32_t ByteRate;
	uint16_t BlockAlign;
	uint16_t BitsPerSample;
	char SubChunk2ID[4];
	uint32_t SubChunk2Size;
	uint32_t NumberOfSamples; //dado criado por mim porque é usado com frequencia

} Wave_t;

#endif