#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

/*
�13 - ������������� � ���������� �������� ������������������ ��������, 
������� ����� ������������� ��� �����������, ��������� �� ����, 
���������� ����� ��� ����������� ���������. � ������ � � ����� ����������� 
����� ���������� ������������ ���������� ��������. ����� �� �������� ����������� 
��� �����-���������� � ������� �� � ���������� ���� � ������� ����������� 
������� �����. ��������� �������� � �������������� �������. ��������� ���������� 
�������� ������������. 
*/

/*
��������� ��������� �� ����� ������ ����������� ������������������ �������� ��������,
��������� �� ��������� � �������� ��������� ���� (A-Z, a-z).
������ ����������� ��������� ������, ������������ �������������.
*/

/*
��������� ��� ��������� ���������� �� ��������� ������� ����.
������������ ����� ��� ��������� �����: Non, non.
*/

struct strtbl                                                                       //���������, �������� ��������� ������ � ���������� ������� � ����� ����� �������
{
    char **table;                      //�������� ������ ����
    int rows;                          //���������� ����� ���������� �������
    int *words_length;                 //����� ������ ������ (����� ����� + "�������" ������ ��� �������� ������� ����� ������)
};

extern strtbl write_input_to_2d_arr(char string_end);                               //������ ���� (��������������, ��� ����� ����� ����� ����� ��� 99 ��������) � ��������� ������������ ������ � ����������� ��������� � �������� � ������ ����� � �������
extern strtbl trunkate_2d_arr(char **_2d_arr, int rows);                            //�������� ������ ������ �� ������ ������ � ��������� ����������� � ���������
extern void free_2d_arr_memory(char **_2d_arr, int rows);                           //����������� ���������� ��� ��������� ������ ������
extern strtbl find_all_palindromes(char **_2d_arr, int rows, int *words_length);    //����� ���� ����������� � ��������� �� � ��������� ������, ������� ��������� � ���������
extern int is_palindrome(char *word, int length);                                   //�������� ����� �� ��������
extern int compare_palindromes_by_length(const void *word1, const void *word2);     //������� ���������, ������� ����� ������������ �������� ���������� qsort()
extern void print_words_from_arr(char **_2d_arr, int rows);                         //������ ���� �� ���������� �������
extern void free_2d_arr_memory(char **_2d_arr, int rows, char *str);                //����������� ���������� ��� ��������� ������ ������

