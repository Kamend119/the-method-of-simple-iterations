#include <iostream>
#include <cmath>
using namespace std;

// Разрядность системы
int count_razr;
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
		cout << "Задайте разрядность системы: ";
		cin >> count_razr;
	} while (count_razr <= 0);

	do {
		cout << "Задайте точность вычисления: ";
		cin >> eps;
	} while (eps <= 0);

	// Выделение памяти после ввода значений
	systems = new float* [count_razr];
	for (int i = 0; i < count_razr; ++i) {
		systems[i] = new float[count_razr];
	}

	z = new float[count_razr];
	norma_martitz = new float[count_razr];
	x0 = new float[count_razr];
	x1 = new float[count_razr];
	ostan = new float[count_razr];

}

// Заполнение неизвестных членов системы
void filling_system_element()
{
	for (int i = 0; i < count_razr; ++i)
	{
		cout << endl;

		for (int j = 0; j < count_razr; ++j)
		{
			cout << "Задайте " << (j + 1) << " переменную " << (i + 1) << " урaвнения: ";
			cin >> systems[i][j];
		}
	}
}


// Заполнение свободных членов системы
void filling_system_z()
{
	for (int i = 0; i < count_razr; ++i)
	{
		cout << "Задайте свободный член " << (i + 1) << " урaвнения: ";
		cin >> z[i];
	}
}

// Нормы матриц
void norma_martitzs()
{
	// Построчные нормы матрицы
	for (int i = 0; i < count_razr; ++i)
	{
		float summ = 0;

		for (int m = 0; m < count_razr; ++m)
		{
			if (i != m)
				summ += systems[i][m];
		}

		norma_martitz[i] = summ / systems[i][i];
	}

	double max = -100000000000000.00;

	for (int i = 0; i < count_razr; ++i)
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
	for (int i = 0; i < count_razr; ++i)
	{
		ostan[i] = fabs(c / (1 - c)) * fabs(x0[i] - x1[i]);
	}
}

// нулевое приближение n
void zero_approximation_method_simpl_iteration()
{
	// x(n)
	for (int i = 0; i < count_razr; ++i)
	{
		x0[i] = z[i] / systems[i][i];
	}
}

void zero_approximation_method_zeidela()
{
	// x(n)
	for (int i = 0; i < count_razr; ++i)
	{
		if (i == 0)
		{
			x0[i] = z[i] / systems[i][i];
		}
		else x0[i] = 0;
	}
}

void clear()
{
	for (int i = 0; i < count_razr; ++i) {
		delete[] systems[i];
	}
	delete[] systems;
	delete[] z;
	delete[] x0;
	delete[] x1;
	delete[] norma_martitz;
	delete[] ostan;
}

void calculation_method_simpl_iteration()
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
		zero_approximation_method_simpl_iteration();

		int ostanovka;
		int a = 0;
		do {

			cout << a++ << endl;

			ostanovka = 0;

			for (int i = 0; i < count_razr; ++i)
			{
				float summ = 0;

				for (int m = 0; m < count_razr; ++m)
				{
					if (i != m)
						summ += (systems[i][m] * x0[m]);
				}

				x1[i] = (z[i] - summ) / systems[i][i];
			}

			// Условие остановки
			stop_condition();

			for (int i = 0; i < count_razr; ++i)
			{
				x0[i] = x1[i];

				if (ostan[i] < eps)
					ostanovka++;
			}

		} while (ostanovka != count_razr);

		cout << endl << "Ответ:" << endl;

		for (int i = 0; i < count_razr; ++i)
		{
			cout << "x(n):" << (x0[i]) << " Оценка:" << (ostan[i]) << endl;
		}
	}

	else
		cout << endl << "Система не сходится";

	clear();
}

void calculation_method_zeidela()
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
		zero_approximation_method_zeidela();

		int ostanovka, a = 0;
		do {
			ostanovka = 0, a++;

			for (int i = 0; i < count_razr; ++i)
			{
				float summ = 0;

				for (int m = 0; m < count_razr; ++m)
				{
					if (i != m)
					{
						if (i == 0)
							summ += (systems[i][m] * x0[m]);
						else
						{
							if (m <= i)
								summ += (systems[i][m] * x1[m]);
							else 
								summ += (systems[i][m] * x0[m]);
						}
					}
						
				}

				x1[i] = (z[i] - summ) / systems[i][i];
			}

			// Условие остановки
			stop_condition();

			for (int i = 0; i < count_razr; ++i)
			{
				x0[i] = x1[i];

				if (ostan[i] < eps)
					ostanovka++;
			}

		} while (ostanovka != count_razr);

		cout << endl << "Ответ:" << endl;

		for (int i = 0; i < count_razr; ++i)
		{
			cout << "x(n):" << (x0[i]) << " Оценка:" << (ostan[i]) << endl;
		}

		cout << "Количество итераций: " << a << endl;
	}

	else
		cout << endl << "Система не сходится";

	clear();
}

void method_selection()
{
	int a = 0;
	cout << "Выберите метод решения СЛАУ" << endl << "1. Метод простых итераций (число 1)" << endl << "2. Метод Зейделя (число 2)" << endl;
	cin >> a;

	if (a == 1)
		calculation_method_simpl_iteration();
	if (a == 2)
		calculation_method_zeidela();

	else
		cout << "Такого метода нету";
}

int main()
{
	setlocale(LC_ALL, "Rus");

	method_selection();

	cin.get();
	cin.get();
	return 0;
}