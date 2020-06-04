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
    const int sizeArray = 10; //мощность массива
	const unsigned short RANGE = 100; //предел для значений элементов
    int oldArray[sizeArray];
    int newArray[sizeArray];

    int i; //индекс (счетчик)
    
    int j = sizeArray-1;
    int k = 0;
    int temp = 0;

    //заполнение массива случайными числами
	srand(time(NULL)); //srand(15); => -5 -56 -38  -1 -62 -84 -44 :::   -5 -44 -84  -1 -62 -38 -56
	printf("Автоматически сфомированный массив состоит из следующих элементов\n");
    if (rand() % 2) //числа в массиве будут только отрицательными
    {
        for (i=0; i<sizeArray; i++)
            {
                oldArray[i] = (rand() % RANGE) * (-1);
                newArray[i] = oldArray[i];
                printf ("%4d", oldArray[i]);
            }
    }
    else //числа в массиве будут как отрицательными, так и положительными
    {
        for (i=0; i<sizeArray; i++)
        {
            if (rand() % 2)
                {
                    oldArray[i] = (rand() % RANGE) * (-1);
                    newArray[i] = oldArray[i];
                }
            else
                {
                    oldArray[i] = (rand() % RANGE);
                    newArray[i] = oldArray[i];
                }
            printf ("%4d", oldArray[i]);
        }
    }
    printf("\n\n%2d\n\n", i);


 
    for(; k < sizeArray; k++) { // заходим в исходный массив
        if(k == j) break; // если индексы равны, значит мы попали в середину, делаем выход
        if(!(oldArray[k] % 2)) { // проверка на четность
            for(; j >= 0; j--) { // заходим в массив с конца
                if(!(oldArray[j] % 2)) { // проверка на четность
                    temp = oldArray[j]; // сохранение значения во временную переменную
                    newArray[j] = oldArray[k]; // замена последнего элемента 
                    newArray[k] = temp; // замена первого элемента
                    j--; // декремент, чтобы не попасть на этот индекс снова
                    break; // выход, чтобы не проходить по циклу еще раз, тк мы меняем местами два значения
                }
            }
        }
    }
 
    //Вывод исходного и преобразованного массивов в одну строку
    printf("\n\nИсходный массив: ");
    for(int k = 0; k < sizeArray; k++) {
        printf("%d ", oldArray[k]);
        if(k==9) 
            printf("; ");
    }
 
    printf("\nпреобразованный массив: ");
    for(int l = 0; l < sizeArray; l++) 
        printf("%d ", newArray[l]);
 
    getch();
    return 0;
}