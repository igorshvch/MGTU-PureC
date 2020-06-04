#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

/*
№6 - Дана целочисленная прямоугольная матрица размером R*C. 
Переставляя её строки столбцы, добиться того, чтобы 
наименьший элемент оказался в верхнем левом углу. Исходную 
и преобразованную матрицы вывести в консольное окно. 
*/

extern void input_data(int *row_col);                                               //сбор данных, введенных пользователем
extern int** create_matr(int row, int col);                                         //создание матрицы с количеством строк и столбцов, введенных пользователем
extern void find_smallest(int **matr, int row, int col, int* smallest_address);     //поиск адреса наименьшего элемента
extern void smallest_on_top(int **matr, int row, int col, int s_row, int s_col);    //перемещение наименьшего элемента в левый верхний угол
extern void print_matr(int **matr, int row, int col);                               //печать матрицы
extern void free_matr_memory(int** matr, int row);                                  //особождение выделенной под матрицу памяти

int main()
{
    int row_col[2];                    //статический массив, хранящий количество строк и столбцов: [строки, столбцы]
    int row, col;                      //переменные для хранения количества строк и столбцов (для удобства чтения кода: обращение идет не к массиву row_col, а переменным)
    int **matr;                        //указатель на двухмерный массив
    int smallest_address[2];           //адрес наименьшего элемента в виде двухэлементного массива: [строка, столбец]

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
    

    input_data(row_col);               //получаем пользовательски ввод
    row = row_col[0];
    col = row_col[1];
    if ((row<2 || row>10) || (col<2 || col >10))
        {
            printf("Incorrect input! Program ends\n");
            return 0;
        }


    matr = create_matr(row, col);      //строим матрицу и заполняем ее случайными числами (0-99)
    print_matr(matr, row, col);        //печать результата
    

    find_smallest(matr, row, col, smallest_address);       //находим адрес наименьшего элемена, загружаем его в двухэлементный массив "smallest_adress"
    

    smallest_on_top(matr, row, col, smallest_address[0], smallest_address[1]); //переставляем наименьший элемент в левый верхний угол матрицы
    print_matr(matr, row, col);                                                //печать результата
    

    free_matr_memory(matr, row);       //освобождаем память из-под матрицы


    getch();
	return 0;
}


void input_data(int *row_col)                                                       //сбор данных, введенных пользователем
{
    printf("Input number of rows (2-10):\n");
    scanf("%d", &row_col[0]);
    printf("Input number of columns (2-10):\n");
    scanf("%d", &row_col[1]);

    printf("Your input:\n\trows: %d\n\tcols: %d\n", row_col[0], row_col[1]);
    printf("=====================================\n");
}


int** create_matr(int row, int col)                                                 //создание матрицы с количеством строк и столбцов, введенных пользователем
{
    int i, j;                          //счетчики
    int **matr;                        //указатель на двухмерный массив
    const short int RANGE = 100;       //числа, заполняющие матрицу, не будут превышать 100

    matr = (int**) calloc(row, sizeof(int));
    for (i=0; i<row; i++)
        matr[i] = (int*) calloc(col, sizeof(int));
    for (i=0; i<row; i++)
            for (j=0; j<col; j++)
                    matr[i][j] = (rand() % RANGE);
    
    printf("Matrix created!\n");
    printf("=====================================\n");

    return matr;
}


void find_smallest(int **matr, int row, int col, int *smallest_address)             //поиск адреса наименьшего элемента
{
    int i, j;                          //счетчики
    int smallest=100;                  //хранение значения наименьшего элемента
    for (i=0; i<row; i++)
        {
            for (j=0; j<col; j++)
                if (matr[i][j] < smallest)
                    {
                        smallest = matr[i][j];
                        smallest_address[0] = i;
                        smallest_address[1] = j;
                    }
        }
    printf("Smallest element search results:\n\telm:\t%2d\n\trow:\t%2d\n\tcol:\t%2d\n", smallest, smallest_address[0], smallest_address[1]);
    printf("=====================================\n");
}


void smallest_on_top(int **matr, int row, int col, int s_row, int s_col)            //перемещение наименьшего элемента в левый верхний угол
{
    int i, j;                          //счетчики
    int tmp;                           //переменная для временного хранения элементов матрицы

    for (j=0; j<col; j++)              //перестановка строк
        {   
            tmp = matr[0][j];
            matr[0][j] = matr[s_row][j];
            matr[s_row][j] = tmp;
        }

    for (i=0; i<row; i++)              //перестановка столбцов
        {   
            tmp = matr[i][0];
            matr[i][0] = matr[i][s_col];
            matr[i][s_col] = tmp;
        }
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


void free_matr_memory(int** matr, int row)                                          //особождение выделенной под матрицу памяти
{
    int i;                             //счетчик

    for (i=0; i<row; i++)
        free((void*) matr[i]);
    free((void*) matr);
    
    printf("Memory free!\n");
    printf("=====================================\n");
}