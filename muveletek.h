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

/*komplex számokat alakít át algebrai alakból, trigonometrikusba (ami itt egyenértékű
 * az exponenciálissal). egyenlőre pointerből pointerbe dolgozik, de ezen később
 * valószínűleg válotoztatni kell.
 * A szög fokban értendő, kéőbb szintén válozni fog.*/
komplex algebrai_to_trig(komplex_algebrai *alg);

/*komplex számok trigonometriai (ami itt egyenérékű az exponenciális alakkkal) alakból alakít áti
 * alegbrai alakba. Egyenlőre pointerekkel dolgozik, mert az fun, de túl bonyinak tűnik...
 * majd át kell alakítani, hogy rendesn stack-en dolgozzon, return value-vel.
 * A szög fokban értendő, kéőbb szintén válozni fog.*/
komplex_algebrai trig_to_alg(komplex *trig);

/*Összead kettő komplex számot algebrai alakban, és algebrai alakban tér vissza
 * nincs kezelve az eset amikor az szám nem valós szám, később tervezem kezelni.*/
komplex_algebrai osszead(komplex_algebrai szam1, komplex_algebrai szam2);

/*Kivon kettő komplex számot algebrai alakban, és algebrai alakban tér vissza*/
//komplex_algebrai kivon(komplex_algebrai kisebbitendo, komplex_algebrai kivonando);
//ez most kommentelt meg valszeg a header file-ba nem is kell ezeket beleírni, mert abban lesz egy fv
//amit a main hív meg a M/O gombra, és az hívogatja meg őket, szóval a main nem is használja.

#endif