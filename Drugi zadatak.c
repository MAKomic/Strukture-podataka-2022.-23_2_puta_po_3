#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STRING_LENGTH 1024
#define NEMA_ELEMENTA_U_LISTI -1
#define USPJESNO_BRISANJE 1
#define USPJESAN_ISPIS 1
#define USPJESAN_UNOS 1




typedef struct osoba {
	char ime[MAX_STRING_LENGTH];
	char prezime[MAX_STRING_LENGTH];
	int godrod;

}osoba;

typedef struct cvor* poz;

typedef struct cvor {
	osoba el;
	poz next;
}cvor;

int unosP(osoba, poz);
int ispis(poz);
int unosK(osoba, poz);
poz trazi(char[], poz);
int brisi(char[], poz);
poz traziP(char[], poz);
osoba unosOsobe();




int main()
{
	cvor head;
	head.next = NULL;
	char tren[MAX_STRING_LENGTH] = { 0 };

	unosP(unosOsobe(), &head);
	unosK(unosOsobe(), &head);
	unosP(unosOsobe(), &head);
	unosP(unosOsobe(), &head);
	unosK(unosOsobe(), &head);
	ispis(head.next);

	printf("\nUnesi prezime koje zelis pronac: ");
	scanf(" %s", tren);
	printf("Adresa elementa sa prezimenom %s je %p\n",tren,trazi(tren, head.next));

	printf("Unesi prezime koje zelis izbrisat: ");
	scanf(" %s", tren);
	brisi(tren, &head);
	printf("\n");
	ispis(head.next);


	return 0;
}

int unosP(osoba x, poz p)
{
	poz q;

	q = (poz)malloc(sizeof(cvor));

	q->el = x;
	q->next = p->next;
	p->next = q;

	return USPJESAN_UNOS;
}

int ispis(poz p)
{
	while (p != NULL)
	{
		printf("%s %s %d\n", p->el.ime, p->el.prezime, p->el.godrod);
		p = p->next;
	}
	return USPJESAN_ISPIS;
}

int unosK(osoba x, poz p)
{
	poz q;
	q = (poz)malloc(sizeof(cvor));

	while (p->next != NULL)
	{
		p = p->next;
	}

	q->el = x;
	p->next = q;
	q->next = NULL;

	return USPJESAN_UNOS;
}

poz trazi(char prez[], poz p)
{
	while (p != NULL && (strcmp(p->el.prezime,prez))!=0)
	{
		p = p->next;
	}

	return p;
}

int brisi(char prez[], poz p)
{
	poz prev, temp;
	prev = traziP(prez, p);

	if (prev == NULL)
	{
		printf("Nema ga!");
		return NEMA_ELEMENTA_U_LISTI;
	}

	else
	{
		temp = prev->next;
		prev->next = temp->next;

		return USPJESNO_BRISANJE;
		free(temp);
	}
}

poz traziP(char prez[], poz p)
{
	poz pret;
	pret = p;
	p = p->next;

	while (p != NULL && (strcmp(p->el.prezime,prez))!=0)
	{
		pret = pret->next;
		p = p->next;
	}

	if (p == NULL)
	{
		return NULL;
	}

	else
	{
		return pret;
	}
}

osoba unosOsobe()
{
	osoba o;

	printf("Unesi ime osobe: ");
	scanf("%s", o.ime);

	printf("Unesi prezime osobe: ");
	scanf("%s", o.prezime);

	printf("Unesi godinu rodenja osobe: ");
	scanf("%d", &(o.godrod));

	return o;
}
