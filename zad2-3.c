#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100

typedef struct osoba * Pozicija;
struct osoba;


struct osoba {
	char ime[MAX];
	char prezime[MAX];
	int god;
	Pozicija next;
};


int UnosP(Pozicija P);
Pozicija Trazi(Pozicija P);
Pozicija TraziPret(Pozicija P);
int Ispis(Pozicija P);
int UnosK(Poz);

Pozicija TraziZadnji(Pozicija P);
int Izbrisi(Pozicija);
int UnesiIspred(Pozicija);
int UnesiIzad(Pozicija);
int BrisiSve(Pozicija);
int Sortiraj(Pozicija);
int CitajDat(Pozicija);
int PisiDat(Pozicija);



int main() {

	struct osoba Head;
	Head.next = NULL;
	struct osoba *k=NULL, *q = NULL;
	int izbor=1, provjera = 0;
		

	while (izbor != 0)
	{
		
		printf("\n 1 - Unesi novi element na pocetak");
		printf("\n 2 - Unesi novi element na kraj");
		printf("\n 3 - Ispisi elemente");
		printf("\n 4 - Izbrisi element");
		printf("\n 5 - Trazi po prezimenu ");
		//printf("\n 6 - Trazi prethodni");  //zanemarit
		printf("\n 7 - Trazi zadnji");
		printf("\n 8 - Unos ispred");
		printf("\n 9 - Unos izad");
		//printf("\n 10 - Brisi sve");
		printf("\n 11 - Sortiraj abecedno");
		printf("\n 12 - Citaj iz datoteke");
		printf("\n 13 - Pisi u datoteku");

		printf("\n 0 - Izlaz");
		printf("\nNapisi svoj izbor: ");
		scanf("%d", &izbor);

		switch (izbor)
		{
		case 1:
			UnosP(&Head);
			break;
		case 2:
			UnosK(&Head);
			break;
		case 3:
			printf("\nPOPIS LJUDI:\n");
			Ispis(Head.next);
			break;
		case 4:
			provjera = Izbrisi(&Head);
			break;
		case 5:
			q = Trazi(Head.next);
			if (q == NULL)
				printf("Trazena osoba ne postoji.");
			else
				printf("\n Trazena osoba je: %s  %s  %d\n", q->ime, q->prezime, q->god);
			break;
		//case 6:
			q = TraziPret(Head.next);
			if (q == NULL)
				printf("Trazena osoba ne postoji.");
			else
				printf("\n Prethodna osoba je: %s  %s  %d\n", q->ime, q->prezime, q->god);
			break;
		case 7:
			q = TraziZadnji(&Head);
			if (q == NULL)
				printf("Lista je prazna ili se ne moze pronaci.");
			else
				printf("\n Zadnja osoba je: %s  %s  %d\n", q->ime, q->prezime, q->god);
			break;
		case 8:
			provjera = UnesiIspred(&Head);
			if (provjera == -1) puts("Nije pronaden element ");
			break;
		case 9:
			provjera = UnesiIzad(&Head);
			if (provjera == -1) puts("Nije pronaden element ");
			break;
		//case 10:
			BrisiSve(&Head);
			break;
		case 11:
			Sortiraj(&Head);
			printf("\n SORTIRAN POPIS LJUDI:\n");
			Ispis(Head.next);
			break;
		case 12:
			provjera = CitajDat(&Head); 
			if (provjera == -1) printf("Problem s otvaranjem datoteke!\n");
			break;
		case 13:
			provjera = PisiDat(Head.next);
			if (provjera == -1) printf("Problem s otvaranjem datoteke!\n");
			break;
		case 0:
			printf("Izlaz iz programa\n");
			break;
		default:
			printf("Greska!");
			break;
		}
	}
	return 0;
}

int UnosP( Pozicija P) {

	Pozicija q;
	q = (Pozicija)malloc(sizeof(struct osoba));		//mogla je bit zasebna funkcija

	if (q == NULL) return NULL;

	printf("Upisi podatke o osobi koju zelite dodat (ime prezime godina): ");
	scanf("%s %s %d", q->ime, q->prezime, &q->god);

	q->next = P->next;
	P->next = q;

	return 0;
}

