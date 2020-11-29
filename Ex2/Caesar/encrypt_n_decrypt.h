/////////////////////////////////////////////////////////////////////////
//////////////////////////encrypt_n_decrypt.h ///////////////////////////
/////////////////////////////////////////////////////////////////////////


//info: This file contain all the function and declarion to the Father
//      process. There are also the include libraries. In this file there
//      is the forest sturct.

#ifndef ENCRYPT_N_DECRYPT_H
#define ENCRYPT_N_DECRYPT_H


//............................Includes.................................//
//.....................................................................//
#include "Caesar.h"
#include "thread.h"


//............................Structs..................................//
//.....................................................................//
typedef enum
{
	THREAD__CODE_SUCCESS,
	THREAD__CODE_NULL_PTR,
} THREAD__return_code_t;

//...........................Functions.................................//
//.....................................................................//
char encrpyt_n_decrypt_letter(int key, char letter);

void encrpyt_n_decrypt_line(char* line, int line_size, int key);

int encrpyt_and_decrypt_file(Caesar* caesar);

DWORD WINAPI encrpyt_n_decrypt_sector(HANDLE* semapohre, THREAD_Params* lpParam);

#endif // !ENCRYPT_N_DECRYPT_H