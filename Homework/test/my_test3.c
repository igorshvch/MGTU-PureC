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

    printf("����� � ���������� �� ���������\n");
    printf("������ ���� struct str_table: %d\n", sizeof(struct str_table));
    (*nt).rows = 0;
    printf("�� ���������: nt.rows=%d\n", (*nt).rows);
    (*nt).rows = 123;
    printf("����� ���������: nt.rows=%d\n", (*nt).rows);

    int i, res;
    printf("������� ������ �������:\n");
    scanf("%d", &i);
    
    //printf("��� ��������� � ���������� hashtable2:%p\n", hashtable2);
      
    res = my_func();//nt);

    printf("��������� => nt.records[%d]=%s, nt.rows=%d\n", (*nt).rows, (*nt).records[(*nt).rows], (*nt).rows);
    free((void*) nt);
    free((void*) nt);
    printf("������� ������, ��� ��\n");
    
    return 0;
}

int my_func()//struct str_table *nt)
{
    char *fname = "my_func2";
    char *n;
    char *str1 = "Name";

    (*nt).rows++;
    printf("FUNC %s -> ����� ���������: nt.rows=%d\n", fname, (*nt).rows);
    (*nt).records = (char**) realloc((*nt).records, sizeof(char*)*(*nt).rows);

    (*nt).records[(*nt).rows] = str1;

    return 0;
}