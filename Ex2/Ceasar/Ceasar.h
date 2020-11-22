/////////////////////////////////////////////////////////////////////////
//////////////////////////////Ceasar.h //////////////////////////////////
/////////////////////////////////////////////////////////////////////////


//info: This file contain all the function and declarion to the Father
//      process. There are also the include libraries. In this file there
//      is the forest sturct.

#ifndef CEASAR_H
#define CEASAR_H


//............................Includes.................................//
//.....................................................................//
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <windows.h>

#include "hard_coded_data.h"

//............................Defines..................................//
//.....................................................................//
#define ASSERT(name, arg) do{                                                    \
    if (!arg){                                                                    \
        if(errno)                                                                \
            printf("%s was failed: %s\n", name, strerror(errno));                \
        else if (GetLastError())                                                \
            printf("%s was failed: WinError 0x%X\n", name, GetLastError());        \
        else                                                                    \
            printf("%s was failed: unknown error\n", name);                        \
    exit(EXIT_FAILURE);                                                            \
    }                                                                            \
} while (0)


//...........................Structs...................................//
//.....................................................................//
typedef struct files {
    FILE* input;
    FILE* output;
    char key;
    char thread;
    char type; 
}Files;


//typedef struct ceasar {
//}Ceasar;

//...........................Functions.................................//
//.....................................................................//
void exit_prog(Files* files);

void file_check(FILE* file);

void print_to_file(Files* files);


#endif // !CEASAR_H
