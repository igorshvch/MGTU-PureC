#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

/*
№13 - Пользователем с клавиатуры вводится последовательность символов, 
которую можно рассматривать как предложение, состоящее из слов, 
разделённых одним или несколькими пробелами. В начале и в конце предложения 
может находиться произвольное количество пробелов. Найти во введённом предложении 
все слова-палиндромы и вывести их в консольное окно в порядке возрастания 
размера слова. Программу написать с использованием функций. Последнее требование 
является обязательным. 
*/

/*
Программа принимает за слово только непрерывную последовательность символов алфавита,
состоящую из заглавных и строчных латинских букв (A-Z, a-z).
Концом предложения считается символ, определенный пользователем.
*/

/*
Программа при выявлении палиндрома не различает регистр букв.
Палиндромами будут оба следующих слова: Non, non.
*/

struct strtbl                                                                       //структура, хранящая двумерный массив с введенными словами и число строк массива
{
    char **table;                      //думерный массив слов
    int rows;                          //количестов строк двумерного массива
    int *words_length;                 //длина каждой строки (длина слова + "единица" памяти для хранения символа конца строки)
};

extern strtbl write_input_to_2d_arr(char string_end);                               //запись слов (предполагается, что слово может иметь длину дол 99 символов) в двумерный динамический массив и возвращения структуры с массивом и числом строк в массиве
extern strtbl trunkate_2d_arr(char **_2d_arr, int rows);                            //удаление лишней памяти из каждой строки и занесение результатов в структуру
extern void free_2d_arr_memory(char **_2d_arr, int rows);                           //особождение выделенной под двумерный массив памяти
extern strtbl find_all_palindromes(char **_2d_arr, int rows, int *words_length);    //поиск всех палиндромов и занесение их в двумерный массив, который заносится в структуру
extern int is_palindrome(char *word, int length);                                   //проверка слова на палинром
extern int compare_palindromes_by_length(const void *word1, const void *word2);     //функция сравнения, которая будет использована функцией сортировки qsort()
extern void print_words_from_arr(char **_2d_arr, int rows);                         //печать слов из двумерного массива
extern void free_2d_arr_memory(char **_2d_arr, int rows, char *str);                //особождение выделенной под двумерный массив памяти

int main()
{
    char string_end;                   //переменная для хранения конца строки
    char *name = "main";               //имя функции
    strtbl string_table;

    printf("============================================\n");
    printf("Input string end symbol:\n");
    scanf("%c", &string_end);          //записываем символ конца строки

    string_table = write_input_to_2d_arr(string_end);
    if (string_table.table == NULL) return 0;

    string_table = trunkate_2d_arr(string_table.table, string_table.rows);
    if (string_table.table == NULL) return 0;

    string_table = find_all_palindromes(string_table.table, string_table.rows, string_table.words_length);
    if (string_table.table == NULL) return 0;

    if (string_table.table[0])
        print_words_from_arr(string_table.table, string_table.rows);
    else
        printf("\n\tNo palindromes!\n\n");
    
    free_2d_arr_memory(string_table.table, string_table.rows, name);

    getch();
    return 0;
}


