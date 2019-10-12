
#include "pch.h"
#include <iostream>
#include <omp.h>


//Написать программу, в которой объявлен массив из 16000 элементов и инициализирован так, что 
//значение элемента массива равно его порядковому номеру.Затем создайте результирующий массив, 
//в котором(за исключением крайних элементов) будут средние значения исходного массива :
//b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0
//Запустите программу с 8 - ю процессами при различных типах распределения работ(static, dynamic, guided, auto(runtime, 
//если auto не работает)) и посмотреть время на разных размерах порций. (4 балла)


void staticProgram(int portion)
{
	int a[16000];
	float b[15998];
	double time = omp_get_wtime();
#pragma omp parallel num_threads(8) shared(portion)
	{
#pragma omp for schedule(static,portion)
		for (int i = 0; i < 16000; i++)
		{
			a[i] = i;
		}
#pragma omp for schedule(static,portion)
		for (int i = 1; i < 15999; i++)
		{
			b[i - 1] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
		}
	}
	double resultTime = omp_get_wtime() - time;
	printf("Static, portion-%d time: %g\n", portion, resultTime);
}

void dynamicProgram(int portion)
{
	int a[16000];
	float b[15998];
	double time = omp_get_wtime();
#pragma omp parallel num_threads(8) shared(portion)
	{
#pragma omp for schedule(dynamic,portion)
		for (int i = 0; i < 16000; i++)
		{
			a[i] = i;
		}
#pragma omp for schedule(dynamic,portion)
		for (int i = 1; i < 15999; i++)
		{
			b[i - 1] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
		}
	}
	double resultTime = omp_get_wtime() - time;
	printf("Dynamic, portion-%d time: %g\n", portion, resultTime);
}

void guidedProgram(int portion)
{
	int a[16000];
	float b[15998];
	double time = omp_get_wtime();
#pragma omp parallel num_threads(8) shared(portion)
	{
#pragma omp for schedule(guided,portion)
		for (int i = 0; i < 16000; i++)
		{
			a[i] = i;
		}
#pragma omp for schedule(guided,portion)
		for (int i = 1; i < 15999; i++)
		{
			b[i - 1] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
		}
	}
	double resultTime = omp_get_wtime() - time;
	printf("Guided, portion-%d time: %g\n", portion, resultTime);
}

void runtimeProgram(int portion)
{
	int a[16000];
	float b[15998];
	double time = omp_get_wtime();
#pragma omp parallel num_threads(8) shared(portion)
	{
#pragma omp for schedule(runtime)
		for (int i = 0; i < 16000; i++)
		{
			a[i] = i;
		}
#pragma omp for schedule(runtime)
		for (int i = 1; i < 15999; i++)
		{
			b[i - 1] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
		}
	}
	double resultTime = omp_get_wtime() - time;
	printf("Auto, portion-%d time: %g\n", portion, resultTime);
}

int main()
{
	staticProgram(1);
	staticProgram(10);
	staticProgram(100);
	staticProgram(1000);
	dynamicProgram(1);
	dynamicProgram(10);
	dynamicProgram(100);
	dynamicProgram(1000);
	guidedProgram(1);
	guidedProgram(10);
	guidedProgram(100);
	guidedProgram(1000);
	runtimeProgram(1);
	runtimeProgram(10);
	runtimeProgram(100);
	runtimeProgram(1000);

}

