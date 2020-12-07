#include <stdio.h>
#include <string.h>

#include "user_input_check.h"

int console_interface(
    char* path_file1,
    char* path_file2,
    char* path_res_file,
    int test_mode,
    void (*print_f)(const char*),
    void (*scan_f)(const char*),
    char* test_str1,
    char* test_str2,
    char* test_str3
);
void dumy_print_f(const char* str);
void dumy_scan_f(const char* str);


