#include "mapa.h"
#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <stdlib.h>

#define TAM 100000

Mapa* preenche (Mapa* m, int inicio, int fim);
void imprimeArvores (Mapa* m1, Mapa* m2);

int main(void) {

    Mapa* mapa1 = cria();
    Mapa* mapa2 = cria();

    // Insercao

    clock_t insert1 = clock();
    for (int i=0; i <= TAM; i++) {
        mapa1 = insere(mapa1, i, 2*i);
    }
    insert1 = clock() - insert1;
    clock_t insert2 = clock();
    mapa2 = preenche(mapa2, 0, TAM);
    insert2 = clock() - insert2;

    double total1 = (double)(insert1) / CLOCKS_PER_SEC;
    double total2 = (double)(insert2) / CLOCKS_PER_SEC;

    printf("Preenchendo: Mapa 1: %.16gs - Mapa 2: %.16gs\n", total1, total2);

    // Busca

    clock_t search11 = clock();
    int hasKey1 = busca(mapa1, TAM-1);
    search11 = clock() - search11;
    if (hasKey1 == INT_MAX) {
        printf("Erro na busca de TAM - 1\n");
        exit(1);
    }

    clock_t search21 = clock();
    int hasKey2 = busca(mapa2, TAM-1);
    search21 = clock() - search21;
    if (hasKey2 == INT_MAX) {
        printf("Erro na busca de TAM - 1\n");
        exit(1);
    }

    total1 = (double)(search11) / CLOCKS_PER_SEC;
    total2 = (double)(search21) / CLOCKS_PER_SEC;

    printf("Busca (TAM - 1): Mapa 1: %.16gs - Mapa 2: %.16gs\n", total1, total2);

    clock_t search12 = clock();
    hasKey1 = busca(mapa1, TAM+1);
    search12 = clock() - search12;
    if (hasKey1 != INT_MAX) {
        printf("Erro na busca de TAM - 1\n");
        exit(1);
    }

    clock_t search22 = clock();
    hasKey2 = busca(mapa2, TAM+1);
    search22 = clock() - search22;
    if (hasKey2 != INT_MAX) {
        printf("Erro na busca de TAM - 1\n");
        exit(1);
    }

    total1 = (double)(search12) / CLOCKS_PER_SEC;
    total2 = (double)(search22) / CLOCKS_PER_SEC;

    printf("Busca (TAM + 1): Mapa 1: %.16gs - Mapa 2: %.16gs\n", total1, total2);

    // imprimeArvores(mapa1, mapa2);

    // Destroi

    clock_t destroy1 = clock();
    destroi(mapa1);
    destroy1 = clock() - destroy1;

    clock_t destroy2 = clock();
    destroi(mapa2);
    destroy2 = clock() - destroy2;

    total1 = (double)(destroy1) / CLOCKS_PER_SEC;
    total2 = (double)(destroy2) / CLOCKS_PER_SEC;

    printf("Destroi: Mapa 1: %.16gs - Mapa 2: %.16gs\n", total1, total2);

    return 0;
}

Mapa* preenche (Mapa* m, int inicio, int fim) {
/* para usar no programa teste com: preenche(meumapa2, 0, TAM) */
  int meio;
  if (inicio > fim) {
      return m;
  }
  meio = (fim+inicio)/2;
  m = insere (m, meio, meio*2);
  m = preenche (m, inicio, meio-1);
  m = preenche (m, meio+1, fim);
  return m;
}

void imprimeArvores (Mapa* m1, Mapa* m2) {

    printf("\nImprime em ordem crescente:\n");
    printf("\nÁrvore 1:\n");
    debug_mostra_mapa(m1);
    printf("\nÁrvore 2:\n");
    debug_mostra_mapa(m2);
}
