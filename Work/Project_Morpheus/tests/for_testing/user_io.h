#ifndef BASIC_FILES
    #define BASIC_FILES
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <locale.h>
    #include <conio.h>
    #include <windows.h>
#endif

int console_interface(char* path_folder, char* path_res_file, int proc_func(char*));
int process_input_string(char *str);