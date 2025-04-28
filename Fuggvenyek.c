#include <stdio.h>
#include <stdlib.h>
#include "debugmalloc.h"
#include <stdbool.h>
#include <string.h>
#include "Fuggvenyek.h"
#include <conio.h>

void kilistaz(lelem *honnan){
    lelem* x=honnan;
    printf("\nAz Esemenyeid:\n");
    while(x!=NULL){             //Elejetol kezdve listaz (sorrendben mivel már rendezve vannak mikor hozzáadjuk őket)
        printf("%s %d.%02d.%02d %02d:%02d %s %s\n",x->esemeny.nev,x->esemeny.ev,x->esemeny.honap,x->esemeny.nap,x->esemeny.ora,x->esemeny.perc,x->esemeny.hely,x->esemeny.megjegyzes);
        x=x->kov;
    }
}

lelem* megkeres(lelem *elso,char nev[50]){
    lelem *x=elso;                          //Végignézi az esemenyéket és összehasonlítja a nevüket
    char talalat;
   for(x;x!=NULL;x=x->kov){
    if((strcmp(x->esemeny.nev,nev))==0){
        return x;
    }
   }

}
lelem* modosit(lelem *elso,char nev[20]){
    char modositott_nev[50];
    int modositott_ev,modositott_honap,modositott_nap,modositott_ora,modositott_perc;
    char modositott_hely[50];
    char modositott_megjegyzes[50];
    lelem *x=megkeres(elso,nev);
    if(x!=NULL){

        printf("Modositasok\n");
        scanf("%s %d.%d.%d %d:%d %s %[^\n]",modositott_nev,&modositott_ev,&modositott_honap,&modositott_nap,&modositott_ora,&modositott_perc,modositott_hely,modositott_megjegyzes);
         if(modositott_ev>9999||modositott_honap>12||modositott_nap>31||modositott_ora>24||modositott_perc>60){
                                printf("Ervenytelen megadas\n");
                                return NULL;
         }
        torles(elso,nev);                           //Kitorli a regit és utána hozzáad egy új modosított eseményt
        strcmp(x->esemeny.nev,modositott_nev);
        x->esemeny.ev=modositott_ev;
        x->esemeny.honap=modositott_honap;
        x->esemeny.nap=modositott_nap;
        x->esemeny.ora=modositott_ora;
        x->esemeny.perc=modositott_perc;
        strcmp(x->esemeny.hely,modositott_hely);
        strcmp(x->esemeny.megjegyzes,modositott_megjegyzes);
        hozzad(elso,modositott_nev,modositott_ev,modositott_honap,modositott_nap,modositott_ora,modositott_perc,modositott_hely,modositott_megjegyzes);
        printf("Sikeres modositas\n");
        return x;
    }
     else{
        return NULL;                //Ha nem sikerült akkor Null-t
     }
}
lelem* hozzad(lelem *elso,char nev[50],int ev,int honap,int nap,int ora,int perc,char hely[50],char megjegyzes[50]){
lelem *uj=(lelem*)malloc(sizeof(lelem));
    strcpy(uj->esemeny.nev,nev);
    uj->esemeny.ev=ev;
    uj->esemeny.honap=honap;                        //atirja az adatokat az ujba
    uj->esemeny.ora=ora;
    uj->esemeny.perc=perc;
    strcpy(uj->esemeny.hely,hely);
    strcpy(uj->esemeny.megjegyzes,megjegyzes);
    uj->esemeny.nap=nap;
    lelem *elotte=NULL;
    lelem *kereso=elso;
     //                  evek                    honapok                                                                       napok                                                                                                                     ORAK                                                                                                                                                                PERCEK
    while(kereso!=NULL && ((uj->esemeny.ev >kereso->esemeny.ev)||((uj->esemeny.ev==kereso->esemeny.ev)&&(uj->esemeny.honap>kereso->esemeny.honap))||((uj->esemeny.ev==kereso->esemeny.ev)&&(uj->esemeny.honap==kereso->esemeny.honap)&&(uj->esemeny.nap>kereso->esemeny.nap))||((uj->esemeny.ev==kereso->esemeny.ev)&&(uj->esemeny.honap==kereso->esemeny.honap)&&(uj->esemeny.nap==kereso->esemeny.nap)&&(uj->esemeny.ora>kereso->esemeny.ora))||((uj->esemeny.ev==kereso->esemeny.ev)&&(uj->esemeny.honap==kereso->esemeny.honap)&&(uj->esemeny.nap==kereso->esemeny.nap)&&(uj->esemeny.ora==kereso->esemeny.ora)&&(uj->esemeny.perc>kereso->esemeny.perc)))){
        elotte=kereso;
        kereso=kereso->kov;  //megnezi hogy korabbi vagy kesobbi esemeny e, aztan tarolja el(azaz a helyét keresi meg).
                            //Így a legkorabbi esemeny lesz legelöl
    }
    if(elotte==NULL){
            uj->kov=elso;   //elso helyre kell rakni
            elso=uj;
    }
    else {
        elotte->kov=uj; //valahova listaba kell helyezni
        uj->kov=kereso;
    }
    return uj;
}

void torles(lelem *elso,char nev[50]){
  lelem *kereso=elso;
  lelem *elotte=NULL;
  while((kereso!=NULL)&&(strcmp(kereso->esemeny.nev,nev)!=0)){
    elotte=kereso;
    kereso=kereso->kov;     //Nem hasznalhato a megkeres fuggveny, mivel visszafele nem tudunk lépni és így nem tudjuk megadni az elõtte lévo elemet csak az utána levõt
  }
    if(kereso==NULL){                    //végére ért és nincs ilyen elem
    }
    else if(elotte==NULL){  // az elso elemeta kéne törölni
        lelem *elso_uj=kereso->kov;
        free(kereso);
        elso=elso_uj;

    }else{
        elotte->kov=kereso->kov;
        free(kereso);
           //kihagyja az elemet(torles) valahonnan (nem előröl)
    }
}w
void fajlbair(lelem *honnan){
  FILE *mentes=fopen("mentes.txt","w");
    lelem* x=honnan;                        //Beirja a faljba a programban letezo esemenyeket(Amik mar rendezve vannak)
    while(x!=NULL){
        fprintf(mentes,"%s %d.%d.%d %d:%d %s %s\n",x->esemeny.nev,x->esemeny.ev,x->esemeny.honap,x->esemeny.nap,x->esemeny.ora,x->esemeny.perc,x->esemeny.hely,x->esemeny.megjegyzes);
        x=x->kov;
    }
   fclose(mentes);
}

void felszabad(lelem *elso){
    lelem* x=elso;          //Végigfut és mindent felszabadít
    while(x!=NULL){
        lelem *kovi=x->kov; //mert aztan x elobb lesz felszabadítva
        free(x);
        x=kovi;
    }
}


