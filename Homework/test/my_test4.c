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
    char *record;
    int rows;
};

static struct str_table nt;

struct table
{
    int *id;
};

int main()
{
    setlocale(LC_ALL, "Russian_Russia.1251");
    const UINT CodePageID = 1251 ;
    SetConsoleCP(CodePageID);
    SetConsoleOutputCP(CodePageID);

    int i, j;
    int m, k = 10;
    int a[10];
    int *pa = a;
    int *pp = &a;
    float f, f2;

    const int N=300;

    int ***mf3;
    int **mf2;
    int *mf1;
    int mf = 6732;

    int * const cpi = &k;
    const int *pci = &N;

    printf("k=%d, &k=%p", k, &k);
    printf("mf=%d, &mf=%p", mf, &mf);

    pritnf("cpi=%p\n", cpi);

    printf("cpi=%p\n", cpi);

    printf("�������� ���������� ��������� �� �������������: nt=%p, nt.record=%p, nt.rows=%p\n", &nt, &nt.record, &nt.rows);

    nt.record = "������";
    nt.rows = 123;

    printf("�������� ���������� ��������� ����� �������������: nt=%p, nt.record=%p, nt.rows=%p\n", &nt, &nt.record, &nt.rows);

    printf("��������� ���������� ������ ����� ���������:\n");
    printf("����� nt: %s\n", nt);
    printf("����� nt.record: %s\n", nt.record);

    i = &nt;

    printf("���������, ��� ����� � 'i': ��� ��������� i=%p; ��� int i=%d\n", i, i);

    printf("\n===========================================================\n");
    printf("���������, ��� � ��� � ������� ������� � ��������� �� ����:\n");
    printf("a=%p\n", a);
    printf("a[0]=%d\n", a[0]);
    printf("pa=%p\n", pa);
    printf("pp=%p\n", pp);
    printf("pa[0]=%d\n", pa[0]);
    printf("&a[0]=%p\n", &a[0]);
    printf("&pa[0]=%p\n", &pa[0]);
    printf("pp[0]=%d\n", pp[0]);
    printf("&pp[0]=%p\n", &pp[0]);

    printf("\n===========================================================\n");
    printf("��������� �� ���������� j � k: j=%d, &j=%p, k=%d, &k=%p, m=%d, &m=%p| sizeof(int)=%d\n", j, &j, k, &k, m, &m, sizeof(int));

    mf1 = &mf;
    mf2 = &mf1;
    mf3 = &mf2;
    printf("\n===========================================================\n");
    printf(
        "���������, ��� ���������� � mf:\nmf=%d\n&mf=%p\n*mf1=%d\n&mf1=%p\nmf1=%p\n**mf2=%d\n&mf2=%p\nmf2=%p\n***mf3=%d\n&mf3=%p\nmf3=%p\n",
        mf, &mf, *mf1, &mf1, mf1, **mf2, &mf2, mf2, ***mf3, &mf3, mf3
        );
    printf(
        "�������� ������ mf:\nmf=%d\n&mf=%p\n***mf3=%d\n&mf3=%p\n",
        mf, &mf, ***mf3, &mf3
        );
    printf("\n===========================================================\n");
    printf("��������� �� �������� ����������:\nmf1=%p\n++mf1=%p\nmf1++=%p\n", mf1, ++mf1, mf1++);
    mf1 = &mf;
    printf("mf1+1=%p\n", (mf1+1));
    printf("mf1-1=%p\n", (mf1-1));
    printf("mf1-2=%p\n", (mf1-2));


    return 0;
}