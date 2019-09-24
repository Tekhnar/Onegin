#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

long ClearingText(unsigned char* buffer, long lenght);

long IsLength(FILE* file);
long HowEnter(unsigned char* buffer, long newlength);
void FillStruct(struct pointer_buffer *strings, unsigned char *buffer, long newlength, long num_enter);

void QuickSort(struct pointer_buffer *strings, long left, long right, int (*cmp)(struct pointer_buffer left, struct pointer_buffer right));
int Compar(struct pointer_buffer left, struct pointer_buffer right);
int ComparRev(struct pointer_buffer left, struct pointer_buffer right);
void Swap(struct pointer_buffer *strings, long left, long right);

int ConvertToMyChar (unsigned char in);
int IsNotLetter(unsigned char input);

unsigned char* Buffering(long length, FILE* file);
void Writing(FILE* sortfile, struct pointer_buffer *strings, long num_enter);

struct pointer_buffer {
    unsigned char* pointer;
    long length;
};

#endif // MAIN_H_INCLUDED
