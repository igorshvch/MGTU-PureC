// CPP_intro.cpp: определяет точку входа для консольного приложения.
//

#include <stdio.h>

void array_print(int *arr, int len);
int *copy_arr(int *arr, int len);

int main()
{
	int i, j, k, n, s, imax, buf;
	int *a, *b, *c;

	n = 10;

	a = new int[n];

	int xc[] = { 3, 23, 7, 4, 2, 67, 8, 3, 2, 12 };

	for (i = 0; i < n; i++)
		a[i] = xc[i];

	//вывести на экран значения из динамического массива

	printf("Elements in dynamic array:\n");

	array_print(a, n);

	//найти все четные элементы и вывести их на экран, а также посчитать их среднее арифметическое

	for (i = 0, k = 0, s = 0; i < n; i++){
		if (a[i] % 2 == 0){
			k++;
			s += a[i];
		}
	}
	printf("Number of all even elements: %d\n", k);
	printf("Mean of all even elements: %d\n", s/k);

	//переместить все четные элементы в новый массив

	b = new int[k];

	for (i = 0, j = 0; i < n; i++){
		if (a[i] % 2 == 0){
			b[j++] = a[i];
		}
	}

	//вывести все элементы нового массива на экран

	printf("All even elements:\n");
	
	array_print(b, k);


	//найти индекс вхождения первого етного элемента в массив

	j = -1;

	for (i = 0; i < n; i++){
		if (a[i] % 2 == 0){
			j = i;
			break;
		}
	}

	printf("The first even element is %d at index %d\n", a[j], j);

	//найти максимальный элемент в массиве и его индекс
	for (i = 0, imax = 0; i < n; i++){
		if (a[i]>a[imax]){
			imax = i;
		}
	}
	printf("MAX array element is %d at index %d\n", a[imax], imax);


	if (k){
		//найдем максимальный четный элемент
		for (i = j, imax = j; i < n; i++){
			if (a[i] % 2 == 0 && a[i] > a[imax]){
				imax = i;
			}
		}
		printf("MAX EVEN array element is %d at index %d\n", a[imax], imax);
	}
	else {
		printf("None even elements were found!\n");
	}

	//отсортировать исходный массив

	c = copy_arr(a, n);

	for (k = 0; k < n-1; k++){
		for (i = k+1, imax = k; i < n; i++)
			if (c[i] > c[imax])
				imax = i;
			
		
		buf = c[imax];
		c[imax] = c[k];
		c[k] = buf;
		printf("c[k] = %d, c[imax]= %d, k = %d, imax = %d\n", c[k], c[imax], k, imax);
	}

	array_print(c, n);

	getchar();	

	return 0;
}

void array_print(int *arr, int len)
{
	printf("\n");
	int i;
	for (i = 0; i < len; i++)
		printf("\t%d\n", arr[i]);
	printf("\n");
}

int *copy_arr(int *arr, int len){
	int i;
	int *nw_arr;

	nw_arr = new int[len];

	for (i = 0; i < len; i++){
		nw_arr[i] = arr[i];
	}
	printf("Array copy - success!\n");

	return nw_arr;
}