#ifndef MUVELETEK_H
#define MUVELETEK_H

// typedef struct komplex_algebrai{
//     int az;
//     double Re, Im;
// } komplex_algebrai;

// typedef struct komplex{
//     int az;
//     double r, fi; //Első körben fokban tárolom a szöget, utána lehet váltani kell radiánra.
// } komplex;


void nagybetube(char *c);
void muvelet(komplex **fej);
komplex_algebrai trig_to_alg(komplex *trig);
komplex_trig algebrai_to_trig(komplex_algebrai alg);


#endif