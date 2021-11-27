#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "beolvasas.h"
#include "muveletek.h"
#include "filekezeles.h"
//#include "debugmalloc.h"

/*Hozzáfüzés függvény:
* Visszatérési érték: komplex pointer, azaz a fej, ami lehetséges, hogy változott,
* paraméterei: a fej (visszatérve változtatja, ha kell), a szám hossza (r, valós szám),
* a szám argumentumszöge (fi, valós szám). Lefoglal egy új komplex számnak memóriában helyet,
* majd hossza fűzi a listához, ha a fej NULL (nincs lista) azt módosítja és adja vissza.
* A függvényt használja más modul is*/
komplex *hozzafuz(komplex *fej, double r, double fi){
    komplex *uj;
    uj = (komplex*) malloc(sizeof(komplex));
    if (uj == NULL)
        printf("malloc null\n");
    uj->r = r;
    uj->fi = fi;
    uj->kov = NULL;
    if (fej == NULL){
        uj->az = 0x1a1; //Innen kezdünk számolni a könnyű megkülönböztethetőség érdekében, és a program mindenhol hexadecimálisan várja és írja ki.
        return uj;
    }

    else {
        komplex *mozgo = fej;
        int utolsoaz = mozgo->az;
        while (mozgo->kov != NULL){
            mozgo = mozgo->kov;
            utolsoaz = mozgo->az;
        }
        uj->az = utolsoaz+1;
        mozgo->kov = uj;
    }
    return fej;
}

/*Lista kiírása.
* Nincs visszatérési értéke, paramétere a fej, nem változtatja azt.
* végigmegy a listán és kiír minden elmet trigonometrikus alakban
* A függvényt használja más modul is*/
void kiir(komplex *fej){
    komplex *mozgo = fej;
    while (mozgo != NULL){
        //printf("belep\n");
        printf("%x: Hossz: %f, Szog: %f\n", mozgo->az, mozgo->r, mozgo->fi);
        mozgo = mozgo->kov;
    }
}

/*Kiírja az utolsó elemet és vissza is adja azt:
* Visszatérési értéke: listaelemre mutató pointer, a lista utolsó eleme.
* Paramétere: a fej, nem változtajta, azt.
* Végigmegy a listán és az utolsó elemet kíírja és vissza is tér vele.*/
komplex *kiirutolso(komplex *fej){
    komplex *mozgo = fej;
    while(mozgo->kov != NULL){
        mozgo = mozgo->kov;
    }
    printf("%x: Hossz: %f, Szog: %f\n", mozgo->az, mozgo->r, mozgo->fi);
    return mozgo;
}

/*Felszabadítás
* Nincs visszatérési értéke, paramétere a lista elejére mutató pointer, fej,
* nem változtatja azt. Végigmegy a listán és felszabadít minden elemet.*/
void felszabadit(komplex *fej){
    komplex *iter = fej;
    while (iter != NULL) {
        komplex *kov = iter->kov;
        free(iter);
        iter = kov;
    }
}

/*BEOLVASÁS MENU
* Nincs visszatérési értéke, paramétere: a lista fejére mutató pointer.
* Kiírja a beolvasás menüt, lekezeli a 3 opciót (algebrai, trigonometrikus, file)
* és ha kell átalakít majd meghívja a hozzafuz függvényt hogy a lista végére fűzze a számot.
* File-ból való beolvasásra meghívja a megfelelő függvényt, majd kiírja mindig a teljes új listát.*/
void beolvasas(komplex **fej){
    printf("Milyen alakban szeretnél beolvasni, vagy File-bol?\n"
    "[A]lgebrai, [T]riginometriai avgy [F]ile?\n");
    char alak;
    scanf(" %c%*[^\n]", &alak);
    nagybetube(&alak);
    if (alak == 'A'){
        komplex_algebrai szam;
        printf("Algebrai alak. Szam valos resze: ");
        scanf("%lf", &szam.Re);
        printf("Szam kepzetes resze: ");
        scanf("%lf", &szam.Im);
        komplex_trig ujszam = algebrai_to_trig(szam);
        *fej = hozzafuz(*fej, ujszam.r, ujszam.fi);
    }
    else if (alak == 'T'){
        double r, fi;
        printf("Trigonometrikus alak. A szam hosza: ");
        scanf("%lf", &r);
        printf("A szam argumentumszoge: ");
        scanf("%lf", &fi);
        *fej = hozzafuz(*fej, r, fi);
    }
    else if (alak == 'F'){
        filebeolvas(&*fej);
    }
    kiir(*fej);

}