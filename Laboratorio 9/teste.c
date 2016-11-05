#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "mapa.h"

int main(int argc, char** argv) {

    Mapa *mapa1 = cria();

    printf("Insere 10\n");
    mapa1 = insere(mapa1, 10);
    debug_mostra_mapa(mapa1);
    printf("Insere 15\n");
    mapa1 = insere(mapa1, 15);
    debug_mostra_mapa(mapa1);
    printf("Insere 6\n");
    mapa1 = insere(mapa1, 6);
    debug_mostra_mapa(mapa1);
    printf("Insere 11\n");
    mapa1 = insere(mapa1, 11);
    debug_mostra_mapa(mapa1);
    printf("Insere 12\n");
    mapa1 = insere(mapa1, 12);
    debug_mostra_mapa(mapa1);
    printf("Insere 8\n");
    mapa1 = insere(mapa1, 8);
    debug_mostra_mapa(mapa1);
    printf("Insere 9\n");
    mapa1 = insere(mapa1, 9);
    debug_mostra_mapa(mapa1);
    printf("Insere 14\n");
    mapa1 = insere(mapa1, 14);
    debug_mostra_mapa(mapa1);
    printf("Insere 16\n");
    mapa1 = insere(mapa1, 16);
    debug_mostra_mapa(mapa1);
    printf("Insere 17\n");
    mapa1 = insere(mapa1, 17);
    debug_mostra_mapa(mapa1);
    printf("Insere 18\n");
    mapa1 = insere(mapa1, 18);
    debug_mostra_mapa(mapa1);

    printf("Busca 7\n");
    printf("%d\n",busca(mapa1, 7));
    printf("Busca 13\n");
    printf("%d\n",busca(mapa1, 13));
    printf("Busca 10\n");
    printf("%d\n",busca(mapa1, 10));
    printf("Busca 8\n");
    printf("%d\n",busca(mapa1, 8));
    printf("Busca 6\n");
    printf("%d\n",busca(mapa1, 6));
    printf("Busca 2\n");
    printf("%d\n",busca(mapa1, 2));


    printf("Retira 8\n");
    mapa1 = retira(mapa1, 8);
    debug_mostra_mapa(mapa1);
    printf("Retira 16\n");
    mapa1 = retira(mapa1, 16);
    debug_mostra_mapa(mapa1);
    printf("Retira 17\n");
    mapa1 = retira(mapa1, 17);
    debug_mostra_mapa(mapa1);
    printf("Retira 14\n");
    mapa1 = retira(mapa1, 14);
    debug_mostra_mapa(mapa1);
    printf("Retira 11\n");
    mapa1 = retira(mapa1, 11);
    debug_mostra_mapa(mapa1);
    printf("Retira 12\n");
    mapa1 = retira(mapa1, 12);
    debug_mostra_mapa(mapa1);
    printf("Retira 10\n");
    mapa1 = retira(mapa1, 10);
    debug_mostra_mapa(mapa1);
    printf("Retira 9\n");
    mapa1 = retira(mapa1, 9);
    debug_mostra_mapa(mapa1);
    
    destroi(mapa1);

    return 0;
}

// void quebraAbstracao(Mapa* m) {
//     printf("[\n");
//     imprimeCrescente(m);
//     printf("]\n");
// }
// void imprimeCrescente(Mapa* m) {
//     if(m == NULL) {
//         return;     
//     } 

//     imprimeCrescente(m->esq);
//     printf("%d - ", m->kp);
//     imprimeCrescente(m->meio);

//     if(m->kg != -1) {
//         printf("%d - ", m->kg);
//         imprimeCrescente(m->dir);    
//     }
// }

