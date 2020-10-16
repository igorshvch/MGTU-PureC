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
void compare(char *file_path1, char *file_path2, char *output_file_path);
int compare_cycle(char *directory_path, char *output_file_path);
int edit_distance_matrix(struct words_table* wt1, struct words_table* wt2);
int** create_matrix(int rows, int cols);
void free_2d_array_int(int **matrix, int rows);


int main()
{
    setlocale(LC_ALL, "Russian_Russia.1251");
    const UINT CodePageID = 1251 ;
    SetConsoleCP(CodePageID);
    SetConsoleOutputCP(CodePageID);

    printf("=====================================================\n");
    printf("Тест модуля 'editdist.c'\n");
    printf("=====================================================\n");

    int i, res;
    char *test_string, *str1, *str2;
    struct words_table wt1, wt2;

    test_string = read_from_file("test_input.txt");

    for (int i=0; i<100; i++)
        printf("%c", test_string[i]);

    str1 = read_from_file("test_input3.txt");
    str2 = read_from_file("test_input4.txt");

    wt1 = create_string_table(str1);
    printf("Строка str1 превращена в таблицу строк\n");
    wt2 = create_string_table(str2);
    printf("Строка str2 превращена в таблицу строк\n");

    if (wt1.len < 10 || wt2.len < 10) {
        for (i=0; i<(wt2.len < wt1.len ? wt2.len : wt1.len); i++) {
            printf("%d)\t%s\t\t%s\n", i, wt1.matrix[i], wt2.matrix[i]);
        }
        printf("%d)\t---\t\t%s\n", i, (wt2.len < wt1.len ? wt2.matrix[i] : wt1.matrix[i]));
    }

    res = edit_distance_matrix(&wt1, &wt2);

    free((void*) str1);
    free((void*) str2);
    free_2d_array_char(wt1.matrix, wt1.len);
    free_2d_array_char(wt2.matrix, wt2.len);

    printf("Редакционное расстояние между str1 и str2: %d, степень схожести фрагментов текста: %.5f\n", res, 1.00 - (double) res/((double) (wt1.len+wt2.len)/2.0));

    compare("test_input1.txt", "test_input2.txt", "test_output3.txt");

    printf("=====================================================\n");

    getch();
    return 0;
}


//__declspec(dllexport) void compare(char *file_path1, char *file_path2, char *output_file_path)
void compare(char *file_path1, char *file_path2, char *output_file_path)
{
    char * F_NAME = "compare";
    printf("::%s -> вход в функицю\n", F_NAME);
    
    int res;
    double proc;
    char *str1, *str2, output[2000];
    struct words_table wt1, wt2;

    str1 = read_from_file(file_path1);
    str2 = read_from_file(file_path2);

    wt1 = create_string_table(str1);
    printf("Строка str1 превращена в таблицу строк\n");
    wt2 = create_string_table(str2);
    printf("Строка str2 превращена в таблицу строк\n");

    res = edit_distance_matrix(&wt1, &wt2);
    proc = 1.00 - (double) res/((double) (wt1.len+wt2.len) / 2.0);
    
    sprintf(output, "%s|%d|%s|%d|%d|%.6f\n", file_path1, wt1.len, file_path2, wt2.len, res, proc);

    write_to_file_append(output_file_path, output);

    free((void*) str1);
    free((void*) str2);
    free_2d_array_char(wt1.matrix, wt1.len);
    free_2d_array_char(wt2.matrix, wt2.len);
}


int compare_cycle(char *directory_path, char *output_file_path)
{
    char * F_NAME = "compare_cycle";
    printf("::%s -> вход в функицю\n", F_NAME);

    int files_num, i, j, k;
    char *file1, *file2;
    char **files;

    files = (char**) calloc(2000, sizeof(char*));
    for (i=0; i<2000; i++)
        files[i] = (char*) calloc(2000, sizeof(char));
    list_directory_contents("C:/Users/igors/MYWRITE/PKP", files, &files_num);
    
    j = files_num;
    for (i=files_num-1; i>1; i--) {
        file1 = files[i];
        j--;
        for (k=0; k<j; k++) {
            file2 = files[k];
            compare(file1, file2, output_file_path);
        }
    }
    
    free_2d_array_char(files, files_num);
}


int edit_distance_matrix(struct words_table* wt1, struct words_table* wt2)
{
    char * F_NAME = "edit_distance_matrix";
    printf("::%s -> вход в функицю\n", F_NAME);

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
    printf("::%s -> вход в функицю\n", F_NAME);

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
    printf("::%s -> вход в функицю\n", F_NAME);

    int i;
    printf("Очищаем память под матрицу\n");
    for (i=0; i<rows; i++)
        free((void*) matrix[i]);
    free((void*) matrix);
    printf("Память под матрицу освобождена!\n");
}