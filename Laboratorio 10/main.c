#include "mapa.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {

    Grafo* g = grafoLe("grafo.dat");

    grafoMostra("Arquivo grafo.dat", g);

    grafoPercorreProfundidade(g, 0);

    return 0;
}