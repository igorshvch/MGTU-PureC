#include "listdir.h"
#include "readwrite.h"
#include "strtbl.h"

#ifndef BASIC_FILES
    #define BASIC_FILES
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <locale.h>
    #include <conio.h>
    #include <windows.h>
#endif

#define MIN_3_VAL(A, B, C) (A < B)? ((A) < (C) ? (A) : (C)) : ((B) < (C) ? (B) : (C))
#define OUTPUT_STR_LEN 5000
#define CHUNK_SIZE_OUTPUT 5000000

//__declspec(dllexport) void compare(char *file_path1, char *file_path2, char *output_file_path);
void test_single_compare(char *file_path1, char *file_path2, char *output_address, int verbose);
int compare_cycle(char *directory_path, char *output_file_path, int verbose);
int compare_cycle_with_writing(char *directory_path, char *output_file_path, int verbose);
void compare(char *file_path1, char *file_path2, char *output_file_path, EMPT_CHAR_MATRIX* wt1, EMPT_CHAR_MATRIX* wt2, int verbose);
int edit_distance_matrix(EMPT_CHAR_MATRIX* wt1, EMPT_CHAR_MATRIX* wt2, int verbose);
int** create_matrix(int rows, int cols, int verbose);
void free_2d_array_int(int **matrix, int rows, int verbose);