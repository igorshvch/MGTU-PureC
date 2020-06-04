#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

/*
Составить программу замены первого отрицательного элемента одномерного массива
суммой положительных элементов. Если замена невозможна, то вывести сообщение об этом.
Вывести одной строкой элементы исходного и преобразованного массива
*/

int main()
{
    const int N = 5; //мощность массива
	const unsigned short RANGE = 100; //предел для значений элементов

	int i; //индекс (счетчик)
	int a[N]; //объявление исходного массива
	int sum_pos = 0; //переменная для хранения суммы положительных элементов
    int tmp; //переменная для хранения промежуточных значений
    int flag_find_fisrt_neg = 1; //переменная для хранения знечния флага для финальной части программы

	//заполнение массива случайными числами
	srand(time(NULL));
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

    //попытка вычисления суммы положительных элементов
    for (i=0; i<N; i++)
    {
        tmp = a[i];
        if (tmp > 0)
            sum_pos += tmp;
    }
    if (sum_pos == 0)
    {
        printf("\nНе удалось вычислить сумму положительных элементов: ни один из элементов массива не провосходит нуль\n");
        printf("Завершение программы\n");
        getch();
	    return 0;
    }

    //преобразование массива и вывод исходного и преобразованного массива
    printf("\nВывод исходного и преобразованного массивов через разделитель ' ::: '\n");
    for (i=0; i<N; i++)
		printf("%4d", a[i]);

    printf(" ::: "); // Разделитель

    for (i=0; i<N; i++)
    {
        tmp = a[i];
        if (tmp < 0 && flag_find_fisrt_neg)
        {
            printf("%4d", sum_pos);
            flag_find_fisrt_neg = 0;
        }
        else
            printf("%4d", tmp); 
    }

    getch();
	return 0;
}