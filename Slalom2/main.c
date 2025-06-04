#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEL " :."
#define INPUT "zavodnici.txt"
#define OUTPUT "vyslednaListina.txt"

typedef struct
{
    int min1;
    int sec1;
    int mili1;
    int min2;
    int sec2;
    int mili2;
} CAS;

typedef struct
{
    int startCislo;
    char prijmeni[50];
    char jmeno[50];
    CAS cas;
} DATA;

DATA cteniSloupcu(char *radek)
{
    int i = 0;
    DATA data;
    char *sloupec = strtok(radek, DEL);

    while (sloupec != NULL)
    {
        switch (i)
        {
        case 0:
            data.startCislo = atoi(sloupec);
            break;
        case 1:
            strcpy(data.prijmeni, sloupec);
            break;
        case 2:
            strcpy(data.jmeno, sloupec);
            break;
        case 3:
            data.cas.min1 = atoi(sloupec);
            break;
        case 4:
            data.cas.sec1 = atoi(sloupec);
            break;
        case 5:
            data.cas.mili1 = atoi(sloupec);
            break;
        case 6:
            data.cas.min2 = atoi(sloupec);
            break;
        case 7:
            data.cas.sec2 = atoi(sloupec);
            break;
        case 8:
            data.cas.mili2 = atoi(sloupec);
            break;
        }
        sloupec = strtok(NULL, DEL);
        i++;
    }
    return data;
}

DATA* cteniRadku(FILE *f, int *pocet)
{
    int i = 0;
    DATA* data = NULL;
    char radek[100];
    fgets(radek, 100, f);
    while (fgets(radek, 100, f) != NULL)
    {
        i++;
        DATA *dataSet = (DATA *)realloc(data, i * sizeof(DATA));

        if (dataSet != NULL)
        {
            data = dataSet;
            data[i - 1] = cteniSloupcu(radek);
        }
        else
        {
            free(data);
            perror("Nastal problem pri pridelovani pameti");
            exit(1);
        }
    }
    *pocet = i;
    return data;
}

DATA* cteniSouboru(int *pocet)
{
    FILE *f;

    f = fopen(INPUT, "r");
    if (f == NULL)
    {
        perror("Nastal problem pri otevirani souboru");
    }

   DATA *data = cteniRadku(f, pocet);


    if (fclose(f) == EOF)
    {
        perror("Nastal problem pri zavirani souboru");
    }

    return data;
}

int min()
{
    int pocet ;
    DATA* data = cteniSouboru(&pocet);

        printf("%10d %10s %10s %2d:%2d.%2d %2d:%2d.%2d\n", data[0].startCislo, data[0].prijmeni, data[0].jmeno,
               data[0].cas.min1, data[0].cas.sec1, data[0].cas.mili1, data[0].cas.min2, data[0].cas.sec2,
               data[0].cas.mili2);


    return 0;
}
