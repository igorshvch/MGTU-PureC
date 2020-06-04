#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

/*
№11 - Пользователем с клавиатуры вводится последовательность символов, 
которую можно рассматривать как предложение, состоящее из слов, 
разделённых одним или несколькими пробелами. Слово - последовательность 
алфавитных символов, например while. В начале и в конце предложения может 
находиться произвольное количество пробелов. Найти в предложении все слова и 
упорядочить их в алфавитном порядке. Вывести в консольное окно исходный и 
преобразованный массивы слов. 
*/

/*
Программа принимает за слово только непрерывную последовательность символов алфавита,
состоящую из заглавных и строчных латинских букв (A-Z, a-z).
Концом предложения считается символ точки - '.'.
*/

extern int** create_2d_arr(int row, int col);                                       //создание двумерного массива
extern char* write_input_to_arr();                                                  //запись слов в одномерный динамический массив
extern char* write_input_to_arr_2();                                                //модификация предыдущей функции
extern char* write_input_to_arr_3();                                                //модификация предыдущей функции
extern void free_2d_arr_memory(int** _2d_arr, int row);                             //особождение выделенной под двумерный массив памяти

int main()
{
    char *str;

    str = write_input_to_arr_3();

    getch();
	return 0;
}


char read_only_alph()
{
    int count(0);                      //счетчик слов
    char c;                            //переменная для хранения считываемого символа

    do 
        {
            c = getchar();        
            if ((c > 64 && c < 91) || (c > 96 && c < 123))           //используются ASCII-коды букв латинского алфавита: 'A'=65, 'Z'=90, 'a'=97, 'z'=122
                {
                    count++;
                    do
                        c = getchar();
                    while ((c > 64 && c < 91) || (c > 96 && c < 123));
                }  
        }
    while (c != '.');

    printf("\nNumber of input words: %d", count);

    return 0;
}


char* write_input_to_arr()                                                          //запись слов в одномерный динамический массив
{
    int i;
    char c;                            //переменная для хранения считываемого из потока ввода символа
    char *str;                         //указатель на одномерный массив для строки
    int pos = 0;                       //переменная, хранящая позицию массива, в ктороую было занесено последний считанный символ
    int arr_size = 1;                  //переменная, хранящая длину массива

    str = (char*) realloc(0, sizeof(char)*arr_size);
    
    do
        {
            c = getchar();             //считываем символ
            /*
            Далее, если символ принадлежит алфавиту, то входим в цикл считывания
            послшедующих символов, предполагая, что они также могут быть алфавитными и,
            следовательно, могут образовывать слово.
            */
            if ((c > 64 && c < 91) || (c > 96 && c < 123))
                {
                    while ((c > 64 && c < 91) || (c > 96 && c < 123))                                     
                        {
                            /*
                            Если значение размера массива равено номеру позиции последнего символа в массиве,
                            то увеличиваем значение переменной, хранящей длину массива и выделяем под новую 
                            длину массива необходимую память.
                            */
                            if (arr_size == pos)
                                {
                                    arr_size++;
                                    str = (char*) realloc(str, sizeof(char)*arr_size);
                                    if (str == NULL)       //проверка выделения памяти
                                        {
                                            printf("\n\t MEMORY ALLOCATION ERROR! PROGRAM TERMINATION!\n");
                                            return "ERROR";
                                        }
                                }
                            str[pos] = c;
                            pos++;
                            c = getchar();
                        }
                    /*
                    Далее добавляем символ пробела после каждого считанного слова
                    */
                    str[pos] = ' ';
                    pos++;
                    arr_size++;
                }
        }
    while (c != '.');
    str[pos] = '\0';

    printf("\n===================\n");
    for (i=0; i<arr_size; i++)
        {
            c = str[i];
            putchar(c);
        }
    putchar('#');
    printf("\n===================\n");

    printf("===================\n");
    free((void*) str);
    printf("Memory free!\n");

    return 0;
}

