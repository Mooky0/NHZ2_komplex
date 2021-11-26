#include <stdlib.h>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <string.h>
#include <ctype.h>


#include "beolvasas.h"
#include "muveletek.h"
//#include "debugmalloc.h"

/*Pointerként kapott char-t alakít át nagybetűssé, ha kisbetű, ha bármi mi más
* a kapott pointerbe visszaadja ugyan az.*/
void nagybetube(char *c){
    int i = 0;
    while (c[i] != '\0'){
        c[i] = toupper(c[i]);
        i++;
    }
}

komplex_trig algebrai_to_trig(komplex_algebrai alg){
    komplex_trig trig;
    trig.r = sqrt(alg.Re*alg.Re + alg.Im * alg.Im);
    trig.fi = atanl(alg.Im/alg.Re) * 180 / M_PI;
    trig.az = alg.az;
    return trig;

}

komplex_algebrai trig_to_alg(komplex *trig){
    komplex_algebrai alg;
    alg.Re = trig->r * cos((trig->fi * M_PI) / 180);
    alg.Im = trig->r * sin(trig->fi * M_PI / 180);
    alg.az = trig->az;
    return alg;
}


komplex_trig osszead(komplex *szam1_trig, komplex *szam2_trig){
	komplex_trig visszaszam;
    komplex_algebrai temp;
    komplex_algebrai szam1, szam2;
    szam1 = trig_to_alg(szam1_trig);
    szam2 = trig_to_alg(szam2_trig);
    temp.Re = szam1.Re + szam2.Re;
	temp.Im = szam1.Im + szam2.Im;
    visszaszam = algebrai_to_trig(temp);
	return visszaszam;

}


komplex_trig kivon(komplex *szam1, komplex *szam2){
    komplex_trig visszaszam;   
    komplex_algebrai temp;
    komplex_algebrai kisebbitendo = trig_to_alg(szam1);
    komplex_algebrai kivonando = trig_to_alg(szam2);
	temp.Re = kisebbitendo.Re - kivonando.Re;
	temp.Im = kisebbitendo.Im - kivonando.Im;
    visszaszam = algebrai_to_trig(temp);
    return visszaszam;
}


komplex_trig szorzas(komplex *szam1, komplex *szam2){
    komplex_trig visszaszam;
    visszaszam.r = szam1->r * szam2->r;
    visszaszam.fi = szam1->fi + szam2->fi;
    return visszaszam;
}


komplex_trig osztas(komplex *osztando, komplex *oszto){
    komplex_trig visszaszam;
    visszaszam.r = osztando->r / oszto->r;
    visszaszam.fi = osztando->fi - oszto->fi;
    return visszaszam;
}


komplex_trig hatvany(komplex *alap, int kitevo){
    komplex_trig visszaszam;
    visszaszam.fi = kitevo * alap->fi;
    double hatvany = alap->r;
    while (kitevo != 1){
        hatvany *= alap->r;
        kitevo--;
    }
    visszaszam.r = hatvany;
    return visszaszam;
}

void muvelet(komplex **fej, komplex **ans){
    char muvelet[4];
    char arg1[4], arg2[4];
    printf("Muvelet vegrehajtasa.\nMuvelet harombetus kodja majd a ket argumentum:\n[ADD szam1 szam2]\t\t- osszeadas\n[SUB kisebbitendo kivonando]\t- kivonas\n"
    "[MUL szam1 szam2]\t\t- szorzas\n[DIV osztando oszto]\t\t- osztas\n[POW szam kitevo]\t\t- egesz hatvanyra emeles\n[CON szam alak(T/A)]\t\t- alakban kiiras.");
    printf("\nAdd meg a muveletet es  az argumentumokat: ");
    scanf(" %s %s %s%*[^\n]", &muvelet, &arg1, &arg2);
    nagybetube(muvelet);
    nagybetube(arg1);
    nagybetube(arg2);

    komplex *szam1;
    if(strcmp(arg1, "ANS") == 0){
        if (*ans == NULL){
            perror("Meg nincs korabbi eredmeny");
            return;
        }
        szam1 = *ans;
    } else{
        char *temp;
        int az1;
        az1 = (int)strtol(arg1, &temp, 16);
        if (*temp != '\0'){
            printf("Nem hexadecimálisan adta meg az azonosítót.");
            return;
        }
        komplex *mozgo = *fej;
        while (mozgo != NULL && mozgo->az != az1){
            mozgo = mozgo->kov;
        }
        if (mozgo == NULL){
            perror("Nincs ilyen azonositoju szám menteve");
            return;
        }
        szam1 = mozgo;
    }

    komplex *szam2;
    if (strcmp(arg2, "ANS") == 0){
        if(*ans == NULL){
            perror("Meg nics korabbi eredmeny");
            return;
        }
        szam2 = *ans;
    } else {
        char *temp;
        /*megnézzük, hogy a művelet ADD/SUB/MUL/DIV mert akkor mindkettő számot ki kell keresni*/
        if (strcmp(muvelet, "ADD") == 0 || strcmp(muvelet, "SUB") == 0 || strcmp(muvelet, "MUL") == 0 || strcmp(muvelet, "DIV") == 0){
            int az2;
            az2 = (int) strtol(arg2, &temp, 16);
            if (*temp != '\0'){
                printf("Nem hexadecimálisan adta meg az azonosítót.");
                return;
            }
            komplex *mozgo = *fej;
            while (mozgo != NULL && mozgo->az != az2){
                mozgo = mozgo->kov;
            }
            if(mozgo == NULL){
                perror("Nincs a listaban ilyen azonositoju szam.");
                return;
            }
            szam2 = mozgo;
        }
    }

    komplex_trig szam;
    if (strcmp(muvelet, "ADD") == 0){
        szam = osszead(szam1, szam2);
        *fej = hozzafuz(*fej, szam.r, szam.fi);
        *ans = kiirutolso(*fej);
    } else if (strcmp(muvelet, "SUB") == 0){
        szam = kivon(szam1, szam2);
        *fej = hozzafuz(*fej, szam.r, szam.fi);
        *ans = kiirutolso(*fej);
    } else if (strcmp(muvelet, "MUL") == 0){
        szam = szorzas(szam1, szam2);
        *fej = hozzafuz(*fej, szam.r, szam.fi);
        *ans = kiirutolso(*fej);
    } else if (strcmp(muvelet, "DIV") == 0){
        szam = osztas(szam1, szam2);
        *fej = hozzafuz(*fej, szam.r, szam.fi);
        *ans = kiirutolso(*fej);
    } else if (strcmp(muvelet, "POW") == 0){
        int kitevo = (int)strtol(arg2, NULL, 10);
        szam = hatvany(szam1, kitevo);
        *fej = hozzafuz(*fej, szam.r, szam.fi);
        *ans = kiirutolso(*fej);
    } else if (strcmp(muvelet, "CON") == 0){
        if (arg2[0] == 'T'){
            printf("%x: Hossz: %f, Szog: %f\n", szam1->az, szam1->r, szam1->fi);
        }
        else if (arg2[0] == 'A'){
            komplex_algebrai szam_alg = trig_to_alg(szam1);
            printf("%x: Re:%f, Im:%f\n", szam_alg.az, szam_alg.Re, szam_alg.Im);
        }
    } else
        perror("Ismertlen muvelet");
}
