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
#include "Ceasar.h"
#include "hard_coded_data.h"

//...........................Functions.................................//
//.....................................................................//
char encrpyt_and_decrypt(Ceasar* ceasar, char letter);

int create_file(char* outfile_path);

#endif // !ENCRYPT_N_DECRYPT_H