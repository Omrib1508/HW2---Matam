/////////////////////////////////////////////////////////////////////////
/////////////////////////////// Ceasar.c ////////////////////////////////
/////////////////////////////////////////////////////////////////////////


//info: This file contain all the function bodies. All this functions are
//      helping to build the Cease process, and olso create the threads.

//............................Includes.................................//
//.....................................................................//
#include "Ceasar.h"
#include "encrypt_n_decrypt.h"
#include "hard_coded_data.h"

//...........................Functions.................................//
//.....................................................................//
/*
* Function:        exit_prog
* description:     this function close the program, close the file and free memory
* input:           input file, output file, forest srtruct
* output:          none
*/
int init_ceasar(Ceasar* ceasar,int argc,char* argv[]) {
	if (argc != ARGUMENTS) {
		printf("Error: invalid number of arguments(%d instead of %d)\n",(argc - 1), ARGUMENTS);
		exit(FAIL_PROCESS);
	}
	else {
		ceasar->input = argv[INPUT_FILE];
		/*if (!PathFileExistsA(ceasar->input)) {
			ASSERT("PathFileExistsA", ceasar->input);
			return FAIL_PROCESS;
		}*/
		ceasar->key = strtol(argv[KEY], NULL, 10);
		if (errno == ERANGE) {
			printf("Error: invaild key\n");
			return FAIL_PROCESS;
		}
		ceasar->thread_num = strtol(argv[THREADS_NUM], NULL, 10);
		if (ceasar->thread_num < 1 || errno == ERANGE) {
			printf("Error: number of thread isn't illegal. must be at least 1\n");
		}
		init_flags(ceasar, argv[FLAG]);
		if (ceasar->d_flag) {
			ceasar->output = get_output_path(argv[INPUT_FILE], output_path[DE]);
		}
		else if (ceasar->e_flag) {
			ceasar->output = get_output_path(argv[INPUT_FILE], output_path[EN]);
			ceasar->key = -ceasar->key;
		}
		else {
			return FAIL_PROCESS;
		}
	}
	return EXIT_SUCCESS;
}


/*
* Function:        init_flag
* description:     this function initalize the flags struct, that tell us if decrypt
*                  or descrypt
* input:           flags sturct, flag argumnet from user
* output:          none
*/
void init_flags(Ceasar* ceasar, char* flag) {

	if (strcmp("-e", flag) == 0) {
		ceasar->d_flag = false;
		ceasar->e_flag = true;
	}
	else if (strcmp("-d", flag) == 0) {
		ceasar->d_flag = true;
		ceasar->e_flag = false;
	}
	else {
		printf("Error: insert correct flag\n");
		printf("Please insert flag [-d] or [-e]\n");
	}
}

/*
* Function:        decrypted_file
* description:     this function initalize the flags struct, that tell us if decrypt
*                  or descrypt
* input:           flags sturct, flag argumnet from user
* output:          none
*/
Sector* devide_file_2_sectors(Ceasar* ceasar){
	FILE*		intput_file = NULL;
	FILE*		output_file = NULL;
	Sector*		sector = NULL;
	int			sector_lines, remaind;
	int			file_lines = 0;
	char		c;

	/*Calc number of lines in input file*/
	intput_file = fopen(ceasar->input, "r");
	ASSERT("fopen", intput_file);
	for (c = getc(intput_file); c != EOF; c = getc(intput_file)) {
		if (c == '\n') {
			file_lines++;
		}
	}
	fclose(intput_file);
	ASSERT("fclose", intput_file);

	/*Divide to sectors*/
	sector_lines = file_lines / ceasar->thread_num;
	remaind = file_lines % ceasar->thread_num;

	if (ceasar->thread_num > file_lines) {
		printf("Error: number of thread are to big for file\n");
		exit(EXIT_FAILURE);
	}
	return sector;
}

/*
* Function:        get_output_path
* description:     this function initalize the flags struct, that tell us if decrypt
*                  or descrypt
* input:           flags sturct, flag argumnet from user
* output:          none
*/
char* get_output_path(char* input_path, char* output_filename) {
	char* output_path = NULL;
	int index = (int)strlen(input_path);
	int size;
		while (input_path[index] != '\\') {
			index--;
		}
		size = index + (int)strlen(output_filename);
		output_path = (char*)calloc(size, sizeof(char));
		ASSERT("malloc", output_path);
		
		memmove(output_path, input_path, index);
		strcat(output_path, "\\");
		strcat(output_path, output_filename);

		return output_path;
}
