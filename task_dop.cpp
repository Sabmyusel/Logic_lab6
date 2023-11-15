#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

int size = 0;
int* last;

struct node {
	int vertex = 0;
	struct node** next;
};
struct node* vert;
void genl() {
	int temp = 0;
	int** arr;
	arr = new int* [size];
	for (int i = 0; i < size; i++)
		arr[i] = new int[size] {0};

	srand(time(NULL));

	for (int i = 0; i < size; i++)
		for (int k = i + 1; k < size; k++) {
			temp = rand() % 2;
			arr[i][k] = temp;
			arr[k][i] = temp;
		}

	vert = new struct node[size];
	for (int i = 0; i < size; i++) {
		vert[i].vertex = i + 1;
		vert[i].next = new struct node* [size] {NULL};
	}

	for (int i = 0; i < size; i++)
		for (int k = i + 1; k < size; k++)
			if (arr[i][k] == 1) {
				vert[i].next[k] = &vert[k];
				vert[k].next[i] = &vert[i];
			}
			else {
				vert[i].next[k] = NULL;
				vert[k].next[i] = NULL;
			}


	delete[] arr;
}

void printl(bool debug) {

	printf("\n Вершины : ");
	for (int i = 0; i < size; i++) {
		if (vert[i].vertex != 0) {
			printf("\n %d ", vert[i].vertex);
			for (int k = 0; k < size; k++)
				if (vert[i].next[k] != NULL)
					printf("-> %d ", vert[k].vertex);
		}
	}

	printf("\n\n");
}

struct node* addl() {
	struct node* arr;

	(size)++;

	arr = new struct node[size];
	for (int i = 0; i < size; i++) {
		arr[i].vertex = vert[i].vertex;
		arr[i].next = new struct node* [size] {NULL};
	}

	for (int i = 0; i < (size)-1; i++)
		for (int k = 0; k < (size)-1; k++)
			arr[i].next[k] = vert[i].next[k];

	for (int i = 0; i < size - 1; i++)
		delete[] vert[i].next;
	delete[] vert;

	return arr;
}

struct node* dell(int n) {// удаляет вершину n
	struct node* arr;

	n--;
	(size)--;

	arr = new struct node[size];
	for (int i = 0; i < size; i++) {
		if (i != n)
			arr[i].vertex = vert[i].vertex;
		else
			arr[i].vertex = i + 1;
		arr[i].next = new struct node* [size] {NULL};
	}

	/* удаление строки */
	for (int i = n; i < size; i++)
		for (int j = 0; j < (size)+1; j++)
			vert[i].next[j] = vert[i + 1].next[j];

	/* удаление столбца */
	for (int i = 0; i < (size)+1; i++)
		for (int j = n; j < (size); j++)
			vert[i].next[j] = vert[i].next[j + 1];

	for (int i = 0; i < (size); i++)
		for (int k = 0; k < (size); k++)
			arr[i].next[k] = vert[i].next[k];


	delete[] vert->next;
	delete[] vert;

	return arr;
}

void help(int* n1) {
	int i = 0;
	int k1 = 0;
	while (k1 == 0 && i < size) {
		if (vert[k1].vertex == *n1) {
			k1 = i;
			break;
		}
		i++;
	}
	*n1 = k1;
}

void l1_AB(int t) {//t == 1 - отождествление,  t == 2 - стягивание
	int n1 = 0, n2 = 0;
	int temp = 0;
	int tmp;
	if (t == 1) {
		printf("Введите номера вершин графа для отождествления: ");

		scanf("%d", &n1);
		scanf("%d", &n2);
		n1--;
		n2--;
		//help(&n1);
		//help(&n2);
	}
	else {
		do {
			printf("Введите номера вершин графа для стягивания: ");
			scanf("%d", &n1);
			scanf("%d", &n2);
			if (n1 == 0 || n2 == 0)
				return;
			n1--;
			n2--;
			if (vert[n1].next[n2] == NULL)
				printf("Нет ребра!\n");
			else if (n1 == n2) {
				vert[n1].next[n1] = NULL;
				return;
			}
			else {
				vert[n1].next[n2] = NULL;
				vert[n2].next[n1] = NULL;
				break;
			}
		} while (vert[n1].next[n2] == NULL);
	}


	for (int k = 0; k < size - 1; k++) {
		if (vert[n1].next[k] == NULL)
			vert[n1].next[k] = vert[n2].next[k];
	}

	vert = dell(n2 + 1);

}

void l1_C(int n, int num) {//расщепление вершины n

	n--;
	vert = addl();
	int n2 = size - 1;
	//help(&n, &n2);
	vert[n2].vertex = size;
	for (int k = 0; k < size - 1; k++)
		vert[n2].next[k] = vert[n].next[k];

	vert[n].next[n2] = &vert[n2];
	vert[n2].next[n] = &vert[n];
}


void list() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	bool close = false;
	int zad = -1, n = 0;

	printf("Введите кол-во вершин графа: ");
	scanf("%d", &size);
	genl();

	while (!close) {
		zad = -1;
		while (zad < 0 || zad > 3) {
			printl(false);
			printf("[1]Отождествление вершин.\n[2]Стягивание ребра.\n[3]Расщепление вершины.\n\n\n[0]Выход.\n");
			scanf("%d", &zad);
			system("cls");
		}

		switch (zad) {
		case 1:
			printl(false);
			l1_AB(1);
			printl(false);
			system("pause");
			system("cls");
			break;
		case 2:
			printl(false);
			l1_AB(2);
			printl(false);
			system("pause");
			system("cls");
			break;
		case 3:
			printl(false);
			printf("Номер вершины для расщепления: ");
			scanf("%d", &n);
			l1_C(n, 0);
			printl(false);
			system("pause");
			system("cls");
			break;
		case 0:
			for (int i = 0; i < size - 1; i++)
				delete[] vert[i].next;
			delete[] vert;
			close = true;
			break;
		}
	}
}