char* write_input_to_arr_2()                                                        //запись слов в одномерный динамический массив
{
    int i, j;
    char c;                            //переменная для хранения считываемого из потока ввода символа
    char **arr, **tmp1;
    char *tmp2;
    int arr_pos = 0;                       
    int arr_size = 1;
    int str_pos = 0;
    int str_size = 1;       

    arr = (char**) malloc(sizeof(char*)*arr_size);
    if (arr == NULL)
        {
            printf("######## === MEMORY ALLOCATION ERROR! === ########\n");
            return "ERROR"; 
        }
    else printf("arr ######## %p\n", arr);
    printf("===================\n");
    printf("Memory for *arr allocated!\n");
    
    do
        {
            c = getchar();             //считываем символ
            printf("\t===================\n");
            printf("\tSymbol '%c' was read!\n", c);
            if ((c > 64 && c < 91) || (c > 96 && c < 123))
                {
                    printf("\t\t===================\n");
                    printf("\t\tarr_size: %d, arr_pos: %d\n", arr_size, arr_pos);
                    if (arr_size == arr_pos)                                            //if length of array is equal to last symbol postition and yet still are some symbols in input add one more cell to array
                        {
                            arr_size++;
                            tmp1 = (char**) realloc(arr, sizeof(char*)*arr_size);
                            if (tmp1 == NULL)
                                {
                                printf("######## === MEMORY ALLOCATION ERROR! === ########\n");
                                return "ERROR";
                                }
                            else printf("arr ######## %p\n", tmp1);
                            arr = tmp1;
                            printf("\t\t\t===================\n");
                            printf("\t\t\tMemory for new cell in *arr allocated!\n");
                            printf("\t\t\tarr_size: %d, arr_pos: %d\n", arr_size, arr_pos);
                        }
                    tmp2  = (char*) malloc(sizeof(char)*str_size);               //initiate word container in the cell
                    if (tmp2 == NULL)
                        {
                            printf("######## === MEMORY ALLOCATION ERROR! === ########\n");
                            return "ERROR";
                        }
                    else printf("arr[%d] ######## %p\n", arr_pos, tmp2);
                    arr[arr_pos] = tmp2;
                    printf("\t\t===================\n");
                    printf("\t\tMemory for word container in cell in *arr allocated!\n");
                    printf("\t\tarr_size: %d, arr_pos: %d\n", arr_size, arr_pos);
                    while ((c > 64 && c < 91) || (c > 96 && c < 123))
                        {
                            printf("\t\t\t===================\n");
                            printf("\t\t\tIn the WHILE LOOP!\n");
                            printf("\t\t\tstr_size: %d, str_pos: %d\n", str_size, str_pos);
                            ///*
                            if (str_size == str_pos)
                                {
                                    str_size++;
                                    tmp2 = (char*) realloc(arr[arr_pos], sizeof(char*)*str_size);
                                    if (tmp2 == NULL)
                                        {
                                            printf("######## === MEMORY ALLOCATION ERROR! === ########\n");
                                            return "ERROR";
                                        }
                                    else printf("arr[%d] ######## %p\n", arr_pos, tmp2);
                                    arr[arr_pos] = tmp2;
                                    printf("\t\t\t\t===================\n");
                                    printf("\t\t\t\tMemory for new word in word container allocated!\n");
                                    printf("\t\t\t\tstr_size: %d, str_pos: %d\n", str_size, str_pos);

                                }
                            arr[arr_pos][str_pos] = c;
                            //*/
                            printf("\t\t\t===================\n");
                            printf("\t\t\tSymbol '%c' was put in the word container\n", c);
                            printf("\t\t\tstr_size: %d, str_pos: %d\n", str_size, str_pos);
                            str_pos++;
                            c = getchar();
                        }
                    arr[arr_pos][str_pos] = '\0';
                    printf("\t\t===================\n");
                    printf("\t\tOut of WHILE LOOP\n");
                    printf("\t\tSymbol '\\0' was put in the word container\n");
                    printf("\t\tstr_size: %d, str_pos: %d\n", str_size, str_pos);
                    str_pos = 0;
                    str_size = 1;
                    arr_pos++;
                    printf("\t\tarr_pos: %d, str_size: %d, str_pos: %d\n", arr_pos, str_size, str_pos);
                }
        }
    while (c != '.');
                    
    printf("\n===================\n");

    for (i=0; i<arr_size; i++)
        {
            printf("%s#\n", arr[i]);
        }
    printf("\n===================\n");

    printf("===================\n");
    for (i=0; i<arr_size; i++)
        free((void*) arr[i]);
    free((void*) arr);
    printf("Memory free!\n");

    printf("\n\tsize of **pointer: %d, sizeof *pointer: %d\n", sizeof(char**), sizeof(char*));

    return "NORMAL";
}


