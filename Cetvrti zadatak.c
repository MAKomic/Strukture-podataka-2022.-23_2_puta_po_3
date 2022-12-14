#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_LINE_SIZE 1024

#define NOVI_CLAN {0,0}

#define DATOTEKA_SE_NIJE_OTVORILA -1
#define MEMORIJA_NEUSPJESNO_ALOCIRANA -1

#define USPJESAN_UNOS 1
#define USPJESAN_ISPIS 1
#define USPJESNO_BRISANJE 1

typedef struct clan {
    int k;
    int exp;
}clan;

typedef struct cvor* poz;

typedef struct cvor {
    clan el;
    poz next;
}cvor;

int pribrojiPolinome(char[]);
int ucitajPolinome(char[], poz*, int);

int ispisiPolinome(poz);

int sortiraniUnos(clan, poz);

int zbrojiPolinome(poz*, poz, int);
int mnoziPolinome(poz, poz);

int izbrisiBO(poz*, poz, int);


int main()
{
    char ime_datoteke[MAX_LINE_SIZE]= { 0 };
    poz* listaAdresaHeadova=NULL;
    poz listaHeadova=NULL;
    int brojPolinoma = 0, i = 0;
    cvor zbrojPolinoma, umnozakPolinoma;
    zbrojPolinoma.next = umnozakPolinoma.next = NULL;

    printf("Unesi ime datoteke: ");
    scanf(" %s", ime_datoteke);

    brojPolinoma=pribrojiPolinome(ime_datoteke);

    while (brojPolinoma == DATOTEKA_SE_NIJE_OTVORILA)
    {
        printf("\nPonovni unos: ");
        scanf(" %s", ime_datoteke);
        brojPolinoma = pribrojiPolinome(ime_datoteke);
    }

    printf("\nBroj polinoma je %d\n", brojPolinoma);

    listaHeadova = (poz)malloc(sizeof(cvor) * brojPolinoma);
    if (listaHeadova == NULL)
    {
        printf("Nesupjesno alocirana memorija.");
        return MEMORIJA_NEUSPJESNO_ALOCIRANA;
    }

    listaAdresaHeadova = (poz*)malloc(sizeof(poz) * brojPolinoma);
    if(listaAdresaHeadova == NULL)
    {
        printf("Nesupjesno alocirana memorija.");
        return MEMORIJA_NEUSPJESNO_ALOCIRANA;
    }

    for (i = 0; i < brojPolinoma; i++)
    {
        listaAdresaHeadova[i] = listaHeadova + i;
        listaAdresaHeadova[i]->next = NULL;
    }

    ucitajPolinome(ime_datoteke, listaAdresaHeadova, brojPolinoma);

    for (i = 0; i < brojPolinoma; i++)
    {
        printf("\nPolinom broj %d:\n", i + 1);
        ispisiPolinome(listaAdresaHeadova[i]);
    }

    zbrojiPolinome(listaAdresaHeadova, &zbrojPolinoma, brojPolinoma);


    printf("\nZbroj polinoma je:\n");
    ispisiPolinome(&zbrojPolinoma);

    ucitajPolinome(ime_datoteke, listaAdresaHeadova, brojPolinoma);

    for (i = 1; i < brojPolinoma ; i++)
    {
        mnoziPolinome(listaAdresaHeadova[0], listaAdresaHeadova[i]->next);
    }

    printf("\nUmnozak polinoma:\n");
    ispisiPolinome(listaAdresaHeadova[0]);

    izbrisiBO(listaAdresaHeadova, &zbrojPolinoma, brojPolinoma);
    
    return 0;
}


int pribrojiPolinome(char ime_datoteke[])
{
    FILE* fp = NULL;
    clan x = NOVI_CLAN;
    int n = 0, brojPolinoma = 0;
    char buffer[MAX_LINE_SIZE] = { 0 };

    fp = fopen(ime_datoteke, "r");
    if (fp == NULL)
    {
        printf("Datoteka se nije otvorila.");
        return DATOTEKA_SE_NIJE_OTVORILA;
    }

    while (!feof(fp))
    {
        fgets(buffer, MAX_LINE_SIZE, fp);
        if (buffer[0] != '\n')
        {
            brojPolinoma++;
        }
    }

    fclose(fp);
    return brojPolinoma;
}

int ucitajPolinome(char ime_datoteke[], poz* listaAdresaHeadova, int brojPolinoma)
{
    FILE* fp = NULL;
    clan x = NOVI_CLAN;
    int n = 0, i = 0;
    fp = fopen(ime_datoteke, "r");
    if (fp == NULL)
    {
        printf("Datoteka se nije otvorila.");
        return DATOTEKA_SE_NIJE_OTVORILA;
    }

    char buffer[MAX_LINE_SIZE] = { 0 };
    char* p = buffer;

    while(!(feof(fp)))
    {
        fgets(buffer, MAX_LINE_SIZE, fp);
        {
            if (buffer[0] != '\n')
            {
                while (strlen(p) > 0)
                {
                    sscanf(p, "%d %d %n", &(x.k), &(x.exp), &n);
                    sortiraniUnos(x, listaAdresaHeadova[i]);
                    p += n;
                }
                p = buffer;
                n = 0;
                i++;
            }

        }

    }
    
    fclose(fp);
    return USPJESAN_UNOS;
}

