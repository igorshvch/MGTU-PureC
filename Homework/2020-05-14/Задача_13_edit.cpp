#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

struct strtbl                                                                       //структура, хранящая двумерный массив с введенными словами и число строк массива
{
    char **table;
    int rows;
    int *words_length;
};

extern strtbl write_input_to_2d_arr(char string_end);                               //запись слов в двумерный динамический массив и возвращения структуры с массивом и числом строк в массиве
extern strtbl trunkate_2d_arr(char **_2d_arr, int rows);
extern void free_2d_arr_memory(char **_2d_arr, int rows);                           //особождение выделенной под двумерный массив памяти
extern int is_palindrome(char *word, int length);
extern strtbl find_all_palindromes(char **_2d_arr, int rows, int *words_length);
extern int compare_palindromes_by_length(const void *word1, const void *word2);
extern void print_words_from_arr(char **_2d_arr, int rows, char *name);
extern void free_2d_arr_memory(char **_2d_arr, int rows, char *str);                //особождение выделенной под двумерный массив памяти

int main()
{
    char string_end;
    char *name = "main";
    strtbl string_table;

    printf("============================================\n");
    printf("Input string end symbol:\n");
    scanf("%c", &string_end);          //записываем символ конца строки

    printf("START: write_input_to_2d_arr\n");
    string_table = write_input_to_2d_arr(string_end);
    if (string_table.table == NULL) return 0;

    printf("START: trunkate_2d_arr\n");
    string_table = trunkate_2d_arr(string_table.table, string_table.rows);
    if (string_table.table == NULL) return 0;

    printf("START: find_all_palindromes\n");
    string_table = find_all_palindromes(string_table.table, string_table.rows, string_table.words_length);
    if (string_table.table == NULL) return 0;

    printf("START: print_words_from_arr\n");
    print_words_from_arr(string_table.table, string_table.rows, name);
    printf("\n");

    printf("START: free_2d_arr_memory\n");
    free_2d_arr_memory(string_table.table, string_table.rows, name);
    
    getch();
    return 0;
}


strtbl write_input_to_2d_arr(char string_end)
{
    char *name = "write_input_to_2d_arr";
    int i, j;                          //счетчики
    char c;                            //переменная для хранения считываемого символа из входной последовательности
    char **arr, **tmp1;                //переменные для хранения двумерного массива со словами и для тестирования результата выделения памяти под массив
    char *tmp2;                        //переменная для тестирования результата выделения памяти под слово
    int arr_pos = 0;                   //переменная, хранящая внешний индекс двумерного массива
    int arr_size = 1;                  //переменная, хранящая длину двумерного массива
    int str_pos = 0;                   //переменная, хранящая внутренний индекс двумерного массива (индекс символа в строке)
    int str_size = 100;                 //переменная, хранящая длину строки двумерного массива
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
                    Если количество строк внешнего массива (области, хранящей указатели на слова)
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

                    arr[arr_pos][str_pos] = '\0';                              //после конца слова добавляем символ конца строки в массиве
                    str_pos = 0;                                               //приводим внутренний индекс к начальному значению
                    arr_pos++;                                                 //увеличиваем переменную, хранящую числов строк, на единицу
                }
        }
    while (c != string_end);

    string_table.table = arr;                                                  //заносим результаты в структуру
    string_table.rows = arr_size;

    print_words_from_arr(arr, arr_size, name);

    printf("============================================\n");

    return string_table;
}


strtbl trunkate_2d_arr(char **_2d_arr, int rows)
{
    char *name = "trunkate_2d_arr";
    int i, j;
    int len;
    int *words_length;
    char **trunk_arr;
    strtbl string_table;

    string_table.table = NULL;
    string_table.rows = rows;
    string_table.words_length = NULL;

    printf("\tFUNC %s: starts\n", name);

    trunk_arr = (char**) calloc(rows, sizeof(char*));
    words_length = (int*) calloc(rows, sizeof(int));
    printf("\tFUNC %s: memmory alloc\n", name);
    if (trunk_arr == NULL || words_length == NULL)
        {
            printf("######## === MEMORY ALLOCATION ERROR! in %s === ########\n", name);
            return string_table;
        }
    printf("\tFUNC %s: start cycle\n", name);
    for (i=0; i<rows; i++)
        {
            //printf("\t\tFUNC %s STEP %4d: cycle step\n", name, i);
            len = strlen(_2d_arr[i]);
            trunk_arr[i] = (char*) calloc(len+1, sizeof(char));
            if (trunk_arr[i] == NULL)
                {
                    printf("######## === MEMORY ALLOCATION ERROR! in %s === ########\n", name);
                    return string_table;
                }
            strcpy(trunk_arr[i], _2d_arr[i]);
            words_length[i] = len+1;
        }

    print_words_from_arr(trunk_arr, rows, name);
    
    string_table.table = trunk_arr;
    string_table.words_length = words_length;

    free_2d_arr_memory(_2d_arr, rows, name);

    return string_table;
}


