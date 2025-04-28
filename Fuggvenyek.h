#ifndef FUGGVENYEK_H_INCLUDED
#define FUGGVENYEK_H_INCLUDED
typedef struct Esemeny{
    char nev[50];
    int ev,honap,nap,ora,perc;
    char hely[50];
    char megjegyzes[50];
}Esemeny;

typedef struct lelem{
    Esemeny esemeny;
    struct lelem *kov;
}lelem;

void kilistaz(lelem *honnan);
lelem* megkeres(lelem *elso,char nev[50]);
lelem* modosit(lelem *elso,char nev[20]);
void fajlbair(lelem *honnan);
void felszabad(lelem *elso);
lelem  *hozzad(lelem *elso,char nev[50],int ev,int honap,int nap,int ora,int perc,char hely[50],char megjegyzes[50]);
void torles(lelem *elso,char nev[50]);


#endif // FUGGVENYEK_H_INCLUDED
