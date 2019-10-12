
#include "pch.h"
#include <iostream>
#include <omp.h>


//Написать программу, в которой определить две параллельные области, выполнение которых
//зависит от условного оператора #pragma omp parallel if (…), если заданное значение
//числа нитей больше 2, область выполняется параллельно, иначе не параллельно.Число нитей
//перед первой областью задать равным 3, перед второй – равным 2. Внутри параллельных областей
//определить количество нитей и номер каждой нити, результат выдать на экран.Убедиться
//в правильности работы программы. (2 балла)

int main()
{
	int thr = 3;

	#pragma omp parallel if(thr > 2) num_threads(thr)
	{
		int num = omp_get_thread_num();
		int thnum = omp_get_num_threads();
		printf("Number of threads in first: %d, Number of thread: %d\n",thnum,num);
	}
	thr = 2;
	#pragma omp parallel if(thr > 2) num_threads(thr)
	{
		int num = omp_get_thread_num();
		int thnum = omp_get_num_threads();
		printf("Number of threads in second: %d, Number of thread: %d\n", thnum, num);
	}

}

