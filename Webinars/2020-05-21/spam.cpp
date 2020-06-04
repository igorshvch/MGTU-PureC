#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

int a;              //глобальная переменная

int main()
{
    int h;          //локальная переменная
    extern int x;   //переменная x определена в другом месте
    static int c;   //локальная статическая переменная
    a = 1;          //присваиваем значение глобальной переменной
    printf("%d\n", a);
    int a;          //локальная переменная a
    a = 2;          //присваивание значение локальной переменной
    printf("%d\n", a);
    ::a = 3;        //присваивание значение глобальной переменной
    printf("%d\n", a);
    printf("%d\n", ::a);

    getch();
    return 0;
}

int x = 4;          //
