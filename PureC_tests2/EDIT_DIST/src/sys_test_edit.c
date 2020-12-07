#include "sys_test_edit.h"

char* global_test(char *stream1, char *stream2)
{
    int res;
    char *str_res;
    int path_size = 32767;
    char path_file_real[32767];
    char WIN_kernel_file[] = "\\kernel32.dll";
    GetSystemDirectory(path_file_real, path_size);
    strcat(path_file_real, WIN_kernel_file);

    char test_path1[300];

    //char stream1[] = "This is a test string1|";
    //char stream2[] = "This is a test string2|";
    char stream3[300];

    FILE *input, *output;
    
    console_interface(
        test_path1, test_path1, test_path1, 1, dumy_print_f, dumy_scan_f, path_file_real, path_file_real, path_file_real
);
    res = count_edit_dist(1, "", "", input, stream1, stream2);

    if (res != 0)
        str_res = write_to_file(1, output, "", stream3,  res);
    else
        str_res = "Zero length";

    return str_res;
}