#include <stdio.h>
#include <stdbool.h>

//#include "debugmalloc.h"
#include "beolvasas.h"
#include "filekezeles.h"
#include "muveletek.h"


/*Mentés függvény. a "szamok.txt"-be menti el a program az aktuálisan tárolt számokat.
* Paramétere: fej, lista elejére mutató pointer, a fv nem változtatja, ezért csak komplex*
* visszatérési értéke bool. true ha sikeres, false ha nem, pl nincs a mappában írási engedélyünk.
* Az alakhoz a "T"-t írja mindenhova, hiszen, csak trigonometrikus alakban tároljuk a számokat. 
* A függvényt csak a main hívja meg a megfelelő parancsra.*/
bool mentes(komplex *fej){
    FILE* fp;
    fp = fopen("szamok.txt", "w");
    if (fp != NULL){
        komplex *mozgo = fej;
        while (mozgo != NULL){
            fprintf(fp, "T %x %f %f\n", mozgo->az, mozgo->r, mozgo->fi); //itt a "T" hardcodeolva van, mert az összes számot T alakban tárolom, a beolvasásnál az A alak is kezelve van.
            mozgo = mozgo->kov;
        }
        fclose(fp);
        return true;
    }
    else{
        perror("Nem sikerult megnyitni a file-t.");
        return false;
    }
}

/*Beolvasas, a "szamok.txt"-ből olvassa be az oda mentett számokat. A fileban
* lévő azonosítókat felülírja a program. A beolvasasánál lekezeli, ha a szám algebrai alakban van mentve.
* visszatérési értéke: bool, a beolvasás sikerességéről, true ha sikeres, false ha nem.
* paramétere: a fejre mutató pointer, mert akár felül is kell írnia azt.
* A függvényt csak a beolvasás hívja meg a megfelelő parancsra.*/
bool filebeolvas(komplex **fej){
    FILE *fp;
    fp = fopen("szamok.txt", "r");
    if (fp == NULL){
        perror("Nem sikerult megnyitni a file-t.");
        return false;
    }
    char alak;
    int az;
    double egy, ketto;
    while(feof(fp) == 0){
        fscanf(fp, " %c %x %lf %lf\n", &alak, &az, &egy, &ketto);
        if (alak == 'T'){
            *fej = hozzafuz(*fej, egy, ketto);
        }
        else if (alak == 'A'){
            komplex_algebrai szam1;
            szam1.az = az;
            szam1.Re = egy;
            szam1.Im = ketto;
            komplex_trig szam = algebrai_to_trig(szam1);
            *fej = hozzafuz(*fej, szam.r, szam.fi);
        }
        else{
            perror("Hibas file, alak hiba, szam atugrasa.");
        }
    }
    fclose(fp);
    return true;
}

/*Ábrázolás
* ábrázolás svg-be "szamsik.svg"-be ábrázol a, mindenképpen felülírja azt, tehát ábrázolás után csak
* az aktuálisan tárolt számokat látjuk ábrázolva. 
* Visszatérési értéke bool. false, ha nem sikerült megnyitni a file-t, true, ha sikeres a kiírás.
* paramétere: a fej, nem írja felül azt, csak olvassa.*/
bool abrazol(komplex *fej){
    FILE *fp;
    fp = fopen("szamsik.svg", "w");
    if (fp == NULL){
        perror("Nem sikerult megnyitni/letrehozni a file-t");
        return false;
    }

    /*Alap számsík rajzolása*/
    fprintf(fp, "<svg width='600' height='600' xmlns='http://www.w3.org/2000/svg' version='1.1'>\n<line style=\"stroke:#000000;\" x1=\"300\" y1=\"0\" x2=\"300\" y2=\"600\" />\n<line style=\"stroke:#000000;\" x1=\"0\" y1=\"300\" x2=\"600\" y2=\"300\" />\n<text x=\"301\" y=\"310\" font-size=\"10\">Origo</text>\n<text x=\"580\" y=\"310\" font-size=\"10\">Re</text>\n<text x=\"301\" y=\"10\" font-size=\"10\">Im</text>\n");

    for (int i=1; i<10; i++){
        fprintf(fp, "<line style=\"stroke:#FF0000;\" x1=\"%d\" y1=\"295\" x2=\"%d\" y2=\"305\"/>\n<text x=\"%d\" y=\"315\" font-size=\"8\">%d</text>\n", (300 + i * 30), (300 + i * 30), (298 + i * 30), i);
    }

    for (int i=1; i<10; i++){
        fprintf(fp, "<line style=\"stroke:#FF0000;\" x1=\"295\" y1=\"%d\" x2=\"305\" y2=\"%d\"/>\n<text x=\"289\" y=\"%d\" font-size=\"8\">%d</text>\n", (300 - i * 30), (300 - i * 30), (302 - i * 30), i);
    }

    /*számok ábrázolása, algebrai alakba alakítás és ábrázolás*/
    komplex *mozgo = fej;
    while (mozgo != NULL){
        komplex_algebrai szam = trig_to_alg(mozgo);
        double x = (szam.Im * 30) + 300;
        double y = 300 - (szam.Re * 30);
        fprintf(fp, "<line style=\"stroke:#d14508;\" x1=\"300\" y1=\"300\" x2=\"%f\" y2=\"%f\"/>\n", x, y);
        fprintf(fp, "<text x=\"%f\" y=\"%f\" font-size=\"8\">%x</text>\n    ", x, y, szam.az);
        mozgo = mozgo->kov;
    }


    fprintf(fp, "\n</svg>");
    fclose(fp);
    return true;
}