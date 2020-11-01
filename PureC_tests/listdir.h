#ifndef BASIC_FILES
    #define BASIC_FILES
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <locale.h>
    #include <conio.h>
    #include <windows.h>
#endif

#ifndef TEST_TABLE_LEN
    #define TEST_TABLE_LEN 5000 //тестовая длина для таблицы файлов
#endif

int list_directory_contents(const char *sDir, char **files, int *i, int verbose);
void free_2d_array_char(char** matrix, int rows, int verbose);