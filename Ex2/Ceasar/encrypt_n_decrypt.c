/////////////////////////////////////////////////////////////////////////
///////////////////////// encrypt_n_decrypt.c ///////////////////////////
/////////////////////////////////////////////////////////////////////////


//info: This file contain all the functions which responseblle on the
//      the encryption and decryption of the Ceasar code

//............................Includes.................................//
//.....................................................................//
#include "Ceasar.h"
#include "encrypt_n_decrypt.h"
#include "hard_coded_data.h"

//...........................Functions.................................//
//.....................................................................//

/*
* Function:        init_flag
* description:     this function initalize the flags struct, that tell us if decrypt
*                  or decrypt
* input:           flags sturct, flag argumnet from user
* output:          none
*/
char encrpyt_and_decrypt(Ceasar* ceasar, char letter) {
	
	if (letter >= A && letter <= Z) {
		return(A + (letter - A - ceasar->key) % 26);
	}
	else if (letter >= 'a' && letter <= 'z') {
		return(a + (letter - a - ceasar->key) % 26);
	}
	else if (letter >= ZERO && letter <= NINE) {
		return( ZERO + (letter - ZERO - ceasar->key) % 10);
	}
	else
		return letter;
}

/*
* Function:        init_flag
* description:     this function initalize the flags struct, that tell us if decrypt
*                  or descrypt
* input:           flags sturct, flag argumnet from user
* output:          none
*/
int create_file(char* outfile_path) {
	HANDLE* h_file = NULL;

	h_file = CreateFileA(outfile_path,                // name of the write
						GENERIC_WRITE,                // open for writing
						FILE_SHARE_WRITE,             // share file for write
						NULL,                         // default security
						CREATE_ALWAYS,                // create new file always
						FILE_ATTRIBUTE_NORMAL,  // normal file
						NULL);                  // no attr. template
	if (h_file == INVALID_HANDLE_VALUE)
	{
		return FAIL_PROCESS;
	}
	
	if (!CloseHandle(h_file)) {
		return FAIL_PROCESS;
	}
	
	return GOOD_PROCESS;
}

