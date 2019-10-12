
#include "pch.h"
#include <iostream>
#include <omp.h>


//Написать программу, в которой объявить и присвоить начальные значения целочисленному 
//массиву a[100].Используя конструкцию parallel for и reduction вычислить средние 
//арифметические значения элементов массива a.Одно при помощи reduction, другое без.
//Сравнить полученные значения.Объяснить возможную разность результатов. (2 балла)

int main()
{
	int a[100];

	#pragma omp parallel
	{
		#pragma omp for
		for (int i = 0; i < 100; i++)
		{
			a[i] = rand();
			srand(a[i] + omp_get_thread_num());
		}
	}

	int sum = 0;
	#pragma omp parallel
	{
		#pragma omp for
		for (int i = 0; i < 100; i++)
		{
			sum += a[i];
		}
	}
	float avg = sum / 100;
	printf("Without reduction: %g\n", avg);

	sum = 0;
		#pragma omp parallel reduction(+:sum)
	{
		#pragma omp for
		for (int i = 0; i < 100; i++)
		{
			sum += a[i];
		}

	}
	avg = sum / 100;
	printf("With reduction: %g\n", avg);

}

