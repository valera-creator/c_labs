#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

int main()
{
	int n, is_fool, summa = 0, count_elems = 0;
	int left = -1, right = -1;
	int *array;
	char buf_string;
	setlocale(LC_ALL, "Russian");

	// ввод и проверка на дурака дл€ числа n
	while (1)
	{
		printf("¬ведите N:\n");
		is_fool = scanf_s("%d", &n);
		if (is_fool)
		{
			break;
		}
		else
		{
			printf("N должно быть числом\n");
			scanf_s("%c", &buf_string); // если ввели строку, считываем буфер
		}
	}
	right = n - 1;
	array = malloc(sizeof(int) * n);

	// заполнение массива
	printf("¬ведите элементы массива\n");
	for (int i = 0; i < n; i++)
	{
		// ввод и проверка на дурака дл€ элементов массива
		while (1)
		{
			printf("¬ведите %d-й элемент массива:\n", i + 1);
			is_fool = scanf_s("%d", &array[i]);
			if (is_fool)
			{
				break;
			}
			else
			{
				printf("элемент должно быть числом\n");
				scanf_s("%c", &buf_string); // если ввели строку, считываем буфер
			}
		}
	}

	// лева€ граница
	for (int i = 0; i < n; i++)
	{
		if (-5 >= array[i] || array[i] >= 7)
		{
			left = i;
			break;
		}
	}

	// если нет левой границы
	if (left == -1)
	{
		printf("левой границы нет;\nсумма: %d\nколичество: %d\n", summa, count_elems);
		return 0;
	}

	// права€ граница
	for (int i = left + 1; i < n; i++)
	{
		if (array[i] < i + 1)
		{
			right = i;
		}
	}

	// printf("left: %d\n", left);
	// printf("right: %d\n", right);

	// вычисление суммы
	for (int i = left; i <= right; i++)
	{
		summa += array[i];
	}

	count_elems = right - left + 1;

	printf("сумма: %d\nколичество: %d\n", summa, count_elems);
	return 0;
}