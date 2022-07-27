// GRR20196992 Lucas Alionco


#include "wav_struct.h"
#include "wav_access.h"

#ifndef WAVE_FILTER
#define WAVE_FILTER

int show_info(Wave_t *waveFile, char *output_arg);

int change_vol(Wave_t *waveFile, FILE* arq, float vol, char *output_arg);

int normalize(Wave_t *waveFile, FILE* arq, char *output_arg);

int reverse(Wave_t *waveFile, FILE* arq, char *output_arg);

int echo(Wave_t *waveFile, FILE* arq, float level, int delay, char *output_arg);

int wide(Wave_t *waveFile, FILE* arq, float level, char *output_arg);

int concat(Wave_t *waveFile, int16_t *sample, char *output_arg);

int mix(Wave_t *waveFile, int16_t *sample, char *output_arg);

#endif