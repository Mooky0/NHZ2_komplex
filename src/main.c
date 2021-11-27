#include <math.h>
#include <stdio.h>

#include "beolvasas.h"
#include "muveletek.h"
#include "filekezeles.h"
#include "debugmalloc.h"


/*FŐMENÜ
* Ez a főprogram. A számokat dinamikusan láncolt listában tárolja a program a lista elejét (fej, az
* első elemre mutató pointer) és az ans (előző müvelet eredményére mutatató pointert) 
* a program itt hozza létre, kezdetben NULL. A kilépés funkció (Q) a 
* ciklus kilépési felétele, emiatt amíg nem akarunk kilépni a menü újra meg újra lefut. A ciklus
* után (ha ki akarunk lépni) van a lista felszabadítása (fv: beolvasás)*/
int main(){
	char opcio;
    komplex *fej = NULL;
    komplex *ans = NULL;
    printf("Ez egy komplex szamologep, komplex szamokat lehet beolvasni, eltarolni es szamolni veluk\n"
    "Az opciok:\n[I] - Beolvasas (Input)\n[O/M] - Muveletvegzes(szamolas, operation)\n[D/A] - Abrazolas (svg file-ba, draw)\n[S] - mentes txt-be (save)\n[P/K] - Kiiras console-ra (print)\n[Q] - kilepes (Quit)\n");
    printf("OPCIO: ");
    scanf(" %c%*[^\n]", &opcio);
    nagybetube(&opcio);
    while(opcio != 'Q'){
        switch (opcio){
        case 'I':
            beolvasas(&fej);
            break;
        case 'O':
        case 'M':
            muvelet(&fej, &ans);
            break;
        case 'D':
        case 'A':
            printf("%s", abrazol(fej) ? "Sikeres abrazolas" : "Sikertelen abrazolas");
            break;
        case 'S':
            printf("%s", mentes(fej) ? "Sikeres filekiiras" : "Sikertelen filekiiras");
            break;
        case 'P':
        case 'K':
            kiir(fej);
            break;
        default:
            printf("Ismeretlen input");
            break;
        }
        printf("Ez egy komplex szamologep, komplex szamokat lehet beolvasni, eltarolni es szamolni veluk\n"
        "Az opciok:\n[I] - Beolvasas (Input)\n[O/M] - Muveletvegzes(szamolas, operation)\n[D/A] - Abrazolas (svg file-ba, draw)\n[S] - mentes txt-be (save)\n[P/K] - Kiiras console-ra (print)\n[Q] - kilepes (Quit)\n");
        printf("\nOPCIO: ");
        scanf(" %c%*[^\n]", &opcio);
        nagybetube(&opcio);
        

    }
    felszabadit(fej);
    return 0;
}

