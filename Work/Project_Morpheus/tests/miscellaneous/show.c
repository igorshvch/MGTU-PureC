#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <wchar.h>

int main()
{
    char  buf1[32767];
    char  buf2[32767];
    int  uSize = 32767;

    /*
    wchar_t buf3[10];
    swprintf(buf3, 6, L"Пять");
    wprintf("%ls\n", buf3);
    */

    printf("Win32 MAX_PATH: %d\n", MAX_PATH);
    GetSystemDirectory(buf1, uSize);
    GetCurrentDirectory(uSize, buf2);
    printf("Current system directory: %s", buf1);
    printf("\tPath length: %d\n", strlen(buf1));
    printf("Current working directory: %s", buf2);
    printf("\tPath length: %d\n", strlen(buf2));

    printf("lets try hardcopy: %s\n", strcat(buf1, buf2));

    getch();
    return 0;
}