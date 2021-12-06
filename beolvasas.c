#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "beolvasas.h"
#include "muveletek.h"
#include "debugmalloc.h"

bool foglal(DinTomb *tomb, int meret){
    komplex *adat = (komplex*) malloc(meret * sizeof(komplex));
    if (adat == NULL)
        return false;
    tomb->adat = adat;
    tomb->meret = meret;
    tomb->utolso_az = 0x1A0; //innen indul a számolás, mert a spec-ben ez van, és mert akkor nehezebb összekeverni mással.
    return true;
}

bool ujrafoglal(DinTomb *tomb){
    
    komplex *ujadat = (komplex*) malloc((tomb->meret +1) * sizeof(komplex));
    if (ujadat == NULL){
        printf("szar az ujrafoglal (NULL)");    
        return false;
    }
    printf("Jo az ujrafoglal.\n");
    //int utolso = tomb->utolso_az;
    //int min = meret < tomb->meret ? meret : tomb->meret;
    for (int i = 0; i < tomb->meret+1; ++i){
        printf("ciklus\n");
        ujadat[i] = tomb->adat[i];
        printf("atmasol ciklus\n");
    }
    printf("atmasol jo\n");
    free(tomb->adat);
    tomb->adat = ujadat;
    tomb->meret = tomb->meret+1;
    tomb->utolso_az = tomb->utolso_az +1;
    printf("struck jo");
    return true;
}

bool tombbeir(DinTomb *tomb, komplex szam){
    printf("belep\n");
    ujrafoglal(tomb);
    printf("ujrafoglal visszater");
    tomb->adat[tomb->meret-1].r = szam.r; 
    tomb->adat[tomb->meret-1].fi = szam.fi; 
    tomb->adat[tomb->meret-1].az = tomb->utolso_az;
    //printf("feltolt jo");
    return true;
}

void dintomb_kiir(DinTomb const *dt) {
    for (int i = 0; i < dt->meret; ++i)
        printf("%f %f", dt->adat[i].r, dt->adat[i].fi);
    printf("\n");
}

void beolvasas(DinTomb *szamok){
    printf("Milyen alakban szeretnél beolvasni?\n"
    "[A]lgebrai vagy [T]riginometriai?\n");
    char alak;
    scanf(" %c", &alak);
    nagybetube(&alak);
    if (alak == 'A'){
        komplex_algebrai szam;
        printf("Algebrai alak. Szam valas resze: ");
        scanf("%lf", &szam.Re);
        printf("Szam kepzetes resze: ");
        scanf("%lf", &szam.Im);
        komplex kompszam = algebrai_to_trig(&szam);
        tombbeir(szamok, kompszam);
    }
    else if (alak == 'T'){
        komplex szam;
        printf("Trigonometrikus alak. A szam hosza: ");
        scanf("%lf", &szam.r);
        printf("A szam argumentumszoge: ");
        scanf("%lf", &szam.fi);
        printf("itt meg\n");
        tombbeir(szamok, szam);
        printf("beiras jo\n");
    }
    printf("Beolvasas sikerer");
    dintomb_kiir(szamok);
}

// /*Pointerként kapott char-t alakít át nagybetűssé, ha kisbetű, ha bármi mi más
// * a kapott pointerbe visszaadja ugyan az.*/
// void nagybetube(char *c){
//     if (*c >= 'a' && *c <= 'z')
//         *c = *c - ('a' - 'A');
//     else
//         *c = *c;
// }
