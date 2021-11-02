#ifndef BEOLVASAS_H
#define BEOLVASAS_H

typedef struct DinTomb{
    int meret;
    char *tomb;
} DinTomb;

typedef struct komplex_algebrai{
    int az;
    double Re, Im;
} komplex_algebrai;

typedef struct komplex{
    int az;
    double r, fi; //Első körben fokban tárolom a szöget, utána lehet váltani kell radiánra.
} komplex;

#endif