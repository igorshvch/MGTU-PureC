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
    struct nlist *next;
    char *name;
    char *defn;
};

struct nlist2
{
    char *name;
    char *defn;
};

int my_func(struct nlist *hashtable, int i);
int my_func2(struct nlist2 hashtable, int i);


struct nlist hashtable[HASHSIZE];
struct nlist2 *hashtable2[HASHSIZE];


int main()
{
    setlocale(LC_ALL, "Russian_Russia.1251");
    const UINT CodePageID = 1251 ;
    SetConsoleCP(CodePageID);
    SetConsoleOutputCP(CodePageID);

    int i, res;
    printf("Введите индекс массива:\n");
    scanf("%d", &i);
    printf("Что находится в переменной hashtable:%p\n", hashtable);
    printf("Что находится в переменной hashtable[%d].next:%p\n", i, hashtable[i].next);
    printf("Что находится в переменной hashtable[%d].name:%p\n", i, hashtable[i].name);
    printf("Что находится в переменной hashtable[%d].defn:%p\n", i, hashtable[i].defn);
    printf("Что находится в переменной &hashtable[%d].next:%p\n", i, &hashtable[i].next);
    printf("Что находится в переменной &hashtable[%d].name:%p\n", i, &hashtable[i].name);
    printf("Что находится в переменной &hashtable[%d].defn:%p\n", i, &hashtable[i].defn);

    res = my_func(hashtable, i);
    
    if (res == -1)
        {
            printf("Введенный индекс за пределами массива\n");
            getch();
            return -1;
        }
    else
        {
            printf(
                "Результат => позиция: %d, nlist.name=%s, nlist.defn=%s, nlist.next=%p\n",
                i,
                hashtable[i].name,
                hashtable[i].defn,
                hashtable[i].next
                );
            printf("Что находится в переменной hashtable:%p\n", hashtable);
            printf("Что находится в переменной hashtable[%d].next:%p\n", i, hashtable[i].next);
            printf("Что находится в переменной hashtable[%d].name:%p\n", i, hashtable[i].name);
            printf("Что находится в переменной hashtable[%d].defn:%p\n", i, hashtable[i].defn);
            printf("Что находится в переменной &hashtable[%d].next:%p\n", i, &hashtable[i].next);
            printf("Что находится в переменной &hashtable[%d].name:%p\n", i, &hashtable[i].name);
            printf("Что находится в переменной &hashtable[%d].defn:%p\n", i, &hashtable[i].defn);
            printf("Что находится в переменной *hashtable[%d].name:(c1)%c\n", i, *hashtable[i].name);
            printf("Что находится в переменной *hashtable[%d].name:(c2)%c\n", i, (*hashtable[i].name+1));
            printf("Что находится в переменной *hashtable[%d].name:(c3)%c\n", i, (*hashtable[i].name+2));
            printf("Что находится в переменной *hashtable[%d].name:(c4)%c\n", i, (*hashtable[i].name+3));
            printf("Что находится в переменной *hashtable[%d].defn:(c1)%c\n", i, *hashtable[i].defn);
            printf("Что находится в переменной *hashtable[%d].defn:(c2)%c\n", i, (*hashtable[i].defn+1));
            printf("Что находится в переменной *hashtable[%d].defn:(c3)%c\n", i, (*hashtable[i].defn+2));
            printf("Что находится в переменной *hashtable[%d].defn:(c4)%c\n", i, (*hashtable[i].defn+3));
            printf("Что находится в переменной hashtable[%d].name:(s)%s\n", i, hashtable[i].name);
            printf("Что находится в переменной hashtable[%d].defn:(s)%s\n", i, hashtable[i].defn);
            getch();
        }
    printf("\n\n=========== ВТОРАЯ ЧАСТЬ c *hashtable2 ===========\n\n");
    printf("\nВведите индекс массива:\n");
    scanf("%d", &i);
    printf("Что находится в переменной hashtable2:%p\n", hashtable2);
    printf("Что находится в переменной (*hashtable2):%p\n", (*hashtable2));
    //printf("Что находится в переменной hashtable2[%d].next:%p\n", i, &(*hashtable2)[i].next);
    printf("Что находится в переменной hashtable2[%d].name:%p\n", i, &(*hashtable2)[i].name);
    //printf("Что находится в переменной hashtable2.name:%p\n", i, (hashtable2)[i]->name);
    printf("Что находится в переменной hashtable2[%d].defn:%p\n", i, &(*hashtable2)[i].defn);
    //printf("Что находится в переменной &hashtable2[%d].next:%p\n", i, &(*hashtable2)[i].next);
    printf("Что находится в переменной &hashtable2[%d].name:%p\n", i, &(*hashtable2)[i].name);
    printf("Что находится в переменной &hashtable2[%d].defn:%p\n", i, &(*hashtable2)[i].defn);

      
    res = my_func2(&hashtable2, i);
    
    if (res == -1)
        {
            printf("Введенный индекс за пределами массива\n");
            getch();
            return -1;
        }
    else
        {
            printf(
                "Результат => позиция: %d, nlist.name=%s, nlist.defn=%s, nlist.next=NONE\n",
                i,
                (*hashtable2)[i].name,
                (*hashtable2)[i].defn//,
                //(*hashtable2)[i].next
                );
            printf("Что находится в переменной hashtable2:%p\n", (*hashtable2));
            //printf("Что находится в переменной hashtable2[%d].next:%p\n", i, (*hashtable2)[i].next);
            printf("Что находится в переменной hashtable2[%d].name:%p\n", i, (*hashtable2)[i].name);
            printf("Что находится в переменной hashtable2[%d].defn:%p\n", i, (*hashtable2)[i].defn);
            //printf("Что находится в переменной &hashtable2[%d].next:%p\n", i, &(*hashtable2)[i].next);
            printf("Что находится в переменной &hashtable2[%d].name:%p\n", i, &(*hashtable2)[i].name);
            printf("Что находится в переменной &hashtable2[%d].defn:%p\n", i, &(*hashtable2)[i].defn);
            printf("Что находится в переменной *hashtable2[%d].name:(c1)%c\n", i, *(*hashtable2)[i].name);
            printf("Что находится в переменной *hashtable2[%d].name:(c2)%c\n", i, (*(*hashtable2)[i].name+1));
            printf("Что находится в переменной *hashtable2[%d].name:(c3)%c\n", i, (*(*hashtable2)[i].name+2));
            printf("Что находится в переменной *hashtable2[%d].name:(c4)%c\n", i, (*(*hashtable2)[i].name+3));
            printf("Что находится в переменной *hashtable2[%d].defn:(c1)%c\n", i, *(*hashtable2)[i].defn);
            printf("Что находится в переменной *hashtable2[%d].defn:(c2)%c\n", i, (*(*hashtable2)[i].defn+1));
            printf("Что находится в переменной *hashtable2[%d].defn:(c3)%c\n", i, (*(*hashtable2)[i].defn+2));
            printf("Что находится в переменной *hashtable2[%d].defn:(c4)%c\n", i, (*(*hashtable2)[i].defn+3));
            printf("Что находится в переменной hashtable2[%d].name:(s)%s\n", i, (*hashtable2)[i].name);
            printf("Что находится в переменной hashtable2[%d].defn:(s)%s\n", i, (*hashtable2)[i].defn);
            getch();
        }
    return 0;
}


int my_func(struct nlist *hashtable, int i)
{
    char *fname = "my_func";
    printf("FUNC %s -> вход в функцию\n", fname);
    if (i>HASHSIZE)
        {
            printf("Здесь ошибка!\n");
            return -1;
        }
    hashtable[i].name="Name";
    hashtable[i].defn="Defn";
    return 0;
}


int my_func2(struct nlist2 hashtable, int i)
{
    char *fname = "my_func2";
    char *n;
    char *str1 = "Name";
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
    hashtable[i].name=n;
    printf("FUNC %s -> успех для name\n", fname);
    //(*hashtable)[i].defn="Def";
    printf("FUNC %s -> успех для defn\n", fname);
    printf("FUNC %s -> все получилось, выход из функции\n", fname);
    return 0;
}