int main()
{
    char string_end;                   //���������� ��� �������� ����� ������
    char *name = "main";               //��� �������
    strtbl string_table;

    printf("============================================\n");
    printf("Input string end symbol:\n");
    scanf("%c", &string_end);          //���������� ������ ����� ������

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
    char *name = "write_input_to_2d_arr";   //��� �������
    int i, j;                          //��������
    char c;                            //���������� ��� �������� ������������ ������� �� ������� ������������������
    char **arr, **tmp1;                //���������� ��� �������� ���������� ������� �� ������� � ��� ������������ ���������� ��������� ������ ��� ������
    char *tmp2;                        //���������� ��� ������������ ���������� ��������� ������ ��� �����
    int arr_pos = 0;                   //����������, �������� ������� ������ ���������� �������
    int arr_size = 1;                  //����������, �������� ����� ���������� �������
    int str_pos = 0;                   //����������, �������� ���������� ������ ���������� ������� (������ ������� � ������)
    /*
    ������������, ��� ����� ������� ������������ ����� ����� �� ����� 99 �������� + ������ ����� ������
    */
    int str_size = 100;                //����������, �������� ����� ������ ���������� ������� (������������ ����� �����)
    strtbl string_table;               //���������, � ������� ������������� ���������: ��������� ������ �� ������� � ����� ����� � ���

    string_table.table = NULL;
    string_table.rows = 0;
    string_table.words_length = NULL;

    printf("Input text:\n");

    arr = (char**) malloc(sizeof(char*)*arr_size);                             //�������������� ��������� ������ ��� ��������� ������
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
            ���� ��������� ������ �������� ������, ������ � ���� ������ ����� � ��������� ��� � ������ ���������� ������.
            �������������� ��������� � ������� ������, �������� ��������� �� �����, �������������� ������
            ��� ������ ��������� �� ��������� �����. ����� �������� ������� ������ ���������� ��� �������� �����
            */
                {
                    if (arr_size == arr_pos)
                    /*
                    ���� ��������� �������� ������� (�������, �������� ��������� �� �����)
                    ����� �������� �������� ������� ���������� �������, ��������� ��� ������ � �������,
                    �������� ��������� �� ���������� ������� �� �������.
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

                    tmp2  = (char*) calloc(str_size, sizeof(char));             //�������� ������� ������ ��� �������� ���������� �����
                    if (tmp2 == NULL)
                        {
                            printf("######## === MEMORY ALLOCATION ERROR! in %s === ########\n", name);
                            return string_table;
                        }
                    arr[arr_pos] = tmp2;

                    do                                                         //������ � ���� ������ �����
                        {
                            arr[arr_pos][str_pos] = c;                         //������� ����������� ����� � ��������� ������
                            str_pos++;                                         //����������� ������
                            c = getchar();                                     //��������� ����� ������ � ����� ������ �����
                        }
                    while ((c > 64 && c < 91) || (c > 96 && c < 123));

                    arr[arr_pos][str_pos] = '\0';                              //����� ����� ����� ��������� ������ ����� ������
                    str_pos = 0;                                               //�������� ���������� ������ � ���������� ��������
                    arr_pos++;                                                 //����������� ����������, �������� ������ �����, �� �������
                }
        }
    while (c != string_end);

    if (!arr_pos)                                                              //�������� �������� ������������������ �� �������
        {
            free((void*) arr);
            printf("\n\tEmpty string!\n\n");
        }
    else
        {
            string_table.table = arr;                                          //������� ���������� � ���������
            string_table.rows = arr_size;
        }

    printf("============================================\n");

    return string_table;
}


strtbl trunkate_2d_arr(char **_2d_arr, int rows)                                    //�������� ������ ������ �� ������ ������ � ��������� ����������� � ���������
{
    char *name = "trunkate_2d_arr";                        //���������� � ������ �������
    int i, j;                                              //��������
    int len;                                               //���������� ��� ����� �������, ����������� ����� (����� ������ + "�������" ������� ������ ��� �������� ������� ����� ������)
    int *words_length;                                     //������, �������� ������������ ����� ������ ������
    char **trunk_arr;                                      //��������� ������, �� �������� ������� ������ ������ ��� ������ �����
    strtbl string_table;

    string_table.table = NULL;
    string_table.rows = rows;
    string_table.words_length = NULL;

    trunk_arr = (char**) calloc(rows, sizeof(char*));      //������� ������ ��� ������� ������ ���������� �������, ���������� ��������� �� �����
    words_length = (int*) calloc(rows, sizeof(int));       //�������� ������ ��� ������ � ������� ������� �����
    if (trunk_arr == NULL || words_length == NULL)         //�������� ��������� ������
        {
            printf("######## === MEMORY ALLOCATION ERROR! in %s === ########\n", name);
            return string_table;
        }

    for (i=0; i<rows; i++)                                 //���� ���������� ������ ������� � ������ �����, ��������������� �������� ����� ����
        {
            len = strlen(_2d_arr[i]) + 1;                  //���������� ����� ������� ��� �������� ������ ������ � ������ ��������������� ������� ����� ������
            trunk_arr[i] = (char*) calloc(len, sizeof(char));        //��������� ������ ��� ������ ������
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


extern strtbl find_all_palindromes(char **_2d_arr, int rows, int *words_length)     //����� ���� ����������� � ��������� �� � ��������� ������, ������� ��������� � ���������
{
    char *name = "find_all_palindromes";    //��� �������
    int i, count(0);                   //��������                
    int arr_pos = 0;                   //���������� ��� ������� ������� ��������� ������� �������
    int arr_size = 1;                  //���������� ��� �������� ����� �������
    int *pal_words_length, *tmp1;      //������ ��� �������� ����� ����� �� �������-������������ (����� ������ = ����� ����� + ������ ����� ������), ���������� ��� ����� ��������� ������
    char *tmp2;                        //���������� ��� ����� ��������� ������
    char **pal_arr, **tmp3;            //��������� ������ ��� �������� �����, ���������� ��� ����� ��������� ������
    strtbl string_table;

    string_table.table = NULL;
    string_table.rows = 0;
    string_table.words_length = NULL;

    pal_words_length = (int*) malloc(sizeof(int)*arr_size);     //������������� �������, ��������� ����� �����
    pal_arr = (char**) malloc(sizeof(char*)*arr_size);          //������������� �������� ������� � ����������� �� ������

    for (i=0; i<rows; i++)                                      //���� �������� ���� �� ����������
        {
            if (is_palindrome(_2d_arr[i], words_length[i]))
                {
                    if (arr_size==arr_pos)                      //��������� ������ �� ������� ������ ��� ������ ��������� �� ������ � ������ � ������ � ������� ����� ����-�����������
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
                    
                    tmp2 = (char*) calloc(words_length[i], sizeof(char));      //�������� ������ ��� ������ �� ������
                    if (tmp2 == NULL)
                        {
                            printf("######## === MEMORY ALLOCATION ERROR in %s! === ########\n", name);
                            return string_table;
                        }

                    pal_arr[arr_pos] = tmp2;

                    strcpy(pal_arr[arr_pos], _2d_arr[i]);                      //���������� ������ � ����������� � ������ pal_arr
                    pal_words_length[arr_pos] = words_length[i];               //���������� ����� ������ � ����������� � ������ pal_words_length
                    arr_pos++;
                }
        }

    if (!arr_pos)                                                              //�������� �� ���������� �����������
        {
            pal_arr[arr_pos] = NULL;
            pal_words_length[arr_pos] = 0;
        }
    else    
        qsort(pal_arr, arr_size, sizeof(char*), compare_palindromes_by_length);

    string_table.table = pal_arr;                                              //������� ���������� � ���������
    string_table.rows = arr_size;
    string_table.words_length = pal_words_length;

    free_2d_arr_memory(_2d_arr, rows, name);

    return string_table;
}


int is_palindrome(char *word, int length)                                           //�������� ����� �� ���������
{
    int i, j;

    for (i=0, j=length-2; i<length, j>(-1); i++, j--)
        if (tolower(word[i]) != tolower(word[j]))
            return 0;

    return 1;
}


int compare_palindromes_by_length(const void *word1, const void *word2)             //������� ���������, ������� ����� ������������ �������� ���������� qsort()
{
    char **w1, **w2;

    w1 = (char**) word1;
    w2 = (char**) word2;

    return strlen((char*) *w1) - strlen((char*) *w2);
}


void print_words_from_arr(char **_2d_arr, int rows)                                 //������ ���� �� ���������� �������
{
    int i;

    printf("\n\t==================RESULT===================\n");
    printf("\t| %4s |%-34s|\n", "#", "Palindromes");
    printf("\t-------------------------------------------\n");

    for (i=0; i<rows; i++)
            printf("\t| %4d |%-34s|\n", i+1, _2d_arr[i]);
    
    printf("\t===========================================\n\n");
}


void free_2d_arr_memory(char **_2d_arr, int rows, char *str)                        //����������� ���������� ��� ��������� ������ ������
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