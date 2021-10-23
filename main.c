#include <math.h>

typedef struct komplex_algebrai{
    double Re, Im;
} komplex_algebrai;

typedef struct komplex_trig{
    double r, fi; //Első kötben fokban tárolom a szöget, utána lehet váltani kell radiánra. inkább radiánban kezdek.
} komplex_trig;

void trig_to_algebrai(komplex_trig *trig, komplex_algebrai *alg){
    trig->r = sqrt(alg->Re*alg->Re + alg->Im * alg->Im);
    trig->fi = atan(alg->Re / alg->Im);

}

int main(){



    return 0;
}