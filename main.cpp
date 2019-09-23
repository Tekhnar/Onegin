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
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);


    struct stat buff_stat; //kill!
    if (stat (NAME_FILE, &buff_stat)){
        printf("Don't found file!\n");
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

    unsigned char* buffer = (unsigned char*) calloc(length, sizeof(unsigned char));
    long read = fread(buffer, sizeof(unsigned char), length, file);
    if (read == length){
        printf("Reading - OK\n");
    } else {
        printf("ERROR in reading\n");
        assert(read == length);
    }


    long newlength = ClearingText(buffer, length);
    buffer = (unsigned char*) realloc(buffer, newlength);
    long num_enter = HowEnter(buffer, newlength);
    if (buffer == NULL){
        printf("ERROR in realloc()!\n");
        assert(buffer != NULL);
    }

    FILE* newfile = fopen("Onegin_clear.txt", "w+");
    fwrite(buffer, sizeof(unsigned char),newlength, newfile);
    fclose(newfile);

    struct pointer_buffer strings[num_enter];
    FillStruct(strings, buffer, newlength, num_enter);

    int arr[6] = {1, 10, 9, 8, 7, 6};
    QuickSort(arr, 6);
//    for (int i = 0; i < 6; i++){
//        printf("%d ", arr[i]);
//    }
    printf("num_enter = %ld", num_enter);
    free(buffer);
    fclose(file);
    return 0;
}
