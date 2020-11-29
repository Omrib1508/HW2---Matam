/////////////////////////////////////////////////////////////////////////
//////////////////////////////thread.h //////////////////////////////////
/////////////////////////////////////////////////////////////////////////

//info: This file contain all the function and declarion to the Thread
//      creation and contain thread params struct

#ifndef THREAD_H
#define THREAD_H

//............................Includes.................................//
//.....................................................................//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "Shlwapi.h"

#include "hard_coded_data.h"
//...........................Structs...................................//
//.....................................................................//
typedef struct thread_params {
	char*	input;
	char*	output;
	int		key;
	int		start;
	int		end;
} THREAD_Params;

//...........................Functions.................................//
//.....................................................................//
int creat_threads(LPTHREAD_START_ROUTINE p_start_routine, THREAD_Params* lpParam,
	HANDLE* thread_array, int thread_num, LPDWORD p_thread_id);

int open_file(char* file_path);

HANDLE* write_file(char* outfile_path);

HANDLE* read_file(char* infile_path);

void init_threads_array(int thread_num, HANDLE* p_thread_handles);

int SemaphoreWaitCheck(HANDLE* semapohre, HANDLE* p_thread_handles, THREAD_Params* lpParam, int thread_num);

#endif // !THREAD_H