/////////////////////////////////////////////////////////////////////////
/////////////////////////////// Ceasar.c ////////////////////////////////
/////////////////////////////////////////////////////////////////////////


//info: This file contain all the function bodies. All this functions are
//      helping to build the Cease process, and olso create the threads.

//............................Includes.................................//
//.....................................................................//
#include "Ceasar.h"
#include "hard_coded_data.h"

extern int errno;
//...........................Functions.................................//
//.....................................................................//
//...........................Functions.................................//
//.....................................................................//

/*
* Function:        initialize
* description:     the function initialize the files string
* input:           files size
* output:          files string
*/
void initialize_str(Files *files, char letter){
    int num, out, chiffre;
    if (letter>='A' && letter<='Z') {
        num=(int)letter;
        chiffre=A+files->key-48;
        out=A+(letter-A-files->key+48)%26;
        fprintf(files->output,"%c", (char)out);
    }
    else if (letter>='a' && letter<='z') {
        out=a+(letter-a-files->key+48)%26;
        fprintf(files->output,"%c", (char)out);

    }
    else if (letter>='0'&& letter<='9') {
        out=ZERO+(letter-ZERO-files->key+48)%10;
        fprintf(files->output,"%c", (char)out);

    }
    else if (letter=='\n'){
        fprintf(files->output, "\n");
    }
    else{
        if (letter!=EOF) {
            fprintf(files->output, "%c", letter);
            printf("%c", letter);
        }
    }

}

/*
* Function:        print to file
* description:     the function prints the string to the output file
* input:           files struct, files string
* output:          none
*/
void print_to_file(Files *files){
    char* files_str=NULL;
    char letter;
    files_str = (char*)malloc(sizeof(Files));
    if (!files_str) {
            printf("Error: memory doesn't allocote correctly\n");
            exit(EXIT_FAILURE);
    }
    while (!feof(files->input)) {
        
        letter = fgetc(files->input);
        initialize_str(files,letter);
    }
}

/*
* Function:        file_check
* description:     check if file open correctlly
* input:           file
* output:          none
*/
void file_check(FILE* file){
    int                errnum;
    
    if (!file) {
        errnum = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error opening file: %s\n", strerror(errnum));
        
        exit(EXIT_FAILURE);
    }
}

/*
* Function:        exit_prog
* description:     this function close the program, close the file and free memory
* input:           input file, output file, forest srtruct
* output:          none
*/
void exit_prog(Files* files) {
    /* Close files*/
    fclose(files->input);
    fclose(files->output);
    //free memory

}

