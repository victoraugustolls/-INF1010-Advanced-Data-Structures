#include <stdio.h>
#include <stdlib.h>
#include "listaprio2.h"

struct _listaprio {
	int max; /* tamanho maximo do heap */
	int pos; /* proxima posicao disponivel no vetor */ 
	int* prioridade; /* vetor das prioridades */
	int* ids; /* identificadores do no */
}; 

static void corrige_abaixo (int* prios, int* ids, int atual, int tam);

ListaP* listap_cria(int max) {

	ListaP* heap = (ListaP*)malloc(sizeof(struct _listaprio)); 
	heap->max = max;
	heap->pos = 0;
	heap->prioridade = (int *)malloc(max*sizeof(int));
	heap->ids = (int *)malloc(max*sizeof(int));

	return heap;
}

static void troca(int a, int b, int* v, int *g) {
	
	int f = v[a];
	int e = g[a];
	v[a] = v[b];
	v[b] = f;
	g[a] = g[b];
	g[b] = e;
}

static void corrige_acima(ListaP* heap, int pos) {

	int pai;

	while (pos > 0) {
		pai = (pos-1)/2;

		if (heap->prioridade[pai] > heap->prioridade[pos])
			troca(pos, pai, heap->prioridade, heap->ids);
		else 
			break;

		pos = pai;
	}
}

void listap_insere(ListaP* heap, int prioridade, int dado) {

	if (heap->pos < heap->max) {
		heap->prioridade[heap->pos] = prioridade;
		heap->ids[heap->pos] = dado;
		corrige_acima(heap, heap->pos); 
		heap->pos++;
	} 
	else {
		printf("Heap CHEIO!\n"); 
		exit(1);
	}
}

static void corrige_abaixo(int* prios, int* ids, int atual, int tam){
	
	int pai = atual;
	int filho_esq, filho_dir, filho;

	while (2*pai+1 < tam){

		filho_esq = 2*pai+1;
		filho_dir = 2*pai+2;

		if (filho_dir >= tam) 
			filho_dir = filho_esq;

		if (prios[filho_esq] < prios[filho_dir])
			filho = filho_esq;
		else
			filho = filho_dir;

		if (prios[pai] > prios[filho])
			troca(pai, filho, prios, ids);
		else
			break;

		pai = filho;
  }
}

int listap_remove(ListaP* heap) {

	if (heap->pos > 0) {
		int topo = heap->ids[0];
		heap->prioridade[0] = heap->prioridade[heap->pos-1];
		heap->ids[0] = heap->ids[heap->pos-1];
		heap->pos--;
		corrige_abaixo(heap->prioridade, heap->ids, 0, heap->pos);
		return topo;
	}
	else {
		return -1;
	}
}

void listap_libera (ListaP * h) {

	free(h->prioridade);
	free(h);
}

void debug_listap_show (ListaP *h, char* title){

	int i;
	printf("%s={",title);
	for (i = 0; i < (h->pos); i++)
		printf("(%d, %d),", h->ids[i], h->prioridade[i]);
	printf("}\n");
}

int *cria_listaordenada (ListaP *lp, int* tam){
	
	int num;
	int i;
	int *prios = lp->prioridade;

	*tam = lp->pos;

	for (i = 0; i <* tam; i++) {
		num = listap_remove(lp);
		lp->prioridade[(*tam-1)-i] = num;
	}

	free(lp);
	return prios;
}

void listap_corrige (ListaP* heap, int novaprio, int dado) {

	int pos = 0;
	for (int i = 0; i < heap->pos; i++) {
		if (heap->ids[i] == dado) {
			pos = i;
			break;
		}
	}

	heap->prioridade[pos] = novaprio;
	corrige_acima(heap, pos);
}
