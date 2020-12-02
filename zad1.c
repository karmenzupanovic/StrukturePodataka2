#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100

typedef struct {
	char ime[MAX];
	char prez[MAX];
	int bod;
}Student;


int Izbroji(FILE* dat) {
	int n = 0;

	while (!feof(dat)) {
		if (fgetc(dat) == '\n')			//sporo-NE koristit getc
			n++;
	}

	rewind(dat);		//vraca na pocetak
	return n;
}

void Upis(Student*s, int n, FILE *dat) {		//citamo datoteku
	int i;

	for (i = 0; i < n; i++)
	{
		fscanf(dat, " %s %s  %d \n", s[i].ime, s[i].prez, &s[i].bod);
	}
	fclose(dat);
	return;
}

void Ispis(Student*s, int n, double max) {		//ispisujemo sta smo procitali
	int i;
	double rel = 0;

	printf("ime\t prezime  bodovi\t relativni\n");
	for (i = 0; i < n; i++)
	{
		rel = (double)s[i].bod / max * 100;		//rel broj bodova

		printf("%s\t %s\t  %d\t\t %lf\n", s[i].ime, s[i].prez, s[i].bod, rel);

	}
	return;
}

int main() {

	Student *s;
	int n;
	double max = 0;
	char str[MAX];


	printf("upisi ime datoteke: ");
	scanf(" %s", str);

	FILE *dat = fopen(str, "r");
	if (dat == NULL) printf("Greska pri otvaranju datoteke!");

	n = Izbroji(dat);
	printf("Broj studenata je: %d \n", n);


	s = (Student *)malloc(n * sizeof(Student));


	printf("Max broj bodova je:");
	scanf("%lf", &max);

	Upis(s, n, dat);
	Ispis(s, n, max);


	return 0;
}
