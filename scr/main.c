#include <math.h>
#include <stdio.h>

#include "beolvasas.h"
#include "muveletek.h"
#include "filekezeles.h"
#include "debugmalloc.h"

int main(){
	char opcio;
    komplex *fej = NULL;
    printf("Ez egy komplex szamologep, komplex szamokat lehet beolvasni, eltarolni es szamolni veluk\n"
    "Az ociok:\n[I] - Beolvasas\n[O/M] - Muveletvegzes(szamolas)\n[D/A] - Abrazolas (svg file-ba)\n[S] - mentes txt-be\n[Q] - kilepes\n");
    printf("OCIO: ");
    scanf(" %c", &opcio);
    nagybetube(&opcio);
    while(opcio != 'Q'){
        switch (opcio){
        case 'I':
            beolvasas(&fej);
            break;
        case 'O':
        case 'M':
            muvelet(&fej);
            break;
        case 'D':
        case 'A':
            printf("Opcio meg nem letezik(D/A)");
            break;
        case 'S':
            printf("%s", mentes(fej) ? "Sikeres filekiiras" : "sikertelen filekiiras");
            break;
        default:
            printf("Ismeretlen input");
            break;
        }
        printf("\nOCIO: ");
        scanf(" %c", &opcio);
        nagybetube(&opcio);
        

    }
    felszabadit(fej);
    return 0;
}

