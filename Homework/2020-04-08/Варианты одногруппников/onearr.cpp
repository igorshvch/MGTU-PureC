#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

/*
Составить программу, которая преобразует одномерный целочисленный массив так,
чтобы все его элементы содержащие нечётные числа остались на своих местах,
а все его элементы содержащие чётные числа расположились в обратном порядке.
Вывести одной строкой элементы исходного и преобразованного массива
*/

int main()
{
    const int N = 7; //мощность массива
	const unsigned short RANGE = 100; //предел для значений элементов

    int i; //индекс (счетчик)
    int a[N]; //объявление исходного массива
    int b[N]; //вспомогательный массив

    int j = N-1;
    int k = 0;
    int temp = 0;

    //заполнение массива случайными числами
	srand(time(NULL)); //srand(15); => -5 -56 -38  -1 -62 -84 -44 :::   -5 -44 -84  -1 -62 -38 -56
	printf("Автоматически сфомированный массив состоит из следующих элементов\n");
    if (rand() % 2) //числа в массиве будут только отрицательными
    {
        for (i=0; i<N; i++)
            {
                a[i] = (rand() % RANGE) * (-1);
                printf ("%4d", a[i]);
            }
    }
    else //числа в массиве будут как отрицательными, так и положительными
    {
        for (i=0; i<N; i++)
        {
            if (rand() % 2)
                a[i] = (rand() % RANGE) * (-1);
            else
                a[i] = (rand() % RANGE);
            printf ("%4d", a[i]);
        }
    }


 
    for(; k < N; k++) { // заходим в исходный массив
        if(k == j) break; // если индексы равны, значит мы попали в середину, делаем выход
        if(!(a[k] % 2)) { // проверка на четность
            for(; j >= 0; j--) { // заходим в массив с конца
                if(!(a[j] % 2)) { // проверка на четность
                    temp = a[j]; // сохранение значения во временную переменную
                    b[j] = a[k]; // замена последнего элемента 
                    b[k] = temp; // замена первого элемента
                    j--; // декремент, чтобы не попасть на этот индекс снова
                    break; // выход, чтобы не проходить по циклу еще раз, тк мы меняем местами два значения
                }
            }
        }
    }
 
    //Вывод исходного и преобразованного массивов в одну строку
    printf("\n\nИсходный массив: ");
    for(int k = 0; k < N; k++) {
        printf("%d ", a[k]);
        if(k==9) 
            printf("; ");
    }
 
    printf("\nпреобразованный массив: ");
    for(int l = 0; l < N; l++) 
        printf("%d ", b[l]);
 
    getch();
    return 0;
}