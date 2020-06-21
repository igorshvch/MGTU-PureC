#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <locale.h>
#include <Windows.h>

#define HASHSIZE 5


struct nlist
{
    char *name;
    char *defn;
};


//struct nlist hashtable[HASHSIZE];
struct nlist *hashtable2[HASHSIZE];
struct nlist orig_nl, *nl = &orig_nl;


int main()
{
    setlocale(LC_ALL, "Russian_Russia.1251");
    const UINT CodePageID = 1251 ;
    SetConsoleCP(CodePageID);
    SetConsoleOutputCP(CodePageID);

    printf("����� � ���������� �� ���������\n");
    //printf("�� ���������: nl.name=%s, nl.defn=%s\n", (*nl).name, (*nl).defn);
    (*nl).name="���";
    (*nl).defn="�����";
    printf("����� ���������: nl.name=%s, nl.defn=%s\n", (*nl).name, (*nl).defn);

    int i, res;
    printf("������� ������ �������:\n");
    scanf("%d", &i);
    
    //printf("��� ��������� � ���������� hashtable2:%p\n", hashtable2);
      
    res = my_func(hashtable2, i);
    
    if (res == -1)
        {
            printf("��������� ������ �� ��������� �������\n");
            getch();
            return -1;
        }
    else
        {
            printf("��������� => �������: %d, nlist.name=%s, nlist.defn=%s\n", i, hashtable2[i]->name, hashtable2[i]->defn);
        }
    return 0;
}

int my_func(struct nlist **hashtable, int i)
{
    char *fname = "my_func2";
    char *n;
    char *str1 = "Name";

    struct nlist *nl;

    nl = (struct nlist*) malloc(sizeof(struct nlist));

    printf("FUNC %s -> ���� � �������\n", fname);
    if (i>HASHSIZE)
        {
            printf("����� ������!\n");
            return -1;
        }
    n = (char*)malloc(sizeof(char)*strlen(str1));
    strcpy(n, str1);

    printf("FUNC %s -> ������ 'str1'(%s) ����������� � 'n'(%s)\n", fname, str1, n);

    printf("FUNC %s -> ��������� ��������� ��������\n", fname);
    hashtable[i] = nl;
    hashtable[i]->name = n;
    printf("FUNC %s -> ����� ��� name\n", fname);
    hashtable[i]->defn="Def";
    printf("FUNC %s -> ����� ��� defn\n", fname);
    printf("FUNC %s -> ��� ����������, ����� �� �������\n", fname);
    return 0;
}