int ispisiPolinome(poz poz_head)
{
    int i = 0;
    while (poz_head->next != NULL)
    {
        if (!i)
        {
            printf("%dx^%d", poz_head->next->el.k, poz_head->next->el.exp);
            poz_head = poz_head->next;
        }
        else
        {
            printf(" + %dx^%d", poz_head->next->el.k, poz_head->next->el.exp);
            poz_head = poz_head->next;
        }
        i = 1;
    }
    printf("\n");
    return USPJESAN_ISPIS;
}

int sortiraniUnos(clan x, poz poz_head)
{
    poz q = NULL;
    poz temp = NULL;
    q = (poz)malloc(sizeof(cvor));

    if (q == NULL)
    {
        printf("Neuspjesno alocirana memorija.");
        return MEMORIJA_NEUSPJESNO_ALOCIRANA;
    }

    while (poz_head->next != NULL && poz_head->next->el.exp < x.exp)
    {
        poz_head = poz_head->next;
    }
    
    if (x.k == 0)
    {
        return USPJESAN_UNOS;
    }

    else if (poz_head->next != NULL && poz_head->next->el.exp == x.exp)
    {
        poz_head->next->el.k += x.k;
        if (poz_head->next->el.k == 0)
        {
            temp = poz_head->next;
            poz_head->next = temp->next;
            free(temp);
        }
        return USPJESAN_UNOS;
    }

    else
    {
        q->el = x;
        q->next = poz_head->next;
        poz_head->next = q;
        return USPJESAN_UNOS;
    }

}

int zbrojiPolinome(poz* listaAdresaHeadova, poz zbroj_polinoma,int brojPolinoma)
{
    int i = 0;
    for (i = 0; i < brojPolinoma; i++)
    {
        while (listaAdresaHeadova[i]->next != NULL)
        {
            sortiraniUnos(listaAdresaHeadova[i]->next->el, zbroj_polinoma);
            listaAdresaHeadova[i]->next = listaAdresaHeadova[i]->next->next;
        }
    }

    return USPJESAN_ISPIS;
}

/*int zbrojiPolinome(poz poz_head1, poz poz_head2, poz poz_head3)
{
    clan x = NOVI_CLAN;
    while (poz_head1 != NULL && poz_head2 != NULL)
    {
        if (poz_head1->el.exp < poz_head2->el.exp)
        {
            unosNaKraj(poz_head1->el, poz_head3);
            poz_head1 = poz_head1->next;
        }
        else if (poz_head2->el.exp < poz_head1->el.exp)
        {
            unosNaKraj(poz_head2->el, poz_head3);
            poz_head2 = poz_head2->next;
        }
        else
        {
            x.exp = poz_head1->el.exp;
            x.k = poz_head1->el.k + poz_head2->el.k;
            unosNaKraj(x, poz_head3);
            poz_head1 = poz_head1->next;
            poz_head2 = poz_head2->next;
        }
    }

    while (poz_head1 != NULL)
    {
        unosNaKraj(poz_head1->el, poz_head3);
        poz_head1 = poz_head1->next;
    }

    while (poz_head2 != NULL)
    {
        unosNaKraj(poz_head2->el, poz_head3);
        poz_head2 = poz_head2->next;
    }

    return USPJESAN_ISPIS;
}*/

int mnoziPolinome(poz poz_head1, poz poz_head2)
{
    clan x = NOVI_CLAN;
    poz stacionarna_poz = poz_head2;
    cvor trenutniUmnozak;
    trenutniUmnozak.next = NULL;

    while (poz_head1->next != NULL)
    {
        while (poz_head2 != NULL)
        {
            x.k = poz_head1->next->el.k * poz_head2->el.k;
            x.exp = poz_head1->next->el.exp + poz_head2->el.exp;
            sortiraniUnos(x, &trenutniUmnozak);
            poz_head2 = poz_head2->next;
        }
        poz_head1->next = poz_head1->next->next;
        poz_head2 = stacionarna_poz;
    }

    while (trenutniUmnozak.next != NULL)
    {
        sortiraniUnos(trenutniUmnozak.next->el, poz_head1);
        trenutniUmnozak.next = trenutniUmnozak.next->next;
    }

    return USPJESAN_ISPIS;
}

int izbrisiBO(poz* listaAdresaHeadova, poz zbrojPolinoma, int brojPolinoma)
{
    int i = 0;
    poz temp = NULL;

    for (i = 0; i < brojPolinoma; i++)
    {
        while (listaAdresaHeadova[i]->next != NULL)
        {
            temp = listaAdresaHeadova[i]->next;
            listaAdresaHeadova[i]->next = temp->next;
            free(temp);
        }
    }

    while (zbrojPolinoma->next != NULL)
    {
        temp = zbrojPolinoma->next;
        zbrojPolinoma->next = temp->next;
        free(temp);
    }

    return USPJESNO_BRISANJE;
}
