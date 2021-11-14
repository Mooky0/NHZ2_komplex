#include <stdlib.h>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <string.h>


#include "beolvasas.h"
#include "muveletek.h"


/*Pointerként kapott char-t alakít át nagybetűssé, ha kisbetű, ha bármi mi más
* a kapott pointerbe visszaadja ugyan az.*/
void nagybetube(char *c){
    if (*c >= 'a' && *c <= 'z')
        *c = *c - ('a' - 'A');
    else
        *c = *c;
}


/*komplex számokat alakít át algebrai alakból, trigonometraiba (ami itt egyenértékű
 * az exponenciálissal). Pointerből dolgozik, trig alakkal tér vissza.
 * A szög fokban értendő, később szintén válozni fog.*/
komplex_trig algebrai_to_trig(komplex_algebrai alg){
    komplex_trig trig;
    trig.r = sqrt(alg.Re*alg.Re + alg.Im * alg.Im);
    trig.fi = atanl(alg.Im/alg.Re) * 180 / M_PI;
    trig.az = alg.az;
    return trig;

}

/*komplex számok trigonometriai (ami itt egyenérékű az exponenciális alakkkal) alakból alakít áti
 * alegbrai alakba. Egyenlőre pointerekkel dolgozik, mert az fun, de túl bonyinak tűnik...
 * majd át kell alakítani, hogy rendesn stack-en dolgozzon, return value-vel.
 * A szög fokban értendő, később szintén válozni fog.*/
komplex_algebrai trig_to_alg(komplex *trig){
    komplex_algebrai alg;
    alg.Re = trig->r * cos((trig->fi * M_PI) / 180);
    alg.Im = trig->r * sin(trig->fi * M_PI / 180);
    alg.az = trig->az;
    return alg;
}

/*Összead kettő komplex számot algebrai alakban, és algebrai alakban tér vissza
 * nincs kezelve az eset amikor az szám nem valós szám, később tervezem kezelni.*/
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

/*Kivon kettő komplex számot algebrai alakban, és algebrai alakban tér vissza*/
komplex_trig kivon(komplex *szam1, komplex *szam2){
    komplex_trig visszaszam;   
    komplex_algebrai temp;
    komplex_algebrai kisebbitendo = trig_to_alg(szam1);
    komplex_algebrai kivonando = trig_to_alg(szam2);
	temp.Re = kisebbitendo.Re + kivonando.Re;
	temp.Im = kisebbitendo.Im + kivonando.Im;
    visszaszam = algebrai_to_trig(temp);
    return visszaszam;
}

/*komplex számokat szoroz össze trig alakban, azzal is tér vissza*/
komplex_trig szorzas(komplex *szam1, komplex *szam2){
    komplex_trig visszaszam;
    visszaszam.r = szam1->r * szam2->r;
    visszaszam.fi = szam1->fi + szam2->fi;
    return visszaszam;
}

/*komplex számokat oszt egymással trig alakban, azzal is tér vissza*/
komplex_trig osztas(komplex *osztando, komplex *oszto){
    komplex_trig visszaszam;
    visszaszam.r = osztando->r / oszto->r;
    visszaszam.fi = osztando->fi - oszto->fi;
    return visszaszam;
}

/*komplex szam egész hatványát számolja, ha nem egész akkor típuskonverzióval levágja a végét*/
komplex_trig hatvany(komplex *alap, int kitevo){
    komplex_trig visszaszam;
    visszaszam.fi = alap->fi * kitevo;
    double hatvany;
    while (kitevo != 0){
        hatvany *= alap->r;
        kitevo--;
    }
    visszaszam.r = hatvany;
    return visszaszam;
}

void muvelet(komplex **fej){
    char muvelet[4];
    char arg1[4], arg2[4];
    printf("Muvelet vegrehajtasa.\nMuvelet harombetus kodja majd a ket argumentum:\n[ADD szam1 szam2]\t\t- osszeadas\n[SUB kisebbitendo kivonando]\t- kivonas\n"
    "[MUL szam1 szam2]\t\t- szorzas\n[DIV osztando oszto]\t\t- osztas\n[POW szam kitevo]\t\t- egesz hatvanyra emeles\n[CON szam alak(T/A)]\t\t- alakban kiiras.");
    printf("\nAdd meg a muveletet es  az argumentumokat: ");
    scanf(" %s %s %s", &muvelet, &arg1, &arg2);
    
    komplex *szam1;
    int az1;
    az1 = (int)strtol(arg1, NULL, 16);
    komplex *mozgo = *fej;
    while (mozgo != NULL){
        if (mozgo->az == az1){
                szam1 = mozgo;
                mozgo = NULL;
        }
        mozgo = (mozgo == NULL) ? NULL : mozgo->kov;
    }

    komplex *szam2;
    /*megnézzük, hogy a művelet ADD/SUB/MUL/DIV mert akkor mindkettő számot ki kell keresni*/
    if (strcmp(muvelet, "ADD") == 0 || muvelet == "SUB" || muvelet == "MUl" || muvelet == "DIV"){
        int az2;
        az2 = (int) strtol(arg2, NULL, 16);
        komplex *mozgo = *fej;
        while (mozgo != NULL){
            if (mozgo->az == az1){
                szam2 = mozgo;
                mozgo = NULL;
            }
            mozgo = (mozgo == NULL) ? NULL : mozgo->kov;
        }        
    }

    if (strcmp(muvelet, "ADD") == 0){
        komplex_trig szam;
        szam = osszead(szam1, szam2);
        *fej = hozzafuz(*fej, szam.r, szam.fi);
        kiir(*fej);
    } else if (muvelet == "SUB"){

    } else if (muvelet == "MUL"){
        
    } else if (muvelet == "DIV"){

    } else if (muvelet == "POW"){

    } else if (muvelet == "CON"){

    }
}