char* write_input_to_arr_3()                                                        //запись слов в одномерный динамический массив
{
    int i, j;
    char c;                            //переменная для хранения считываемого из потока ввода символа
    char **arr, **tmp1;
    char *tmp2;
    int arr_pos = 0;                       
    int arr_size = 1;
    int str_pos = 0;
    int str_size = 1;       

    arr = (char**) malloc(sizeof(char*)*arr_size);
    if (arr == NULL)
        {
            printf("######## === MEMORY ALLOCATION ERROR! === ########\n");
            return "ERROR"; 
        }
    
    do
        {
            c = getchar();             //считываем символ
            if ((c > 64 && c < 91) || (c > 96 && c < 123))
                {
                    if (arr_size == arr_pos)                                            //if length of array is equal to last symbol postition and yet still are some symbols in input add one more cell to array
                        {
                            arr_size++;
                            tmp1 = (char**) realloc(arr, sizeof(char*)*arr_size);
                            if (tmp1 == NULL)
                                {
                                printf("######## === MEMORY ALLOCATION ERROR! === ########\n");
                                return "ERROR";
                                }
                            arr = tmp1;
                        }

                    tmp2  = (char*) malloc(sizeof(char)*str_size);               //initiate word container in the cell
                    if (tmp2 == NULL)
                        {
                            printf("######## === MEMORY ALLOCATION ERROR! === ########\n");
                            return "ERROR";
                        }
                    arr[arr_pos] = tmp2;

                    while ((c > 64 && c < 91) || (c > 96 && c < 123))
                        {
                            if (str_size == str_pos)
                                {
                                    str_size++;
                                    tmp2 = (char*) realloc(arr[arr_pos], sizeof(char*)*str_size);
                                    if (tmp2 == NULL)
                                        {
                                            printf("######## === MEMORY ALLOCATION ERROR! === ########\n");
                                            return "ERROR";
                                        }
                                    arr[arr_pos] = tmp2;
                                }

                            arr[arr_pos][str_pos] = c;
                            str_pos++;
                            c = getchar();
                        }

                    arr[arr_pos][str_pos] = '\0';
                    str_pos = 0;
                    str_size = 1;
                    arr_pos++;
                }
        }
    while (c != '.');
                    
    printf("\n===================\n");
    for (i=0; i<arr_size; i++)
        {
            printf("%s#\n", arr[i]);
        }
    printf("===================\n");

    for (i=0; i<arr_size; i++)
        free((void*) arr[i]);
    free((void*) arr);
    printf("Memory free!\n");

    return "NORMAL";
}


int** create_2d_arr(int row, int col)                                               //создание двумерного массива
{
    int i, j;                          //счетчики
    int **_2d_arr;                     //указатель на двумерный массив
    const short int RANGE = 100;       //числа, заполняющие матрицу, не будут превышать 100

    _2d_arr = (int**) calloc(row, sizeof(int));
    for (i=0; i<row; i++)
        _2d_arr[i] = (int*) calloc(col, sizeof(int));
    for (i=0; i<row; i++)
            for (j=0; j<col; j++)
                    _2d_arr[i][j] = (rand() % RANGE);
    
    printf("Matrix created!\n");
    printf("=====================================\n");

    return _2d_arr;
}


void free_2d_arr_memory(int** _2d_arr, int row)                                     //особождение выделенной под двумерный массив памяти
{
    int i;                             //счетчик

    for (i=0; i<row; i++)
        free((void*) _2d_arr[i]);
    free((void*) _2d_arr);
    
    printf("Memory free!\n");
    printf("=====================================\n");
}