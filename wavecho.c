// GRR20196992 Lucas Alionco


#include "wav_struct.h"
#include "wav_filter.h"
#include "wav_access.h"
#include "wav_terminal.h"

int main(int argc, char *argv[]) {

	//inicio do tratamento da linha de comando

	char *level_arg = NULL;
	char *delay_arg = NULL;
	char *input_arg = NULL;
	char *output_arg = NULL;

	wave4_args(argc, argv, &level_arg, &delay_arg, &input_arg, &output_arg);

	float level;
	int delay;

	if(level_arg == NULL){
		level = 0.5;
	} else {
		level = (float) atof(level_arg);
	}

	if(delay_arg == NULL) {
		delay = 1000;
	} else {
		delay = atoi(delay_arg);
	}

	if(level < 0 || level > 1) {
		fprintf(stderr, "Parametro -l deve estar entre 0.0 e 1.0\n");
		exit (1);
	}

	if(delay < 0){
		fprintf(stderr, "Parametro -t deve ser maior que 0\n");
		exit (1);
	}

	//fim do tratamento da linha de comando

	//inicio do acesso ao arquivo

	FILE* arq;
	if(input_arg == NULL) {
		arq = freopen(input_arg, "r", stdin); //pra pegar da entrada padrao quando nao foi passado -i
	} else { 
		arq = fopen(input_arg, "r");
	}

	if (!arq) {
		perror ("Erro ao abrir arquivo ou ler arquivo da entrada");
		exit (1);
	}

	// fim do acesso ao arquivo

	// inicio do filtro

	Wave_t waveFile;
	get_header(&waveFile, arq);

	echo(&waveFile, arq, level, delay, output_arg); //funcao que define este programa e o diferencia dos demais

	fclose(arq);

	// fim do filtro


	return 0;
}