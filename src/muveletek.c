#include <stdlib.h>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <string.h>
#include <ctype.h>


#include "beolvasas.h"
#include "muveletek.h"
#include "debugmalloc.h"

/*Pointerként kapott char-t, ami lehet str is alakít át nagybetűssé, ha kisbetű, ha bármi mi más
* a kapott pointerbe visszaadja ugyan azt. A függvényt más modulok is használják*/
void nagybetube(char *c){
    int i = 0;
    while (c[i] != '\0'){
        c[i] = toupper(c[i]);
        i++;
    }
}

/*Algebrai alakban kapott komplex számot alakít, trigonometrikus alakúvá
* nem listaelemmé. Visszatérési értéke egy trigonometrikus komplex szám,
* ezt a függvényt más modulok is használják.*/
komplex_trig algebrai_to_trig(komplex_algebrai alg){
    komplex_trig trig;
    trig.r = sqrt(alg.Re*alg.Re + alg.Im * alg.Im);
    trig.fi = atanl(alg.Im/alg.Re) * 180 / M_PI;
    trig.az = alg.az;
    return trig;

}

/*Komlex listalemet alakít algebrai alakú komplex számmá.
* Visszatérési értéke egy algebrai kompox szám.
* Ezt a függvényt más modulok is használják.*/
komplex_algebrai trig_to_alg(komplex *trig){
    komplex_algebrai alg;
    alg.Re = trig->r * cos((trig->fi * M_PI) / 180);
    alg.Im = trig->r * sin(trig->fi * M_PI / 180);
    alg.az = trig->az;
    return alg;
}

/*Kettő listaelemere muató pointer a paramétere, ezeket összeadja,
* és visszaad egy trigonometrikus nem komplexet. A függvény először átaélakítja algebriai
* alakká, a fenti müggvénnyel, majd a két részt összeadja, és az összeget visszaalakítja
* trigonometrikus alakúva, de ez nem listattelem, a listáhot adás, a hívó dolga, ha szeretné.*/
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

/*Kettő listaelemere muató pointer a paramétere, ezeket kivonja,
* és visszaad egy trigonometrikus nem komplexet. A függvény először átaélakítja algebriai
* alakká, a fenti müggvénnyel, majd a két részt kivonja, és az összeget visszaalakítja
* trigonometrikus alakúva, de ez nem listattelem, a listáhot adás, a hívó dolga, ha szeretné.*/
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

/*Kettő listaelemere muató pointer a paramétere, ezeket összeszorozza,
* és visszaad egy trigonometrikus nem komplexet, de ez nem listattelem,
* a listáhot adás, a hívó dolga, ha szeretné.*/
komplex_trig szorzas(komplex *szam1, komplex *szam2){
    komplex_trig visszaszam;
    visszaszam.r = szam1->r * szam2->r;
    visszaszam.fi = szam1->fi + szam2->fi;
    return visszaszam;
}

/*Kettő listaelemere muató pointer a paramétere, először az osztandó,
* majd az osztó ezeket elosztja, és visszaad egy trigonometrikus
* nem komplexet, de ez nem listattelem,
* a listáhot adás, a hívó dolga, ha szeretné.*/
komplex_trig osztas(komplex *osztando, komplex *oszto){
    komplex_trig visszaszam;
    visszaszam.r = osztando->r / oszto->r;
    visszaszam.fi = osztando->fi - oszto->fi;
    return visszaszam;
}

/*Paramáterei: komplex listattele, tehát trigonometrikus alakban a hatványalap,
* majd egy egész szám, a hatványkitevő*/
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

