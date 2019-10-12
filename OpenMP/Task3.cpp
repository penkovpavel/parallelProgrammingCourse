
#include "pch.h"
#include <iostream>
#include <omp.h>


//Написать программу, в которой объявить и присвоить начальные значения 
//целочисленным переменным : a и b, определить две параллельные области,
//первая – с числом нитей 2, вторая – с числом нитей 4. Для первой области
//переменные a и b объявить защищенными, с режимом доступа private и firstprivate
//соответственно, внутри области определить номер нити и выполнить увеличение
//значения переменных на эту величину.Выдать на экран значения переменных
//до входа в параллельную область, внутри параллельной области и после 
//выхода из параллельной области.Для второй области переменную a объявить
//общей, переменную b объявить защищенной, с режимом доступа private, определить
//номер нити и выполнить уменьшение значения переменных на эту величину.Выдать
//на экран значения переменных до входа в параллельную область, внутри параллельной
//области и после выхода из параллельной области. (2 балла)

int main()
{
	int a;
	int b;
	a = 8;
	b = 12;
	printf("Before first parallel a=%d, b=%d\n", a, b);
    #pragma omp parallel private(a) firstprivate(b) num_threads(2)
	{
		a = omp_get_thread_num();
		b += a;
		printf("Inside first parallel a=%d,b=%d\n", a, b);
	}
	printf("After first parallel a=%d,b=%d\n", a, b);
	printf("Before second parallel a=%d, b=%d\n", a, b);
    #pragma omp parallel num_threads(4) shared(a) private(b)
	{
		b = omp_get_thread_num();
		a -= b;
		printf("Inside second parallel a=%d,b=%d\n", a, b);
	}
	printf("After second parallel a=%d,b=%d\n", a, b);

}

