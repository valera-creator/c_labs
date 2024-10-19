#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#define MAX_ROWS 20
#define MAX_COLS 20

void input_n_m(int* N, int* M)
{
	printf("Введите n: ");
	*N = get_correct_type_value();
	while (*N > MAX_ROWS)
	{
		printf("N должно быть не более %d\nВведите n заново", MAX_ROWS);
		*N = get_correct_type_value();
	}

	printf("Введите M: ");
	*M = get_correct_type_value();
	while (*M > MAX_COLS)
	{
		printf("m должно быть не более %d\nВведите n заново", MAX_COLS);
		*M = get_correct_type_value();
	}
	return;
}


void input_matrix(int arr[][MAX_COLS], int rows, int cols)
{
	int i, j;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{	
			printf("[%d][%d] = ", i, j);
			arr[i][j] = get_correct_type_value();
		}
	}
	return;
}

void print_matrix(const int arr[][MAX_COLS], int rows, int cols)
{
	int i, j;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
	return;
}


int get_correct_type_value()
{
	// возвращает число, когда оно корректное (подходит под int)
	int res, num;
	char buf;
	while (1)
	{
		res = scanf_s("%d", &num);

		if (!res)
		{
			printf("Введено некорректное значение, введите по новой: ");
			scanf_s("%c", &buf);
			printf("\n");
		}
		else
		{
			return num;
		}
	}
}


int main()
{
	int i, j, N, M, ** matrix_a;
	setlocale(0, "");

	input_n_m(&N, &M);

	// выделение памяти
	matrix_a = (int**)malloc(sizeof(int*) * N); // под строки
	if (matrix_a == NULL) // проверка, что не выделилась память
	{
		printf("во время выделения памяти память не выделилась");
		return 0;
	}

	for (j = 0; j < M; j++) // под столбцы
	{
		matrix_a[j] = (int*)malloc(sizeof(int) * M);
		if (matrix_a[j] == NULL) // проверка, что не выделилась память
		{
			printf("во время выделения памяти столбцов память не выделилась");
			return 0;
		}
	}

	input_matrix(matrix_a, N, M);
	print_matrix(matrix_a, N, M);

	// освобождение памяти
	for (i = 0; i < N; i++)
	{
		free(matrix_a[i]);
	}
	free(matrix_a);

	return 0;
}
