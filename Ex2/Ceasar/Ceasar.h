/////////////////////////////////////////////////////////////////////////
//////////////////////////////Ceasar.h //////////////////////////////////
/////////////////////////////////////////////////////////////////////////


//info: This file contain all the function and declarion to the Father
//      process. There are also the include libraries. In this file there
//      is the forest sturct.

#ifndef CEASAR_H
#define CEASAR_H

#define _CRT_SECURE_NO_WARNINGS
//............................Includes.................................//
//.....................................................................//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <tchar.h>
#include <windows.h>
#include "Shlwapi.h"

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
	exit(EXIT_FAILURE);																		\
	}																						\
} while (0)

static char* output_path[] = {
	[DE] = "decrypted.txt",
	[EN] = "encrypted.txt",
};

//...........................Structs...................................//
//.....................................................................//
typedef struct ceasar {
	char*	input;
	char*	output;
	int		key;
	int		thread_num;
	bool	d_flag;
	bool	e_flag;
}Ceasar;

typedef struct thread {
	char* input;
	char* output;
	int key;
	int start;
	int end;
} Thread;

typedef struct sector {
	int start;
	int end;
} Sector;

//...........................Functions.................................//
//.....................................................................//
int init_ceasar(Ceasar* ceasar, int argc, char* argv[]);

void init_flags(Ceasar* ceasar, char* flag);

Sector* devide_file_2_sectors(Ceasar* ceasar);

char* get_output_path(char* input_path, char* output_filename);

#endif // !CEASAR_H