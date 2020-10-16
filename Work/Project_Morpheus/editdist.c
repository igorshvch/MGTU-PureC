/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
*/

#include "strtbl.h"
#include "readwrite.h"
#include "listdir.h"

#define MIN_3_VAL(A, B, C) (A < B)? ((A) < (C) ? (A) : (C)) : ((B) < (C) ? (B) : (C))

//__declspec(dllexport) void compare(char *file_path1, char *file_path2, char *output_file_path);
void compare(char *file_path1, char *file_path2, char *output_file_path, struct words_table* wt1, struct words_table* wt2);
void compare_cycle(char *directory_path, char *output_file_path);
int edit_distance_matrix(struct words_table* wt1, struct words_table* wt2);
int** create_matrix(int rows, int cols);
void free_2d_array_int(int **matrix, int rows);


int main()
{
    setlocale(LC_ALL, "Russian_Russia.1251");
    const UINT CodePageID = 1251 ;
    SetConsoleCP(CodePageID);
    SetConsoleOutputCP(CodePageID);

    //printf("=====================================================\n");
    //printf("Тест модуля 'editdist.c'\n");
    //printf("=====================================================\n");

    /*
    int i, res;
    char *test_string, *str1, *str2;
    struct words_table wt1, wt2;

    test_string = read_from_file("test_input.txt");

    for (int i=0; i<100; i++)
        //printf("%c", test_string[i]);

    str1 = read_from_file("test_input3.txt");
    str2 = read_from_file("test_input4.txt");

    wt1 = create_string_table(str1);
    //printf("Строка str1 превращена в таблицу строк\n");
    wt2 = create_string_table(str2);
    //printf("Строка str2 превращена в таблицу строк\n");

    if (wt1.len < 10 || wt2.len < 10) {
        for (i=0; i<(wt2.len < wt1.len ? wt2.len : wt1.len); i++) {
            //printf("%d)\t%s\t\t%s\n", i, wt1.matrix[i], wt2.matrix[i]);
        }
        //printf("%d)\t---\t\t%s\n", i, (wt2.len < wt1.len ? wt2.matrix[i] : wt1.matrix[i]));
    }

    res = edit_distance_matrix(&wt1, &wt2);

    free((void*) str1);
    free((void*) str2);
    free_2d_array_char(wt1.matrix, wt1.len);
    free_2d_array_char(wt2.matrix, wt2.len);

    //printf("Редакционное расстояние между str1 и str2: %d, степень схожести фрагментов текста: %.5f\n", res, 1.00 - (double) res/((double) (wt1.len+wt2.len)/2.0));

    compare("test_input1.txt", "test_input2.txt", "test_output3.txt");
    */

    compare_cycle("C:/Users/igors/MYWRITE/PKP_new_test", "C:/Users/igors/MYWRITE/RES/RESULTS.txt");

    //printf("=====================================================\n");

    getch();
    return 0;
}


//__declspec(dllexport) void compare(char *file_path1, char *file_path2, char *output_file_path)
void compare(char *file_path1, char *file_path2, char *output_file_path, struct words_table* wt1, struct words_table* wt2)
{
    char * F_NAME = "compare";
    //printf("::%s -> вход в функицю\n", F_NAME);
    
    int res;
    double proc;
    char *str1, *str2, output[2000];

    str1 = read_from_file(file_path1);
    str2 = read_from_file(file_path2);

    create_string_table(str1, wt1);
    //printf("Строка str1 превращена в таблицу строк\n");
    create_string_table(str2, wt2);
    //printf("Строка str2 превращена в таблицу строк\n");

    res = edit_distance_matrix(wt1, wt2);
    //mean_len = ((double) (wt1->len+wt2->len)) / 2.0;
    proc = 1.0 - ((double) res / ((double) (wt1->len > wt2->len ? wt1->len : wt2->len)));
    
    sprintf(output, "%s|%d|%s|%d|%d|%.6f\n", file_path1, wt1->len, file_path2, wt2->len, res, proc);

    write_to_file_append(output_file_path, output);

    free((void*) str1);
    free((void*) str2);
    //free_2d_array_char(wt1->matrix, wt1->len);
    //free_2d_array_char(wt2->matrix, wt2->len);
    //free((void*) wt1);
    //free((void*) wt2);
}