strtbl write_input_to_2d_arr(char string_end)
{
    char *name = "write_input_to_2d_arr";   //имя функции
    int i, j;                          //счетчики
    char c;                            //переменная для хранения считываемого символа из входной последовательности
    char **arr, **tmp1;                //переменные для хранения двумерного массива со словами и для тестирования результата выделения памяти под массив
    char *tmp2;                        //переменная для тестирования результата выделения памяти под слово
    int arr_pos = 0;                   //переменная, хранящая внешний индекс двумерного массива
    int arr_size = 1;                  //переменная, хранящая длину двумерного массива
    int str_pos = 0;                   //переменная, хранящая внутренний индекс двумерного массива (индекс символа в строке)
    /*
    Предполагаем, что длина каждого считываемого слова будет не более 99 символов + символ конца строки
    */
    int str_size = 100;                //переменная, хранящая длину строки двумерного массива (максимальную длину слова)
    strtbl string_table;               //структура, в которую записсывается результат: двумерный массив со словами и число строк в нем

    string_table.table = NULL;
    string_table.rows = 0;
    string_table.words_length = NULL;

    printf("Input text:\n");

    arr = (char**) malloc(sizeof(char*)*arr_size);                             //первоначальное выделение памяти под двумерный массив
    if (arr == NULL)
        {
            printf("######## === MEMORY ALLOCATION ERROR! in %s === ########\n", name);
            return string_table; 
        }
    
    do
        {
            c = getchar();
            if ((c > 64 && c < 91) || (c > 96 && c < 123))
            /*
            Если считанный символ явялется буквой, входим в цикл чтения слова и занесения его в строку двумерного массва.
            Предварительно добавляем к области памяти, хранящей указатели на слова, дополнительную память
            для нового указателя на очередное слово. ТАкже выделяем область памяти собственно для хранения слова
            */
                {
                    if (arr_size == arr_pos)
                    /*
                    Если элементов внешнего массива (области, хранящей указатели на слова)
                    равна значению внешнего индекса двумерного массива, добавляем еще память к области,
                    хранящей указатели на одномерные массивы со словами.
                    */
                        {
                            arr_size++;
                            tmp1 = (char**) realloc(arr, sizeof(char*)*arr_size);
                            if (tmp1 == NULL)
                                {
                                printf("######## === MEMORY ALLOCATION ERROR! in %s === ########\n", name);
                                return string_table;
                                }
                            arr = tmp1;
                        }

                    tmp2  = (char*) calloc(str_size, sizeof(char));             //выделяем область памяти для хранения очередного слова
                    if (tmp2 == NULL)
                        {
                            printf("######## === MEMORY ALLOCATION ERROR! in %s === ########\n", name);
                            return string_table;
                        }
                    arr[arr_pos] = tmp2;

                    do                                                         //входим в цикл чтения слова
                        {
                            arr[arr_pos][str_pos] = c;                         //заносим прочитанную букву в двумерный массив
                            str_pos++;                                         //увеличиваем индекс
                            c = getchar();                                     //считываем новый символ в цикле чтения слова
                        }
                    while ((c > 64 && c < 91) || (c > 96 && c < 123));

                    arr[arr_pos][str_pos] = '\0';                              //после конца слова добавляем символ конца строки
                    str_pos = 0;                                               //приводим внутренний индекс к начальному значению
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

    printf("============================================\n");

    return string_table;
}


strtbl trunkate_2d_arr(char **_2d_arr, int rows)                                    //удаление лишней памяти из каждой строки и занесение результатов в структуру
{
    char *name = "trunkate_2d_arr";                        //переменная с именем функции
    int i, j;                                              //счетчики
    int len;                                               //переменная для длины массива, содержащего слово (длина строки + "единица" области памяти для хранения символа конца строки)
    int *words_length;                                     //массив, хранящий ффактическую длину каждой строки
    char **trunk_arr;                                      //двумерный массив, их которого удалена лишняя память под каждое слово
    strtbl string_table;

    string_table.table = NULL;
    string_table.rows = rows;
    string_table.words_length = NULL;

    trunk_arr = (char**) calloc(rows, sizeof(char*));      //выедяем память под внешний массив двумерного массива, содержащий указатели на слова
    words_length = (int*) calloc(rows, sizeof(int));       //выделяем память под массив с длинами каждого слова
    if (trunk_arr == NULL || words_length == NULL)         //проверка выделения памяти
        {
            printf("######## === MEMORY ALLOCATION ERROR! in %s === ########\n", name);
            return string_table;
        }

    for (i=0; i<rows; i++)                                 //цикл заполнения нового массива с длиной строк, соответствующей реальной длине слов
        {
            len = strlen(_2d_arr[i]) + 1;                  //вычисление длины массива под хранение каждой строки с учетом дополнительного символа конца строки
            trunk_arr[i] = (char*) calloc(len, sizeof(char));        //выделение памяти для каждой строки
            if (trunk_arr[i] == NULL)
                {
                    printf("######## === MEMORY ALLOCATION ERROR! in %s === ########\n", name);
                    return string_table;
                }
            strcpy(trunk_arr[i], _2d_arr[i]);
            words_length[i] = len;
        }
    
    string_table.table = trunk_arr;
    string_table.words_length = words_length;

    free_2d_arr_memory(_2d_arr, rows, name);

    return string_table;
}


extern strtbl find_all_palindromes(char **_2d_arr, int rows, int *words_length)     //поиск всех палиндромов и занесение их в двумерный массив, который заносится в структуру
{
    char *name = "find_all_palindromes";    //имя функции
    int i, count(0);                   //счетчики                
    int arr_pos = 0;                   //переменная для хранния индекса последней позиции массива
    int arr_size = 1;                  //переменная для хранения длины массива
    int *pal_words_length, *tmp1;      //массив для хранения длинн строк со словами-палиндромами (длина строки = длина слова + символ конца строки), переменная для теста выделения памяти
    char *tmp2;                        //переменная для теста выделения памяти
    char **pal_arr, **tmp3;            //двумерный массив для хранения строк, переменная для теста выделения памяти
    strtbl string_table;

    string_table.table = NULL;
    string_table.rows = 0;
    string_table.words_length = NULL;

    pal_words_length = (int*) malloc(sizeof(int)*arr_size);     //инициализация массива, хранящего длины строк
    pal_arr = (char**) malloc(sizeof(char*)*arr_size);          //инициализация внешнего массива с указателями на строки

    for (i=0; i<rows; i++)                                      //цикл проверки слов на палиндромы
        {
            if (is_palindrome(_2d_arr[i], words_length[i]))
                {
                    if (arr_size==arr_pos)                      //добавляем память во внешний массив для нового указателя на строку и память в массив с длинами строк слов-палиндромов
                        {
                            arr_size++;
                            tmp1 = (int*) realloc(pal_words_length, sizeof(int)*arr_size);
                            tmp3 = (char**) realloc(pal_arr, sizeof(char*)*arr_size);
                            if (tmp1 == NULL || tmp3 == NULL )
                                {
                                    printf("######## === MEMORY ALLOCATION ERROR in %s! === ########\n", name);
                                    return string_table;
                                }

                            pal_words_length = tmp1;
                            pal_arr = tmp3;
                        }
                    
                    tmp2 = (char*) calloc(words_length[i], sizeof(char));      //выделяем память для строки со словом
                    if (tmp2 == NULL)
                        {
                            printf("######## === MEMORY ALLOCATION ERROR in %s! === ########\n", name);
                            return string_table;
                        }

                    pal_arr[arr_pos] = tmp2;

                    strcpy(pal_arr[arr_pos], _2d_arr[i]);                      //записываем строку с палиндромом в массив pal_arr
                    pal_words_length[arr_pos] = words_length[i];               //записываем длину строки с палиндромом в массив pal_words_length
                    arr_pos++;
                }
        }

    if (!arr_pos)                                                              //проверка на отсутствие палиндромов
        {
            pal_arr[arr_pos] = NULL;
            pal_words_length[arr_pos] = 0;
        }
    else    
        qsort(pal_arr, arr_size, sizeof(char*), compare_palindromes_by_length);

    string_table.table = pal_arr;                                              //заносим результаты в структуру
    string_table.rows = arr_size;
    string_table.words_length = pal_words_length;

    free_2d_arr_memory(_2d_arr, rows, name);

    return string_table;
}


int is_palindrome(char *word, int length)                                           //проверка слова на палиндром
{
    int i, j;

    for (i=0, j=length-2; i<length, j>(-1); i++, j--)
        if (tolower(word[i]) != tolower(word[j]))
            return 0;

    return 1;
}


int compare_palindromes_by_length(const void *word1, const void *word2)             //функция сравнения, которая будет использована функцией сортировки qsort()
{
    char **w1, **w2;

    w1 = (char**) word1;
    w2 = (char**) word2;

    return strlen((char*) *w1) - strlen((char*) *w2);
}


void print_words_from_arr(char **_2d_arr, int rows)                                 //печать слов из двумерного массива
{
    int i;

    printf("\n\t==================RESULT===================\n");
    printf("\t| %4s |%-34s|\n", "#", "Palindromes");
    printf("\t-------------------------------------------\n");

    for (i=0; i<rows; i++)
            printf("\t| %4d |%-34s|\n", i+1, _2d_arr[i]);
    
    printf("\t===========================================\n\n");
}


void free_2d_arr_memory(char **_2d_arr, int rows, char *str)                        //особождение выделенной под двумерный массив памяти
{
    int i;

    for (i=0; i<rows; i++)
        {
            //printf("ID: %4d ADDRESS: %p, string: %s\n", i, _2d_arr[i], _2d_arr[i]);
            free((void*) _2d_arr[i]);
        }
    free((void*) _2d_arr);
    
    printf("Memory free!\n");
    printf("[function CALL FROM %20s()]\n", str);
    printf("============================================\n");
}