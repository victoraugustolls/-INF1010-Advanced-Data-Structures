#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "listaprio.h"

int compara (const void* a, const void* b);

int main(void) {
    int i;
    int quantidade;

    int info, v[]={25, 48, 37, 12, 57, 86, 33, 92};

    // ListaP* lp = listap_cria(30, 0, NULL);

    FILE *vector;

    vector = fopen("vector.txt", "r");

    if (vector == NULL) {
        printf("Error opening vector.txt file!\n");
        exit(1);
    }

    if (fscanf(vector, "%d", &quantidade) == 1) {
        printf("Quantidade de entradas: %d\n", quantidade);
    }

    int *entradas = (int*)malloc(sizeof(int)*quantidade);
    for (int j = 0; j < quantidade; j++) {
        fscanf(vector, "%d", &entradas[j]);
    }

    fclose(vector);

    clock_t t1 = clock();
    ListaP *lp1 = listap_cria(2000, 0, NULL);
    for (int i = 0; i < quantidade; i++) {
        listap_insere(lp1, entradas[i]);
        // debug_listap_show(lp1, "lp1 = ");
    }
    t1 = clock() - t1;

    clock_t t2 = clock();
    ListaP *lp2 = listap_cria(2000, quantidade, entradas);
    t2 = clock() - t2;
    debug_listap_show(lp2, "lp2 = ");

    double total1 = (double)t1 / CLOCKS_PER_SEC;
    double total2 = (double)t2 / CLOCKS_PER_SEC;

    printf("Inserir: %.16g - Criar: %.16g\n", total1, total2);

    listap_libera(lp1);

    t1 = clock();
    qsort(entradas, quantidade, sizeof(int), compara);
    t1 = clock() - t1;

    t2 = clock();
    int *ordenada = cria_listaordenada(lp2, &quantidade);
    t2 = clock() - t2;

    for (int j = 0; j < quantidade; j++) {
        printf("%d\n", ordenada[j]);
    }

    total1 = (double)t1 / CLOCKS_PER_SEC;
    total2 = (double)t2 / CLOCKS_PER_SEC;

    printf("quick: %.16g - heap: %.16g\n", total1, total2);

    // for (i=0;i<n;i++) {
    //     listap_insere(lp,v[i]);
    //     printf("insere %d, ", v[i]);
    //     debug_listap_show(lp, "lp=");
    // }
    //
    // do {
    //     info = listap_remove(lp);
    //     printf("remove %d ", info);
    //     debug_listap_show(lp, "lp=");
    // } while(info>0);
    //
    // ListaP* lp2 = listap_cria(30, n, v);
    // debug_listap_show(lp2, "lp2=");
    //
    // listap_libera(lp);
    return 0;
}

int compara (const void* a, const void* b) {
    int *ia = (int*)a;
    int *ib = (int*)b;
    if (*ia>*ib)
        return 1;
    else if (*ib>*ia)
        return -1;
    else
        return 0;
}
