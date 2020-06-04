#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

int try_math (int a, int b);
int upper_math (int (*try_math) (int a, int b), int a, int b);

int main()
{   
    int a,b;

    printf("\n=============================\n");
    printf("Input a:\n");
    scanf("%d", &a);
    printf("Input b:\n");
    scanf("%d", &b);

    upper_math(try_math, a, b);

    printf("\n=============================\n");

    getch();
	return 0;
}


int upper_math (int (*try_math) (int a, int b), int a, int b)
{
    try_math(a, b);
    return 0;
}


int try_math (int a, int b)
{
    printf("\n\tresult: %d", a+b);
    return 0;
}