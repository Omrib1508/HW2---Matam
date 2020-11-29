/////////////////////////////////////////////////////////////////////////
/////////////////////////////// thread.c ////////////////////////////////
/////////////////////////////////////////////////////////////////////////

//info: This tread.c file of the Ceasar process is incharge of creating 
//      the thread, making them produce the output file that need to 
//      return.

//............................Includes.................................//
//.....................................................................//
#include "thread.h"

//............................Functions................................//
//.....................................................................//
/*
* Function:        creat_threads
* description:     this function create the threads with the crtic function
* input:           thread function, threads parameters struct, threads handles array,
*                  number of thread, thread id array
* output:          create fail or success
*/
int creat_threads(LPTHREAD_START_ROUTINE p_start_routine, THREAD_Params* lpParam,
					HANDLE* thread_array, int thread_num, LPDWORD p_thread_id){
	for (int i = 0;i < thread_num;i++) {
		p_thread_id[i] = i;
		thread_array[i] = CreateThread(NULL,                /* default security attributes */
										0,                   /* use default stack size */
										p_start_routine,     /* thread function */
										&lpParam[i], /* argument to thread func */
										0,                   /* use default creation flags */
										&p_thread_id);        /* returns the thread id */
		if (thread_array[i]) {
			printf("Error: thread_array[%d] was failed: WinError 0x%X\n", i, GetLastError());
			return EXIT_FAILURE;
		}
	}

	return EXIT_SUCCESS;
}

/*
* Function:        write_file
* description:     this function Create a new file to share with all Threads
* input:           outfile_path
* output:          create fail or success
*/
int open_file(char* file_path) {
	HANDLE* h_file = NULL;

	h_file = CreateFileA(file_path,                // name of the write
						GENERIC_WRITE,                // open for writing
						FILE_SHARE_WRITE,             // share file for write
						NULL,                         // default security
						CREATE_ALWAYS,                // create new file always
						FILE_ATTRIBUTE_NORMAL,        // normal file
						NULL);                        // no attr. template

	if (h_file == INVALID_HANDLE_VALUE) {
		printf("Error: CreateFileA was failed: WinError 0x%X\n", GetLastError());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}


/*
* Function:        write_file
* description:     this function Create a new file to share with all Threads
* input:           outfile_path
* output:          create fail or success
*/
HANDLE* write_file(char* outfile_path) {
	HANDLE* h_file = NULL;

	h_file = CreateFileA(outfile_path,                // name of the write
		GENERIC_WRITE,                // open for writing
		FILE_SHARE_WRITE,             // share file for write
		NULL,                         // default security
		OPEN_ALWAYS,                // one file always
		FILE_ATTRIBUTE_NORMAL,  // normal file
		NULL);                  // no attr. template

	return h_file;
}

/*
* Function:        write_file
* description:     this function Create a new file to share with all Threads
* input:           outfile_path
* output:          create fail or success
*/
HANDLE* read_file(char* infile_path) {
	HANDLE* h_file = NULL;

	h_file = CreateFileA(infile_path,                // name of the write
						GENERIC_READ,                // open for writing
						FILE_SHARE_READ,             // share file for write
						NULL,                         // default security
						CREATE_ALWAYS,                // create new file always
						FILE_ATTRIBUTE_NORMAL,  // normal file
						NULL);                  // no attr. template

	return h_file;
}

/*
* Function:        init_threads_array
* description:     this function allocate memory and create threads array
* input:           number of threads, handle to thread array
* output:          none
*/
void init_threads_array(int thread_num, HANDLE* p_thread_handles) {
	for (int i = 0; i < thread_num; i++) {
		p_thread_handles[i] = NULL;
	}
}

/*
* Function:        SemaphoreWaitCheck
* description:     this function handles the wait time of the semaphore
* input:           semphore handle, handle to thread array, thread parameters array, number of threads 
* output:          exitcode
*/
int SemaphoreWaitCheck(HANDLE* semapohre, HANDLE* p_thread_handles, THREAD_Params* lpParam, int thread_num) {
	int			retVal = EXIT_SUCCESS;
	BOOL		term;
	DWORD		wait_code, exit_code;
	
	wait_code = WaitForMultipleObjects(thread_num,
										p_thread_handles,
										TRUE,
										TIMEOUT_IN_MILLISECONDS);
	if (wait_code != WAIT_OBJECT_0) {
		if (wait_code == WAIT_FAILED) {
			printf("Error: WaitForMultipleObjects was failed: WinError 0x%X\n", GetLastError());
		}
		for (int i = 0; i < thread_num; i++) {
			wait_code = WaitForSingleObject(p_thread_handles[i],
											THREAD_WAIT_TIME_IN_MILISECONDS);
			if (wait_code != WAIT_OBJECT_0) {
				if (wait_code == WAIT_FAILED) {
					printf("Error: WaitForMultipleObjects was failed: WinError 0x%X\n", GetLastError());
				}
				return EXIT_FAILURE;
			}
			
		}
		retVal = EXIT_FAILURE;
	}
	for (int i = 0; i < thread_num; i++) {
		term = GetExitCodeThread(p_thread_handles[i], &exit_code);
		if (!term) {
			printf("Error: GetExitCodeThread was failed: WinError 0x%X\n", GetLastError());
		}
		if (!exit_code) {
			retVal = EXIT_FAILURE;
		}
	}
	return retVal;
}