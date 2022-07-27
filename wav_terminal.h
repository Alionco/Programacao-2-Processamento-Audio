// GRR20196992 Lucas Alionco


#include "wav_struct.h"

#ifndef WAVE_TERMINAL
#define WAVE_TERMINAL

int wave1_args_input(int argc, char *argv[], char **input_arg);

int wave1_args_output(int argc, char *argv[], char **output_arg);

int wave2_args(int argc, char *argv[], char **input_arg, char **output_arg);

int wave3_args(int argc, char *argv[], char **level_arg, char **input_arg, char **output_arg);

int wave4_args(int argc, char *argv[], char **level_arg, char **delay_arg, char **input_arg, char **output_arg);







#endif