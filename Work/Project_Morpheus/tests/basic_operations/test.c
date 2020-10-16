#include <stdio.h>
#include <conio.h>

int main()
{
    int i, j, k;
    double res;

    i = 100;
    j = 234;
    k = 123;

    res = 1 - ((double) k / (((double) (i+j)) / 2.0));

    printf("%f\n", res);

    char str[10];

    for (i=0; i<9;i++)
        str[i] = 'S';
    str[i] = '\0';
    printf("%s\n", str);

    for (i=0; i<5;i++)
        str[i] = 'S';
    str[i] = '\0';
    printf("%s\n", str);

    for (i=0;i<10;i++)
        printf("%c", str[i]);

    getch();
    return 0;
}