void compare_cycle(char *directory_path, char *output_file_path)
{
    char * F_NAME = "compare_cycle";
    //printf("::%s -> вход в функицю\n", F_NAME);

    int files_num, i, j, k, m, base_matr_size, base_row_size;
    char *file1, *file2;
    char **files;
    struct words_table *wt1, *wt2;

    base_matr_size = MATRIX_ROWS;
    base_row_size = ROW_LEN;

    wt1 = (struct words_table*) malloc(sizeof(struct words_table));
    wt2 = (struct words_table*) malloc(sizeof(struct words_table));

    //Инициализируем структуры для хранения таблиц слов
    wt1->matrix = (char**) calloc(base_matr_size, sizeof(char*));
    for (i = 0; i<base_matr_size; i++)
        wt1->matrix[i] = (char*) calloc(base_row_size, sizeof(char));

    wt2->matrix = (char**) calloc(base_matr_size, sizeof(char*));
    for (i = 0; i<base_matr_size; i++)
        wt2->matrix[i] = (char*) calloc(base_row_size, sizeof(char));
    //Конец инициализации структур

    files_num = 0;

    //printf("1\n");
    files = (char**) calloc(2000, sizeof(char*));
    for (i=0; i<2000; i++)
        files[i] = (char*) calloc(2000, sizeof(char));
    list_directory_contents(directory_path, files, &files_num);
    //printf("2\n");
    j = files_num;
    for (i=files_num-1; i>0; i--) {
        file1 = files[i];
        j--;
        //printf("3\n");
        for (k=0; k<j; k++) {
            file2 = files[k];
            compare(file1, file2, output_file_path, wt1, wt2);
            //printf("4\n");
            /*
            //Удаляем строки со словами из матриц в структурах таблиц слов
            for (m = 0; m<base_matr_size; m++) {
                free((void*) wt1->matrix[m]);
                //printf("c1 (%d)", m);
            }
            for (m = 0; m<base_matr_size; m++) {
                free((void*) wt2->matrix[m]);
                //printf("c2 (%d)", m);
            }
            //Инициализируем новые строки в матрицах в структурах таблиц слов
            for (m = 0; m<base_matr_size; m++) {
                wt1->matrix[m] = (char*) calloc(base_row_size, sizeof(char));
                //printf("c3 (%d)", m);
            }
            for (m = 0; m<base_matr_size; m++) {
                wt2->matrix[m] = (char*) calloc(base_row_size, sizeof(char));
                //printf("c4 (%d)", m);
            }
            */
        }
        printf("Прогон № %d\n", files_num-j);
    }
    
    free_2d_array_char(files, files_num);
    free_2d_array_char(wt1->matrix, wt1->len);
    free_2d_array_char(wt2->matrix, wt2->len);
    free((void*) wt1);
    free((void*) wt2);

    printf("::%s -> Завершение работы\n", F_NAME);
}


int edit_distance_matrix(struct words_table* wt1, struct words_table* wt2)
{
    char * F_NAME = "edit_distance_matrix";
    //printf("::%s -> вход в функицю\n", F_NAME);

    int x_coord, y_coord, res;

    int** matrix = create_matrix(wt1->len+1, wt2->len+1);
    
    for (x_coord = 1; x_coord <= wt1->len; x_coord++)
        matrix[x_coord][0] = matrix[x_coord-1][0] + 1;

    for (y_coord = 1; y_coord <= wt2->len; y_coord++)
        matrix[0][y_coord] = matrix[0][y_coord-1] + 1;

    if (wt1->len == 0)
        return wt2->len;
    if (wt2->len == 0)
        return wt1->len;

    for (x_coord = 1; x_coord <= wt1->len; x_coord++)
        for (y_coord = 1; y_coord <= wt2->len; y_coord++)
            matrix[x_coord][y_coord] = MIN_3_VAL(
                matrix[x_coord-1][y_coord] + 1,
                matrix[x_coord][y_coord-1] + 1,
                matrix[x_coord-1][y_coord-1] + ((strcmp(wt1->matrix[x_coord], wt2->matrix[y_coord]) == 0) ? 0 : 1)
            );

    res = matrix[wt1->len][wt2->len];

    free_2d_array_int(matrix, wt1->len+1);

    return res;
}


int** create_matrix(int rows, int cols)
{
    char * F_NAME = "create_matrix";
    //printf("::%s -> вход в функицю\n", F_NAME);

    int row;
    int **matrix;

    matrix = (int**) calloc(rows, sizeof(int));
    for (row = 0; row < rows; row++)
        matrix[row] = (int*) calloc(cols, sizeof(int));
    matrix[0][0] = 0;

    return matrix;
}


void free_2d_array_int(int** matrix, int rows)
{
    char * F_NAME = "free_2d_array_int";
    //printf("::%s -> вход в функицю\n", F_NAME);

    int i;
    //printf("Очищаем память под матрицу\n");
    for (i=0; i<rows; i++)
        free((void*) matrix[i]);
    free((void*) matrix);
    //printf("Память под матрицу освобождена!\n");
}