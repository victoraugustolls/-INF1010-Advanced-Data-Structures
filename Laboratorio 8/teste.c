#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <stdlib.h>
#include "mapa.h"

#define TAM 15

int main(void) {

    int i;

    Mapa *mapa1 = cria();

    printf ("Insercao sempre a esquerda:\n");

    for (i = TAM-1; i >= 0; i--) {
        mapa1 = insere (mapa1, i, i);
    }
    
    debug_mostra_mapa(mapa1);

    return 0;
}
