#ifndef LISTDIR
    #define LISTDIR
    #include "listdir.h"
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


#define CHUNK_SIZE 1000000 //начальна€ длина строки
#define TEST_TABLE_LEN 5000 //тестова€ длина дл€ таблицы файлов

char* read_from_file(char *file_name, int verbose);
int write_to_file(char *file_name, char *my_string, const char *mode, int verbose);
int write_to_file_words_table(char *file_name, char **words_table, int table_len, const char *mode, int verbose);
int test_raw_copy(char *input_f_name, char *output_f_name, int verbose);
void test_copy(char *input_f_name, char *output_f_name, int verbose);


//#define DLL_PREF __declspec(dllexport)
//__declspec(dllexport) <объ€вление функции>