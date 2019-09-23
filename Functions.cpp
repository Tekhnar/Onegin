long IsLength(FILE* file){
    assert(file != NULL);
    fseek(file, 0, SEEK_END);
    long result = ftell(file);
    fseek(file, 0, SEEK_SET);

    return result;
}
long HowEnter(unsigned char* buffer, long newlength){
    long num_enter = 0;
    for (int i = 0; i < newlength; i++){
        if (buffer[i] == '\n') num_enter++;
    }
    return num_enter;
}
void FillStruct(struct pointer_buffer strings[], unsigned char buffer[], long newlength, long num_enter){
    int elem_n = 1;
    strings[0].pointer = &buffer[0];
    for (int symbol = 1; symbol < newlength; symbol++){
        if (buffer[symbol] == '\n') {
            strings[elem_n].pointer = &buffer[symbol];
            strings[elem_n-1].length = strings[elem_n].pointer - strings[elem_n-1].pointer;
            elem_n++;
        }
        if (elem_n == num_enter) {
            strings[elem_n - 1].length = &buffer[newlength - 1] - strings[elem_n-1].pointer + 1;
            break;
        }
    }
}

void QuickSort(const int* arr, int many/*, int (*c)(const void* , const void*)*/);
int Compar(int left, int right);
void Swap(int* left, int* right);

void QuickSort(int* arr, int many/*, int (*c)(const int* , const int*)*/){
    //assert(arr == 0);
    int right = many;
    int left = 0;
    int mid = arr[(many-1)/2];
    printf("mid - %d\n", mid);

    do {
        while (arr[left] < mid){
            printf("arr[left] - %d left - %d\n", arr[left], left);
            left++;
        }
        while (mid < arr[right]) {
                right--;
            printf("arr[right] - %d right - %d\n", arr[right], right);
        }

        if (left <= right) {
                int temp = arr[left];
                arr[left] = arr[right];
                arr[right] = temp;
            //Swap(&arr[left], &arr[right]);
            left++;
            right--;
        }
    } while (left <= right);
    printf("%d %d\n", left, right);
    assert(left != right);
    if (right > 0) QuickSort(arr, right);
    if (left < many) QuickSort(arr + left, (many - 1) - left);
    for (int i = 0; i < many; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}


int Compar(int left,int right){
    if (left > right) return 1;
    else return 0;
}

void Swap(int* left, int* right){
    int *temp;
    *temp = *right;
    *right = *left;
    *left = *temp;
}
