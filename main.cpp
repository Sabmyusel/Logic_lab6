#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include "task_main.h"
#include "task_dop.h"

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int m = -1;
	bool close = false;

	while (!close) {
		do {
			m = -1;
			system("cls");
			printf("[1]Матрицы.\n[2]Список.\n\n\n\n[0]Назад.\n");
			scanf("%d", &m);
			system("cls");
		} while (m < 0 || m > 4);

		switch (m) {
		case 1:
			matr();
			break;
		case 2:
			list();
			break;
		case 0:
			m = -1;
			close = true;
			break;
		}
	}
	return 0;
}