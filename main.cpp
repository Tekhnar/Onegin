#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <windows.h>
#include <sys\stat.h>

#include "ClearingText.cpp"
#include "main.h"
#include "Functions.cpp"


//------File which we read----------//
const char* NAME_FILE = "Onegin.txt";
//----------------------------------//


int main()
{
    printf("\"Onegin\"\n");
    printf("Line sorting program\n");
    printf("with text cleaning. \n");
    printf("Created by Michail Kaskov.\n\n");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);


    struct stat buff_stat; //kill!
    if (stat (NAME_FILE, &buff_stat)){
        printf("Don't found file \"Onegin\" with text!\n");
        assert(stat(NAME_FILE, &buff_stat));
    }

    long length = buff_stat.st_size;
    //----------------------------------------------------//
    // buff_stat.st_size - (int), but
    // length - (long), because it is blanks for the future.
    // If the length is longer, then we will use ftell()
    //----------------------------------------------------//


    FILE* file = fopen(NAME_FILE, "rb");
    if (file == NULL) {
        printf("Can't open or found file!\n");
        assert(file != NULL);
    }

    //-------------------------------------------------//
    // If the length is longer, then we will use ftell()

    // long length = IsLength(file);

    //-------------------------------------------------//

    unsigned char* buffer = Buffering(length, file);

    long newlength = ClearingText(buffer, length);
    buffer = (unsigned char*) realloc(buffer, newlength);


    long num_enter = HowEnter(buffer, newlength);
    num_enter++; // because has +1 string

    FILE* newfile = fopen("Onegin_clear.txt", "w+");
    fwrite(buffer, sizeof(unsigned char),newlength, newfile);


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
    printf("Writing - OK\n");
    printf("Work is done!");
    free(buffer);
    fclose(sortfile);
    fclose(newfile);
    fclose(file);

    return 0;
}
