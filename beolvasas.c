#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "beolvasas.h"

bool ujrafoglal(DinTomb tomb, int meret){
    DinTomb *uj;
    uj = (DinTomb*) malloc(meret* sizeof());
    if (uj == NULL)
        return false;
    uj->meret = meret;
    for (int i=0; i<meret; i++){
        uj->tomb[i]
    }
}

void beolvasas(){
    printf("Milyen alakban szeretnél beolvasni?\n"
    "[A]lgebrai vagy [T]riginometriai?\n");
    char alak;
    scanf("%c", &alak);
    nagybetube(&alak);
    if (alak == 'A'){
        
    }
}

/*Pointerként kapott char-t alakít át nagybetűssé, ha kisbetű, ha bármi mi más
* a kapott pointerbe visszaadja ugyan az.*/
void nagybetube(char *c){
    if (*c >= 'a' && *c <= 'z')
        *c = *c - ('a' - 'A');
    else
        *c = *c;
}
