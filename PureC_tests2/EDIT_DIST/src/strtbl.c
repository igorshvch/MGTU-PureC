#include "strtbl.h"

void create_string_table(char *my_string, EMPT_CHAR_MATRIX *wrd_tbl)
{
    int i, row, col, len;
    char c;

    row = 0;
    col = 0;    
    len = strlen(my_string);
    
    for (i=0; i<len; i++) {
        c = my_string[i];
        if (c >= '0' && c <= '9' || c >= 'A' && c <= 'z') {
            while (c >= '0' && c <= '9' || c == '-' || c >= 'A' && c <= 'z' || c == '@' || c == '#' || c == '/') {//while (c != ' ' && c != '\n' &&  c != '\t') {
                wrd_tbl->table[row][col] = c;
                i++; col++;
                c = my_string[i];
            }
            wrd_tbl->table[row][col] = '\0';
            col = 0;
            row++;
        }
    }
    wrd_tbl->rows = row;
}