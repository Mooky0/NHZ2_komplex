#include <math.h>
#include <stdlib.h>
#include <stdio.h>

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
komplex algebrai_to_trig(komplex_algebrai *alg){
    komplex trig;
    trig.r = sqrt(alg->Re*alg->Re + alg->Im * alg->Im);
    trig.fi = (atan(alg->Im / alg->Re) * 180) / M_PI;
    trig.az = alg->az;
    return trig;

}

/*komplex számok trigonometriai (ami itt egyenérékű az exponenciális alakkkal) alakból alakít áti
 * alegbrai alakba. Egyenlőre pointerekkel dolgozik, mert az fun, de túl bonyinak tűnik...
 * majd át kell alakítani, hogy rendesn stack-en dolgozzon, return value-vel.
 * A szög fokban értendő, később szintén válozni fog.*/
komplex_algebrai trig_to_alg(komplex *trig){
    komplex_algebrai alg;
    alg.Re = trig->r * cos((trig->fi * M_PI) / 180);
    alg.Im = trig->r * sin((trig->fi * M_PI) / 180);
    alg.az = trig->az;
    return alg;
}

/*Összead kettő komplex számot algebrai alakban, és algebrai alakban tér vissza
 * nincs kezelve az eset amikor az szám nem valós szám, később tervezem kezelni.*/
komplex_algebrai osszead(komplex_algebrai szam1, komplex_algebrai szam2){
	komplex_algebrai visszaszam;
	visszaszam.Re = szam1.Re + szam2.Re;
	visszaszam.Im = szam1.Im + szam2.Im;
	return visszaszam;

}

/*Kivon kettő komplex számot algebrai alakban, és algebrai alakban tér vissza*/
komplex_algebrai kivon(komplex_algebrai kisebbitendo, komplex_algebrai kivonando){
    komplex_algebrai visszaszam;   
	visszaszam.Re = kisebbitendo.Re + kivonando.Re;
	visszaszam.Im = kisebbitendo.Im + kivonando.Im;
    return visszaszam;
}

/*komplex számokat szoroz össze trig alakban, azzal is tér vissza*/
komplex szorzas(komplex szam1, komplex szam2){
    komplex visszaszam;
    visszaszam.r = szam1.r * szam2.r;
    visszaszam.fi = szam1.fi + szam2.fi;
    return visszaszam;
}

/*komplex számokat oszt egymással trig alakban, azzal is tér vissza*/
komplex osztas(komplex osztando, komplex oszto){
    komplex visszaszam;
    visszaszam.r = osztando.r / oszto.r;
    visszaszam.fi = osztando.fi - oszto.fi;
    return visszaszam;
}

/*komplex szam egész hatványát számolja, ha nem egész akkor típuskonverzióval levágja a végét*/
komplex hatvany(komplex alap, int kitevo){
    komplex visszaszam;
    visszaszam.fi = alap.fi * kitevo;
    double hatvany;
    while (kitevo != 0){
        hatvany *= alap.r;
        kitevo--;
    }
    visszaszam.r = hatvany;
    return visszaszam;
}