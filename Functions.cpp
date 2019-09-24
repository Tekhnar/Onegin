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
void FillStruct(struct pointer_buffer *strings, unsigned char buffer[], long newlength, long num_enter){
    int elem_n = 1;
    strings[0].pointer = &buffer[0];
    for (int symbol = 1; symbol < newlength; symbol++){
        if (buffer[symbol] == '\n') {
            strings[elem_n].pointer = &buffer[symbol + 1];
            strings[elem_n-1].length = strings[elem_n].pointer - strings[elem_n-1].pointer;
            elem_n++;
        }
        if (elem_n == num_enter) {
            strings[elem_n - 1].length = &buffer[newlength - 1] - strings[elem_n-1].pointer + 1;
            break;
        }
    }
}


void QuickSort(struct pointer_buffer *strings, long left, long right){
    assert(strings != 0);

    if (left >= right) return;
    Swap(strings, left, (right + left)/2);
    long last = left;
    for (long i = left + 1; i <= right; i++){
        if (Compar(strings[i] ,strings[left])) Swap(strings, ++last, i);
    }
    Swap(strings, left, last);
    QuickSort(strings, left, last - 1);
    QuickSort(strings, last + 1, right);

//    int i, last;
//    //void swap(int v[], int i, int j);
//    if (left >= right) /* ничего не делается, если */
//        return; /* в массиве менее двух элементов */
//    swapp(v, left, (left + right)/2); /* делящий элемент */
//    last = left; /* переносится в v[0] */
//    for(i = left+1; i <= right; i++) /* деление на части */
//        if (v[i] < v[left])
//            swapp(v, ++last, i);
//    swapp(v, left, last); /* перезапоминаем делящий элемент */
//    QuickSort(v, left, last-1);
//    QuickSort(v, last+1, right);

    /*
    assert(strings[0].length != 0);
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
    //assert(left != right);
    if (right > 0) QuickSort(strings, right);
    if (left < many) QuickSort(&strings[left], (many - 1) - left);
//    for (int i = 0; i < many; i++){
//        printf("%d ", arr[i]);
//    }
//    printf("\n");
    */
//    long i, last;
//    if (left >= right) /* ничего не делается, если */
//        return; /* в массиве менее двух элементов */
//    Swap(v, left, (left + right)/2); /* делящий элемент */
//    last = left; /* переносится в v[0] */
//    for(i = left + 1; i <= right; i++) /* деление на части */
//        if (v[i] < v[left])
//            Swap(v, ++last, i);
//    Swap(v, left, last); /* перезапоминаем делящий элемент */
//    QuickSort(v, left, last-1);
//    QuickSort(v, last+1, right);
}


int Compar(struct pointer_buffer left, struct pointer_buffer right){

    long minim = left.length +1;
    if (right.length < minim) minim = right.length;
    //printf("Is right.pointer[j] - %p \n", right.pointer);
    long j = 0;
    for (long i = 0; (i < minim) && (j < minim); i++){

        while(IsNotLetter(left.pointer[i]) && (i < minim)) i++;
        //printf("Is right.pointer[j] - %c \n", left.pointer[i]);
        while(IsNotLetter(right.pointer[j]) && (j < minim)) j++;

//        printf("First char - %c Second char - %c\n", left.pointer[i], *right.pointer[i] );
        if (ConvertToMyChar(left.pointer[i]) < ConvertToMyChar(right.pointer[j])) return 1;
        if (ConvertToMyChar(left.pointer[i]) > ConvertToMyChar(right.pointer[j])) return 0;
        j++;
    }
    if (right.length > minim) return 1;

    return 0;
    //else return 0;
}

void Swap(struct pointer_buffer *strings, long left, long right){
    struct pointer_buffer temp;
   // printf("lenght before %d ", strings[left].pointer);
    temp.length = strings[left].length;
    temp.pointer = strings[left].pointer;

    strings[left].length = strings[right].length;
    strings[left].pointer = strings[right].pointer;

    strings[right].length = temp.length;
    strings[right].pointer = temp.pointer;


    //strings[left] = strings[right];
    //strings[right] = temp;
    //printf("lenght after %d\n", strings[left].pointer);
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

/*int IsNotLetter(unsigned char input){
    if ((input <= 47)
        || (input >= 58 && input <= 64)
        || (input >= 91 && input <= 96)
        || (input >= 123 && input <= 167)
        || (input >= 169 && input <= 183)
        || (input >= 185 && input <= 191)) return 1;
            else return 0;
}*/

int IsNotLetter(unsigned char input){
    //assert(input == 177);
    if (   (input >= 65 && input <= 90)
        || (input >= 192 && input <= 197)
        || (input >= 224 && input <= 229)

        || (input == 168 || input == 184)
        || (input >= 198 && input <= 223)
        || (input >= 230 && input <= 255)) return 0;
            else return 1;
}
