#include <stdio.h>
#include <locale.h>
#define ALL_WORDS 30 
#define ALL_BOOKS 20 + 1 // берем еще 1 символ на '\0'


int input_str(int* cnt_words, char str[][ALL_BOOKS], char *end_symbol)
{
    // функция вернет 1, если был корректный ввод, иначе 0
    int index_i = 0, index_j = 0;
    char buf;

    scanf_s("%c", &buf);
    while (1)
    {
        while (('a' <= buf && buf <= 'z') || ('A' <= buf && buf <= 'Z'))
        {   
            // проверка на превышение букв в слове
            if (index_j >= ALL_BOOKS - 1) 
            {
                printf("Ошибка: Число букв превысило допустимое значение %d", ALL_BOOKS - 1);
                return 0;
            }

            str[index_i][index_j] = buf;
            index_j++;

            scanf_s("%c", &buf);
        }

        // Если не буква
        if (index_j > 0) 
        {
            str[index_i][index_j] = '\0';
            index_j = 0;
            (*cnt_words)++;
            index_i++;
        }

        // проверка на превышение слов
        if ((*cnt_words) >= ALL_WORDS)
        {
            printf("Ошибка: Кол-во слов превышает допустимое значение, %d", ALL_WORDS);
            return 0;
        }

        // Пропускаем пробелы
        while (buf == ' ')
        {   
            scanf_s("%c", &buf);
        }

        // Конец строки
        if (buf == '.' || buf == '!' || buf == '?')
        {   
            (*end_symbol) = buf;
            return;
        }

        // если введено некорректно
        if (!(('a' <= buf && buf <= 'z') || ('A' <= buf && buf <= 'Z')) && !(buf == ' ') && !((buf == '.' || buf == '!' || buf == '?')))
        {
            if (!(('a' <= buf && buf <= 'z') || ('A' <= buf && buf <= 'Z')))
                printf("Была введена не латинская буква, не символ из конца предложения и не пробел\n");
            else
                printf("Предложение не завершилась символом из предложенных: '?', '!', '.'");
            return 0;
        }
    }
    return 1;
}


void print_str(int cnt_words, const char str[][ALL_BOOKS], char end_symbol)
{   
    // функция выводит слова, последнее слово она выводит без пробела для приклеивания точки в конец предложения
    int i;
    printf("Введенный текст с преобразованием удаления лишних пробелов между словами: ");
    for (i = 0; i < cnt_words; i++)
    {   
        if (i == cnt_words - 1)
            printf("%s", str[i]);
        else
            printf("%s ", str[i]);
    }
    printf("%c\n", end_symbol);
    return;
}


void check_books(const char str[][ALL_BOOKS], int cnt_words)
{   
    // функция ведет подсчет букв пословно в предложении
    char cur_symbol = 'a';
    int cnt_books = 0, i = 0;
    printf("Пословный подсчет букв в предложении:\n");
    for (cur_symbol; cur_symbol != 'z' + 1; cur_symbol = cur_symbol + 1)
    {
        for (i = 0; i < cnt_words; i++)
        {
            if (check_book_in_word(str[i], cur_symbol))
                cnt_books += 1;
        }
        printf("'%c' = %d\n", cur_symbol, cnt_books);
        cnt_books = 0;
    }
    return;
}


int check_book_in_word(const char str[ALL_BOOKS], char symbol)
{   // функция проверяет, есть ли в слове символ, не учитывая регистр
    int i;
    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == symbol || str[i] == symbol - 32)
            return 1;
    }
    return 0;
}


int main()
{
    char str[ALL_WORDS][ALL_BOOKS];
    char end_symbol;
    int cnt_words = 0;
    setlocale(0, "");

    if (!input_str(&cnt_words, str, &end_symbol))
        return 0;

    if (cnt_words == 0)
    {
        printf("Было введено пустое предложение");
        return 0;
    }
        
    print_str(cnt_words, str, end_symbol);
    check_books(str, cnt_words);

    return 0;
}
