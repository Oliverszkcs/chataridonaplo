#include <stdio.h>
#include <stdlib.h>
#include "debugmalloc.h"
#include <stdbool.h>
#include <string.h>
#include "Fuggvenyek.h"

int main()
{  lelem *elso=NULL;
    char c=196;
   int valasztas=0;
   char sor[150];
    FILE *mentes=fopen("mentes.txt","r");
    lelem *scannelt;                                                               //fajlbololvas
    char scannelt_nev[50],scannelt_hely[50],scannelt_megjegyzes[50];
    int scannelt_ev,scannelt_honap,scennelt_ora,scannelt_perc,scannelt_nap;        //Bescannel 1 sor és utana szedi szét adatokra
    while(fgets(sor,sizeof(sor),mentes)!=0){

        sscanf(sor,"%s %d.%d.%d %d:%d %s %[^\n]",scannelt_nev,&scannelt_ev,&scannelt_honap,&scannelt_nap,&scennelt_ora,&scannelt_perc,scannelt_hely,scannelt_megjegyzes);
        if(elso==NULL)
            elso=hozzad(elso,scannelt_nev,scannelt_ev,scannelt_honap,scannelt_nap,scennelt_ora,scannelt_perc,scannelt_hely,scannelt_megjegyzes);
        else
            hozzad(elso,scannelt_nev,scannelt_ev,scannelt_honap,scannelt_nap,scennelt_ora,scannelt_perc,scannelt_hely,scannelt_megjegyzes);
    }
    while(1){

            printf("\n");           //MENU (while azert (1) Mivel ameddig nem lep ki a return 0 koddal addig fusson.
            printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c);
            printf("Kerlek valassz a lehetosegek kozul:\n 1: Letrehozas\n 2: Szerkesztes\n 3: Torles\n 4: Kilistazas\n 5: Kereses\n 6: Kilepes\n");
            printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c,c);

            scanf("%d",&valasztas);
            switch(valasztas){

                case 1:{
                    // HOZZAADAS
                        int uj_ev,uj_honap,uj_nap,uj_ora,uj_perc;
                        char uj_nev[50],uj_hely[50],uj_megjegyzes[50];
                        printf("Adj meg egy esemenyt.\nForma: Nev ev.honap.nap ora:perc hely megjegyzes\n");
                        scanf("%s %d.%d.%d %d:%d %s %[^\n]",uj_nev,&uj_ev,&uj_honap,&uj_nap,&uj_ora,&uj_perc,uj_hely,uj_megjegyzes);
                        if(uj_ev>9999||uj_honap>12||uj_nap>31||uj_ora>24||uj_perc>60){          //Maximum ertekek meghatarozasa
                                printf("Ervenytelen megadas\n");
                                break;
                        }else{
                        if(elso=NULL){              //Ha ez az első elem
                            elso=hozzad(elso,uj_nev,uj_ev,uj_honap,uj_nap,uj_ora,uj_perc,uj_hely,uj_megjegyzes);
                            break;
                        }
                        else{                       //Ha nem az első
                            hozzad(elso,uj_nev,uj_ev,uj_honap,uj_nap,uj_ora,uj_perc,uj_hely,uj_megjegyzes);
                         break;
                        }
                    }
                }
                case 2:{  //SZERKESZTES
                    FILE *mentes=fopen("mentes.txt","r");
                            if(mentes==NULL){
                                printf("Meg nincsenek letezo esemenyek.\n");
                                break;                      //Ha a fajl nem letezik akkor szol
                                fclose(mentes);
                                }
                            else{
                                printf("Melyik esemenyt szeretned modositani?\n");
                                char modositando[50];
                                scanf("%s",modositando);
                                if(megkeres(elso,modositando)!=NULL){
                                    modosit(elso,modositando);          //Ha van ilyen nevű akkor modositja
                                    break;
                                }else{
                                printf("Nincs ilyen nevu esemeny.\n");
                                }                   //Ha nincs ilyen akkor kilép vissza a menübe és szól
                                break;
                                fclose(mentes);
                        }
                }
                case 3:{//TORLES
                    char torolnikivantnevu[50];
                    FILE*mentes=fopen("mentes.txt","r");
                            if(mentes==NULL){
                                printf("Meg nincsenek letezo esemenyek.\n");
                                break;
                                }
                            else{
                                    printf("Add meg a torolni kivant esemeny nevet.\n");
                                    scanf("%s",torolnikivantnevu);
                                    if(megkeres(elso,torolnikivantnevu)!=NULL){ //Megnézi létezik-e ilyen nevű esemény
                                    printf("Sikeresen torolted a %s-nevu esemenyt\n",torolnikivantnevu);
                                    torles(elso,torolnikivantnevu);
                                    }else{
                                    printf("Nincs ilyen nevu esemeny.\n");}
                                    break;
                            }
                }
                case 4:{    //KILISTAZAS
                      FILE*mentes=fopen("mentes.txt","r");
                            if(mentes==NULL){
                                printf("Meg nincsenek letezo esemenyek.\n");
                                }
                            else{                                   //A futo programban levo eseményeket listázza ki, nem azokat ami a fajlban van
                                kilistaz(elso);
                            }
                        fclose(mentes);
                        break;
                }
                case 5:{ //KERESES
                        char keresettnevu[20];
                        printf("Add meg a keresett esemenyt nevet.\n");
                        scanf("%s",keresettnevu);
                        lelem *keresett=megkeres(elso,keresettnevu);
                            if(keresett!=NULL){
                                    printf("\nA keresett esemeny: \n%s %d.%02d.%02d %02d:%02d %s %s\n",keresett->esemeny.nev,keresett->esemeny.ev,keresett->esemeny.honap,keresett->esemeny.nap,keresett->esemeny.ora,keresett->esemeny.perc,keresett->esemeny.hely,keresett->esemeny.megjegyzes);
                            }
                            else{
                                        printf("Nincs ilyen nevu esemeny\n");
                            }
                        break;
                }
                case 6:{
                    fajlbair(elso);             //Kilepeskor menti el az esemenyeket ezert fontos hogy ezzel lepjunkki,illetve felszabadítdja a foglalt memoriat
                    felszabad(elso);
                    return 0;
                }
            default:{
                    printf("Nincs ilyen opcio, csak a szamot ird be.\n");       //Egyéb esetben nem csinal semmit
            }
        }

    }
    return 0;
}
