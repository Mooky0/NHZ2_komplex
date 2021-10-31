#include <math.h>
#include <stdio.h>

typedef struct komplex_algebrai{
    int az;
    double Re, Im;
} komplex_algebrai;

typedef struct komplex{
    int az;
    double r, fi; //Első kötben fokban tárolom a szöget, utána lehet váltani kell radiánra.
} komplex;

/*komplex számokat alakít át algebrai alakból, trigonometrikusba (ami itt egyenértékű
 * az exponenciálissal). egyenlőre pointerből pointerbe dolgozik, de ezen később
 * valószínűleg válotoztatni kell.
 * A szög fokban értendő, kéőbb szintén válozni fog.*/
void algebrai_to_trig(komplex_algebrai *alg, komplex *trig){
    trig->r = sqrt(alg->Re*alg->Re + alg->Im * alg->Im);
    trig->fi = (atan(alg->Im / alg->Re) * 180) / M_PI;

}

/*komplex számok trigonometriai (ami itt egyenérékű az exponenciális alakkkal) alakból alakít áti
 * alegbrai alakba. Egyenlőre pointerekkel dolgozik, mert az fun, de túl bonyinak tűnik...
 * majd át kell alakítani, hogy rendesn stack-en dolgozzon, return value-vel.
 * A szög fokban értendő, kéőbb szintén válozni fog.*/
void trig_to_alg(komplex *trig, komplex_algebrai *alg){
    alg->Re = trig->r * cos((trig->fi * M_PI) / 180);
    alg->Im = trig->r * sin((trig->fi * M_PI) / 180);
}

/*Összead kettő komplex számot algebrai alakban, és algebrai alakban tér vissza
 * nincs kezelve az eset amikor az szám nem valós szám, később tervezem kezelni.*/
komplex_algebrai osszead(komplex_algebrai szam1, komplex_algebrai szam2){
	komplex_algebrai visszaszam;
	visszaszam.Re = szam1.Re + szam2.Re;
	visszaszam.Im = szam1.Im + szam2.Im;

	return visszaszam;

}

int main(){
	char opcio[1];
    printf("OCIO: ");
    scanf("%c", &opcio[1]);
    while(opcio != 'Q'){
        /* TODO lower to upper*/
        switch (opcio[1]){
        case 'I':
            /* TODO Ide jön a beolvasás*/
            printf("Opcio meg nem letezik(I)");
            break;
        case 'O':
        case 'M':
            /* TODO Ide jön a műveletes rész*/
            printf("Opcio meg nem letezik(O/M)");
            break;
        case 'D':
        case 'A':
            /* TODO ábrázolás rész*/
            printf("Opcio meg nem letezik(D/A)");
            break;
        case 'S':
            /* TODO mentes txt-be*/
            printf("Opcio meg nem letezik(S)");
            break;
        default:
            printf("Ismeretlen input");
            break;
        }
        printf("\nOCIO: ");
        scanf("%c", &opcio[1]);

    }
    printf("itt van.");

    return 0;
}
