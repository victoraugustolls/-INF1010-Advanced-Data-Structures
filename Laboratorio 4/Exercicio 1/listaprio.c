#include <stdio.h>
#include <stdlib.h>
#include "listaprio.h"

struct _listaprio {
    int max; /* tamanho maximo do heap */
    int pos; /* proxima posicao disponivel no vetor */
    int* prioridade; /* vetor das prioridades */
};

static void listap_monta (ListaP* heap, int n, int *prios);

ListaP* listap_cria(int max, int qtos, int* iniciais){
    ListaP* heap=(ListaP*)malloc(sizeof(struct _listaprio)); heap->max=max;
    heap->pos=0;
    heap->prioridade=(int *)malloc(max*sizeof(int));
    if (qtos>0) {
        listap_monta(heap, qtos, iniciais);
        // printf ("criação com valores iniciais ainda não foi implementada! \n");
        // exit(1);
    }
    return heap;
}

static void troca(int a, int b, int* v) {
    int f = v[a];
    v[a] = v[b];
    v[b] = f;
}

static void corrige_acima(ListaP* heap, int pos) {
    int pai;
    while (pos > 0){
        pai = (pos-1)/2;
        if (heap->prioridade[pai] < heap->prioridade[pos])
            troca(pos,pai,heap->prioridade);
        else
            break;
        pos=pai;
    }
}

void listap_insere(ListaP* heap, int prioridade) {
    if ( heap->pos < heap->max ) {
        heap->prioridade[heap->pos]=prioridade;
        corrige_acima(heap,heap->pos);
        heap->pos++;
    }
    else {
        printf("Heap CHEIO!\n");
        exit(1);
    }
}

static void corrige_abaixo(ListaP* heap, int pos){
    int pai = pos;
    while (2*pai+1 < heap->pos){
        int filho_esq=2*pai+1;
        int filho_dir=2*pai+2;
        int filho;
        if (filho_dir >= heap->pos) filho_dir=filho_esq;
        if (heap->prioridade[filho_esq]>heap->prioridade[filho_dir])
            filho=filho_esq;
        else
            filho=filho_dir;
        if (heap->prioridade[pai]<heap->prioridade[filho])
            troca(pai,filho,heap->prioridade);
        else
            break;
        pai=filho;
    }
}

int listap_remove(ListaP* heap) {
    if (heap->pos>0) {
        int topo=heap->prioridade[0];
        heap->prioridade[0]=heap->prioridade[heap->pos-1];
        heap->pos--;
        corrige_abaixo(heap, 0);
        return topo;
    }
    else {
        printf("Heap VAZIO!");
        return -1;
    }
}

void listap_libera (ListaP * h) {
    free(h->prioridade);
    free( h );
}

void debug_listap_show (ListaP *h, char* title){
	int i;
	printf("%s={",title);
	for (i=0; i<(h->pos); i++)
		printf("%d,",h->prioridade[i]);
	printf("}\n");
}

static void listap_monta (ListaP* heap, int n, int *prios) {
    int tamanhoInicial = n/2 + 1;
    int tamanhoFinal = n/2 - 1;
    for (int i = 0; i < n; i++) {
        heap->prioridade[i] = prios[i];
        heap->pos++;
    }
    for (int i = tamanhoFinal; i > 0 ; i--) {
        corrige_abaixo(heap, i);
    }
}

int *cria_listaordenada (ListaP *lp, int* tam) {
    int temp;
    int *ordenada;

    for (int i = 0; i < ((*tam) - 1); i++) {
        temp = listap_remove(lp);
        lp->prioridade[(*tam)-1-i] = temp;
    }
    ordenada = lp->prioridade;
    listap_libera(lp);

    return ordenada;
}

int *meuheapsort (int nums[], int tam) {
    ListaP *lp = listap_cria (tam, tam, nums);
    int *novosnums = cria_listaordenada (lp, &tam);
    return novosnums;
}
