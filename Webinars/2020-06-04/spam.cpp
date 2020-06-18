#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <locale.h>
#include <Windows.h>

int main()
{
    //setlocale(LC_CTYPE, "Russian_Russia.1251");
    //const UINT CodePageID = 1251 ;
    //SetConsoleCP(CodePageID);
    
    char c;
    
    printf("Some test!\n");
    printf("Какой-то тест!\n");
    scanf("%c", &c);

    printf("%c\n", c);

    getch();
    return 0;
}

