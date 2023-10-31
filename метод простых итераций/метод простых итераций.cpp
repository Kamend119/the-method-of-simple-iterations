#include <iostream>
#include <cmath>
using namespace std;

// Количество уровнений
int count_equation;
// Колисчество элементов в уровнениях
int count_element;
// Точность вычисления
float eps = 0;
//
float** systems;
// Свободные члены
float* z;
// Построчные нормы матрицы
float* norma_martitz;
// Норма матрицы
float c = 0;
// Нулевое приближение n
float* x0;
// Нулевое приближение n+1
float* x1;
// Условие остановки для каждого примера
float* ostan;

//Начало работы
void getting_started()
{
	do {
		cout << "Задайте количество уравнений: ";
		cin >> count_equation;
	} while (count_equation <= 0);

	do {
		cout << "Задайте количество переменных в уравнении: ";
		cin >> count_element;
	} while (count_element <= 0);

	do {
		cout << "Задайте точность вычисления: ";
		cin >> eps;
	} while (eps <= 0);

	// Выделение памяти после ввода значений
	systems = new float* [count_equation];
	for (int i = 0; i < count_equation; ++i) {
		systems[i] = new float[count_element];
	}

	z = new float[count_equation];
	norma_martitz = new float[count_equation];
	x0 = new float[count_equation];
	x1 = new float[count_equation];
	ostan = new float[count_equation];

}

// Заполнение неизвестных членов системы
void filling_system_element()
{
	for (int i = 0; i < count_equation; ++i)
	{
		for (int j = 0; j < count_element; ++j)
		{
			cout << "Задайте " << (j + 1) << " переменную " << (i + 1) << " урaвнения: ";
			cin >> systems[i][j];
		}

		cout << endl;
	}
}


// Заполнение свободных членов системы
void filling_system_z()
{
	for (int i = 0; i < count_equation; ++i)
	{
		cout << "Задайте свободный член " << (i + 1) << " урaвнения: ";
		cin >> z[i];
	}
}

// Нормы матриц
void norma_martitzs()
{
	// Построчные нормы матрицы
	for (int i = 0; i < count_equation; ++i)
	{
		float summ = 0;

		for (int m = 0; m < count_element; ++m)
		{
			if (i != m)
				summ += systems[i][m];
		}

		norma_martitz[i] = summ / systems[i][i];
	}

	double max = -100000000000000.00;

	for (int i = 0; i < count_equation; ++i)
	{
		if (fabs(norma_martitz[i]) > max)
		{
			max = norma_martitz[i];
		}
	}

	// Норма матрицы
	c = max;
}

// Условие остановки
void stop_condition()
{
	for (int i = 0; i < count_equation; ++i)
	{
		ostan[i] = fabs(c / (1 - c)) * fabs(x0[i] - x1[i]);
	}
}

// нулевое приближение n
void zero_approximation()
{
	// x(n)
	for (int i = 0; i < count_equation; ++i)
	{
		x0[i] = z[i] / systems[i][i];
	}
}

void clear()
{
	for (int i = 0; i < count_equation; ++i) {
		delete[] systems[i];
	}
	delete[] systems;
	delete[] z;
	delete[] x0;
	delete[] x1;
	delete[] norma_martitz;
	delete[] ostan;
}

void calculation()
{
	//Начало работы
	getting_started();
	
	// Заполнение неизвестных членов системы
	filling_system_element();

	// Заполнение свободных членов системы
	filling_system_z();

	// Нормы матриц
	norma_martitzs();

	if (c < 1 && c > 0)
	{
		// нулевое приближение n
		zero_approximation();

		int ostanovka;
		int a = 0;
		do {

			cout << a++ << endl;

			ostanovka = 0;

			for (int i = 0; i < count_equation; ++i)
			{
				float summ = 0;

				for (int m = 0; m < count_element; ++m)
				{
					if (i != m)
						summ += (systems[i][m] * x0[m]);
				}

				x1[i] = (z[i] - summ) / systems[i][i];
			}

			// Условие остановки
			stop_condition();

			for (int i = 0; i < count_equation; ++i)
			{
				x0[i] = x1[i];

				if (ostan[i] < eps)
					ostanovka++;
			}

		} while (ostanovka != count_equation);

		cout << endl << "Ответ:" << endl;

		for (int i = 0; i < count_equation; ++i)
		{
			cout << "x(n):" << (x0[i]) << " Оценка:" << (ostan[i]) << endl;
		}
	}

	else
		cout << endl << "Система не сходится";

	clear();
}


int main()
{
	//setlocale(LC_ALL, "Russian");
	//setlocale(0, "");
	setlocale(LC_ALL, "Rus");

	calculation();

	cin.get();
	cin.get();
	return 0;
}