#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct element;
typedef struct element *pos;
typedef struct element
{
	char x;
	pos left;
	pos right;
}EL;

struct st;
typedef struct st *position;
typedef struct st
{
	pos el;
	position next;
}ST;

pos NewNode();
int Ucitavanje(position);
position NovaGlava();
pos Pop(position);
int Inorder(position);
int Ispisivanje(pos, FILE *);

int main(void)
{
	ST stog;
	stog.el = NULL;
	stog.next = NULL;

	if (Ucitavanje(&stog) != 0)
		printf("Greska!!!\n");

	if (Inorder(&stog) != 0)
		printf("Greska!!!\n");

	return 0;
}
int Inorder(position stog)
{
	FILE *f = NULL;
	char *filename = NULL;

	filename = (char *)malloc(20 * sizeof(char));
	if (filename == NULL)
		printf("Greska!!!\n");

	printf("Unesite ime datoteke u koju zelite napisati infix izraz : ");
	scanf("%s", filename);
	strcat(filename, ".txt");

	f = fopen(filename, "w");
	if (f == NULL)
		printf("Greska!!!\n");

	fprintf(f, "Infix\n");

	if (Ispisivanje(stog->next->el, f) != 0)
		printf("Greska!!!\n");

	fclose(f);
	free(filename);

	return 0;
}
int Ispisivanje(pos stog, FILE *f)
{
	if (stog != NULL)
	{
		fprintf(f, "(");		//previse zagrada
		Ispisivanje(stog->left, f);

		if (stog->x == '*' || stog->x == '+' || stog->x == '/' || stog->x == '-')
		{

			fprintf(f, "%c", stog->x);
		}
		else
			fprintf(f, "%d", (int)stog->x);

		Ispisivanje(stog->right, f);
		fprintf(f, ")");
	}

	return 0;
}
int Ucitavanje(position stog)
{
	FILE *f = NULL;
	char *filename = NULL;
	char *a = NULL;
	int x = 0;
	position novi_clan_stoga = NULL;

	a = (char *)malloc(10 * sizeof(char));
	if (a == NULL)
		printf("Greska!!!\n");

	memset(a, 0, 10);

	filename = (char *)malloc(20 * sizeof(char));
	if (filename == NULL)
		printf("Greska!!!\n");

	memset(filename, 0, 20);

	printf("Unesite ime datoteke iz koje zelitu ucitat postfix izraz: ");
	scanf(" %s", filename);
	strcat(filename, ".txt");

	f = fopen(filename, "r");
	if (f == NULL)
		printf("Datoteka je prazna!!!\n");

	while (!feof(f))
	{
		fscanf(f, " %s", a);

		//ako je broj ulazi u if
		if (isdigit(*a) != 0) //odi je problem neki
		{
			x = atoi(a);

			novi_clan_stoga = NovaGlava();		//alociras novi element
			novi_clan_stoga->el = NewNode();
			novi_clan_stoga->el->x = x;

			novi_clan_stoga->next = stog->next;	//povezujes odma iza heada
			stog->next = novi_clan_stoga;
		}
		else
		{
			novi_clan_stoga = NovaGlava();
			novi_clan_stoga->el = NewNode();
			novi_clan_stoga->el->x = *a;

			novi_clan_stoga->el->right = Pop(stog);
			novi_clan_stoga->el->left = Pop(stog);

			novi_clan_stoga->next = stog->next;
			stog->next = novi_clan_stoga;
		}
	}

	fclose(f);
	free(filename);
	free(a);

	return 0;
}
pos Pop(position stog)
{
	position temp = NULL;
	pos temp1 = NULL;

	temp = stog->next;
	temp1 = temp->el;

	stog->next = temp->next;

	free(temp);

	return temp1;
}
position NovaGlava()
{
	position Novaglava = 0;

	Novaglava = (position)malloc(sizeof(ST));
	if (Novaglava == NULL)
		printf("Greska!!!\n");

	Novaglava->el = NULL;
	Novaglava->next = NULL;

	return Novaglava;
}
pos NewNode()
{
	pos el = NULL;

	el = (pos)malloc(sizeof(EL));
	if (el == NULL)
		printf("Greska!!!\n");

	el->left = NULL;
	el->right = NULL;

	return el;
}