#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <locale.h>
#include <Windows.h>

#define HASHSIZE 5

struct str_table
{
    char **records;
    int rows;
};

static struct str_table *nt;



int main()
{
    setlocale(LC_ALL, "Russian_Russia.1251");
    const UINT CodePageID = 1251 ;
    SetConsoleCP(CodePageID);
    SetConsoleOutputCP(CodePageID);

    nt = (struct str_table*) malloc(sizeof(struct str_table));

    printf("Проба с указателем на структуру\n");
    printf("Размер типа struct str_table: %d\n", sizeof(struct str_table));
    (*nt).rows = 0;
    printf("До изменений: nt.rows=%d\n", (*nt).rows);
    (*nt).rows = 123;
    printf("После изменений: nt.rows=%d\n", (*nt).rows);

    int i, res;
    printf("Введите индекс массива:\n");
    scanf("%d", &i);
    
    //printf("Что находится в переменной hashtable2:%p\n", hashtable2);
      
    res = my_func();//nt);

    printf("Результат => nt.records[%d]=%s, nt.rows=%d\n", (*nt).rows, (*nt).records[(*nt).rows], (*nt).rows);
    free((void*) nt);
    free((void*) nt);
    printf("Удалили дважды, все ок\n");
    
    return 0;
}

int my_func()//struct str_table *nt)
{
    char *fname = "my_func2";
    char *n;
    char *str1 = "Name";

    (*nt).rows++;
    printf("FUNC %s -> после изменений: nt.rows=%d\n", fname, (*nt).rows);
    (*nt).records = (char**) realloc((*nt).records, sizeof(char*)*(*nt).rows);

    (*nt).records[(*nt).rows] = str1;

    return 0;
}