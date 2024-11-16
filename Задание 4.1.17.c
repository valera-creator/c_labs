#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct list
{
	int inf;
	struct list* next;
};


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


int input_list(struct list** head, struct list** last)
{
	int res, val;
	char buf;
	int cnt_elems = 0;
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
			cnt_elems++;
			if (!insert_end(val, head, last))
			{
				printf("ошибка выделения памяти");
				return 0;
			}
			printf("введите %d-й элемент списка (число) или не число для прекращения ввода: ", cnt_elems + 1);
		}
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


int write_elems_new_list(struct list** head_first, struct list** head_second, struct list** last_second)
{
	struct list* cur_first_list = (*head_first);
	struct list* prev_first_list = (*head_first);
	int cur_num_elems = 0;

	while (cur_first_list != NULL)
	{
		cur_num_elems ++;
		if (cur_first_list->inf > cur_num_elems)
		{
			if (cur_first_list == (*head_first)) // если самый первый элемент из первого списка подошел
			{
				if ((*head_second) == NULL) // если во втором списке еще ничего нет
				{
					(*head_second) = (*head_first);
					(*last_second) = (*head_first);
					(*head_first) = (*head_first)->next;
					prev_first_list = cur_first_list;
					cur_first_list = cur_first_list->next;
					(*head_second)->next = NULL;
				}
				else // если во втором списке уже что-то есть (на прошлом этапе из первого списка забрали элемент, а текущий элемент снова подошел)
				{
					(*last_second)->next = (*head_first);
					(*last_second) = (*head_first);
					(*head_first) = (*head_first)->next;
					prev_first_list = cur_first_list;
					cur_first_list = cur_first_list->next;
					(*last_second)->next = NULL;
				}

			}
			else
			{
				if ((*head_second) == NULL) // создаем первый элемент второго списка
				{
					(*head_second) = cur_first_list;
					(*last_second) = cur_first_list;
					prev_first_list->next = cur_first_list->next;
					cur_first_list = cur_first_list->next;
					(*head_second)->next = NULL;
				}
				else // добавляем уже к существующему элементу во второй список
				{
					(*last_second)->next = cur_first_list;
					(*last_second) = cur_first_list;
					prev_first_list->next = cur_first_list->next;
					cur_first_list = cur_first_list->next;
					(*last_second)->next = NULL;
				}
			}
		}
		else
		{
			prev_first_list = cur_first_list;
			cur_first_list = cur_first_list->next;

		}
	}
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
	struct list* head_first, * last_first, * head_second, * last_second;
	head_first = last_first = head_second = last_second = NULL;


	if (!input_list(&head_first, &last_first)) // ошибка выделения памяти возникла
	{
		return 0;
	}

	printf("\nПервый список до изменений: ");
	print_list(&head_first);

	if (head_first != NULL)
	{
		write_elems_new_list(&head_first, &head_second, &last_second);
		printf("\nПервый список после изменений: ");
		print_list(&head_first);
	}
	
	printf("\nВторой список: ");
	print_list(&head_second);

	clear_list(&head_first, &last_first);
	clear_list(&head_second, &last_second);
	return 0;
}
