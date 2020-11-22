/////////////////////////////////////////////////////////////////////////
/////////////////////////////// Ceasar.c ////////////////////////////////
/////////////////////////////////////////////////////////////////////////


//info: This file contain all the function bodies. All this functions are
//      helping to build the Cease process, and olso create the threads.

//............................Includes.................................//
//.....................................................................//
#include "Ceasar.h"
#include "hard_coded_data.h"



int main(int argc, char* argv[]) {
    Files*            files = NULL;

    files = (Files*) malloc(sizeof(Files));
    if (!files) {
        printf("Error: memory doesn't allocote correctly\n");
        exit(EXIT_FAILURE);
    }

    if (argc != ARGUMENT) {
        printf("Error: invalid number of arguments(%d instead of %d)\n", (argc - 1), ARGUMENT);
        exit(EXIT_FAILURE);
    }
    else {
        files->input = fopen(argv[ARGUMENT - 5], "r");
        //files->input=fopen("/Users/estellemiara/Desktop/Université TAU/סמסטר 1 שנה ד׳/מבוא לתכנות מערכות /Exercice 2/top_secret_file.txt","r");
        file_check(files->input);
        files->output = fopen(argv[ARGUMENT - 1], "w");
        //files->output=fopen("/Users/estellemiara/Desktop/Université TAU/סמסטר 1 שנה ד׳/מבוא לתכנות מערכות /Exercice 2/decrypted.txt","w");
        file_check(files->output);
        files->key=*argv[ARGUMENT -4];
        files->thread=*argv[ARGUMENT-3];
        files->type=*argv[ARGUMENT - 2];
        
        //prinnt to file
        print_to_file(files);
        
        // exit and free memory
        exit_prog(files);
    }

    return EXIT_SUCCESS;
}
