// GRR20196992 Lucas Alionco


#include "wav_terminal.h"

int wave1_args_input(int argc, char *argv[], char **input_arg) {
	
	int option;

	while((option = getopt(argc, argv, "i:")) != -1) {
		switch(option) {
			case 'i':
				*input_arg = optarg;
				break;

			default:
				fprintf(stderr, "O programa %s aceita -i como parametro.", argv[0]);
				exit (1);
		}
	}
	return 1;
}


int wave1_args_output(int argc, char *argv[], char **output_arg) {

	int option;

	while((option = getopt(argc, argv, "o:")) != -1) {
		switch(option) {
			case 'o':
				*output_arg = optarg;
				break;

			default:
				fprintf(stderr, "O programa %s aceita -o como parametro.", argv[0]);
				exit (1);
		}
	}

	return 1;
}

int wave2_args(int argc, char *argv[], char **input_arg, char **output_arg) {

	int option;

	while((option = getopt(argc, argv, "i:o:")) != -1) {
		switch(option) {
			case 'i':
				*input_arg = optarg;
				break;

			case 'o':
				*output_arg = optarg;
				break;

			default:
				fprintf(stderr, "O programa %s aceita -i -o como parametros.", argv[0]);
				exit (1);
		}
	}

	return 1;
}

int wave3_args(int argc, char *argv[], char **level_arg, char **input_arg, char **output_arg) {

	int option;

	while((option = getopt(argc, argv, "l:i:o:")) != -1) {
		switch(option) {
			case 'l':
				*level_arg = optarg;
				break;

			case 'i':
				*input_arg = optarg;
				break;

			case 'o':
				*output_arg = optarg;
				break;

			default:
				fprintf(stderr, "O programa %s aceita -l -i -o como parametros.", argv[0]);
				exit (1);
		}
	}

	return 1;
}

int wave4_args(int argc, char *argv[], char **level_arg, char **delay_arg, char **input_arg, char **output_arg) {

	int option;

	while((option = getopt(argc, argv, "l:t:i:o:")) != -1) {
		switch(option) {
			case 'l':
				*level_arg = optarg;
				break;

			case 't':
				*delay_arg = optarg;
				break;

			case 'i':
				*input_arg = optarg;
				break;

			case 'o':
				*output_arg = optarg;
				break;

			default:
				fprintf(stderr, "O programa %s aceita -l -t -i -o como parametros.", argv[0]);
				exit (1);
		}
	}

	return 1;
}





