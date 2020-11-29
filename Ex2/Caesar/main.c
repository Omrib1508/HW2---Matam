/////////////////////////////////////////////////////////////////////////
///////////////////////////////// main.c ////////////////////////////////
/////////////////////////////////////////////////////////////////////////

//info: This main.c file of the Ceasar process is incharge of reading the
//      input file, dicript the ceasar code, and print in the output
//      file.

//............................Includes.................................//
//.....................................................................//
#include "Caesar.h"
#include "encrypt_n_decrypt.h"

//...........................Functions.................................//
//.....................................................................//
/*
* Function:        main
* description:     the main function does the process
* input:           number of arguments, array of argument
* output:          process exit code
*/
int main(int argc, char* argv[]) {
	Caesar* caesar = NULL;
	int exit_code = EXIT_SUCCESS;

	caesar = (Caesar*)malloc(sizeof(Caesar));
	ASSERT("malloc", caesar);
	
	/*Initalize ceasar stuct*/
	exit_code = init_caesar(caesar, argc, argv);
	
	/*Main function that decrypt and descrpyt*/
	exit_code = encrpyt_and_decrypt_file(caesar);
	
	free(caesar);
	return exit_code;
}