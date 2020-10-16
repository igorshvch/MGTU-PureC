#include "readwrite.h"

#define MATRIX_ROWS 15000
#define ROW_LEN 200

struct words_table {
    char** matrix;
    int len;
};

void create_string_table(char *my_string, struct words_table *wrd_tbl);
void free_2d_array_char(char** matrix, int rows);