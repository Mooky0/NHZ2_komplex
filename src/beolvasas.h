#ifndef BEOLVASAS_H
#define BEOLVASAS_H
#include <stdbool.h>


typedef struct komplex_algebrai{
    int az;
    double Re, Im;
} komplex_algebrai;

typedef struct komplex_trig{
    int az;
    double r, fi;
} komplex_trig;

//struktúra amelyben linked list-ben táoljuk a számokat.
typedef struct komplex{
    int az;
    double r, fi;
    struct komplex *kov;
} komplex;


void beolvasas(komplex **fej);
void felszabadit(komplex *fej);
//void nagybetube(char *c);
komplex *hozzafuz(komplex *fej, double r, double fi);
void kiir(komplex *fej);
komplex *kiirutolso(komplex *fej);

#endif