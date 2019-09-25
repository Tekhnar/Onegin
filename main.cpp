#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <windows.h>
#include <sys\stat.h>

#include "ClearingText.cpp"
#include "main.h"
#include "Functions.cpp"


//------File which we read----------//
//const char* NAME_FILE = "Onegin.txt";
//----------------------------------//


int main(int num_arg, char *poin_arg[])
{
    printf("%s\n", poin_arg[2]);
    printf("\"Onegin\"\n");
    printf("Line sorting program\n");
    printf("with text cleaning. \n");
    printf("Created by Michail Kaskov.\n\n");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    long num_symb_name_file = 0;
    char *name_file = SearchText(num_arg, poin_arg, &num_symb_name_file);


    struct stat buff_stat = {};
    if (stat (name_file, &buff_stat)){
        printf("Don't found file with text!\n");
        assert(stat(name_file, &buff_stat));
    }

    long length = buff_stat.st_size;
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

    FILE* clearfile = fopen("Onegin_clear.txt", "w+");

    //-------------------------------------------------//
    // If the length is longer, then we will use ftell()

    // long length = ItLength(file);

    //-------------------------------------------------//
    long newlength = 0;
    long num_enter = 0;
    unsigned char* buffer = WordProcessing(length, &newlength, &num_enter, file, clearfile);


//    unsigned char* buffer = Buffering(length, file);
//
//    long newlength = ClearingText(buffer, length);
//    buffer = (unsigned char*) realloc(buffer, newlength);
//
//
//    long num_enter = HowEnter(buffer, newlength);
//    num_enter++; // because has +1 string
//
//    fwrite(buffer, sizeof(unsigned char),newlength, clearfile);
//
//
    struct pointer_buffer strings[num_enter];
    FillStruct(strings, buffer, newlength, num_enter);


    FILE* sortfile = fopen("Onegin_sort.txt", "w+");

    QuickSort(strings, 0, (num_enter - 1),  Compar);
    Writing(sortfile, strings, num_enter);

    fputc('\n', sortfile);

    QuickSort(strings, 0, (num_enter - 1),  ComparRev);
    Writing(sortfile, strings, num_enter);

    buffer[newlength - 1] = '\0';
    fputc('\n', sortfile);

    fwrite(buffer, sizeof(unsigned char), newlength, sortfile);
    if (logs == 1) printf("Writing - OK\n");
    printf("Work is done!");
    free(buffer);
    fclose(sortfile);
    fclose(clearfile);
    fclose(file);
    getchar();

    return 0;
}
