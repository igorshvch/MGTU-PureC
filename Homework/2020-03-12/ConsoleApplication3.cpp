// ConsoleApplication3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <conio.h>

#pragma warning(disable: 4996)

// Дождаться ввода пользователем числа
// Посчитать количества цифр в числе
// Вычислить сумму цифр в числе
// Определить наибольшую и наименьшую цифру в записи
// Преобразовать число: оставить в записи только четные цифры в том же порядке, в котором они вводились пользователем

int _tmain(int argc, _TCHAR* argv[])
{
	int num(0), holder(0), in_cycle(0), holder2(0);
	int num_quant(0);
	int num_sum(0);
	int biggest(0);
	int lowest(9);
	int recomb1(0), recomb2(1);

	setlocale(LC_ALL, "Rus");

	printf("������� ����� �����:\n");
	scanf("%d", &num);
	printf("�� ����� �����\n%d\n", num);

	//printf("Проба деления по модулю на 10: %d\n", num%10);
	//printf("Проба деления по модулю на 100: %d\n", num%100);
	//printf("Проба деления по модулю на 1000: %d\n", num%1000);

	//printf("Проба деления на 10 с результатом int: %d\n", num/10);
	//printf("Проба деления на 100 с результатом int: %d\n", num/100);
	//printf("Проба деления на 1000 с результатом int: %d\n", num/1000);

	holder = num;

	do 
	{
		num_quant++;
		in_cycle = holder%10;
		num_sum += in_cycle;
		if (in_cycle < lowest)
		{
			lowest = in_cycle;
		}
		if (in_cycle > biggest)
		{
			biggest = in_cycle;
		}
		if (in_cycle%2 == 0)
		{
			printf("\t\tЧисло %d четное!\n", in_cycle);
			holder2 = num_quant;
			while (holder2-=1 > 0)
				recomb2 *= 10;
			recomb1 += in_cycle*recomb2;
			printf("\t\tПолучаем число: %d\n", recomb1);
		}
		printf("Прогон цикла № %d\n", num_quant);
		printf("\tПромежуточный результат деления по модулю: %d\n", in_cycle);
		printf("\tПромежуточное наибольшее: %d\n", biggest);
		printf("\tПромежуточное наименьшее: %d\n", lowest);
	}
	while (holder /= 10);

	printf("\nВсего цифр в записи числа: %d\n", num_quant);
	printf("\nСумма цифр в записи числа: %d\n", num_sum);
	printf("Наибольшая цифра в записи: %d\n", biggest);
	printf("Наименьшая цифра в записи: %d\n", lowest);

	getch();
	return 0;
}

