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
    #define CHAR_MATRIX_ROWS 5000 //максимальное количество слов в таблице
    #define WORD_LEN 400 //максимальная длина одного слова
#endif

#define MIN_3_VAL(A, B, C) (A < B)? ((A) < (C) ? (A) : (C)) : ((B) < (C) ? (B) : (C))
#define OUTPUT_STR_LEN 5000
#define CHUNK_SIZE_OUTPUT 5000000

int edit_distance_matrix(EMPT_CHAR_MATRIX* wt1, EMPT_CHAR_MATRIX* wt2);
int** create_zero_matrix(int rows, int cols);