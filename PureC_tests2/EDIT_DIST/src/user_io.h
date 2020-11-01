#ifndef BASIC_FILES
    #define BASIC_FILES
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <locale.h>
    #include <conio.h>
    #include <windows.h>
#endif

#define ERROR_CASH char err_cach[500];

//int console_interface(char* path_folder, char* path_res_file, int (*proc_func)(char*));
int verify_not_too_long_WIN(char* str);
//int verify_only_permitted_symbols_WIN(char* str);
//int verify_path_is_valid(char* str, char* mode);
//void change_backslash_to_slash(char* str);