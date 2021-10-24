#include <math.h>
#include <stdio.h>
#define PI 3.141592654

typedef struct komplex_algebrai{
    double Re, Im;
} komplex_algebrai;

typedef struct komplex{
    double r, fi; //Első kötben fokban tárolom a szöget, utána lehet váltani kell radiánra.
} komplex;

void algebrai_to_trig(komplex_algebrai *alg, komplex *trig){
    trig->r = sqrt(alg->Re*alg->Re + alg->Im * alg->Im);
    trig->fi = (atan(alg->Im / alg->Re) * 180) / PI;

}

void trig_to_alg(komplex *trig, komplex_algebrai *alg){
    alg->Re = trig->r * cos((trig->fi * PI) / 180);
    alg->Im = trig->r * sin((trig->fi * PI) / 180);
}

int main(){
    komplex_algebrai kiszam;
    komplex szam;
    scanf("%lf %lf", &kiszam.Re, &kiszam.Im);
    algebrai_to_trig(&kiszam, &szam);
    printf("r=%f fi=%f", szam.r, szam.fi);
    trig_to_alg(&szam, &kiszam);
    printf("Re= %f, Im=%f", kiszam.Re, kiszam.Im);


    return 0;
}