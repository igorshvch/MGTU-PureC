#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <wchar.h>

int main()
{
    wchar_t c;

    printf("Size of wchar_t: %d\n", sizeof(wchar_t));

    printf("Example with ciryllic: что-то на русском!\n");

    printf("Определение номера символа: %wc, %d\n", 53392, 'А');

    printf("Input char:\n");

    scanf("%wc", &c);
    printf("CHAR: %wc, %d", c, c);

    getch();
    return 0;
}