#include <stdio.h>
#include <stdlib.h>

#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))

const int n=5;
int D[5][5];

int main()
{
    int i, j, k=0, l=0;
    for (i=0; i<n; i++)
    for (j=0; j<n; j++)
    if ((i+j) %2 == 0) D[i][j] = ++k;
    else D[i][j] = --l;



    for (k=0; k<2; k++)
    for(i=0;i<n;i++)
    for(j=0;j<n;j++)
    D[i][j] = MAX(D[i][j], D[i][k]+D[k][j]);
    
    for (i=0; i<n; i++){
        printf("\n");
        for (j=0; j<n; j++)
            printf("\t%d", D[i][j]);
    }
    
    return 0;
}
