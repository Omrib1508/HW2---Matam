/////////////////////////////////////////////////////////////////////////
//////////////////////////////Caesar.h //////////////////////////////////
/////////////////////////////////////////////////////////////////////////


//info: This file contain all the function and declarion to the Father
//      process. There are also the include libraries. In this file there
//      is the caesar sturct.

#ifndef CAESAR_H
#define CAESAR_H

#pragma comment(lib, "Shlwapi.lib")
#define _CRT_SECURE_NO_WARNINGS
//............................Includes.................................//
//.....................................................................//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "Shlwapi.h"

#include "thread.h"
#include "hard_coded_data.h"
//............................Defines..................................//
//.....................................................................//
#define ASSERT(name, arg) do{																\
	if (!arg){																				\
		if(errno)																			\
			printf("Error: %s was failed: %s\n", name, strerror(errno));					\
		else if (GetLastError())															\
			printf("Error: %s was failed: WinError 0x%X\n", name, GetLastError());			\
		else																				\
			printf("Error: %s was failed: unknown error\n", name);							\
		return(EXIT_FAILURE);																\
	}																						\
} while (0);

static char* output_path[] = {
	[DE] = "decrypted.txt",
	[EN] = "encrypted.txt",
};

//...........................Structs...................................//
//.....................................................................//
typedef struct caesar {
	char*	input;
	char*	output;
	int		key;
	int		thread_num;
	BOOL	d_flag;
	BOOL	e_flag;
} Caesar;


//...........................Functions.................................//
//.....................................................................//
int init_caesar(Caesar* caesar, int argc, char* argv[]);

void init_flags(Caesar* caesar, char* flag);

int devide_file_2_sectors(Caesar* caesar, THREAD_Params* Params_array);

int get_output_path(Caesar* caesar, char* input_path, char* output_filename);

#endif // !CAESAR_H