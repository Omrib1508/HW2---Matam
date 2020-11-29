/////////////////////////////////////////////////////////////////////////
///////////////////////// encrypt_n_decrypt.c ///////////////////////////
/////////////////////////////////////////////////////////////////////////

//info: This file contain all the functions which responseblle on the
//      the encryption and decryption of the Caesar code.

//............................Includes.................................//
//.....................................................................//
#include "encrypt_n_decrypt.h"

//...........................Functions.................................//
//.....................................................................//
/*
* Function:        encrpyt_n_decrypt_letter
* description:     this function encrpyt or decrypt letter in Ceasar code
* input:           Ceasar sturct, flag argumnet from user
* output:          none
*/
char encrpyt_n_decrypt_letter(int key, char letter) {
	if (letter >= A && letter <= Z) {
		return(A + (letter - A - key) % 26);
	}
	else if (letter >= 'a' && letter <= 'z') {
		return(a + (letter - a - key) % 26);
	}
	else if (letter >= ZERO && letter <= NINE) {
		return( ZERO + (letter - ZERO - key) % 10);
	}
	else
		return letter;
}

/*
* Function:        encrpyt_n_decrypt_letter
* description:     this function encrpyt or decrypt letter in Ceasar code
* input:           Ceasar sturct, flag argumnet from user
* output:          none
*/
void encrpyt_n_decrypt_line(char* line,int line_size, int key) {
	for (int i = 0; i < line_size; i++) {
		line[i] = encrpyt_n_decrypt_letter(key, line[i]);
	}
}

/*
* Function:        encrpyt_and_decrypt_file
* description:     this function initalize the flags struct, that tell us if decrypt
*                  or descrypt
* input:           flags sturct, flag argumnet from user
* output:          none
*/
int encrpyt_and_decrypt_file(Caesar* caesar) {
	HANDLE*			semaphore = NULL;
	HANDLE*			p_thread_handles = NULL;
	LPDWORD			p_thread_ids = NULL;
	DWORD			wait_code;
	BOOL			retVal = FALSE;
	THREAD_Params*	p_thread_params;
	
	/* create semaphore */
	semaphore = CreateSemaphore(NULL,					/* Default security attributes */
								0,						/* Initial Count - no slots are full */
								caesar->thread_num,		/* Maximum Count */
								NULL);					/* un-named */
	ASSERT("CreateSemaphore", semaphore);

	/* create thread array */
	p_thread_handles = (HANDLE*)malloc(caesar->thread_num * sizeof(HANDLE));
	if (!p_thread_handles) {
		retVal = CloseHandle(semaphore);
		ASSERT("malloc", p_thread_handles);
	}
	
	/* create tread id array*/
	p_thread_ids = (LPDWORD*)malloc(caesar->thread_num * sizeof(LPDWORD));
	if (!p_thread_handles) {
		retVal = CloseHandle(semaphore);
		free(p_thread_handles);
		ASSERT("malloc", p_thread_ids);
	}
	init_threads_array(caesar->thread_num, p_thread_handles);
	
	do {
		/* allocate memory to thread parameter sturct */
		p_thread_params = (THREAD_Params*)malloc(caesar->thread_num * sizeof(THREAD_Params));
		if (!p_thread_params) { break; }

		/* open output file for write */
		retVal = open_file(caesar->output);
		if (retVal) { break; }
		
		/* split file to sectors */
		retVal = devide_file_2_sectors(caesar, p_thread_params);
		if (retVal) { break; }

		/* insert paramters to thread array */
		for (int i = 0; i < caesar->thread_num; i++) {
			p_thread_params[i].input = caesar->input;
			p_thread_params[i].output = caesar->output;
			p_thread_params[i].key = caesar->key;
		}
	

		/* create the thread array */
		retVal = creat_threads(encrpyt_n_decrypt_sector, p_thread_params, p_thread_handles\
			, caesar->thread_num, p_thread_ids);
		if (retVal) { break; }

		/* wait for all threads to finish */
		retVal = SemaphoreWaitCheck(semaphore, p_thread_handles, p_thread_params, caesar->thread_num);
	} while (TRUE);
	
	/* close handles of thread and semaphore */
	for (int i = 0; i < caesar->thread_num; i++) {
		retVal = CloseHandle(p_thread_handles[i]);
		if (retVal) { ASSERT("CloseHandle", p_thread_handles[i]); }	
	}
	retVal = CloseHandle(semaphore);
	if (retVal) { ASSERT("CloseHandle", semaphore); }

	/* free memory that allocate */
	free(p_thread_handles);
	ASSERT("free", p_thread_handles);

	free(p_thread_ids);
	ASSERT("free", p_thread_ids);

	free(p_thread_params);
	ASSERT("free", p_thread_params);

	return EXIT_SUCCESS;
}

/*
* Function:        encrpyt_n_decrypt_sector
* description:     this function initalize the thread function
* input:           semaphore handle, Thread Parameters
* output:          Thread function
*/
DWORD WINAPI encrpyt_n_decrypt_sector(HANDLE* semapohre, THREAD_Params* lpParam) {
	HANDLE					h_input = NULL;
	HANDLE					h_output = NULL;
	char*					line = NULL;
	DWORD					waitcode;
	int						start_p, end_p, len_p;
	BOOL					retVal;
	
	waitcode = WaitForSingleObject(semapohre, INFINITE);
	if (waitcode != WAIT_OBJECT_0) {
		printf("Error: ending program. Last Error = 0x%x\n", GetLastError());
		ExitThread(THREAD__CODE_NULL_PTR);
	}

	start_p = lpParam->start;
	end_p = lpParam->end;
	len_p = end_p - start_p;
	
	do {
		/* Stop Conditions */
		if (!lpParam->input || !lpParam->output) { 
			break;
		}
		if (start_p < 0 || end_p < 0 || len_p < 0) {
			break;
		}

		/* open input file and read */
		h_input = read_file(lpParam->input);
		if (h_input == INVALID_HANDLE_VALUE) {
			break;
		}
		/* open output file and write*/
		h_output = write_file(lpParam->input);
		if (h_output == INVALID_HANDLE_VALUE) {
			break;
		}

		/*check if start point exist in input and output file*/
		if (SetFilePointer(h_input, start_p, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER) {
			break;
		}
		if (SetFilePointer(h_output, start_p, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER) {
			break;
		}
		
		/* allocate line memory*/
		line = (char*)malloc(len_p * sizeof(char));
		ASSERT("malloc", line);

		/* read from file*/
		retVal = ReadFile(h_input, line, len_p, NULL, NULL);
		if (retVal) { 
			break;
		}
		encrpyt_n_decrypt_line(line, len_p, lpParam->key);

		retVal = WriteFile(h_output, line, len_p, NULL, NULL);
		if (retVal) {
			break;
		}
	} while (TRUE);

	free(line);

	if (h_input) {
		retVal = CloseHandle(h_input);
		if (!retVal) {
			ExitThread(THREAD__CODE_NULL_PTR);
		}
	}
	if (h_output) {
		retVal = CloseHandle(h_output);
		if (!retVal) {
			ExitThread(THREAD__CODE_NULL_PTR);
		}
	}
	retVal = ReleaseSemaphore(semapohre,
								1,		/* Signal that exactly one cell was filled */
								NULL);
	if (!retVal) {
		ExitThread(THREAD__CODE_NULL_PTR);
	}
	ExitThread(THREAD__CODE_SUCCESS);
}