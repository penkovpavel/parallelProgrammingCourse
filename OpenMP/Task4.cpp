
#include "pch.h"
#include <iostream>
#include <omp.h>


//Написать программу, в которой объявить и присвоить начальные значения целочисленным
//массивам a[10] и b[10], определить параллельную область, количество нитей задать 
//равным 2, выделить код для основной(номер 0) и нити с номером 1. Основная нить(master)
//должна выполнять поиск min значения элементов массива a, нить с номером 1 - поиск max
//значения элементов массива b.Результат выдать на экран. (2 балла)

int main()
{
	int a[] = { 1,12,1,13,1,14,1,15,0,2 };
	int b[] = { -5,3,1,6,2,4,-4,0,0,12 };
    #pragma omp parallel num_threads(2)
	{
       #pragma omp master
		{
			int n = omp_get_thread_num();
			int min = INT_MAX;
			for (int i = 0; i < 10; i++) 
			{
				if (a[i] < min) 
				{
					min = a[i];
				}
			}
			printf("Thread %d calculated min of a, its %d\n", n, min);
		}
       #pragma omp single
		{
			int n = omp_get_thread_num();
			int max = INT_MIN;
			for (int i = 0; i < 10; i++)
			{
				if (b[i] > max)
				{
					max = b[i];
				}
			}
			printf("Thread %d calculated max of b, its %d\n", n, max);
		}
	}
}

