#ifndef BEOLVASAS_H
#define BEOLVASAS_H
#include <stdbool.h>


typedef struct komplex_algebrai{
    int az;
    double Re, Im;
} komplex_algebrai;

// typedef struct komplex{
//     int az;
//     double r, fi; //Első körben fokban tárolom a szöget, utána lehet váltani kell radiánra.
// } komplex;

// typedef struct DinTomb{
//     int utolso_az; //0x1A0-től indul a számolás, mert a spec-ben ez van, és mert akkor nehezebb összekeverni mással.
//     int meret;
//     komplex *adat;
// } DinTomb;

typedef struct komplex{
    int az;
    double r, fi;
    struct komplex *kov;
} komplex;


void beolvasas(komplex **fej);
void felszabadit(komplex *fej);
void nagybetube(char *c);

#endif