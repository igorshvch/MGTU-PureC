#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

/*
Написать программу, которая преобразует одномерный 
целочисленный массив так, чтобы все его чётные элементы 
разместились в начале массива, а нечётные в конце.
Задачу надо решить без использования дополнитнльных
массивов
*/

/*
В качестве примера целочисленного массива используется вводимое пользователем число.
Цифры, укзаывающие его разряды, записываются в отдельные ячеки массива,
который в дальнешем преобразуется согласно заданию
*/

int main()
{
    int a, tmp; //переменные для хранения вводимого числа и промежуточных значений
    int i(0), j(0), k(0); //счетчики
    int power_var(1); /*
                      переменная для возведения числа в сетпень
                      (используется для вычисления длины массива,
                      хранящего значения разрядов)
                      */
    int *store(NULL); //указатель для выделения массива
    
    printf("=============================\n");
    printf("Input integer\n");
    scanf("%d", &a);
    printf("Your input is:\n\ta = %d\n", a);
    printf("=============================\n");

    //Выделение памяти под массив необходимой длины для хранения цифр в разрядах чисел

    for (i=0; a!=(a%power_var); i++, power_var *= 10); //подсчет необходимого количества ячеек в массиве по максимальному введенному значению
    
    store = (int*) calloc(i, sizeof(int)); //выделение памяти для массива
    
    printf("Array length: %d\n", i);
    printf("=============================\n");

    //Поразрядная запись числа в массив

    j = --i; //приведение счетчика к последней позиции массива
    do //цикл заполнения массива
        {
            tmp1 = a%10;
            *(store+j) = tmp1;
            printf("\tWrite tmp1=%d to position: %d\n", tmp1, j);
            j--;
        }
    while (a/=10); //окончание цикла заполнения массива
    //i--; //приведение значения счетчика к номеру последнего элемента в массиве

    for (j=0; j < (i+1); j++) //цикл печати значений внутри массива для тестирования
        {
            //printf(":::%d:::", j);
            printf("%d ", *(store+j));
        } //окончанине цикла печати для тестирования
    printf("\n");

    printf("Pointer i = %d, j = %d, k = %d\n", i, j, k);
    
    
    k = -1;
    for (j=0; j < i+1; j++) //https://tkramesh.wordpress.com/2011/02/11/shifting-even-numbers-to-the-left-in-array-coding-in-c-6/
        {
            if (!(*(store+j)%2))
                {
                    tmp = *(store+j);
                    *(store+j) = *(store+(k+1));
                    *(store+(k+1)) = tmp1;
                    k++;
                }
        }
    /*
    k = 0;
    for (j=i; j>(-1); j--)
        {
            tmp1 = *(store+j);
            printf("\tEnd value # %d: %d\n", j, tmp1);
            if ((tmp1%2) == 0)
                {
                    printf("\tEnd value # %d: %d is even\n", j, tmp1);
                    for (; k<i; k++)
                        {
                            tmp2 = *(store+k);
                            printf("\t\tStart value # %d: %d\n", k, tmp2);
                            if ((tmp2%2) != 0)
                                {
                                    printf("\t\tStart value # %d: %d is odd\n", k, tmp2);
                                    printf("\t\tValues: end = %d: start = %d\n", *(store+j), *(store+k));
                                    *(store+k) = tmp1;
                                    *(store+j) = tmp2;
                                    printf("\t\tValues after exchage: end = %d: start = %d\n", *(store+j), *(store+k));
                                    printf("\t1. Exit from inner cicle; j=%d, k=%d\n", j, k);
                                    k++;
                                    break;
                                }
                        }
                }
            if (j==k)
                {
                printf("\t2. Cicle endes due to j==k: j=%d, k=%d\n", j, k);
                break;
                }
        }
    */
    printf("=============================\n");
    printf("Pointer i = %d, j = %d, k = %d\n", i, j, k);
    for (j=0; j < (i+1); j++) //цикл печати значений внутри массива для тестирования
        {
            //printf(":::%d:::", j);
            printf("%d ", *(store+j));
        } //окончанине цикла печати для тестирования
    printf("\n");

    free( (void*) store); //освобождение памяти, выделенной под массив

    getch();
	return 0;
}
