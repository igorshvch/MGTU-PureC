#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

int main()
{
    FILE *pf(NULL);
    char *fn = "C:\\Users\\igors\\My_Code\\PureC\\Webinars\\2020-05-28\\Example1.txt";
    
    if ((pf = fopen(fn, "r")) == NULL)
        printf("Unable to open file %s", fn);
        ferror(pf);
        perror("");
        clearerr(pf);


    fclose(pf);
    getch();
    return 0;    
}

