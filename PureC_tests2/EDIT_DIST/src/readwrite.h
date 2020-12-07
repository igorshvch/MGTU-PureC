#ifndef BASIC_FILES
    #define BASIC_FILES
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <locale.h>
    #include <conio.h>
    #include <windows.h>
#endif

#define CHUNK_SIZE 20000 //начальная длина строки

char* read_from_file(int test_mode, FILE *input, char *stream, char *file_name);
char* write_to_file(int test_mode, FILE *output, char *file_name, char *stream,  int res);