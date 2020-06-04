#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

int** create_matr(int order, int flag_paste);
void print_matr(int **matr, int row, int col);


int main()
{
    int **matr;
    int rows, cols;
    int order;
    int random_seed;
    int flag;

    printf("Input flag:\n");
    scanf("%d", &flag);
    printf("Input random seed:\n");
    scanf("%d", &random_seed);
    printf("Input matrix order:\n");
    scanf("%d", &order);

    srand(random_seed);

    rows = order;
    cols = order;

    matr = create_matr(order, flag);

    print_matr(matr, rows, cols);

    getch();
    return 0;
}

int** create_matr(int order, int flag_paste)                                    //создание матрицы с количеством строк и столбцов, введенных пользователем
{
    int i, j;                          //счетчики
    int **matr;                        //указатель на двухмерный массив
    const short int RANGE = 100;       //числа, заполняющие матрицу, не будут превышать 100

    matr = (int**) calloc(order, sizeof(int*));
    for (i=0; i<order; i++)
        matr[i] = (int*) calloc(order, sizeof(int));
    for (i=0; i<order; i++)
            for (j=0; j<order; j++)
                if (flag_paste)
                    matr[i][j] = (rand() % RANGE);
                else
                    matr[i][j] = 0;
    
    printf("Matrix created!\n");
    printf("=====================================\n");

    return matr;
}

void print_matr(int **matr, int row, int col)                                       //печать матрицы
{
    int i, j;                          //счетчики

    printf("Print matrix:\n");
    for (i=0; i<row; i++)
        {
        printf("\t");
        for (j=0; j<col; j++)
            printf("\t%2d", matr[i][j]);
        printf("\n");
        }
    printf("=====================================\n");
}