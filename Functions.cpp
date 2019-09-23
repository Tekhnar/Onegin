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

void QuickSort(struct pointer_buffer strings[], long many/*, int (*c)(const void* , const void*)*/);
int Compar(struct pointer_buffer left, struct pointer_buffer right);
void Swap(struct pointer_buffer strings[], long left, long right);
int ConvertToMyChar (unsigned char in);
int IsNotLetter(unsigned char input);

void QuickSort(struct pointer_buffer strings[], long many/*, int (*c)(const int* , const int*)*/){
    //assert(arr == 0);
    long right = many;
    long left = 0;
    long mid = (many-1)/2;
    //printf("mid - %ld\n", mid);

    do {
        while (Compar(strings[left], strings[mid])) left++;
            //printf("arr[left] - left - %d\n", left);
        while (Compar(strings[mid], strings[right])) right--;
            //printf("arr[right] - %d right - %d\n", arr[right], right);

        if (left <= right) {
            Swap(strings, left, right);
            left++;
            right--;
        }
    } while (left <= right);
    //printf("%d %d\n", left, right);
    assert(left != right);
    if (right > 0) QuickSort(strings, right);
    if (left < many) QuickSort(&strings[left], (many - 1) - left);
//    for (int i = 0; i < many; i++){
//        printf("%d ", arr[i]);
//    }
//    printf("\n");
}


int Compar(struct pointer_buffer left, struct pointer_buffer right){

    long minim = left.length;
    if (right.length < minim) minim = right.length;

    long j = 0;
    for (long i = 0; i < minim; i++){
        while(IsNotLetter(left.pointer[i])) i++;
        while(IsNotLetter(right.pointer[j])) j++;

        if (ConvertToMyChar(left.pointer[i]) < ConvertToMyChar(right.pointer[j])) return 1;
        j++;
    }
    if (right.length > minim) return 1;

    return 0;
    //else return 0;
}

void Swap(struct pointer_buffer strings[], long left, long right){
    struct pointer_buffer temp;
   // printf("lenght before %d", strings[left].length);
    temp = strings[left];
    strings[left] = strings[right];
    strings[right] = temp;
   // printf("lenght after %d\n", strings[left].length);
}


int ConvertToMyChar (unsigned char in){
    int input = in;
    if (input >= 65 && input <= 90) {
        input += 32;
    //    return input;
    }
    else if ((input >= 192 && input <= 197) || (input >= 224 && input <= 229)) { // Russian char start from 300
        input += 108;
    //    return input;
    }
    else if (input == 168 || input == 184) {
        input = 306;
    //    return input;
    }
    else if ((input >= 198 && input <= 223) || (input >= 230 && input <= 255)){
        input += 109;
    }

    return input;

}

int IsNotLetter(unsigned char input){
    if ((input <= 47)
        || (input >= 58 && input <= 64)
        || (input >= 91 && input <= 96)
        || (input >= 123 && input <= 167)
        || (input >= 169 && input <= 183)
        || (input >= 185 && input <= 191)) return 1;
            else return 0;
}
