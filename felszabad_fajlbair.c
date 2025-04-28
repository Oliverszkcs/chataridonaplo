#include <stdio.h>
#include <stdlib.h>
#include "debugmalloc.h"
#include <stdbool.h>
#include <string.h>
#include "Fuggvenyek.h"
#include "felszabad_fajlbair.h"
#include "hozzad_torol.h"
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


