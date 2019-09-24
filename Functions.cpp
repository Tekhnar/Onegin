unsigned char* Buffering(long length, FILE* file){
    unsigned char* point = (unsigned char*) calloc(length, sizeof(unsigned char));
    if (point == NULL){
        printf("ERROR in realloc()!\n");
        assert(point != NULL);
    }

    long read = fread(point, sizeof(unsigned char), length, file);
    if (read == length){
        printf("Reading - OK\n");
    } else {
        printf("ERROR in reading\n");
        assert(read == length);
    }

    return point;
}

void Writing(FILE* sortfile, struct pointer_buffer *strings, long num_enter){
    assert(sortfile != NULL);

    for (int i = 0; i < num_enter; i++){
        long write = fwrite(strings[i].pointer, sizeof(unsigned char), strings[i].length, sortfile);
        if (write != strings[i].length){
            printf("ERROR in writing in file!\n");
            assert(write == strings[i].length);
        }
    }
}

long IsLength(FILE* file){
    assert(file != NULL);

    fseek(file, 0, SEEK_END);
    long result = ftell(file);
    fseek(file, 0, SEEK_SET);

    return result;
}

long HowEnter(unsigned char* buffer, long newlength){
    assert(buffer != NULL);
    assert(newlength > 0);

    long num_enter = 0;
    for (int i = 0; i < newlength; i++){
        if (buffer[i] == '\n') num_enter++;
    }

    return num_enter;
}

void FillStruct(struct pointer_buffer *strings, unsigned char buffer[], long newlength, long num_enter){
    assert(strings != NULL);
    assert(buffer != NULL);
    assert(newlength >= 0);
    assert(newlength >= 0);

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

void QuickSort(struct pointer_buffer *strings, long left, long right, int (*cmp)(struct pointer_buffer left, struct pointer_buffer right)){
    assert(strings != NULL);
    assert(cmp != NULL);
    assert(left >= 0);

    if (left >= right) return;
    Swap(strings, left, (right + left)/2);

    long last = left;
    for (long i = left + 1; i <= right; i++){
        if ((*cmp)(strings[i] ,strings[left])) Swap(strings, ++last, i);
    }

    Swap(strings, left, last);
    QuickSort(strings, left, last - 1, cmp);
    QuickSort(strings, last + 1, right, cmp);


}

int Compar(struct pointer_buffer left, struct pointer_buffer right){
    assert(left.pointer != NULL);
    assert(right.pointer != NULL);

    long minim = left.length +1;
    if (right.length < minim) minim = right.length;

    long j = 0;
    for (long i = 0; (i < minim) && (j < minim); i++){
        while(IsNotLetter(left.pointer[i]) && (i < minim)) i++;
        while(IsNotLetter(right.pointer[j]) && (j < minim)) j++;

        if (ConvertToMyChar(left.pointer[i]) < ConvertToMyChar(right.pointer[j])) return 1;
        if (ConvertToMyChar(left.pointer[i]) > ConvertToMyChar(right.pointer[j])) return 0;
        j++;
    }
    if (right.length > minim) return 1;

    return 0;
}

int ComparRev(struct pointer_buffer left, struct pointer_buffer right){
    assert(left.pointer != NULL);
    assert(right.pointer != NULL);

    long minim = left.length +1;
    if (right.length < minim) minim = right.length;

    long j = 0;
    for (long i = 0; (i < minim) && (j < minim); i++){
        while(IsNotLetter(left.pointer[left.length - i - 1]) && (i < minim)) i++;
        while(IsNotLetter(right.pointer[right.length - j - 1]) && (j < minim)) j++;

        if (ConvertToMyChar(left.pointer[left.length - i - 1]) < ConvertToMyChar(right.pointer[right.length - j - 1])) return 1;
        if (ConvertToMyChar(left.pointer[left.length - i - 1]) > ConvertToMyChar(right.pointer[right.length - j - 1])) return 0;
        j++;
    }
    if (right.length > minim) return 1;

    return 0;
}

void Swap(struct pointer_buffer *strings, long left, long right){
    assert(strings != NULL);
    assert(left >= 0);
    assert(right >= 0);

    struct pointer_buffer temp;

    temp = strings[left];
    strings[left] = strings[right];
    strings[right] = temp;
}

int ConvertToMyChar (unsigned char in){
    int input = in;
    if (input >= 65 && input <= 90) {
        input += 32;
    }
    else if ((input >= 192 && input <= 197) || (input >= 224 && input <= 229)) { // Russian char start from 300
        input += 108;
    }
    else if (input == 168 || input == 184) {
        input = 306;
    }
    else if ((input >= 198 && input <= 223) || (input >= 230 && input <= 255)){
        input += 109;
    }

    return input;
}

int IsNotLetter(unsigned char input){
    //assert(input == 177);
    if (   (input >= 65 && input <= 90)
        || (input >= 192 && input <= 197)
        || (input >= 224 && input <= 229)

        || (input == 168 || input == 184)
        || (input >= 198 && input <= 223)
        || (input >= 230 && input <= 255))
        return 0;
        else return 1;
}
