// GRR20196992 Lucas Alionco


#include "wav_access.h"

int get_header(Wave_t *waveFile, FILE* arq) {

	char array[4];
	uint16_t unsigned16; //variaveis temporarias
	uint32_t unsigned32;
	int i;

	int read;

	read = fread(array, 4 * sizeof(char), 1, arq); //le ChunkID
	if(read == 1) {
		for(i = 0; i < 4; i++) {
			waveFile->ChunkID[i] = array[i];
		}
	}

	read = fread(&unsigned32, sizeof(uint32_t), 1, arq); //le ChunkSize
	if(read == 1) {
		waveFile->ChunkSize = unsigned32;
	}


	read = fread(array, 4 * sizeof(char), 1, arq); //le Format
	if(read == 1) {
		for(i = 0; i < 4; i++) {
			waveFile->Format[i] = array[i];
		}
	}


	read = fread(array, 4 * sizeof(char), 1, arq); //le SubChunk1ID
	if(read == 1) {
		for(i = 0; i < 4; i++) {
			waveFile->SubChunk1ID[i] = array[i];
		}
	}


	read = fread(&unsigned32, sizeof(uint32_t), 1, arq); //le SubChunk1Size
	if(read == 1) {
		waveFile->SubChunk1Size = unsigned32;
	}


	read = fread(&unsigned16, sizeof(uint16_t), 1, arq); //le AudioFormat 
	if(read == 1) {
		waveFile->AudioFormat = unsigned16;
	}

	read = fread(&unsigned16, sizeof(uint16_t), 1, arq); //le NumberOfChannels
	if(read == 1) {
		waveFile->NumberOfChannels = unsigned16;
	}


	read = fread(&unsigned32, sizeof(uint32_t), 1, arq); //le SampleRate
	if(read == 1) {
		waveFile->SampleRate = unsigned32;
	}


	read = fread(&unsigned32, sizeof(uint32_t), 1, arq); //le ByteRate
	if(read == 1) {
		waveFile->ByteRate = unsigned32;
	}


	read = fread(&unsigned16, sizeof(uint16_t), 1, arq); //le BlockAlign
	if(read == 1) {
		waveFile->BlockAlign = unsigned16;
	}


	read = fread(&unsigned16, sizeof(uint16_t), 1, arq); //le BitsPerSample
	if(read == 1) {
		waveFile->BitsPerSample = unsigned16;
	}


	read = fread(array, 4 * sizeof(char), 1, arq); //le SubChunk2ID
	if(read == 1) {
		for(i = 0; i < 4; i++) {
			waveFile->SubChunk2ID[i] = array[i];
		}
	}

	read = fread(&unsigned32, sizeof(uint32_t), 1, arq); //le SubChunk2Size
	if(read == 1) {
		waveFile->SubChunk2Size = unsigned32;
	}

	waveFile->NumberOfSamples = waveFile->SubChunk2Size / (waveFile->BitsPerSample / 8);  //n. de amostras = qtd de bytes de dados / qtd de bytes por amostra(PCM 16 = 2)

	return 0; 
}

int16_t *get_samples(Wave_t *waveFile, FILE* arq) {

	fseek(arq, 44, SEEK_SET); //move o ponteiro de posicao para o fim do cabeçalho do arquivo de musica


	int16_t *sample;

	sample = malloc(sizeof(int16_t) * waveFile->NumberOfSamples); //aloca o vetor de ints que armazenam as amostras
	if(sample == 0){
		printf("erro de alocacao"); //mudar para stderr
		exit (0);
	}

	fread(sample, sizeof(int16_t), waveFile->NumberOfSamples, arq); //armazena as amostras

	return sample; //retorna o ponteiro para o vetor que contem as amostras
}

int write_waveFile(Wave_t *waveFile, int16_t *sample, uint32_t NumberOfSamples, char *output_arg) {

	FILE* arq_d; //arquivo de destino

	if(output_arg == NULL){
		arq_d = freopen(output_arg, "w", stdout); // escreve em um arquivo de saída
	} else {
		arq_d = fopen(output_arg, "w"); // escreve em um arquivo de saída
	}

	if (!arq_d) {
		perror ("Erro ao escrever arquivo de saida");
		exit (1);
	}

	fwrite(waveFile, sizeof(Wave_t), 1, arq_d); //cõpia do header original

	fwrite(sample, sizeof(int16_t), NumberOfSamples, arq_d); // escreve as amostras alteradas na saída

	fclose(arq_d);

	return 0;
}



