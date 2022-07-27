// GRR20196992 Lucas Alionco


#include "wav_struct.h"
#include "wav_filter.h"
#include "wav_access.h"
#include "wav_terminal.h"

int main(int argc, char *argv[]) {

	char *output_arg = NULL;
	wave1_args_output(argc, argv, &output_arg);

	uint32_t ChunkSize_final, SubChunk2Size_final;
	ChunkSize_final = 0;
	SubChunk2Size_final = 0;

	Wave_t waveFile_final, waveFile;

	FILE* arq_in;

	int ini, cont;

	if(output_arg == NULL){
		ini = 1; //nao tem -o, tenho argc - 1 arquivos de entrada, a leitura deve comecar em argv[1]
		cont = argc - 1;
	} else {
		ini = 3; //tem -o, tenho argc - 3 arquivos de entrada, a leitura deve comecar em argv[3] porque getopt permuta o vetor
		cont = argc - 3;
	}

	int16_t *samples_final = NULL; //vetor final que vai receber as amostras de cada file
	int16_t *samples_parcial = NULL; 


	int i, j;
	j = 0;

	for(i = ini; i < argc; i++) {

		arq_in = fopen(argv[i], "r");
		if(!arq_in) {
			perror ("Erro ao abrir arquivo ou ler arquivo da entrada");
			exit (1);
		}

		get_header(&waveFile, arq_in);

		if(waveFile.ChunkSize > ChunkSize_final) { //atualizando os dados que vao ser usados no header final
			ChunkSize_final = waveFile.ChunkSize;
		}

		if(waveFile.SubChunk2Size > SubChunk2Size_final) {
			SubChunk2Size_final = waveFile.SubChunk2Size;
		}

		samples_parcial = get_samples(&waveFile, arq_in);

		if(waveFile.NumberOfSamples > j) {
			samples_final = realloc(samples_final, waveFile.NumberOfSamples * sizeof(int16_t)); //aumento do tamanho do vetor final pra receber mais elementos caso seja necessário
		}
		if(!samples_final) {
			perror("Erro ao usar realloc");
			exit (1);
		}
		for(j = 0; j < waveFile.NumberOfSamples; j++) {
			samples_final[j] = samples_final[j] + (int16_t)(samples_parcial[j] / cont); //soma todos os elementos e coloca no vetor
		}
		
	} //loop termina com os valores finais de chunksize e subchunk2size prontos e uma matriz de samples

	waveFile_final = waveFile; //ajuste do header do arquivo final
	waveFile_final.ChunkSize = ChunkSize_final;
	waveFile_final.SubChunk2Size = SubChunk2Size_final;
	waveFile_final.NumberOfSamples = waveFile_final.SubChunk2Size / (waveFile_final.BitsPerSample / 8); 


	mix(&waveFile_final, samples_final, output_arg); //escreve o arquivo final com o header ajustado e o vetor mix

	return 0;
}



