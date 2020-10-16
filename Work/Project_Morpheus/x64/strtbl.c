#include "readwrite.h"
#include "strtbl.h"

#define MATRIX_ROWS 15000
#define ROW_LEN 200

struct words_table create_string_table(char *my_string);
void free_2d_array_char(char** matrix, int rows);

int main_test_strtbl()
{
    setlocale(LC_ALL, "Russian_Russia.1251");
    const UINT CodePageID = 1251 ;
    SetConsoleCP(CodePageID);
    SetConsoleOutputCP(CodePageID);

    printf("=====================================================\n");
    printf("Тест модуля 'strtbl.c'\n");
    printf("=====================================================\n");

    int i;
    char* my_string;
    struct words_table wrd_tbl;

    my_string = read_from_file("test_input.txt");

    wrd_tbl = create_string_table(my_string);
    printf("Получили матрицу\n");

    printf("--------------------------\n");
    for (i=456; i<456+50; i++) {
        //printf("%s ", wrd_tbl.matrix[i]);
        printf("%d)\t%s\n", i, wrd_tbl.matrix[i]);
    }
    printf("\n--------------------------\n");

    getch();

    free_2d_array_char(wrd_tbl.matrix, wrd_tbl.len);
    
    printf("=====================================================\n");

    getch();
    return 0;
}


struct words_table create_string_table(char *my_string)
{
    char * F_NAME = "create_string_table";
    printf("::%s -> вход в функицю\n", F_NAME);

    int i, row, col, len, base_matr_size, base_row_size;
    char c;

    row = col = 0;

    struct words_table wrd_tbl;
    
    base_matr_size = MATRIX_ROWS;
    base_row_size = ROW_LEN;

    len = strlen(my_string);
    printf("Длина считанной из файла строки равна: %d\n", len);

    wrd_tbl.matrix = (char**) calloc(base_matr_size, sizeof(char*));
    for (i = 0; i<base_matr_size; i++)
        wrd_tbl.matrix[i] = (char*) calloc(base_row_size, sizeof(char));

    printf("Память под матрицу выделена\n");
    
    for (i=0, row=0; i<len; i++) {
        c = my_string[i];
        if (c >= '0' && c <= '9' || c >= 'А' && c <= 'я') {
            while (c >= '0' && c <= '9' || c == '-' || c >= 'А' && c <= 'я' || c == '@' || c == '#') {//while (c != ' ' && c != '\n' &&  c != '\t') {
                wrd_tbl.matrix[row][col] = c;
                i++; col++;
                c = my_string[i];
            }
            wrd_tbl.matrix[row][col] = '\0';
            col = 0;
            row++;
        }
    }
    
    printf("Обработка строки закончена\n");
    printf("Всего слов: %d\n", row);

    wrd_tbl.len = row;

    return wrd_tbl;
}


void free_2d_array_char(char** matrix, int rows)
{
    char * F_NAME = "free_2d_array_char";
    printf("::%s -> вход в функицю\n", F_NAME);

    int i;
    printf("Очищаем память под матрицу\n");
    for (i=0; i<rows; i++)
        free((void*) matrix[i]);
    free((void*) matrix);
    printf("Память под матрицу освобождена!\n");
}