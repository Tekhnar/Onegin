//----------------MACRO------------------///
#define FlagsOFF_macro()\
    if (is_enter == 1) is_enter = 0;\
        if (is_3point == 1) { \
            is_3point = 0;\
            is_second_3point = 0;\
        }\
        if (is_space == 1) {\
            is_space = 0;\
            is_second_space = 0;\
        }\
        is_last_3point = 0
//----------------MACRO------------------///


long ClearingText(unsigned char* buffer, long lenght){
    assert(buffer != 0);
    assert(lenght > 0);

    bool
        is_space  = 0,
        is_enter  = 0,
        is_first_chapter = 0,
        is_second_chapter = 0,
        is_second_space = 0,
        is_marker = 0,
        is_3point = 0,
        is_second_3point = 0,
        is_last_3point = 0,
        is_write  = 1;

    long
        newtext = 0,
        num_first_chapter = 0;

    for (long text = 0; text < lenght; text++){
        if (is_marker == 0 || buffer[text] == ']')
        switch (buffer[text]){

        case '\t':case '\0':
            newtext--;
            is_write = 0;

            FlagsOFF_macro();
            break;

        case '\r':
            newtext--;
            is_write = 0;
            break;

        case '\n':
            if (is_enter == 0){
                is_enter = 1;
            } else {
                newtext--;
                is_write = 0;
            }

            if (is_last_3point == 1){
                is_last_3point = 0;
                newtext--;
                is_write = 0;
            }

            if (is_first_chapter == 1){
                newtext -= (text - num_first_chapter);
                is_first_chapter = 0;
                is_write = 0;
            }

            if (is_3point == 1) {
                is_3point = 0;
                is_second_3point = 0;
            }
            if (is_space == 1) {
                is_space = 0;
                is_second_space = 0;
            }
            break;

        case ' ': case 160: // it is space
            if (is_space == 0){
                is_space = 1;
            } else {
                if (is_second_space == 0){
                    newtext--;
                    is_second_space = 1;
                }
                newtext--;
                is_write = 0;
            }

            if (is_enter == 1) is_enter = 0;
            if (is_3point == 1) {
                is_3point = 0;
                is_second_3point = 0;
            }
            is_last_3point = 0;
            break;

        case 133: // it is '…'
            if (is_3point == 0){
                is_3point = 1;
            } else {
                if (is_second_3point == 0){
                    newtext--;
                    is_second_3point = 1;
                }
                newtext--;
                is_write = 0;
                is_last_3point = 1;
            }


            if (is_enter == 1) is_enter = 0;
            if (is_space == 1) {
                is_space = 0;
                is_second_space = 0;
            }
            break;

        case '[':
            is_marker = 1;

            FlagsOFF_macro();
            break;

        case ']':
            is_marker = 0;
            newtext--;
            is_write = 0;

            FlagsOFF_macro();
            break;

        default:
            if (buffer[text] == 'I' || buffer[text] == 'V' || buffer[text] == 'X' || buffer[text] == 'L'){
                if (is_first_chapter == 0){
                    is_first_chapter = 1;
                    num_first_chapter = text;
                } else {
                    if (is_second_chapter == 0){
                        is_second_chapter = 1;
                    }
                }
            } else if (buffer[text] != '.' && buffer[text] != 160){
                is_first_chapter = 0;
                is_second_chapter = 0;
            }

            FlagsOFF_macro();
            break;
        }

        if (is_marker == 1){
            newtext--;
            is_write = 0;
        }
        if (is_write == 1 && newtext != text) buffer[newtext] = buffer[text];
        newtext++;
        is_write = 1;

    }
    buffer[newtext] = '\n';

    return newtext + 1;
}
