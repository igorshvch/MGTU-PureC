#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

/*
№9 - В целочисленной квадратной динамической матрице размером N*N
(значение N запрашивается  у пользователя), заполненной 
случайными числами, найти количество четных элементов, расположенных 
выше главной диагонали матрицы. Все элементы главной диагонали 
матрицы заменить на найденное значение. Исходную и преобразованную 
матрицу вывести в консольное окно.
*/

extern int input_data();                                                       //сбор данных, введенных пользователем
extern int** create_matr(int order, int flag_paste);                           //создание матрицы с количеством строк и столбцов, введенных пользователем
                                                                               // (флаг влияет на заполнение или незаполнение матрицы)
extern int num_of_even_elm(int **matr, int order);                             //вычисление количества четных элементов выше главной диагонали
extern void change_diag(int **matr, int order, int total);                     //замена элементов главной диагонали на число четных элементов
extern void print_matr(int **matr, int order);                                 //печать матрицы
extern void free_matr_memory(int** matr, int order);                           //особождение выделенной под матрицу памяти

int main()
{
    int order;                         //переменная для хранения порядка матрицы
    int total;                         //переменная для хранения количества четных элементов над главной диагональю
    int **matr;                        //указатель на двухмерный массив

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
    print_matr(matr, order);           //печать результата

    
    total = num_of_even_elm(matr, order);   //вычисляем количество четных элементов над главной диагональю
    change_diag(matr, order, total);        //заменяем элементы главной диагонали
    print_matr(matr, order);                //печать результата


    free_matr_memory(matr, order);     //освобождаем память из-под начальной матрицы


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


int num_of_even_elm(int **matr, int order)                                     //вычисление количества четных элементов выше главной диагонали
{
    int total(0);                      //переменная для хранения суммы четных элементов над главной диагональю
    int i, j;                          //счетчики

    for (i=0; i<order; i++)
        {
            for (j=0; j<order; j++)
                {
                    if ( (i<j) && ( !(matr[i][j]%2) ) )
                        total++;
                }
        }

    printf("Number of even 'elements: %d\n", total);
    printf("=====================================\n");

    return total;
}


void change_diag(int **matr, int order, int total)                             //замена элементов главной диагонали на число четных элементов
{
    int i, j;                          //счетчики

    for (i=0; i<order; i++)
        {
            for (j=0; j<order; j++)
                {
                    if (i==j)
                        matr[i][j] = total;
                }
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