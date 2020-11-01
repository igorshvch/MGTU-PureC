#ifndef READWRITE
    #define READWRITE
    #include "readwrite.h"
#endif

#ifndef BASIC_FILES
    #define BASIC_FILES
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <locale.h>
    #include <conio.h>
    #include <windows.h>
#endif

#ifndef EMPT_CHAR_MATRIX
    struct my_matrix {
        char** table;
        int rows;
        int max_len;
    };
    #define EMPT_CHAR_MATRIX struct my_matrix
#endif

#define CHAR_MATRIX_ROWS 50000 //максимальное количество слов в таблице
#define WORD_LEN 400 //максимальная длина одного слова

void create_string_table(char *my_string, EMPT_CHAR_MATRIX *wrd_tbl, int verbose);