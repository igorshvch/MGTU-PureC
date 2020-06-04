#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
Концом предложения считается символ, определенный пользователем.
*/

struct strtbl                                                                       //структура, хранящая двумерный массив с введенными словами и число строк массива
{
    char **table;
    int rows;
};


extern strtbl write_input_to_2d_arr(char string_end);                               //запись слов в двумерный динамический массив и возвращения структуры с массивом и числом строк в массиве
extern char** copy_2d_array(char **_2d_arr, int rows);                              //копировать двумерный массив массив
extern void sort(char **table, int rows);                                           //сортировка строк в двумерном массиве
extern void pretty_print(char **origin_table, char **sorted_table, int rows);       //печать исходного и сортированного спика слов
extern void free_2d_arr_memory(char **_2d_arr, int rows);                           //особождение выделенной под двумерный массив памяти


int main()
{
    char **arr_copy;                   //переменная для хранения копии двумерного массива
    char string_end;                   //переменная для хранения символа конца строки, выбранного пользователем
    strtbl string_table;               //переменная для хранения структуры

    printf("==============================\n");
    printf("Input string end symbol:\n");
    scanf("%c", &string_end);          //записываем символ конца строки

    string_table = write_input_to_2d_arr(string_end);                //считываем последовательность символов, введенных пользователем, и записываем каждое слово в строку двумерного массива

    /*
    Если при обработки входящего потока символов произошла ошибка выделения памяти,
    программа завершается. Сообщение об ошибки выводится функцией обработки строки.
    */
    if (string_table.table == NULL)
        return 0;

    arr_copy = copy_2d_array(string_table.table, string_table.rows);                          //копируем полученный массив слов для последующей сортировки
    if (arr_copy==NULL)
        return 0;

    sort(arr_copy, string_table.rows);                               //сортируем копию исходного массива

    pretty_print(string_table.table, arr_copy, string_table.rows);   //выводим исходный и сортированный массивы

    free_2d_arr_memory(string_table.table, string_table.rows);       //освобождаем память из-под исходного массива
    free_2d_arr_memory(arr_copy, string_table.rows);                 //освобождаем память из-под сортированного массива

    getch();
	return 0;
}

strtbl write_input_to_2d_arr(char string_end)                 //запись слов в двумерный массив
{
    int i, j;                          //счетчики
    char c;                            //переменная для хранения считываемого символа из входной последовательности
    char **arr, **tmp1;                //переменные для хранения двумерного массива со словами и для тестирования результата выделения памяти под массив
    char *tmp2;                        //переменная для тестирования результата выделения памяти под слово
    int arr_pos = 0;                   //переменная, хранящая внешний индекс двумерного массива
    int arr_size = 1;                  //переменная, хранящая длину двумерного массива
    int str_pos = 0;                   //переменная, хранящая внутренний индекс двумерного массива (индекс символа в строке)
    int str_size = 1;                  //переменная, хранящая длину строки двумерного массива
    strtbl string_table;               //структура, в которую записсывается результат: двумерный массив со словами и число строк в нем

    string_table.table = NULL;
    string_table.rows = 0;

    printf("Input text:\n");

    arr = (char**) malloc(sizeof(char*)*arr_size);                        //первоначальное выделение памяти под двумерный массив
    if (arr == NULL)
        {
            printf("######## === MEMORY ALLOCATION ERROR! === ########\n");
            return string_table; 
        }
    
    do
        {
            c = getchar();
            if ((c > 64 && c < 91) || (c > 96 && c < 123))
            /*
            Если считанный символ явялется буквой, входим в цикл чтения слова и занесения его в строку двумерного массва.
            Предварительно добавляем к области памяти, хранящей указатели на слова, дополнительную память
            для нового указателя на очередное слово. Также выделяем область памяти собственно для хранения слова
            */
                {
                    if (arr_size == arr_pos)
                    /*
                    Если количество элементов внешнего массива (области, хранящей указатели на слова)
                    равна значению внешнего индекса двумерного массива, добавляем еще память к области,
                    хранящей указатели на одномерные массивы со словами.
                    */
                        {
                            arr_size++;
                            tmp1 = (char**) realloc(arr, sizeof(char*)*arr_size);
                            if (tmp1 == NULL)
                                {
                                printf("######## === MEMORY ALLOCATION ERROR! === ########\n");
                                return string_table;
                                }
                            arr = tmp1;
                        }

                    tmp2  = (char*) malloc(sizeof(char)*str_size);             //выделяем область памяти для хранения очередного слова
                    if (tmp2 == NULL)
                        {
                            printf("######## === MEMORY ALLOCATION ERROR! === ########\n");
                            return string_table;
                        }
                    arr[arr_pos] = tmp2;

                    do                                                         //входим в цикл чтения слова
                        {
                            if (str_size == str_pos)
                            /*
                            Если длина массива, хранещего слово, равна значению внутреннего индекса двумерного массива
                            (индексу последнего считанного символа в слове), добавляем память к строке.
                            */
                                {
                                    str_size++;
                                    tmp2 = (char*) realloc(arr[arr_pos], sizeof(char*)*str_size);
                                    if (tmp2 == NULL)
                                        {
                                            printf("######## === MEMORY ALLOCATION ERROR! === ########\n");
                                            return string_table;
                                        }
                                    arr[arr_pos] = tmp2;
                                }

                            arr[arr_pos][str_pos] = c;                         //заносим прочитанную букву в двумерный массив
                            str_pos++;                                         //увеличиваем индекс
                            c = getchar();                                     //считываем новый символ в цикле чтения слова
                        }
                    while ((c > 64 && c < 91) || (c > 96 && c < 123));

                    arr[arr_pos][str_pos] = '\0';                              //после конца слова добавляем символ конца строки в массиве
                    str_pos = 0;                                               //приводим внутренний индекс и длину строки к начальным значениям 
                    str_size = 1;
                    arr_pos++;                                                 //увеличиваем переменную, хранящую числов строк, на единицу
                }
        }
    while (c != string_end);

    if (!arr_pos)                                                              //проверка входящей последовательности на пустоту
        {
            free((void*) arr);
            printf("\n\tEmpty string!\n\n");
        }
    else
        {
            string_table.table = arr;                                          //заносим результаты в структуру
            string_table.rows = arr_size;
        }

    return string_table;
}


