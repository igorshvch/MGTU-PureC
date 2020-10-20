#include <conio.h>
#include <locale.h>
#include <windows.h>
#include "cov_me.h"

static char *tested_module = "cov_me.c";

void test_divisible();

int main()
{
    setlocale(LC_ALL, "Russian_Russia.1251");
    const UINT CodePageID = 1251 ;
    SetConsoleCP(CodePageID);
    SetConsoleOutputCP(CodePageID);

    printf("Драйвер для тестирования модуля \"%s\"\n", tested_module);
    test_divisible();
    getch();
    return 0;
}

void test_divisible()
{
    char *tested_func = "my_divisible";
    int switcher = 1;
    int i = 0;

    printf("Модуль \"%s\" => тестирование функции \"%s\"\n", tested_module, tested_func);
    
    while (switcher) {
        printf("\tВведите число: ");
        scanf("%d", &i);
        printf("Вы ввели: %d\n", i);
        my_divisible(i);
        printf("\n");
        printf("\tДля выхода нажмите \"0\", для продолжения - \"1\" ");
        scanf("%d", &switcher);
        printf("\n");
    }
    printf("Модуль \"%s\" => окончание теста функции \"%s\"\n", tested_module, tested_func);
}