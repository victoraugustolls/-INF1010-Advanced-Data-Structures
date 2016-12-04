#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <assert.h>
#include <limits.h>
#include "grafo.h"
#include "listaprio2.h"

typedef struct _viz Viz;
struct _viz {
  int noj;
  float peso;
  Viz*  prox;
};

struct _grafo {
  int nv;           /* numero de nos ou vertices */
  int na;           /* numero de arestas */
  Viz** viz;         /* viz[i] aponta para a lista de arestas vizinhas do no i */
};

/* aux para fila e pilha */
typedef struct _sq SQ;
struct _sq {
  int info;
  SQ* prox;
};


static SQ* push(SQ* stack, int info){
/* empilha um item */
	SQ* novo = (SQ*)malloc(sizeof(SQ));
	assert(novo);
	novo->info = info;
	novo->prox = stack;
	return novo;
}

static SQ* enqueue(SQ* queue, int info){
/* enfileira um item */
	SQ* novo = (SQ*)malloc(sizeof(SQ));
	SQ* aux = queue;
	assert(novo);
	novo->info = info;
	novo->prox = NULL;
	if (!queue){
		return novo;
	}
	while (aux->prox){
		aux = aux->prox;
	}
	aux->prox = novo;

	return queue;
}

static SQ* pop(SQ* stack,int* popped_info){
/* retira um item da fila/pilha */
	SQ* libera;

	if (!stack) {
		*popped_info = -1;
		return NULL;
	}

	*popped_info = stack->info;
	libera = stack;
	stack = stack->prox;

	free(libera);

	return stack;
}

static Viz* criaViz(Viz* head, int noj, float peso) {
/* insere vizinho no inicio da lista */
	Viz* no = (Viz*) malloc(sizeof(Viz));
	assert(no);

	no->noj = noj;
	no->peso = peso;
	no->prox = head;

	return no;
}

static Grafo* grafoCria(int nv, int na) {

	int i;
	Grafo* g = (Grafo *) malloc(sizeof(Grafo));
	g->nv = nv;
	g->na = na;
	g->viz = (Viz **) malloc(sizeof(Viz *) * nv);
	for (i = 0; i < nv; i++)
		g->viz[i] = NULL;
	return g;
}


Grafo* grafoLe( char* filename ) {
/* cria grafo nÃ£o orientado - supÃµe que arquivo estÃ¡ correto! */

	FILE *arq = fopen(filename,"rt");
	int nv, na, no1, no2 = 0;
	float peso;
	Grafo* novo;
	
	fscanf(arq, "%d %d", &nv, &na);
	novo = grafoCria(nv, na);
	assert(novo);
	while (fscanf(arq, "%d %d %f", &no1, &no2, &peso) == 3) {
		novo->viz[no1] = criaViz(novo->viz[no1], no2, peso);
		novo->viz[no2] = criaViz(novo->viz[no2], no1, peso);
	}
	return novo;
}

Grafo* grafoLibera(Grafo* grafo) {
	if (grafo) {
		int i = 0;
		Viz* no,*aux;
		for (i = 0; i < grafo->nv; i++){
			no = grafo->viz[i];
			while (no){
				aux = no->prox;
				free(no);
				no = aux;
			}
		}
		free(grafo->viz);
		free(grafo);
  	}
  return NULL;
}

void grafoMostra (char* title, Grafo * grafo) {
  	int i;

	if (title) {
		printf("%s", title);
	}

  	if (grafo) {

		printf("NV: %d, NA: %d\n", grafo->nv, grafo->na);

		for (i = 0; i < grafo->nv; i++){
			Viz* viz = grafo->viz[i];
			printf("[%d]->", i);

			while (viz) {
				printf("{%d, %g}->", viz->noj, viz->peso);
				viz = viz->prox;
			}

			printf("NULL\n");
		}
	}
}

void grafoPercorreProfundidade(Grafo *grafo, int no_inicial){

}

Grafo* criaArvoreGeradora (Grafo *grafo, int no_inicial) {
  return NULL;
}

void grafoPercorreLargura(Grafo *grafo, int no_inicial) {

	int *visitados = (int*) malloc(grafo->nv * sizeof(int));
	int j;

	SQ* fila = NULL;
	Viz* viz;

	for (int i = 0; i < grafo->nv; i++)
		visitados[i] = 0;

	fila = enqueue(fila, no_inicial);
	visitados[no_inicial] = 1;
	fila = pop(fila, &j);

	while(j != -1)
	{
		viz = grafo->viz[j];
		printf("%d, ", j);
		while(viz != NULL)
		{
			if (!visitados[viz->noj])
			{
				fila = enqueue(fila, viz->noj);
				visitados[viz->noj] = 1;	
			}
			viz = viz->prox;
		}
		fila = pop(fila, &j);
	}
	printf("\n\n");
} 

int* menoresCaminhos(Grafo* grafo, int noinicial) {

    int no = noinicial;

    Viz * viz = grafo->viz[noinicial];
    ListaP * heap = listap_cria(grafo->nv);

    int * percurso = (int *)malloc((grafo->nv + 1) * sizeof(int));
    int * visitados = (int *)malloc(grafo->nv * sizeof(int));

    for (int i = 0; i < grafo->nv; i++) {
    	visitados[i] = 0;
    	percurso[i] = INT_MAX;
    	if (i != noinicial) {
    		listap_insere(heap, INT_MAX, i);
    	}
    }
    percurso[noinicial] = 0;
    visitados[noinicial] = 1;
    percurso[grafo->nv] = -1;

	for(int i = 0; i < grafo->nv; i++) {
		while(viz != NULL) {
			if (!visitados[viz->noj]) {
				int peso = viz->peso + percurso[no];
				if (percurso[viz->noj] > peso) {
					percurso[viz->noj] = peso;
					listap_corrige(heap, peso, viz->noj);
				}
			}
			viz = viz->prox;
		}
		visitados[no] = 1;
		no = listap_remove(heap);
		viz = grafo->viz[no];
    }
    
    return percurso;
}

