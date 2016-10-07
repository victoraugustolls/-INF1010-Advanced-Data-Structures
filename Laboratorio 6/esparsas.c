#include "esparsas.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct smatrix {
    int l, c; /* número de linhas e colunas */
    int nelems;
    int *vals;
    int *cols;
    int *ri;
} tsm;

tsm* createFromFile (FILE *h) {

    int linhas, colunas, num_elementos;
    int linha, coluna, valor;

    tsm *matriz = (tsm*)malloc(sizeof(tsm));

    fscanf(h, "%d %d", &linhas, &colunas);
    fscanf(h, "%d", &num_elementos);

    matriz->l = linhas;
    matriz->c = colunas;
    matriz->nelems = num_elementos;

    matriz->vals = (int*)malloc(num_elementos*sizeof(int));
    matriz->cols = (int*)malloc(num_elementos*sizeof(int));
    matriz->ri = (int*)malloc(linhas*sizeof(int));

    for (int i = 0; i < linhas; i++) {
        matriz->ri[i] = -1;
    }

    for (int i = 0; i < num_elementos; i++) {
        fscanf(h, "%d %d %d", &linha, &coluna, &valor);
        matriz->vals[i] = valor;
        matriz->cols[i] = coluna;
        if (matriz->ri[linha] == -1) {
            matriz->ri[linha] = i;
        }
    }

    printf("Numero de linhas: %d\n", matriz->l);
    printf("Numero de colunas: %d\n", matriz->c);
    printf("Numero de elementos: %d\n", matriz->nelems);

    printf("Valores: ");
    for (int i = 0; i < num_elementos; i++) {
        printf("%d ", matriz->vals[i]);
    }
    printf("\n");

    printf("Colunas: ");
    for (int i = 0; i < num_elementos; i++) {
        printf("%d ", matriz->cols[i]);
    }
    printf("\n");

    printf("Linhas: ");
    for (int i = 0; i < linhas; i++) {
        printf("%d ", matriz->ri[i]);
    }
    printf("\n");

    return matriz;
}

int* matrixvectormult (tsm* a, int *b, int tamb) {

    if (a->c != tamb) {
        return NULL;
    }

    int linhas = a->l;
    int j = 0;

    int* result = (int*)malloc(linhas*sizeof(int));
    for (int i = 0; i < linhas; i++) {
        result[i] = 0;
    }

    int offset = 0;
    for (int i = 0; i < linhas; i++) {
        if (a->ri[i+1] != -1) {
            for (; j < a->ri[i+1]; j++) {
                result[i-offset] += a->vals[j] * b[a->cols[j]];
            }
            offset = 0;
        }
        else {
            offset++;
        }
        if (i == linhas - 1) {
            for (; j < a->nelems; j++) {
                result[i] += a->vals[j] * b[a->cols[j]];
            }
        }
    }

    return result;
}