int Ispis(Pozicija P) {

	if (P == NULL)
		printf("Lista je prazna! \n");
	else {

		while (P != NULL) {
			printf("%s %s %d\n", P->ime, P->prezime, P->god);
			P = P->next;
		}
	}
	return 0;
}

int UnosK(Pozicija P) {

	Pozicija q;
	q = (Pozicija)malloc(sizeof(struct osoba));

	if (q == NULL) return NULL;

	else {
		printf("Upisi podatke o osobi koju zelite dodati(ime prezime godina): ");
		scanf("%s %s %d", q->ime, q->prezime, &q->god);

		while (P->next != NULL)
			P = P->next;

			q->next = P->next;
			P->next = q;
		
	}
	return 0;
}

Pozicija Trazi(Pozicija P) {
	char prez[MAX];

	printf("Koje prezime trazite?");
	scanf(" %s", prez);

	while (P != NULL && (strcmp( P->prezime,prez)) !=0) {
		P = P->next;
	}
	//if (P == NULL)
		//printf("nema tog prezimena.\n");
	
	return P;
}

Pozicija TraziPret(Pozicija P)
{
	char string[20];

	puts("upisi prezime koje trazis :");
	scanf(" %s", string);

	while (P->next != NULL && strcmp(P->next->prezime,string) != 0)
		P = P->next;
	if (P->next == NULL) return NULL;
	return P;
}

int Izbrisi(Pozicija P)
{
	Pozicija prev;

	prev = TraziPret(P);
	if (prev != NULL){
		P = prev->next;
			prev->next = P->next;
			free(P);
	}
	if (prev == NULL) {
		printf("Osoba ne postoji.");
	}
	return 0;
}



Pozicija TraziZadnji(Pozicija P) {

	{
		if (P->next == NULL)
			return NULL;
		while (P->next != NULL)
			P = P->next;

		return P;
	}
}
int BrisiSve(Pozicija P) 
{
	Pozicija temp = NULL;

	while (P->next != NULL)
	{
		temp = P->next;
		P->next = temp->next;
		free(temp);
	}
return 0;
}

int UnesiIspred(Pozicija P)
{
	P = TraziPret(P);
	if (P == NULL) return -1;
	UnosP(P);
	return 0;
}
int UnesiIzad(Pozicija P)
{
	P = Trazi(P);
	if (P == NULL) return -1;
	UnosP(P);

	return 0;
}

int Sortiraj(Pozicija p)
{
	Pozicija prevj = p, j = NULL, end = NULL, temp = NULL;

	while (p->next != end)
	{
		prevj = p;
		j = p->next;
		while (j->next != end)
		{
			if (strcmp(j->prezime, j->next->prezime) > 0)
			{

				temp = j->next;
				prevj->next = temp;
				j->next = temp->next;
				temp->next = j;

				j = temp;
			}
			prevj = j;
			j = j->next;
		}
		end = j;
	}

	return 0;
}

int CitajDat(Pozicija p)
{
	Pozicija temp = NULL;
	FILE * dat = NULL;
	char str[20];

	printf("Upisi ime datoteke: ");
	scanf(" %s", str);
	if (strchr(str, '.') == NULL)
		strcat(str, ".txt");

	dat = fopen(str, "r");

	if (dat == NULL)
		return -1;
	while (!feof(dat))
	{
		temp = (Pozicija)malloc(sizeof(struct osoba));

		if (temp == NULL) return -1;

		fscanf(dat, " %s %s %d", temp->ime, temp->prezime, &temp->god);
		temp->next = p->next;
		p->next = temp;
		p = temp;
	}
	fclose(dat);

	return 0;
}

int PisiDat(Pozicija p)
{
	FILE * dat;
	char str[20];

	printf("Upisi ime datoteke: ");
	scanf(" %s", str);
	if (strchr(str, '.') == NULL)
		strcat(str, ".txt");

	dat = fopen(str, "w");

	if (dat == NULL)
		return -1;
	fprintf(dat, "POPIS LJUDI\n\n");
	while (p != NULL)
	{
		fprintf(dat, "%s\t%s\t%d\n", p->ime, p->prezime, p->god);
		p = p->next;
	}

	fclose(dat);
	return 0;
}

