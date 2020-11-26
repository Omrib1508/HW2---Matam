/////////////////////////////////////////////////////////////////////////
///////////////////////////////// main.c ////////////////////////////////
/////////////////////////////////////////////////////////////////////////

//info: This main.c file of the Ceasar process is incharge of reading the
//      input file, dicript the ceasar code, and print in the output
//      file.

//............................Includes.................................//
//.....................................................................//
#include "Ceasar.h"
#include "encrypt_n_decrypt.h"


//...........................Functions.................................//
//.....................................................................//

/*
* Function:        main
* description:     the main function does the process
* input:           number of arguments, array of argument
* output:          number of trees that was burn in process
*/
int main(int argc, char* argv[]) {
	Ceasar* ceasar = NULL;
	Sector* sector = NULL;
	int ex;

	ceasar = (Ceasar*)malloc(sizeof(Ceasar));
	ASSERT("malloc", ceasar);
	
	/*Initalize ceasar stuct*/
	ex = init_ceasar(ceasar, argc, argv);
	
	//sector = devide_file_2_sectors(ceasar);
	/*Main function that decrypt and descrpyt*/
	
	free(ceasar);
	return EXIT_SUCCESS;
}