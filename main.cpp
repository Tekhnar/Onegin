#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <windows.h>
#include <sys\stat.h>

#include "ClearingText.cpp"
#include "main.h"
#include "Functions.cpp"



int main(int num_arg, char *poin_arg[])
{
   // printf("%s\n", poin_arg[1]);
    printf("\"Onegin\"\n");
    printf("Line sorting program\n");
    printf("with text cleaning. \n");
    printf("Created by Michail Kaskov.\n\n");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    long num_symb_name_file = 0;
    char *name_file = SearchText(num_arg, poin_arg, &num_symb_name_file);


//    struct stat buff_stat = {};
//    if (stat (name_file, &buff_stat)){
//        printf("Don't found file with text!\n");
//        assert(stat(name_file, &buff_stat));
//    }
//
//    long length = buff_stat.st_size;
    //----------------------------------------------------//
    // buff_stat.st_size - (int), but
    // length - (long), because it is blanks for the future.
    // If the length is longer, then we will use ftell()
    //----------------------------------------------------//


    FILE* file = fopen(name_file, "rb");
    if (file == NULL) {
        printf("Can't open or found file!\n");
        assert(file != NULL);
    }

    FILE* sortfile  = fopen("Onegin_sort.txt" , "w+");

    //-------------------------------------------------//
    // If the length is longer, then we will use ftell()
    //-------------------------------------------------//

    long newlength = 0;
    long num_enter = 0;
    struct pointer_buffer* strings = NULL;
    unsigned char* buffer = WordProcessing(&newlength, &num_enter, file, &strings);
    //printf("%p\n", strings);

    QuickSort(strings, 0, (num_enter - 1),  Compar);
    Writing(sortfile, strings, num_enter);
    fputc('\n', sortfile);

    QuickSort(strings, 0, (num_enter - 1),  ComparRev);
    Writing(sortfile, strings, num_enter);
    buffer[newlength - 1] = '\0';
    fputc('\n', sortfile);

    fwrite(buffer, sizeof(unsigned char), newlength, sortfile);

    if (Logs == 1) printf("Writing - OK\n\n");
    printf("The work is done!");

    free(strings);
    free(buffer);
    fclose(sortfile);
    fclose(file);
    getchar();

    return 0;
}
