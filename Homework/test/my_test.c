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
    printf("������� ������ �������:\n");
    scanf("%d", &i);
    printf("��� ��������� � ���������� hashtable:%p\n", hashtable);
    printf("��� ��������� � ���������� hashtable[%d].next:%p\n", i, hashtable[i].next);
    printf("��� ��������� � ���������� hashtable[%d].name:%p\n", i, hashtable[i].name);
    printf("��� ��������� � ���������� hashtable[%d].defn:%p\n", i, hashtable[i].defn);
    printf("��� ��������� � ���������� &hashtable[%d].next:%p\n", i, &hashtable[i].next);
    printf("��� ��������� � ���������� &hashtable[%d].name:%p\n", i, &hashtable[i].name);
    printf("��� ��������� � ���������� &hashtable[%d].defn:%p\n", i, &hashtable[i].defn);

    res = my_func(hashtable, i);
    
    if (res == -1)
        {
            printf("��������� ������ �� ��������� �������\n");
            getch();
            return -1;
        }
    else
        {
            printf(
                "��������� => �������: %d, nlist.name=%s, nlist.defn=%s, nlist.next=%p\n",
                i,
                hashtable[i].name,
                hashtable[i].defn,
                hashtable[i].next
                );
            printf("��� ��������� � ���������� hashtable:%p\n", hashtable);
            printf("��� ��������� � ���������� hashtable[%d].next:%p\n", i, hashtable[i].next);
            printf("��� ��������� � ���������� hashtable[%d].name:%p\n", i, hashtable[i].name);
            printf("��� ��������� � ���������� hashtable[%d].defn:%p\n", i, hashtable[i].defn);
            printf("��� ��������� � ���������� &hashtable[%d].next:%p\n", i, &hashtable[i].next);
            printf("��� ��������� � ���������� &hashtable[%d].name:%p\n", i, &hashtable[i].name);
            printf("��� ��������� � ���������� &hashtable[%d].defn:%p\n", i, &hashtable[i].defn);
            printf("��� ��������� � ���������� *hashtable[%d].name:(c1)%c\n", i, *hashtable[i].name);
            printf("��� ��������� � ���������� *hashtable[%d].name:(c2)%c\n", i, (*hashtable[i].name+1));
            printf("��� ��������� � ���������� *hashtable[%d].name:(c3)%c\n", i, (*hashtable[i].name+2));
            printf("��� ��������� � ���������� *hashtable[%d].name:(c4)%c\n", i, (*hashtable[i].name+3));
            printf("��� ��������� � ���������� *hashtable[%d].defn:(c1)%c\n", i, *hashtable[i].defn);
            printf("��� ��������� � ���������� *hashtable[%d].defn:(c2)%c\n", i, (*hashtable[i].defn+1));
            printf("��� ��������� � ���������� *hashtable[%d].defn:(c3)%c\n", i, (*hashtable[i].defn+2));
            printf("��� ��������� � ���������� *hashtable[%d].defn:(c4)%c\n", i, (*hashtable[i].defn+3));
            printf("��� ��������� � ���������� hashtable[%d].name:(s)%s\n", i, hashtable[i].name);
            printf("��� ��������� � ���������� hashtable[%d].defn:(s)%s\n", i, hashtable[i].defn);
            getch();
        }
    printf("\n\n=========== ������ ����� c *hashtable2 ===========\n\n");
    printf("\n������� ������ �������:\n");
    scanf("%d", &i);
    printf("��� ��������� � ���������� hashtable2:%p\n", hashtable2);
    printf("��� ��������� � ���������� (*hashtable2):%p\n", (*hashtable2));
    //printf("��� ��������� � ���������� hashtable2[%d].next:%p\n", i, &(*hashtable2)[i].next);
    printf("��� ��������� � ���������� hashtable2[%d].name:%p\n", i, &(*hashtable2)[i].name);
    //printf("��� ��������� � ���������� hashtable2.name:%p\n", i, (hashtable2)[i]->name);
    printf("��� ��������� � ���������� hashtable2[%d].defn:%p\n", i, &(*hashtable2)[i].defn);
    //printf("��� ��������� � ���������� &hashtable2[%d].next:%p\n", i, &(*hashtable2)[i].next);
    printf("��� ��������� � ���������� &hashtable2[%d].name:%p\n", i, &(*hashtable2)[i].name);
    printf("��� ��������� � ���������� &hashtable2[%d].defn:%p\n", i, &(*hashtable2)[i].defn);

      
    res = my_func2(&hashtable2, i);
    
    if (res == -1)
        {
            printf("��������� ������ �� ��������� �������\n");
            getch();
            return -1;
        }
    else
        {
            printf(
                "��������� => �������: %d, nlist.name=%s, nlist.defn=%s, nlist.next=NONE\n",
                i,
                (*hashtable2)[i].name,
                (*hashtable2)[i].defn//,
                //(*hashtable2)[i].next
                );
            printf("��� ��������� � ���������� hashtable2:%p\n", (*hashtable2));
            //printf("��� ��������� � ���������� hashtable2[%d].next:%p\n", i, (*hashtable2)[i].next);
            printf("��� ��������� � ���������� hashtable2[%d].name:%p\n", i, (*hashtable2)[i].name);
            printf("��� ��������� � ���������� hashtable2[%d].defn:%p\n", i, (*hashtable2)[i].defn);
            //printf("��� ��������� � ���������� &hashtable2[%d].next:%p\n", i, &(*hashtable2)[i].next);
            printf("��� ��������� � ���������� &hashtable2[%d].name:%p\n", i, &(*hashtable2)[i].name);
            printf("��� ��������� � ���������� &hashtable2[%d].defn:%p\n", i, &(*hashtable2)[i].defn);
            printf("��� ��������� � ���������� *hashtable2[%d].name:(c1)%c\n", i, *(*hashtable2)[i].name);
            printf("��� ��������� � ���������� *hashtable2[%d].name:(c2)%c\n", i, (*(*hashtable2)[i].name+1));
            printf("��� ��������� � ���������� *hashtable2[%d].name:(c3)%c\n", i, (*(*hashtable2)[i].name+2));
            printf("��� ��������� � ���������� *hashtable2[%d].name:(c4)%c\n", i, (*(*hashtable2)[i].name+3));
            printf("��� ��������� � ���������� *hashtable2[%d].defn:(c1)%c\n", i, *(*hashtable2)[i].defn);
            printf("��� ��������� � ���������� *hashtable2[%d].defn:(c2)%c\n", i, (*(*hashtable2)[i].defn+1));
            printf("��� ��������� � ���������� *hashtable2[%d].defn:(c3)%c\n", i, (*(*hashtable2)[i].defn+2));
            printf("��� ��������� � ���������� *hashtable2[%d].defn:(c4)%c\n", i, (*(*hashtable2)[i].defn+3));
            printf("��� ��������� � ���������� hashtable2[%d].name:(s)%s\n", i, (*hashtable2)[i].name);
            printf("��� ��������� � ���������� hashtable2[%d].defn:(s)%s\n", i, (*hashtable2)[i].defn);
            getch();
        }
    return 0;
}


int my_func(struct nlist *hashtable, int i)
{
    char *fname = "my_func";
    printf("FUNC %s -> ���� � �������\n", fname);
    if (i>HASHSIZE)
        {
            printf("����� ������!\n");
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
    hashtable[i].name=n;
    printf("FUNC %s -> ����� ��� name\n", fname);
    //(*hashtable)[i].defn="Def";
    printf("FUNC %s -> ����� ��� defn\n", fname);
    printf("FUNC %s -> ��� ����������, ����� �� �������\n", fname);
    return 0;
}