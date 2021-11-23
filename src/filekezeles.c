#include <stdio.h>
#include <stdbool.h>

//#include "debugmalloc.h"
#include "beolvasas.h"
#include "filekezeles.h"
#include "muveletek.h"

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
        //printf("%c", alak);
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
            perror("Hibas file, alak hiba, szam atugrasa");
        }
    }
    fclose(fp);
    //kiir(*fej);
    return true;
}

bool abrazol(komplex *fej){
    FILE *fp;
    fp = fopen("szamsik.svg", "w");
    if (fp == NULL){
        perror("Nem sikerult megnyitni/letrehozni a file-t");
        return false;
    }
    fprintf(fp, "<svg width='200' height='200' xmlns='http://www.w3.org/2000/svg' version='1.1'>\n");

    /*kód*/

    fprintf(fp, "\n</svg>");
    fclose(fp);
    return true;
}