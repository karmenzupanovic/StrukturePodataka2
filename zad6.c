#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct mem;
typedef struct mem * poz;
struct mem {
	int broj;
	poz next;
};

int random();
poz CreateNew();
int ispis(poz);
int push(poz);		//red i stog ubacuju na pocetak
int stogpop(poz);		//stog brise sa pocetka (first in last out)
int redpop(poz);		//red brise sa kraja (first in first out)

int main()
{
	int izbor = 0;
	struct mem stog;
	struct mem red;
	stog.next = NULL;
	red.next = NULL;

	while (izbor != 7)
	{
		printf("\t upisi broj sto zelis napraviti:\n");
		printf("1- ispisi stog\n");
		printf("2- upisivanje broja u stog\n");
		printf("3- brisanje broja sa stoga\n");
		printf("4- ispisi red\n");
		printf("5- upisivanje broja u red\n");
		printf("6- brisanje broja iz reda\n");
		printf("7- izlaz\n");

		scanf(" %d", &izbor);
		printf("\n");

		switch (izbor)
		{
		case 1:
			printf("stog: ");
			ispis(stog.next);
			printf("\n");
			break;

		case 2:
			push(&stog);
			break;

		case 3:
			stogpop(&stog);
			break;


		case 4:
			printf("red: ");
			ispis(red.next);
			printf("\n");
			break;

		case 5:
			push(&red);
			break;

		case 6:
			redpop(&red);
			break;

		case 7:
			printf("izlaz iz programa.\n");
			break;

		default:
			printf("krivo upisan broj\n\n");
			break;
		}

	}
	return 0;
}

int random()
{
	int x;
	srand((unsigned)time(NULL));
	x = rand() % (100 - 10 + 1) + 10;
	return x;
}

poz CreateNew()
{
	poz q = NULL;
	q = (struct mem *) malloc(sizeof(struct mem));
	if (q == NULL) {
		printf("greska.\n");
		return NULL;
	}
	return q;
}

int ispis(poz P) {

	if (P == NULL)
		printf("lista je prazna.");

	while (P != NULL) {
		printf("%d  ", P->broj);
		P = P->next;
	}
	printf("\n");
	return 0;
}
int push(poz P) {

	poz q;
	q = CreateNew();
	q->next = P->next;
	P->next = q;
	q->broj = random();

	return 0;
}

int stogpop(poz P) {

	if (P->next == NULL)
		printf("lista je prazna, nema se sto obrisati.\n\n");

	else
	{
		poz temp;
		temp = P->next;
		P->next = temp->next;
		free(temp);
	}
	return 0;
}

int redpop(poz P) {

	if (P->next == NULL)
		printf("lista je prazna, nema se sto obrisati.\n\n");

	else
	{
		while (P->next->next != NULL)
			P = P->next;


		free(P->next->next);
		P->next = NULL;
	}
	return 0;
}