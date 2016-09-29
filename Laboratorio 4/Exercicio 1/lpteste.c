#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "listaprio.h"

int compara (const void* a, const void* b);
void testa_com_arquivo(char* nome);

int main(void) {
    testa_com_arquivo("entrada-1000-cresce");
    testa_com_arquivo("entrada-1000-decresce");
    testa_com_arquivo("entrada-1000-troca");
    testa_com_arquivo("entrada-10000-cresce");
    testa_com_arquivo("entrada-10000-decresce");
    testa_com_arquivo("entrada-10000-troca");
    testa_com_arquivo("entrada-100000-cresce");
    testa_com_arquivo("entrada-100000-decresce");
    testa_com_arquivo("entrada-100000-troca");
    testa_com_arquivo("entrada-1000000-cresce");
    testa_com_arquivo("entrada-1000000-decresce");
    testa_com_arquivo("entrada-1000000-troca");

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

void testa_com_arquivo(char* nome) {

    printf("Início do teste com arquivo %s\n", nome);

    int i,n=8;
    int quantidade;

    int info, v[]={25, 48, 37, 12, 57, 86, 33, 92};

    FILE *vector;

    vector = fopen(nome, "r");

    if (vector == NULL) {
        printf("Error opening vector.txt file!\n");
        exit(1);
    }

    if (fscanf(vector, "%d", &quantidade) == 1) {
        printf("Quantidade de entradas: %d\n", quantidade);
    }

    int *entradas = (int*)malloc(sizeof(int)*quantidade);
    int *entradas2 = (int*)malloc(sizeof(int)*quantidade);
    for (int j = 0; j < quantidade; j++) {
        fscanf(vector, "%d", &entradas[j]);
    }
    for (int j = 0; j < quantidade; j++) {
        entradas2[j] = entradas[j];
    }
    // for (int j = 0; j < quantidade; j++) {
    //     printf("Q: %d | H: %d\n", entradas[j], entradas2[j]);
    // }

    fclose(vector);

    clock_t t1 = clock();
    ListaP *lp1 = listap_cria(10000000, 0, NULL);
    for (int i = 0; i < quantidade; i++) {
        listap_insere(lp1, entradas[i]);
    }
    t1 = clock() - t1;

    clock_t t2 = clock();
    ListaP *lp2 = listap_cria(10000000, quantidade, entradas2);
    t2 = clock() - t2;

    double total1 = (double)t1 / CLOCKS_PER_SEC;
    double total2 = (double)t2 / CLOCKS_PER_SEC;

    printf("Inserir: %.16g - Criar: %.16g\n", total1, total2);

    listap_libera(lp1);
    // listap_libera(lp2);

    t1 = clock();
    qsort(entradas, quantidade, sizeof(int), compara);
    t1 = clock() - t1;

    t2 = clock();
    int *ordenada = cria_listaordenada(lp2, &quantidade);//meuheapsort(entradas2, quantidade); //cria_listaordenada(lp2, &n);
    t2 = clock()-t2;

    total1 = (double)t1 / CLOCKS_PER_SEC;
    total2 = (double)t2 / CLOCKS_PER_SEC;

    // for (int j = 0; j < quantidade; j++) {
    //     printf("Q: %d | H: %d\n", entradas[j], entradas2[j]);
    // }

    printf("quick: %.16g - heap: %.16g\n", total1, total2);

    printf("Fim do teste com arquivo %s\n\n", nome);
}
