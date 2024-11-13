#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct list
{
	int inf;
	struct list* next;
};

int input_list(struct list** head, struct list** last, int* cnt_elems)
{
	int res, val;
	char buf;
	printf("ввод элементов списка будет происходить, пока не введено не число\n");
	printf("введите 1-й элемент списка (число) или не число для прекращения ввода: ");
	while (1)
	{
		res = scanf_s("%d", &val);
		if (!res)
		{
			scanf_s("%c", &buf);
			break;
		}
		else
		{
			(*cnt_elems)++;
			if (!insert_end(val, head, last))
			{
				printf("ошибка выделения памяти");
				return 0;
			}
			printf("введите %d-й элемент списка (число) или не число для прекращения ввода: ", (*cnt_elems) + 1);
		}
	}
	return 1;
}


int insert_end(int val, struct list** head, struct list** last)
{
	// функция вернет 1, если нет ошибок с выделением памяти, иначе 0, если есть
	struct list* cur;
	cur = (struct list*)malloc(sizeof(struct list));

	if (cur == NULL) // если ошибка выделения памяти
		return 0;

	cur->next = NULL;
	cur->inf = val;
	if ((*head) == NULL)
	{
		(*head) = cur;
		(*last) = cur;
	}
	else
	{
		(*last)->next = cur;
		(*last) = cur;
	}
	return 1;
}


void print_list(struct list** head)
{
	struct list* cur = (*head);

	if (cur == NULL)
	{
		printf("пустой список\n");
		return;
	}

	while (cur != NULL)
	{
		printf("%d ", cur->inf);
		cur = cur->next;
	}
	return;
}

void clear_list(struct list** head, struct list** last)
{
	struct list* cur = *head;
	struct list* next_elem = NULL;

	while (cur != NULL)
	{
		next_elem = cur->next;
		free(cur);
		cur = next_elem;
	}
	(*head) = (*last) = NULL;
	return;
}

int main()
{
	setlocale(0, "");
	struct list* head_first, * last_first, *head_second, *last_second;
	head_first = last_first = head_second = last_second = NULL;
	int cnt_elems = 0;
	
	
	if (!input_list(&head_first, &last_first, &cnt_elems)) // ошибка выделения памяти возникла
	{
		return 0;
	}

	print_list(&head_first);
	clear_list(&head_first, &last_first);

	return 0;
}
