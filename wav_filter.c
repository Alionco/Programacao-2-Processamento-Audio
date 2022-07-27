// GRR20196992 Lucas Alionco


#include "wav_filter.h"


int show_info(Wave_t *waveFile, char *output_arg) {

	int i;

	printf("RIFF TAG: ");
	for(i = 0; i < 4; i++) {
		printf("%c", waveFile->ChunkID[i]);
	}
	printf("\n");

	printf("RIFF SIZE: %u\n", waveFile->ChunkSize);

	printf("WAVE TAG: ");
	for(i = 0; i < 4; i++) {
		printf("%c", waveFile->Format[i]);
	}
	printf("\n");


	printf("FORMAT TAG: ");
	for(i = 0; i < 4; i++) {
		printf("%c", waveFile->SubChunk1ID[i]);
	}
	printf("\n");

	printf("FORMAT SIZE: %u\n", waveFile->SubChunk1Size);
	printf("AUDIO FORMAT: %u\n", waveFile->AudioFormat);
	printf("NUMER OF CHANNELS: %u\n", waveFile->NumberOfChannels);
	printf("SAMPLE RATE: %u\n", waveFile->SampleRate);
	printf("BYTE RATE: %u\n", waveFile->ByteRate);
	printf("BLOCK ALIGN: %u\n", waveFile->BlockAlign);
	printf("BITS PER SAMPLE: %u\n", waveFile->BitsPerSample);

	printf("DATA TAG: ");
	for(i = 0; i < 4; i++) {
		printf("%c", waveFile->SubChunk2ID[i]);
	}
	printf("\n");

	printf("DATA SIZE: %u\n", waveFile->SubChunk2Size);

	printf("NUMBER OF SAMPLES: %u\n", waveFile->NumberOfSamples);

	return 1;
}

int change_vol(Wave_t *waveFile, FILE* arq, float vol, char *output_arg) {

	int16_t *sample;
	sample = get_samples(waveFile, arq);

	int i;
	for(i = 0; i < waveFile->NumberOfSamples; i++){ // aumenta ou diminui o volume
		sample[i] *= vol;
		if(sample[i] > 30000){
			sample[i] = 30000;
		} else if(sample[i] < -30000){
			sample[i] = -30000;
		}
	}

	write_waveFile(waveFile, sample, waveFile->NumberOfSamples, output_arg);

	free(sample);

	return 0;
}

int normalize(Wave_t *waveFile, FILE* arq, char *output_arg) {

	int16_t *sample;
	sample = get_samples(waveFile, arq);

	int i;
	int16_t maior;

	maior = 0;

	for(i = 0; i < waveFile->NumberOfSamples; i++){ // pega cada amostra e guarda a maior de todas
		if((int16_t) fabs(sample[i]) > maior) { //nao tem problema converter de double pra int16 porque o vetor só tem int16
			maior = sample[i];
		}
	}

	float factor;
	factor = (float) 32767 / maior;

	for(i = 0; i < waveFile->NumberOfSamples; i++){ // multiplica cada amostra pelo fator de normalizacao
		sample[i] *= factor;
	}

	write_waveFile(waveFile, sample, waveFile->NumberOfSamples, output_arg);

	free(sample);

	return 0;
}

int reverse(Wave_t *waveFile, FILE* arq, char *output_arg) {

	int16_t *sample;
	sample = get_samples(waveFile, arq);

	int16_t *sample_rev;
	sample_rev = malloc(sizeof(int16_t) * waveFile->NumberOfSamples); //vetor reverso
	if(sample == 0){
		perror("erro de alocacao do vetor reverso"); //mudar para stderr
		exit (0);
	}

	int i;
	for(i = 0; i < waveFile->NumberOfSamples; i++) { //inverte a posicao das amostras
		sample_rev[i] = sample[waveFile->NumberOfSamples - i];
	}

	write_waveFile(waveFile, sample_rev, waveFile->NumberOfSamples, output_arg);
	free(sample);
	free(sample_rev);

	return 0;
}

int echo(Wave_t *waveFile, FILE* arq, float level, int delay, char *output_arg) {

	int16_t *sample;
	sample = get_samples(waveFile, arq);

	int i;
	for(i = 44 * delay; i < waveFile->NumberOfSamples; i++) {
		sample[i] = sample[i] + (level * sample[i - 44 * delay]);
	}

	write_waveFile(waveFile, sample, waveFile->NumberOfSamples, output_arg);
	free(sample);

	return 0;
}

int wide(Wave_t *waveFile, FILE* arq, float level, char *output_arg) {

	int16_t *sample;
	sample = get_samples(waveFile, arq);

	int i;
	int16_t diff;

	for(i = 1; i < waveFile->NumberOfSamples; i+= 2) {

		diff = sample[i] - sample[i-1]; //calculo da diferenca


		sample[i] = sample[i] + level * diff;
		if(sample[i] > 25000){
			sample[i] = 25000;
		} else if(sample[i] < -25000){
			sample[i] = -25000;
		}

		sample[i-1] = sample[i-1] - level * diff;
		if(sample[i-1] > 25000){
			sample[i-1] = 25000;
		} else if(sample[i-1] < -25000){
			sample[i-1] = -25000;
		}
	}

	write_waveFile(waveFile, sample, waveFile->NumberOfSamples, output_arg);
	free(sample);

	return 0;
}

int concat(Wave_t *waveFile, int16_t *sample, char *output_arg) {

	write_waveFile(waveFile, sample, waveFile->NumberOfSamples, output_arg);
	free(sample);

	return 0;
}

int mix(Wave_t *waveFile, int16_t *sample, char *output_arg) {

	write_waveFile(waveFile, sample, waveFile->NumberOfSamples, output_arg);
	free(sample);

	return 0;
}

