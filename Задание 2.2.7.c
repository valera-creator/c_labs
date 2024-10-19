#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#define MAX_ROWS 20
#define MAX_COLS 20
#define DIV 5

void input_n_m(int* N, int* M)
{
	printf("Введите N: ");
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


int get_min_colum(const int arr[][MAX_COLS], int rows, int cols)
{	
	// вернет номер столбца, если найдется подходящий или вернет -1, если такого нет
	int i, j, is_ok = 1;
	for (i = 0; i < cols; i++)
	{	
		is_ok = 1;
		for (j = 0; j < rows - 1; j++)
		{	
			if (arr[j][i] % DIV == 0 || arr[j + 1][i] % DIV == 0 || arr[j][i] <= arr[j + 1][i])
			{
				is_ok = 0;
				break;
			}
		}

		if (is_ok)
		{
			return i;
		}
	}
	return -1;
}


void filling_matrix(const int arr_a[][MAX_COLS], int arr_b[][MAX_COLS], int rows, int cols, int del_col)
{	
	// is_del_col - флаг, примет значение 1, когда мы дошли до столбца, который не нужно записывать в матрицу b
	int i, j, is_del_col = 0;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			if (j == del_col)
			{
				is_del_col = 1;
			}

			else if (!is_del_col)
			{
				arr_b[i][j] = arr_a[i][j];
			}

			if (is_del_col)
			{
				arr_b[i][j] = arr_a[i][j + 1];
			}
		}
		is_del_col = 0;
	}
	return;
}


int main()
{
	int i, j, N, M, min_col, ** matrix_a, **matrix_b;
	setlocale(0, "");

	input_n_m(&N, &M);

	// выделение памяти для матрицы a
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
	min_col = get_min_colum(matrix_a, N, M);

	if (min_col == -1)
	{
		printf("столбца, удовлетворяющего условиям, не найдено\n");
		printf("исходная матрица\n");
		print_matrix(matrix_a, N, M);
	}

	else
	{
		// выделение памяти для матрицы b
		matrix_b = (int**)malloc(sizeof(int*) * N); // под строки
		if (matrix_b == NULL) // проверка, что не выделилась память
		{
			printf("во время выделения памяти память не выделилась");
			return 0;
		}

		for (j = 0; j < M - 1; j++) // под столбцы
		{
			matrix_b[j] = (int*)malloc(sizeof(int) * M);
			if (matrix_b[j] == NULL) // проверка, что не выделилась память
			{
				printf("во время выделения памяти столбцов память не выделилась");
				return 0;
			}
		}

		// заполнение matrix_b
		filling_matrix(matrix_a, matrix_b, N, M - 1, min_col);
		printf("исходная матрица\n");
		print_matrix(matrix_a, N, M);

		printf("измененная матрица\n");
		print_matrix(matrix_b, N, M - 1);

		// освобождение памяти матрицы b
		for (i = 0; i < N; i++)
		{
			free(matrix_b[i]);
		}
		free(matrix_b);
	}

	// освобождение памяти матрицы a
	for (i = 0; i < N; i++)
	{
		free(matrix_a[i]);
	}
	free(matrix_a);

	return 0;
}
