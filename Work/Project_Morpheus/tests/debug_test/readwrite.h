#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
#include <windows.h>

char* read_from_file(char *file_name);
int write_to_file(char *file_name, char *my_string);
int write_to_file_append(char *file_name, char *my_string);
int test_copy(char *input_f_name, char *output_f_name);