#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "beolvasas.h"
//#include "muveletek.h"
#include "debugmalloc.h"

komplex *hozzafuz(komplex *fej, double r, double fi){
    komplex *uj;
    uj = (komplex*) malloc(sizeof(komplex));
    if (uj == NULL)
        printf("malloc null\n");
    //printf("malloc jo\n");
    uj->az = 0x1a1;
    uj->r = r;
    uj->fi = fi;
    uj->kov = NULL;
    //printf("felotoltes jo\n");
    if (fej == NULL)
        return uj;

    else {
        komplex *mozgo = fej;
        while (mozgo->kov != NULL)
            mozgo = mozgo->kov;
        mozgo->kov = uj;
    }
}

void kiir(komplex *fej){
    komplex *mozgo = fej;
    while (mozgo != NULL){
        //printf("belep\n");
        printf("%x: Hossz: %f, Szog: %f\n", mozgo->az, mozgo->r, mozgo->fi);
        mozgo = mozgo->kov;
    }
}

void felszabadit(komplex *fej){
    komplex *iter = fej;
    while (iter != NULL) {
        komplex *kov = iter->kov;
        free(iter);
        iter = kov;
    }
}

void beolvasas(komplex **fej){
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
        //komplex kompszam = algebrai_to_trig(&szam);
    }
    else if (alak == 'T'){
        double r, fi;
        printf("Trigonometrikus alak. A szam hosza: ");
        scanf("%lf", &r);
        printf("A szam argumentumszoge: ");
        scanf("%lf", &fi);
        printf("itt meg\n");
        *fej = hozzafuz(*fej, r, fi);
        printf("beiras jo\n");
        kiir(*fej);
    }
    printf("Beolvasas sikerer");

}

/*Pointerként kapott char-t alakít át nagybetűssé, ha kisbetű, ha bármi mi más
* a kapott pointerbe visszaadja ugyan az.*/
void nagybetube(char *c){
    if (*c >= 'a' && *c <= 'z')
        *c = *c - ('a' - 'A');
    else
        *c = *c;
}