/*MÜVELETI MENÜ FÜGGVÉNY
* A főmenü hívja meg, nincs visszatérési értéke.
* Paraméterei: a lista elejére mutató pointer pointer (fej), az ans szintén komplex** ezt a főprogram tárolja.
* Kiírja és kezeli a műveletek menüjét. Átalakítja a művelet parancs után kapott 2 paramétert számmá, 
* ha kell, és meghívja a műveleti függvényeket, az új számot hozzáírja a listához, és kiírja az új számot.*/
void muvelet(komplex **fej, komplex **ans){
    bool feltetel = true;
    while (feltetel){
        char *muvelet, tomb[15];
        char *arg1, *arg2;
        char elem;
        int n = 0;
        printf("Muvelet vegrehajtasa.\nMuvelet harombetus kodja majd a ket argumentum:\n[ADD szam1 szam2]\t\t- osszeadas\n[SUB kisebbitendo kivonando]\t- kivonas\n"
        "[MUL szam1 szam2]\t\t- szorzas\n[DIV osztando oszto]\t\t- osztas\n[POW szam kitevo]\t\t- egesz hatvanyra emeles\n[CON szam alak(T/A)]\t\t- alakban kiiras.\n"
        "[Q]\t\t\t\t- Visszalepes\nAz \"ANS\" szóra, az előző művelet eredményét veszi operátornak");
        printf("\nAdd meg a muveletet es  az argumentumokat: ");
        
        gets(tomb);

        //beolvasott nagybetűbe alakítása és kilépési feltétel ellenőrzés
        nagybetube(tomb);
        if (tomb[0] == 'Q'){
            feltetel = false;
            return;
        }
        char *rest = tomb;

        //beolvasott felszabdalása 3 str-é (muvelet, arg1, arg2)
        muvelet = strtok_r(tomb, " ", &rest);
        arg1 = strtok_r(NULL, " ", &rest);
        if (arg1 == NULL){
            printf("Ismeretlen muvelet");
            return;
        }
        arg2 = strtok_r(NULL, " ", &rest);
        if (arg2 == NULL){
            printf("ismeretlen muvelet");
            return;
        }

        //elso számnak mindeképp azonosítónak kell lennie, vagy ans-nak
        //megnézzük, hogy ans-e, és ha nem, szám kikeresése a kistából
        komplex *szam1;
        if(strcmp(arg1, "ANS") == 0){
            if (*ans == NULL){
                perror("Meg nincs korabbi eredmeny");
                return;
            }
            szam1 = *ans;
        } else{ //kikeresés a listából
            szam1 = kikeres(*fej, arg1);
            if (szam1 == NULL)
                return;
        }

        //megnézzük, hogy a második argumentum ans-e
        komplex *szam2;
        if (strcmp(arg2, "ANS") == 0){
            if(*ans == NULL){
                perror("Meg nics korabbi eredmeny");
                return;
            }
            szam2 = *ans;
        } else {
            char *temp;
            /*megnézzük, hogy a művelet ADD/SUB/MUL/DIV mert akkor mindkettő számot ki kell keresni, ha igen, kikeressük a 2. számot is*/
            if (strcmp(muvelet, "ADD") == 0 || strcmp(muvelet, "SUB") == 0 || strcmp(muvelet, "MUL") == 0 || strcmp(muvelet, "DIV") == 0){
                szam2 = kikeres(*fej, arg2);
                if (szam2 == NULL)
                    return;
            }
        }
        fflush(stdin);
        //menü lekezelése, esetek
        komplex_trig szam;
        if (strcmp(muvelet, "ADD") == 0){
            szam = osszead(szam1, szam2);
            *fej = hozzafuz(*fej, szam.r, szam.fi);
            *ans = kiirutolso(*fej);
            getchar();
        } else if (strcmp(muvelet, "SUB") == 0){
            szam = kivon(szam1, szam2);
            *fej = hozzafuz(*fej, szam.r, szam.fi);
            *ans = kiirutolso(*fej);
            getchar();
        } else if (strcmp(muvelet, "MUL") == 0){
            szam = szorzas(szam1, szam2);
            *fej = hozzafuz(*fej, szam.r, szam.fi);
            *ans = kiirutolso(*fej);
            getchar();
        } else if (strcmp(muvelet, "DIV") == 0){
            szam = osztas(szam1, szam2);
            *fej = hozzafuz(*fej, szam.r, szam.fi);
            *ans = kiirutolso(*fej);
            getchar();
        } else if (strcmp(muvelet, "POW") == 0){
            char *temp;
            int kitevo = (int)strtol(arg2, &temp, 10);
            if(*temp != '\0'){
                printf("Nem megfelelo hatványkitevo");
                return;
            }
            szam = hatvany(szam1, kitevo);
            *fej = hozzafuz(*fej, szam.r, szam.fi);
            *ans = kiirutolso(*fej);
            getchar();
        } else if (strcmp(muvelet, "CON") == 0){
            if (arg2[0] == 'T'){
                printf("0x%X: Hossz: %f, Szog: %f\n", szam1->az, szam1->r, szam1->fi);
                getchar();
            }
            else if (arg2[0] == 'A'){
                komplex_algebrai szam_alg = trig_to_alg(szam1);
                printf("0x%X: Re:%f, Im:%f\n", szam_alg.az, szam_alg.Re, szam_alg.Im);
                getchar();
            }
        } else{
            perror("Ismertlen muvelet");
            getchar();
        }
    }
}
