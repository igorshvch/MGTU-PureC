#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

/*
№8 - Дана целочисленная квадратная динамическая матрица размером N*N
(значение N запрашивается  у пользователя), заполненная 
случайными числами. Написать программу транспонирования данной 
матрицы. Исходную и преобразованную матрицу вывести в консольное окно.
*/

extern int input_data();                                                       //сбор данных, введенных пользователем
extern int** create_matr(int order, int flag_paste);                           //создание матрицы с количеством строк и столбцов, введенных пользователем
                                                                               // (флаг влияет на заполнение или незаполнение матрицы)
extern void transpose(int **matr, int **t_matr, int order);                    //транспонирование
extern void print_matr(int **matr, int order);                                 //печать матрицы
extern void free_matr_memory(int** matr, int order);                           //особождение выделенной под матрицу памяти

int main()
{
    int order;                         //переменная для хранения порядка матрицы
    int **matr;                        //указатель на двухмерный массив
    int **t_matr;                      //указатьль на транспонированный двухмерный массив

    srand(time(NULL));                 //srand(5);
/*
При srand(5); и квадртаной матрице порядка 3 получаем:
                54      93      55
                49      60      30
                27      49      72
*/                  
    
    printf("=====================================\n");
    printf("Programm starts!\n");
    printf("=====================================\n");
    

    order = input_data();              //получаем пользовательски ввод
    if (order<2 || order>10)
        {
            printf("Incorrect input! Program ends\n");
            return 0;
        }


    matr = create_matr(order, 1);      //строим матрицу и заполняем ее случайными числами (0-99)
    t_matr = create_matr(order, 0);    //строим матрицу и заполняем ее нулями
    print_matr(matr, order);           //печать результата
    print_matr(t_matr, order);         //печать результата

    transpose(matr, t_matr, order);    //транспонируем
    
    print_matr(t_matr, order);         //печать результата


    free_matr_memory(matr, order);     //освобождаем память из-под начальной матрицы
    free_matr_memory(t_matr, order);   //освобождаем память из-под транспонированной матрицы


    getch();
	return 0;
}


int input_data()                                                               //сбор данных, введенных пользователем
{
    int order;                         //порядок квадратной матрицы

    printf("Input matrix order (2-10):\n");
    scanf("%d", &order);

    printf("Your input:\n\torder: %d\n", order);
    printf("=====================================\n");
    
    return order;
}


int** create_matr(int order, int flag_paste)                                    //создание матрицы с количеством строк и столбцов, введенных пользователем
{
    int i, j;                          //счетчики
    int **matr;                        //указатель на двухмерный массив
    const short int RANGE = 100;       //числа, заполняющие матрицу, не будут превышать 100

    matr = (int**) calloc(order, sizeof(int));
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


void transpose(int **matr, int **t_matr, int order)                            //транспонирование
{
    int i, j;                          //счетчики             

    for (i=0; i<order; i++)
        {
            for (j=0; j<order; j++)
                t_matr[j][i] = matr[i][j];
        }
}


void print_matr(int **matr, int order)                                         //печать матрицы
{
    int i, j;                          //счетчики

    printf("Print matrix:\n");
    for (i=0; i<order; i++)
        {
        printf("\t");
        for (j=0; j<order; j++)
            printf("\t%2d", matr[i][j]);
        printf("\n");
        }
    printf("=====================================\n");
}


void free_matr_memory(int** matr, int order)                                   //особождение выделенной под матрицу памяти
{
    int i;                             //счетчик

    for (i=0; i<order; i++)
        free((void*) matr[i]);
    free((void*) matr);
    
    printf("Memory free!\n");
    printf("=====================================\n");
}