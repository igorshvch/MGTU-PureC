#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main()
{
    char c = '\0' ;
    int n = 0 ;
    int* tmp = 0;

    tmp = &n;
    printf("Value: %d\nAdress: %p", n, tmp);

    
    char* pc1 = &c ; //цепочка состоящая из 3-х
    char* pc11 = &c ;
    char** pc2 = &pc1 ; //типизированных указателей

        **pc2 = 'Y' ;
    
    printf("all vals:\n");
    printf(
        "\tc=%c\n\tn=%d\n\tpc1=%p\tpc1=%c\n\tpc11=%p\tpc11=%c\n\tpc2=%p\tpc2=%c\n",
        c, n, pc1, *pc1, pc11, *pc11, pc2, **pc2);
    
    void* pv1 = NULL ; //цепочка состоящая
    void** pv2 = &pv1 ; //из 3-х не типизированных
    void*** pv3 = &pv2 ; //указателей
    pv1 = &c ;
    **( (char**) pv2 ) = 'X' ;
        pv1 = &n ;
        ***( (int***) pv3 ) = 10 ;
    


    getch();
	return 0;
}