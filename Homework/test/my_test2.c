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

    printf("Проба с указателем на структуру\n");
    //printf("До изменений: nl.name=%s, nl.defn=%s\n", (*nl).name, (*nl).defn);
    (*nl).name="Имя";
    (*nl).defn="Опред";
    printf("После изменений: nl.name=%s, nl.defn=%s\n", (*nl).name, (*nl).defn);

    int i, res;
    printf("Введите индекс массива:\n");
    scanf("%d", &i);
    
    //printf("Что находится в переменной hashtable2:%p\n", hashtable2);
      
    res = my_func(hashtable2, i);
    
    if (res == -1)
        {
            printf("Введенный индекс за пределами массива\n");
            getch();
            return -1;
        }
    else
        {
            printf("Результат => позиция: %d, nlist.name=%s, nlist.defn=%s\n", i, hashtable2[i]->name, hashtable2[i]->defn);
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

    printf("FUNC %s -> вход в функцию\n", fname);
    if (i>HASHSIZE)
        {
            printf("Здесь ошибка!\n");
            return -1;
        }
    n = (char*)malloc(sizeof(char)*strlen(str1));
    strcpy(n, str1);

    printf("FUNC %s -> строка 'str1'(%s) скопирована в 'n'(%s)\n", fname, str1, n);

    printf("FUNC %s -> попробуем присвоить значения\n", fname);
    hashtable[i] = nl;
    hashtable[i]->name = n;
    printf("FUNC %s -> успех для name\n", fname);
    hashtable[i]->defn="Def";
    printf("FUNC %s -> успех для defn\n", fname);
    printf("FUNC %s -> все получилось, выход из функции\n", fname);
    return 0;
}