char** copy_2d_array(char **_2d_arr, int rows)                            //копирование двумерного массива со строками разной длинны
{
    int i;
    int string_len;
    char **arr, **tmp1;
    char *tmp2;

    tmp1 = (char**) malloc(sizeof(char*)*rows);
    if (tmp1 == NULL)
        {
            printf("######## === MEMORY ALLOCATION ERROR!  === ########\n");
            return NULL;
        }
    arr = tmp1;

    for (i=0; i<rows; i++)
        {
            string_len = strlen(_2d_arr[i])+1;
            tmp2 = (char*) malloc(sizeof(char*)*string_len);
            if (tmp2 == NULL)
                {
                    printf("######## === MEMORY ALLOCATION ERROR! === ########\n");
                    return NULL;
                }
            arr[i] = tmp2;
            strcpy(arr[i], _2d_arr[i]);
        }

    return arr;
}


void sort(char **table, int rows)                                         //пузырькова сортировка строк через результат функции strcmp()
{
    int i, j;
    char *tmp;

    for (i=0; i<(rows-1); i++)
        {
            for (j=0; j<(rows-1)-i; j++)
                {
                    if (strcmp(table[j], table[j+1])>0)
                        {
                            tmp = table[j];
                            table[j] = table[j+1];
                            table[j+1] = tmp;
                        }
                }
        }
}


void pretty_print(char **origin_table, char **sorted_table, int rows)     //печать таблицы из исходной и сортированной последовательности слов
{
    int i;

    printf("\n=========Result table=========\n");
    printf("\t------------------------------------------------------\n");
    printf("\t| %4c |%-20s\t|%-20s|\n", '#', "Origin", "Sorted (A-z)");
    printf("\t------------------------------------------------------\n");
    for (i=0; i<rows; i++)
        {
            printf("\t| %4d |%-20s\t|%-20s|\n", i+1, origin_table[i], sorted_table[i]);
        }
    printf("\t------------------------------------------------------\n");
    printf("==============================\n");

}


void free_2d_arr_memory(char **_2d_arr, int rows)                         //особождение выделенной под двумерный массив памяти
{
    int i;

    for (i=0; i<rows; i++)
        free((void*) _2d_arr[i]);
    free((void*) _2d_arr);
    
    printf("Memory free!\n");
    printf("==============================\n");
}