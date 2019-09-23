#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED


long IsLength(FILE* file);
long HowEnter(unsigned char* buffer, long newlength);
long ClearingText(unsigned char* buffer, long lenght);
void FillStruct(struct pointer_buffer strings[], unsigned char buffer[], long newlength, long num_enter);

struct pointer_buffer {
    unsigned char* pointer;
    long length;
};

#endif // MAIN_H_INCLUDED
