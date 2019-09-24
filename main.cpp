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

//    printf("buffer %c\n", buffer[newlength-7]);
//    printf("buffer %c\n", buffer[newlength-6]);
//    printf("buffer %c\n", buffer[newlength-5]);
//    printf("buffer %c\n", buffer[newlength-4]);
//    printf("buffer %c\n", buffer[newlength-3]);
//    printf("buffer %c\n", buffer[newlength-2]);
//    printf("buffer %c\n", buffer[newlength-1]);
//    printf("buffer %c\n", buffer[newlength]);

    long num_enter = HowEnter(buffer, newlength);
    if (buffer == NULL){
        printf("ERROR in realloc()!\n");
        assert(buffer != NULL);
    }

    FILE* newfile = fopen("Onegin_clear.txt", "w+");
    fwrite(buffer, sizeof(unsigned char),newlength, newfile);

    num_enter++; // because has +1 string

    struct pointer_buffer strings[num_enter];
    FillStruct(strings, buffer, newlength, num_enter);

    //printf("%d \n", strings[0].pointer[strings[0].length-1]);

    for (int j = 0; j < num_enter - 1; j++){
//        for (unsigned char* i = strings[j].pointer; i <  (strings[j+1].pointer); i++){
//            if (*i != 0){
//                printf("Error,  not '\0' in string - %d", j);
//            }
//        }
        if (strings[j].pointer[0] == 10){
                printf("Error,  not '10' in string - %d\n", j);
                assert(strings[j].pointer[0] != 10);
            }
        //printf("%ld \n", strings[i].length);
    }


    printf("\n");

    QuickSort(strings, 0, (num_enter - 1) );
    for (unsigned char* i = strings[0].pointer; i <  (strings[0].pointer + 7); i++){
            printf("%d ", *i);
        }
    FILE* sortfile = fopen("Onegin_sort.txt", "w+");

    for (int i = 0; i < num_enter; i++){
        fwrite(strings[i].pointer, sizeof(unsigned char), strings[i].length, sortfile);
    }

//    for (int i = 0; i < num_enter; i++){
//        printf("%ld \n", strings[i].length);
//    }
//    for (unsigned char* i = strings[num_enter-1].pointer; i <  (strings[num_enter-1].pointer+7); i++){
//        printf("%d ", *i);
//    }
    //int arr[6] = {1, 10, 9, 8, 7, 6};
//    QuickSort(strings, num_enter);

    printf("num_enter = %ld", num_enter);
    fclose(sortfile);
    fclose(newfile);
    free(buffer);
    fclose(file);
    return 0;
}
