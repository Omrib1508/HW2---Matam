/////////////////////////////////////////////////////////////////////////
/////////////////////////////// Caesar.c ////////////////////////////////
/////////////////////////////////////////////////////////////////////////

//info: This file contain all the function bodies. All this functions are
//      helping to build the Cease process, and olso create the threads.

//............................Includes.................................//
//.....................................................................//
#include "Caesar.h"

//...........................Functions.................................//
//.....................................................................//
/*
* Function:        init_caesar
* description:     this function initalize the Ceasar struct
* input:           Ceasar sturct, num of user arg, array of user args
* output:          create fail or success
*/
int init_caesar(Caesar* caesar,int argc,char* argv[]) {
	int retVal;
	
	if (argc != ARGUMENTS) {
		printf("Error: invalid number of arguments(%d instead of %d)\n",(argc - 1), ARGUMENTS);
		exit(EXIT_FAILURE);
	}
	else {
		caesar->input = argv[INPUT_FILE];
		retVal = PathFileExistsA(caesar->input);
		if(!retVal){
			ASSERT("PathFileExistsA", caesar->input);
		}

		caesar->key = strtol(argv[KEY], NULL, 10);
		if (errno == ERANGE) {
			printf("Error: invaild key\n");
			return EXIT_FAILURE;
		}
		caesar->thread_num = strtol(argv[THREADS_NUM], NULL, 10);
		if (caesar->thread_num < 1 || errno == ERANGE) {
			printf("Error: number of thread isn't illegal. must be at least 1\n");
			return EXIT_FAILURE;
		}
		init_flags(caesar, argv[FLAG]);
		if (caesar->d_flag) {
			retVal = get_output_path(caesar, argv[INPUT_FILE], output_path[DE]);
			if (retVal) {
				return EXIT_FAILURE;
			}
		}
		else if (caesar->e_flag) {
			caesar->key = -caesar->key;
			retVal = get_output_path(caesar->output, argv[INPUT_FILE], output_path[EN]);
			if (retVal) {
				return EXIT_FAILURE;
			}
		}
		else {
			return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}

/*
* Function:        init_flag
* description:     this function initalize the flags struct, that tell us if decrypt
*                  or descrypt
* input:           Caesar sturct, flag argumnet from user
* output:          none
*/
void init_flags(Caesar* caesar, char* flag) {

	if (strcmp("-e", flag) == 0) {
		caesar->d_flag = FALSE;
		caesar->e_flag = TRUE;
	}
	else if (strcmp("-d", flag) == 0) {
		caesar->d_flag = TRUE;
		caesar->e_flag = FALSE;
	}
	else {
		printf("Error: insert correct flag\n");
		printf("Please insert flag [-d] or [-e]\n");
	}
}

/*
* Function:        devide_file_2_sectors
* description:     this function create the file sector that the thread take to encrypt
*                  or descrypt
* input:           Caesar sturct
* output:          exit code
*/
int devide_file_2_sectors(Caesar* caesar, THREAD_Params* Params_array) {
	FILE*		input_file = NULL;
	int			sector_lines, remaind;
	int			file_lines = 0, line_counter = 0, letter_counter = 0;
	char		c;

	/* Calc number of lines in input file */
	input_file = fopen(caesar->input, "r");
	ASSERT("fopen", input_file);
	for (c = getc(input_file); c != EOF; c = getc(input_file)) {
		if (c == '\n') {
			file_lines++;
		}
	}
	fclose(input_file);
	ASSERT("fclose", input_file);

	/* Divide to sectors */
	sector_lines = file_lines / caesar->thread_num;
	remaind = file_lines % caesar->thread_num;

	/* calculate the sectors size */
	input_file = fopen(caesar->input, "r");
	ASSERT("fopen", input_file);
	
	for (int i = 0; i < caesar->thread_num;i++) {
		line_counter = 0;
		Params_array[i].start = letter_counter;
		for (c = getc(input_file); line_counter < sector_lines; c = getc(input_file)) {
			letter_counter++;
			if(c == '\n'){
				letter_counter++;
				line_counter++;
			}
			else if (c == EOF) {
				letter_counter--;
				line_counter++;
			}
		}
		if (remaind > 0) {
			while (c = getc(input_file)) {
				letter_counter++;
				if (c == '\n') {
					letter_counter++;
					break;
				}
				else if (c == EOF) {
					letter_counter--;
					line_counter++;
					break;
				}
			}
		}
		Params_array[i].end = letter_counter;
	}
	fclose(input_file);
	ASSERT("fclose", input_file);

	return EXIT_SUCCESS;
}

/*
* Function:        get_output_path
* description:     this function initalize the flags struct, that tell us if decrypt
*                  or descrypt
* input:           flags sturct, flag argumnet from user
* output:          none
*/
int get_output_path(Caesar* caesar, char* input_path, char* output_filename) {
	int index = (int)strlen(input_path);
	int size;

	caesar->output = NULL;
	while (input_path[index] != '\\') {
		index--;
	}
	size = index + (int)strlen(output_filename);
	caesar->output = (char*)calloc(size, sizeof(char));
	ASSERT("malloc", output_path);
		
	memmove(caesar->output, input_path, index);
	strcat(caesar->output, "\\");
	strcat(caesar->output, output_filename);
		
	return EXIT_SUCCESS;
}