#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

struct element;
typedef struct element *position;
typedef struct element {
	int x;
	position next;
}el;

int Ucitavanje(position);
int Stavinastog(position, int);
int Pop(position);
int Operacija(int, int, char *);
int Print(position);
int Brojac(position);

int main(void)
{
	el head;
	head.next = NULL;

	if (Ucitavanje(&head) != 0)
		printf("Greska!!!\n");

	return 0;
}
int Ucitavanje(position p)
{
	FILE *f = NULL;
	char *filename = NULL;
	char *temp = NULL;
	int prvibr = 0, drugibr = 0, rez = 0;

	filename = (char *)malloc(20 * sizeof(char));
	if (filename == NULL)
		printf("Greska!!!\n");

	temp = (char *)malloc(20 * sizeof(char));
	if (temp == NULL)
		printf("Greska!!!\n");

	printf("Unesite ime datoteke : \n");
	scanf("%s", filename);

	strcat(filename, ".txt");

	f = fopen(filename, "r");
	if (f == NULL)
		printf("Greska!!!\n");

	while (!feof(f))
	{
		fscanf(f, "%s ", temp);

		if (isdigit(*temp))
		{
			if (Stavinastog(p, atoi(temp)) != 0)
				printf("Greska!!!\n");

			printf("Ucitajem novi element na stog :\n");
			if (Print(p) != 0)
				printf("Greska!!!\n");
		}
		else
		{
			prvibr = Pop(p);
			drugibr = Pop(p);
			if (drugibr == -1)
			{
				printf("Krivo napisan postfix izraz!!!\n");  
				return 0;
			}


			rez = Operacija(prvibr, drugibr, temp);
			if (Stavinastog(p, rez) != 0)
				printf("Greska!!!\n");
			if (rez == -1) {
				printf("Greska!!!\n");
				return 0;
			}

			printf("Nakon nailaska na operator \"%s\": \n", temp);
			if (Print(p) != 0)
				printf("Greska!!!\n");
		}
	}

	if (Brojac(p) != 1)
		printf("Krivo napisan postfix izraz!!!\n");

	return 0;
}

int Stavinastog(position p, int a)
{
	position novo = NULL;

	novo = (position)malloc(sizeof(el));
	if (novo == NULL)
		printf("Greska!!!\n");

	novo->x = a;

	novo->next = p->next;
	p->next = novo;

	return 0;
}
int Brojac(position p)
{
	int br = 0;

	while (p->next != NULL)
	{
		br++;
		p = p->next;
	}

	return br;
}
int Print(position p)
{
	while (p->next != NULL)
	{
		printf("%d\n", p->next->x);
		p = p->next;
	}

	return 0;
}
int Operacija(int a, int b, char *c)
{
	switch (*c)
	{
	case '+':
		return b + a;
		break;
	case '*':
		return b * a;
		break;
	case '-':
		return b - a;
		break;
	case '/':
		if (a == 0)
		{
			printf("Dijeljenje s nulom nije dozvoljeno!\n");
			return -1;
		}
		return b / a;
		break;
	}
}
int Pop(position p)
{
	position temp = NULL;
	int a = 0;

	if (p->next != NULL)
	{
		temp = p->next;
		p->next = p->next->next;
		a = temp->x;
		free(temp);

		return a;
	}
	else
		return -1;

}
