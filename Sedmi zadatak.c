#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LINE_SIZE 1024

#define USPJESAN_UNOS 1
#define USPJESAN_ISPIS 1
#define USPJESNO_BRISANJE 1

#define NEUSPJESNA_ALOKCIJA -1

typedef struct cvor* poz;
typedef struct stog* poz_;

typedef struct cvor {
	char ime[MAX_LINE_SIZE];
	char sadrzaj[MAX_LINE_SIZE];
	poz sibling;
	poz child;

}cvor;

typedef struct stog {
	poz el;
	poz_ next;
}stog;


int ispisIzbornika();

int md(poz, poz);
poz cd_dir(poz);
poz cd__(poz_);
int dir(poz);
poz brisiSve(poz);

poz find(poz, char[MAX_LINE_SIZE], poz*);

int ispisTrenutnog(poz);

int push(poz, poz_);
poz pop(poz_);
int brisiStog(poz_);


int main()
{
	cvor root;
	char naredba = '1';

	stog head;
	head.next = NULL;

	root.sibling = NULL;
	root.child = NULL;

	poz current = &root;
	poz kontrola = NULL;
	
	int level = 0;

	strcpy(root.ime, "ROOT");
	strcpy(root.sadrzaj, "ROOT");

	printf("Pocetni direktorij ima ime \"ROOT\" i sadrzaj \"ROOT\"");

	while (naredba != '0')
	{
		ispisIzbornika();

		printf("\nUnesi slovo: ");
		scanf(" %c", &naredba);

		switch (naredba)
		{

		case 'a':
			md(current->child, current);
			break;

		case 'b':
			kontrola = cd_dir(&root);

			if (kontrola != NULL)
			{
				push(current, &head);
				current = kontrola;
				ispisTrenutnog(current);
			}
			break;

		case 'c':
			kontrola = cd__(&head);

			if (kontrola != NULL)
			{
				current = kontrola;
				ispisTrenutnog(current);
			}
			break;

		case 'd':
			printf("\n<%s>\t%s\n", current->ime, current->sadrzaj);
			dir(current->child, level + 1);
			break;

		case '0':
			brisiStog(&head);
			brisiSve(&root);

		default:
			printf("\nKrivi unos!\n");
		}

	}

	return 0;
}


int ispisIzbornika()
{
	printf("\n<> <> <> <> <> IZBORNIK <> <> <> <> <>\n\na)md\nb)cd dir\nc)cd ..\nd)dir\n\n0)Kraj programa\n\n<> <> <> <> <> <> <> <> <> <> <> <> <> ");
	return USPJESAN_ISPIS;
}


int md(poz current_child, poz current)
{
	poz q = NULL;

	q = (poz)(malloc(sizeof(cvor)));
	if (q == NULL)
	{
		printf("Neuspjesno alocirna memorija.");
		return NEUSPJESNA_ALOKCIJA;
	}
	q->child = NULL;

	char tempIme[MAX_LINE_SIZE] = { 0 };
	char tempSadrzaj[MAX_LINE_SIZE] = { 0 };

	printf("Unesi naziv novog direktorija: ");
	scanf(" %[^\n]%*c", tempIme);
	strcpy(q->ime, tempIme);

	printf("Unesi sadrzaj novog direktorija: ");
	scanf(" %[^\n]%*c", tempSadrzaj);
	strcpy(q->sadrzaj, tempSadrzaj);

	if (current->child == NULL)
	{
		current->child = q;
		q->sibling = NULL;
		printf("\nUspjesan unos!\n");
		return USPJESAN_UNOS;
	}

	if (strcmp(tempIme, current->child->ime) <= 0)
	{
		q->sibling = current->child;
		current->child = q;
		printf("\nUspjesan unos!\n");
		return USPJESAN_UNOS;
	}

	while (current_child->sibling != NULL && strcmp(tempIme, current_child->sibling->ime) > 0)
	{
		current_child = current_child->sibling;
	}


	q->sibling = current_child->sibling;
	current_child->sibling = q;
	printf("\nUspjesan unos!\n");

	return USPJESAN_UNOS;
}

poz cd_dir(poz adresa_root)
{
	char tempIme[MAX_LINE_SIZE] = { 0 };
	poz* pom = (poz*)malloc(sizeof(poz));
	if (pom == NULL)
	{
		printf("Nesupjesna alokacija.");
		return NULL;
	}
	*pom = NULL;

	poz tempRoot = adresa_root;

	printf("Unesi ime direktorija u koji zelis otic: ");
	scanf(" %[^\n]%*c", tempIme);

	find(tempRoot, tempIme, pom);

	if (*pom == NULL)
	{
		printf("\nNe postoji direktorij toga imena!\n");
		return NULL;
	}

	else
	{
		printf("\nUspjesno promijenjen direktorij.\n");
	}

	return *pom;
}

poz cd__(poz_ head)
{
	if (head->next != NULL)
	{
		printf("\nUspjesno promijenjen direktorij.\n");
		return pop(head);
	}

	else
	{
		printf("\nNema se di vratit!\n");
		return NULL;
	}

}

int dir(poz current, int level)
{
	if (current == NULL)
	{
		return USPJESAN_ISPIS;
	}
	
	int i = 0;

	printf("\n");

	for (i = 0; i < level; i++) printf("\t");

	printf("<%s>\t%s\n", current->ime, current->sadrzaj);

	dir(current->child, level + 1);
	printf("\n");
	dir(current->sibling, level);

	return USPJESAN_ISPIS;

}

poz brisiSve(poz root)
{
	if (root == NULL)
	{
		return NULL;
	}

	brisiSve(root->sibling);
	brisiSve(root->child);

	free(root);

	return NULL;
}


poz find(poz tempRoot, char tempIme[MAX_LINE_SIZE], poz* pom)
{

	if (tempRoot == NULL)
	{
		return NULL;
	}

	if (strcmp(tempRoot->ime, tempIme) == 0)
	{
		*pom = tempRoot;
		return NULL;
	}


	find(tempRoot->sibling, tempIme, pom);
	find(tempRoot->child, tempIme, pom);


	return NULL;
}


int ispisTrenutnog(poz current)
{
	printf("\nTrenutni direktorij je %s.", current->ime);
	printf("\nSadrzaj trenutnog direktroija je %s.", current->sadrzaj);

	return USPJESAN_ISPIS;
}


int push(poz x, poz_ head)
{
	poz_ q = NULL;
	q = (poz_)malloc(sizeof(stog));

	if (q == NULL)
	{
		printf("Neuspjesno alocirana memorija.");
		return NEUSPJESNA_ALOKCIJA;
	}

	q->el = x;
	q->next = head->next;
	head->next = q;

	return USPJESAN_UNOS;
}

poz pop(poz_ head)
{
	poz_ temp = NULL;
	poz pom = NULL;

	pom = head->next->el;

	temp = head->next;
	head->next = temp->next;
	free(temp);

	return pom;

}

int brisiStog(poz_ head)
{
	poz temp = NULL;

	while (head->next != NULL)
	{
		temp = pop(head);
	}

	free(temp);

	return USPJESNO_BRISANJE;
}
