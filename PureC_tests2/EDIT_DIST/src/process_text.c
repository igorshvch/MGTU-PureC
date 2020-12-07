#include "process_text.h"

int count_edit_dist(int test_mode, char *path_file1, char *path_file2, FILE *input, char *stream1, char *stream2)
{
    int i, res;
    char *str1, *str2;
    EMPT_CHAR_MATRIX *wrd_tbl1, *wrd_tbl2;

/////////////////////////
    wrd_tbl1 = (EMPT_CHAR_MATRIX*) malloc(sizeof(EMPT_CHAR_MATRIX));
    wrd_tbl1->max_len = CHAR_MATRIX_ROWS;
    wrd_tbl1->rows = 0;
    wrd_tbl1->table = (char**) calloc(wrd_tbl1->max_len, sizeof(char*));
    for (i=0; i<wrd_tbl1->max_len; i++)
        wrd_tbl1->table[i] = (char*) calloc(WORD_LEN, sizeof(char));

    wrd_tbl2 = (EMPT_CHAR_MATRIX*) malloc(sizeof(EMPT_CHAR_MATRIX));
    wrd_tbl2->max_len = CHAR_MATRIX_ROWS;
    wrd_tbl2->rows = 0;
    wrd_tbl2->table = (char**) calloc(wrd_tbl2->max_len, sizeof(char*));
    for (i=0; i<wrd_tbl2->max_len; i++)
        wrd_tbl2->table[i] = (char*) calloc(WORD_LEN, sizeof(char));
/////////////////////////

    str1 = read_from_file(test_mode, input, stream1, path_file1);
    str2 = read_from_file(test_mode, input, stream2, path_file2);

    create_string_table(str1, wrd_tbl1);
    create_string_table(str2, wrd_tbl2);

    res = edit_distance_matrix(wrd_tbl1, wrd_tbl2);

/////////////////////////
    for (i=0; i<wrd_tbl1->max_len; i++) {
        free((void *) wrd_tbl1->table[i]);
    }
    free((void *) wrd_tbl1->table);
    free((void *) wrd_tbl1);

    for (i=0; i<wrd_tbl2->max_len; i++) {
        free((void *) wrd_tbl2->table[i]);
    }
    free((void *) wrd_tbl2->table);
    free((void *) wrd_tbl2);

    return res;

}