
#include "pch.h"
#include <iostream>
#include <omp.h>


//Используя возможности OpenMP написать программу умножения матрицы на вектор.Сравнить время выполнения 
//последовательной и параллельных программ(выбрать наилучший schedule).Определить размеры матрицы при которых 
//параллельная программа начинает работать быстрей последовательной(3 балла)

int** initializeMatrix(int size)
{
	int **ar = new int*[size];
	for (int i = 0; i < size; i++) {
		ar[i] = new int[size];
		for (int j = 0; j < size; j++) {
			ar[i][j] = rand();
			srand(i + j);
		}
	}
	return ar;
}

int* initializeVector(int size)
{
	int* vector = new int[size];
	for (int i = 0; i < size; i++) {
		vector[i] = rand();
		srand(vector[i]);
	}
	return vector;
}

void parallelMultiply(int** matrix, int* vector, int size)
{
	double time = omp_get_wtime();
	int* resVector = new int[size];
	int s = size / 16;
	#pragma omp parallel
	{
	#pragma omp for schedule(guided, s)
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			resVector[i] += vector[i] * matrix[j][i];
		}
	}
	}
	double restime = omp_get_wtime() - time;
	printf("Parallel programm time for size %d: %g\n", size, restime);
}

void commonMultiply(int** matrix, int* vector, int size)
{
	double time = omp_get_wtime();
	int* resVector = new int[size];
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			resVector[i] += vector[i] * matrix[j][i];
		}
	}
	double restime = omp_get_wtime() - time;
	printf("Common programm time for size %d: %g\n", size, restime);
}

int main()
{
	//260 - бывает по разному, 270 в 90% запусков параллельная быстрее
	int size = 270;
	int** matrix = initializeMatrix(size);
	int* vector = initializeVector(size);
	commonMultiply(matrix, vector, size);
	parallelMultiply(matrix, vector, size);
}

