// GRR20196992 Lucas Alionco


#include "wav_struct.h"

#ifndef WAVE_ACCESS
#define WAVE_ACCESS

int get_header(Wave_t *waveFile, FILE* arq);

int16_t *get_samples(Wave_t *waveFile, FILE* arq);

int write_waveFile(Wave_t *waveFile, int16_t *sample, uint32_t NumberOfSamples, char *output_arg);

#endif

