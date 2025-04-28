#include <stdio.h>
#include <stdlib.h>
#include "debugmalloc.h"
#include <stdbool.h>
#include <string.h>
#include "Fuggvenyek.h"
#include "felszabad_fajlbair.h"
#include "hozzad_torol.h"



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
        elotte->kov=kereso->kov;    //kihagyja az elemet(torles) valahonnan (nem előröl)
    }
}
