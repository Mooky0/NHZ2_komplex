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
            /* TODO Ide jön a beolvasás*/
            beolvasas(&fej);
            //printf("Opcio meg nem letezik(I)");
            break;
        case 'O':
        case 'M':
            /* TODO Ide jön a műveletes rész*/
            muvelet(&fej);
            //printf("Opcio meg nem letezik(O/M)");
            break;
        case 'D':
        case 'A':
            /* TODO ábrázolás rész*/
            printf("Opcio meg nem letezik(D/A)");
            break;
        case 'S':
            /* TODO mentes txt-be*/
            printf("%s", mentes(fej) ? "Sikeres filekiiras" : "sikertelen filekiiras");
            //printf("Opcio meg nem letezik(S)");
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

