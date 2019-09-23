//----------------MACRO------------------///
#define FlagsOFF_macro()\
    if (flag_enter == 1) flag_enter = 0;\
        if (flag_3point == 1) { \
            flag_3point = 0;\
            flag_second_3point = 0;\
        }\
        if (flag_space == 1) {\
            flag_space = 0;\
            flag_second_space = 0;\
        }\
        flag_last_3point = 0
//----------------MACRO------------------///


long ClearingText(unsigned char* buffer, long lenght){
    assert(buffer != 0);
    assert(lenght > 0);

    bool
    flag_space  = 0,
    flag_enter  = 0,
    flag_first_chapter = 0,
    flag_second_chapter = 0,
    flag_second_space = 0,
    flag_marker = 0,
    flag_3point = 0,
    flag_second_3point = 0,
    flag_last_3point = 0,
    flag_write  = 1;

    long
    newtext = 0,
    num_first_chapter = 0;

    for (long text = 0; text < lenght; text++){
        if (flag_marker == 0 || buffer[text] == ']')
        switch (buffer[text]){

        case '\t':case '\0':
            newtext--;
            flag_write = 0;

            FlagsOFF_macro();
            break;

        case '\r':
            newtext--;
            flag_write = 0;
            break;

        case '\n':
            if (flag_enter == 0){
                flag_enter = 1;
            } else {
                newtext--;
                flag_write = 0;
            }

            if (flag_last_3point == 1){
                flag_last_3point = 0;
                newtext--;
                flag_write = 0;
            }

            if (flag_first_chapter == 1){
                newtext -= (text - num_first_chapter);
                flag_first_chapter = 0;
                flag_write = 0;
            }

            if (flag_3point == 1) {
                flag_3point = 0;
                flag_second_3point = 0;
            }
            if (flag_space == 1) {
                flag_space = 0;
                flag_second_space = 0;
            }
            break;

        case ' ': case 160: // it is space
            if (flag_space == 0){
                flag_space = 1;
            } else {
                if (flag_second_space == 0){
                    newtext--;
                    flag_second_space = 1;
                }
                newtext--;
                flag_write = 0;
            }

            if (flag_enter == 1) flag_enter = 0;
            if (flag_3point == 1) {
                flag_3point = 0;
                flag_second_3point = 0;
            }
            flag_last_3point = 0;
            break;

        case 133: // it is '…'
            if (flag_3point == 0){
                flag_3point = 1;
            } else {
                if (flag_second_3point == 0){
                    newtext--;
                    flag_second_3point = 1;
                }
                newtext--;
                flag_write = 0;
                flag_last_3point = 1;
            }


            if (flag_enter == 1) flag_enter = 0;
            if (flag_space == 1) {
                flag_space = 0;
                flag_second_space = 0;
            }
            break;

        case '[':
            flag_marker = 1;

            FlagsOFF_macro();
            break;

        case ']':
            flag_marker = 0;
            newtext--;
            flag_write = 0;

            FlagsOFF_macro();
            break;

        default:
            if (buffer[text] == 'I' || buffer[text] == 'V' || buffer[text] == 'X' || buffer[text] == 'L'){
                if (flag_first_chapter == 0){
                    flag_first_chapter = 1;
                    num_first_chapter = text;
                } else {
                    if (flag_second_chapter == 0){
                        flag_second_chapter = 1;
                    }
                }
            } else if (buffer[text] != '.' && buffer[text] != 160){
                flag_first_chapter = 0;
                flag_second_chapter = 0;
            }

            FlagsOFF_macro();
            break;
        }

        if (flag_marker == 1){
            newtext--;
            flag_write = 0;
        }
        if (flag_write == 1 && newtext != text) buffer[newtext] = buffer[text];
        newtext++;
        flag_write = 1;

    }
    buffer[newtext] = '\n';

    return newtext;
}
