#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "revert_string.h"

int main(int argc, char *argv[])
/*принимает аргументы командной строки: argc- кол-во аргументов
командной строки (включая имя программы), argv - вектор строк С,
где элементы - отдельные строки аргументов командной строки */
{
	if (argc != 2)
	/*Проверяем, ввел ли пользователь 2 аргумент 
	и печатаем имя программы (нулевой аргумент)*/
	{
		printf("Usage: %s string_to_revert\n", argv[0]);
		return -1;
	}
	/*argv[1] - имя файла, который мы откроем, чтобы выполнить программу.
	выделяем память в куче, чтобы скопировать название файла в reverted_str*/
	char *reverted_str = malloc(sizeof(char) * (strlen(argv[1]) + 1));
	strcpy(reverted_str, argv[1]);

	RevertString(reverted_str);

	printf("Reverted: %s\n", reverted_str);
	free(reverted_str);
	return 0;
}

