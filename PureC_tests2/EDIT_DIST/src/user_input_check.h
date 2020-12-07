#ifndef BASIC_FILES
    #define BASIC_FILES
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <math.h>
    #include <locale.h>
    #include <conio.h>
    #include <windows.h>
#endif

#define ERROR_CASH char err_cach[500];

int verify_not_too_long_file(char* str);
int verify_not_too_long_dir(char* str);
int verify_only_valid_symbols(char* str);
int verify_file_path_as_valid(char* str);
int change_backslash_to_slash(char* str);