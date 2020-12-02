#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct polinom;
typedef struct polinom * Polinom;
struct polinom {
	int koef;
	int pot;
	Polinom next;
};

Polinom Novi();
int Unos(Polinom);
int Ispis(Polinom);
int Zbroji(Polinom, Polinom, Polinom);
int Pomnozi(Polinom, Polinom, Polinom);

int main()
{
	int pr;
	struct polinom p1, p2, suma, produkt;
	p1.next = p2.next = suma.next = produkt.next = NULL;

	pr = Unos(&p1);
	if (pr == -1) printf("Greska! \n");
	pr = Unos(&p2);
	if (pr == -1) printf("Greska! \n");

	printf("\nPrvi polinom: \n ");
	Ispis(p1.next);
	printf("\nDrugi polinom: \n ");
	Ispis(p2.next);

	pr = Zbroji(p1.next, p2.next, &suma);
	if (pr == -1) printf("Greska! \n");

	printf("\n Suma: \n ");
	Ispis(suma.next);

	pr = Pomnozi(p1.next, p2.next, &produkt);
	if (pr == -1) printf("Greska! \n");

	printf("\n Produkt: \n ");
	Ispis(produkt.next);



	return 0;
}

Polinom Novi()
{
	Polinom q = NULL;
	q = (Polinom)malloc(sizeof(struct polinom));
	if (q == NULL) return q;
	q->next = NULL;

	return q;
}

int Unos(Polinom P)
{
	char str[20];
	FILE * dat = NULL;
	Polinom q = NULL, prev = NULL, temp = NULL;

	printf("Upisi ime datoteke: ");
	scanf(" %s", str);

	dat = fopen(str, "r");
	if (dat == NULL) return -1;

	while (!feof(dat))
	{
		q = Novi();
		if (q == NULL) return -1;
		fscanf(dat, "%d %d", &q->koef, &q->pot);

		prev = P;
		temp = P->next;

		while (temp != NULL && temp->pot > q->pot)
		{
			prev = temp;
			temp = temp->next;
		}
		q->next = temp;
		prev->next = q;
	}
	fclose(dat);
	return 0;
}

int Ispis(Polinom P)
{
	while (P != NULL)
	{
		printf("%d*x^%d  ", P->koef, P->pot);
		P = P->next;
	}
	return 0;
}

int Zbroji(Polinom P1, Polinom P2, Polinom S)
{
	Polinom q, temp;
	q = temp = NULL;

	while (P1 != NULL && P2 != NULL)
	{
		q = Novi();
		if (q == NULL) return -1;

		if (P1->pot > P2->pot)
		{
			q->koef = P1->koef;
			q->pot = P1->pot;

			P1 = P1->next;
		}
		else if (P1->pot < P2->pot)
		{
			q->koef = P2->koef;
			q->pot = P2->pot;

			P2 = P2->next;
		}
		else		//jednake pot
		{
			q->koef = P1->koef + P2->koef;
			q->pot = P1->pot;

			P1 = P1->next;
			P2 = P2->next;
		}
		q->next = S->next;
		S->next = q;
		S = q;
	}

	if (P1 != NULL)
		temp = P1;
	else
		temp = P2;

	while (temp != NULL)
	{
		q = Novi();
		if (q == NULL) return -1;

		q->koef = temp->koef;
		q->pot = temp->pot;

		S->next = q;
		S = q;

		temp = temp->next;
	}
	return 0;
}

int Pomnozi(Polinom P1, Polinom P2, Polinom P)
{
	Polinom q = NULL, Pocetak1 = P1, Pocetak2 = P2, temp = P->next, prev = P;
	int ZbrPot;

	while (P1 != NULL)
	{
		P2 = Pocetak2;

		while (P2 != NULL)
		{
			prev = P;
			temp = P->next;

			ZbrPot = P1->pot + P2->pot;

			while (temp != NULL && temp->pot > ZbrPot)
			{
				temp = temp->next;
				prev = prev->next;
			}

			if (temp != NULL && temp->pot == ZbrPot)
			{
				temp->koef += (P1->koef * P2->koef);
			}
			else
			{
				q = Novi();
				if (q == NULL) return -1;

				q->koef = P1->koef * P2->koef;
				q->pot = ZbrPot;

				prev->next = q;
				q->next = temp;
			}
			P2 = P2->next;
		}
		P1 = P1->next;
	}
	return 0;
}
