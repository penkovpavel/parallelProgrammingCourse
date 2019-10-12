
#include "pch.h"
#include <iostream>
#include <omp.h>


//Написать программу, в которой объявить и присвоить начальные значения элементам двумерного массива d[6][8],
//для инициализации значений использовать генератор случайных чисел.Используя конструкцию директивы sections…section
//определить три секции для выполнения следующих операций :
//первая секция выполняет вычисление среднего арифметического значения элементов двумерного массива,
//вторая секция выполняет вычисление минимального и максимального значений элементов двумерного массива,
//третья секция выполняет вычисление количества элементов массива, числовые значения которых кратны 3.

int main()
{
	int d[6][8];

	#pragma omp parallel shared(d)
	{
	#pragma omp for
		for (int i = 0; i < 6; i++) {
			for (int j = 0;j<8; j++){
				d[i][j] = rand();
				srand(rand() + omp_get_thread_num());
			}
		}
	}
	#pragma omp parallel shared(d)
	{
	#pragma omp sections
		{
			#pragma omp section
			{
				int k = 0;
				for (int i = 0; i < 6; i++) {
					for (int j = 0; j < 8; j++) {
						k += d[i][j];
					}
				}
				float avg = k / 14;
				printf("Average: %g\n", avg);
			}
			#pragma omp section
			{
				int max = INT_MIN;
				int min = INT_MAX;
				for (int i = 0; i < 6; i++) {
					for (int j = 0; j < 8; j++) {
						if (d[i][j] > max) {
							max = d[i][j];
						}
						if (d[i][j] < min) {
							min = d[i][j];
						}
					}
				}
				printf("Max: %d, Min: %d \n", max,min);
			}
			#pragma omp section
			{
				int k = 0;
				for (int i = 0; i < 6; i++) {
					for (int j = 0; j < 8; j++) {
						if (d[i][j] % 3 == 0) {
							k += 1;
						}
					}
				}
				printf("Divided by 3: %d\n", k);
			}
		}
	}

}

