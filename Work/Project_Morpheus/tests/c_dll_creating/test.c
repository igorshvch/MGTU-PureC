#include <stdio.h>
#include <stdlib.h>

__declspec(dllexport) int main()
{
    return 0;
}

__declspec(dllexport) int sum(int a, int b)
{
    return a + b;
}

__declspec(dllexport) char* out()
{
    printf("Function 'out': runs...\n");

    char s[] = "Simple output";

    int i, j=14;
    char* st1;

    st1 = (char*) calloc(j, sizeof(char));

    for (i=0; i<13; i++){
        st1[i] = s[i];
        printf("%c(%d)\n", st1[i], i);
    }
    
    st1[++i]='\0';

    printf("Finale string: %s\n", st1);

    return st1;
}
