#include "readwrite.h"

struct words_table {
    char** matrix;
    int len;
};

struct words_table create_string_table(char *my_string);
void free_2d_array_char(char** matrix, int rows);