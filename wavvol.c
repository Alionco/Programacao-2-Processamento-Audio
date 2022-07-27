// GRR20196992 Lucas Alionco


#include "wav_struct.h"
#include "wav_filter.h"
#include "wav_access.h"
#include "wav_terminal.h"

int main(int argc, char *argv[]) {

	//inicio do tratamento da linha de comando

	char *level_arg = NULL;
	char *input_arg = NULL;
	char *output_arg = NULL;

	wave3_args(argc, argv, &level_arg, &input_arg, &output_arg);

	float level;
	
	if(level_arg == NULL){
		level = 1.0;
	} else {
		level = (float) atof(level_arg);
	}

	if(level < 0 || level > 10) {
		fprintf(stderr, "Parametro -l deve estar entre 0.0 e 10.0\n");
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

	change_vol(&waveFile, arq, level, output_arg); //funcao que define este programa e o diferencia dos demais

	fclose(arq);

	//fim do filtro

	return 0;
}