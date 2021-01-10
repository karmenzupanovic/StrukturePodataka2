#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

struct Element;
typedef struct Element *position;
typedef struct Element
{
	int x;
	position left;
	position right;
}_el;

position Unos_novog_el(position, int);
int Ispis(position);
position Trazi(int, position);
position Brisanje(int, position);
position TraziMax(position);

int main(void)
{
	position stablo = NULL;
	position trazeni_element = NULL;
	int izbor = 0;
	int temp = 0;

	while (izbor != 5)
	{
		printf("\n\n 1 - Unosenje novog elementa\n 2 - Ispis elemenata\n 3 - Brisanje\n 4 - Trazi element\n 5 - Kraj\n");
		printf("Unesite broj sto zelite napraviti: ");
		scanf("%d", &izbor);

		switch (izbor)
		{
		case 1:
			printf("Unesite vrijednost novog elemnta: ");
			scanf("%d", &temp);

			stablo = Unos_novog_el(stablo, temp);
			break;
		case 2:
			if (Ispis(stablo) != 0)
				printf("Greska!!!\n");
			break;
		case 3:
			printf("Unesite element koji zelite izbrisati: ");
			scanf("%d", &temp);
			stablo = Brisanje(temp, stablo);
			break;
		case 4:
			printf("Unesite element koji zelite pronaci: ");
			scanf("%d", &temp);
			trazeni_element = Trazi(temp, stablo);

			if (trazeni_element != NULL)
				printf("Element %d je na adresi %x.\n", temp, (unsigned int)trazeni_element);
			else
				printf("Trazeni element ne postoji!!!\n");
			break;
		case 5:
			break;
		default:
			printf("Niste unjeli ni jednu od ponudenih opcija, pokusajte ponovo!\n");
		}
	}

	return 0;
}

position Unos_novog_el(position S, int x) {

	if (S == NULL) {
		S = malloc((position)malloc(sizeof(_el)));
		if (S == NULL)
			printf("Greska!!!\n");
		S->x = x;
		S->left = NULL;
		S->right = NULL;
		return S;
	}

	if (x < S->x) {
		S->left = Unos_novog_el(S->left, x);
		return S;
	}

	else if (x > S->x) {
		S->right = Unos_novog_el(S->right, x);
		return S;
	}

	else {
		printf("Dupli element!!!");
		//free(x);
		return S;
	}
}

int Ispis(position S) {

	if (S == NULL)
		return;
	
	Ispis(S->left);
	printf("  %d  ", S->x);
	Ispis(S->right);

	return 0;
}

position Trazi(int x, position S)

{

	if (S == NULL) {
		return NULL;
	}

	if (x < S->x) {
		return Trazi(x, S->left);
	}

	else if (x > S->x) {
		return Trazi(x, S->right);
	}
	else if (x == S->x) { 
		return S;
	}
}

position TraziMax(position S) {

	if (S == NULL)
		return S;

	else {

		if (S->right == NULL)
			return S;

		return TraziMax(S->right);
	}

}

position Brisanje(int x, position S) {

	if (S == NULL) {
		printf("Nema ga!!!");
		return S;
	}

	if (x < S->x) {
		S->left = Brisanje(x, S->left);
		return S;
	}


	else if (x > S->x) {
		S->right = Brisanje(x, S->right);
		return S;
	}

	else if ((S->left && S->right) != NULL) {

		position temp = NULL;

		temp = TraziMax(S->left);
		S->x = temp->x;

		S->left = Brisanje(S->x, S->left);

		return S;
	}
	else {
		position temp = S;

		if (NULL == S->left)
			S = S->right;

		else
		S = S->left;

		free(temp);

		return S;
	}
}