int is_palindrome(char *word, int length)
{
    char *name = "is_palindrome";
    int i, j;
    
    printf("\t\t\tTHIS IS %s FUNC! word: %s\n", name, word);

    for (i=0, j=length-2; i<length, j>(-1); i++, j--)
        {
            printf("\t\t\t\tFUNC %s STEP %4d: i=%2d, j=%2d, c%2d=%c, c%2d=%c\n", name, i, i, j, i, word[i], j, word[j]);
            if (word[i] != word[j])
                {
                    printf("\t\t\t\tTHIS IS NOT PAL!\n");
                    return 0;
                }
        }
    printf("\t\tTHIS IS PAL\n");

    return 1;
}


extern strtbl find_all_palindromes(char **_2d_arr, int rows, int *words_length)
{
    char *name = "find_all_palindromes";
    int i, j, k;
    int arr_pos = 0;
    int arr_size = 1;
    int len;
    int *pal_words_length, *tmp1;
    char *tmp2;
    char **pal_arr, **tmp3;
    strtbl string_table;

    string_table.table = NULL;
    string_table.rows = 0;
    string_table.words_length = NULL;

    pal_words_length = (int*) malloc(sizeof(int)*arr_size);
    pal_arr = (char**) malloc(sizeof(char*)*arr_size);

    for (i=0; i<rows; i++)
        {
            if (arr_size == arr_pos)
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
            if (is_palindrome(_2d_arr[i], words_length[i]))
                {
                    tmp2 = (char*) calloc(words_length[i], sizeof(char));
                    if (tmp2 == NULL)
                        {
                            printf("######## === MEMORY ALLOCATION ERROR in %s! === ########\n", name);
                            return string_table;
                        }
                    pal_arr[arr_pos] = tmp2;
                    strcpy(pal_arr[arr_pos], _2d_arr[i]);
                    pal_words_length[arr_pos] = words_length[i];
                    arr_pos++;
                }
        }
    
    printf("FUNC %s: arr_size = %d\n", name, arr_size);
    qsort(pal_arr, arr_size-1, sizeof(char*), compare_palindromes_by_length);

    string_table.table = pal_arr;
    string_table.rows = arr_size-1;
    string_table.words_length = pal_words_length;

    free_2d_arr_memory(_2d_arr, rows, name);

    return string_table;
}


int compare_palindromes_by_length(const void *word1, const void *word2)
{
    char **w1, **w2;

    w1 = (char**) word1;
    w2 = (char**) word2;

    printf("\t\t\tFUNC cmp: %s, %s, %d - %d = %d\n", (char*) *w1, (char*) *w2, strlen((char*) *w1), strlen((char*) *w2), strlen((char*) *w1) - strlen((char*) *w2));

    return strlen((char*) *w1) - strlen((char*) *w2);
}


void print_words_from_arr(char **_2d_arr, int rows, char *name)
{
    int i;

    printf("\n\t==================RESULT===================\n");
    printf("\t|function CALL FROM %20s()|\n", name);
    printf("\t-------------------------------------------\n");

    for (i=0; i<rows; i++)
            printf("\t| %4d |%-34s|\n", i+1, _2d_arr[i]);
    
    printf("\t===========================================\n\n");
}


void free_2d_arr_memory(char **_2d_arr, int rows, char *str)                   //особождение выделенной под двумерный массив памяти
{
    int i;

    for (i=0; i<rows; i++)
        free((void*) _2d_arr[i]);
    free((void*) _2d_arr);
    
    printf("function CALL FROM %20s()\n", str);
    printf("Memory free!\n");
    printf("============================================\n");
}