#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED


long IsLength(FILE* file);
long HowEnter(unsigned char* buffer, long newlength);
long ClearingText(unsigned char* buffer, long lenght);
void FillStruct(struct pointer_buffer *strings, unsigned char *buffer, long newlength, long num_enter);

void QuickSort(struct pointer_buffer *strings, long left, long right, int (*cmp)(struct pointer_buffer left, struct pointer_buffer right));
int Compar(struct pointer_buffer left, struct pointer_buffer right);
int ComparRev(struct pointer_buffer left, struct pointer_buffer right);
void Swap(struct pointer_buffer *strings, long left, long right);
int ConvertToMyChar (unsigned char in);
int IsNotLetter(unsigned char input);

struct pointer_buffer {
    unsigned char* pointer;
    long length;
};

#endif // MAIN_H_INCLUDED
