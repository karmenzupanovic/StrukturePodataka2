#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


typedef struct lista *Poz;
typedef struct lista brojevi;

struct lista {
	int br;
	Poz next;
};

Poz CreateNew();
int Ispis(Poz);
int IspisIzDat(Poz);
int Unija(Poz, Poz, Poz);
int Presjek(Poz, Poz, Poz);


int main()
{
	brojevi L1, L2, Un, Pr;
	L1.next = L2.next = Un.next = Pr.next = NULL;
	int pr = 100, x = 0;

	while (pr != 0)
	{
		printf("\n1 - Ispis iz datoteke u prvu listu");
		printf("\n2 - Ispis iz datoteke u drugu listu");
		printf("\n3 - Ispis dviju lista");
		printf("\n4 - Ispis unija lista");
		printf("\n5 - Ispis presjeka lista");

		printf("\n0 - Izlaz");

		printf("\nUpisi svoj izbor: ");
		scanf("%d", &pr);

		switch (pr)
		{
		case 1:
			x = IspisIzDat(&L1);
			if (x == -1) printf("Greska! Lista je prazna.\n");
			break;
		case 2:
			IspisIzDat(&L2);
			if (x == -1) printf("Greska! Lista je prazna.\n");
			break;
		case 3:
			printf("Prva lista:");
			x = Ispis(L1.next);
			if (x == -1) printf("Prva lista je prazna!\n");

			printf("Druga lista:");
			x = Ispis(L2.next);
			if (x == -1) printf("Druga lista je prazna!\n");
			break;
		case 4:
			printf("Unija:");
			x = Unija(L1.next, L2.next, &Un);
			if (x == -1) printf("Greska!\n");
			Ispis(Un.next);
			break;
		case 5:
			printf("Presjek:");
			x = Presjek(L1.next, L2.next, &Pr);
			if (x == -1) printf("Greska!\n");
			Ispis(Pr.next);
			break;
		case 0:
			printf("Izlaz iz programa.\n");
			break;
		default:
			printf("Nepoznat unos!!!\n");
			break;
		}
	}
	return 0;
}

Poz CreateNew()
{
	Poz q = NULL;
	q = (Poz)malloc(sizeof(brojevi));
	if (q == NULL) return q;

	q->next = NULL;

	return q;
}

int Ispis(Poz P)
{
	if (P == NULL) return -1;

	while (P != NULL)
	{
		printf(" %d", P->br);
		P = P->next;
	}
	printf("\n");
	return 0;
}

int IspisIzDat(Poz P)
{
	FILE * dat = NULL;
	char str[20];
	Poz q, Pocetak;
	q = NULL;
	Pocetak = P;

	printf("Upisi ime datoteke: ");
	scanf(" %s", str);

	dat = fopen(str, "r");
	if (dat == NULL) return -1;

	while (!feof(dat))
	{
		q = CreateNew();
		if (q == NULL) return -1;
		fscanf(dat, "%d", &q->br);

		while (P->next != NULL && P->next->br < q->br)
			P = P->next;

		q->next = P->next;
		P->next = q;
		P = Pocetak;
	}
	fclose(dat);
	return 0;
}

int Unija(Poz L1, Poz L2, Poz Un) {

	Poz q;
	Poz temp=NULL;
	

	while (L1 != NULL && L2 != NULL) {

		q = CreateNew();
		if (q == NULL) return -1;
		
		q->next = Un->next;
		Un->next = q;
		

		if (L1->br == L2->br) {
			q->br = L1->br;
			L1 = L1->next;
			L2 = L2->next;
		}

		else if (L1->br < L2->br) {

			q->br = L1->br;
			L1 = L1->next;
		}

		else if (L1->br > L2->br) {

			q->br = L2->br;
			L2 = L2->next;
		}
		Un = q;
		
	}
	if (L1 == NULL)
		temp = L2;
	if (L2 == NULL)
		temp = L1;


	while (temp != NULL) {

		q = CreateNew();
		if (q == NULL) return -1;
		q->br = temp->br;

		q->next = Un->next;
		Un->next = q;
		Un = q;
		
		temp = temp->next;

	}
	return 0;
}

int Presjek(Poz L1, Poz L2, Poz Pr) {

	Poz q;


	while (L1 != NULL && L2 != NULL) {


		if (L1->br == L2->br) {

			q = CreateNew();
			if (q == NULL) return -1;
			q->br = L1->br;

			q->next = Pr->next;
			Pr->next = q;
			Pr = q;

			L1 = L1->next;
			L2 = L2->next;

		}

		else if (L1->br < L2->br)
			L1 = L1->next;


		else if (L1->br > L2->br)
			L2 = L2->next;
	}
	return 0;
}
