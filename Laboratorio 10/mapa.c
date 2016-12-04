#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <assert.h>
#include "mapa.h"

static void grafoPercorreProfundidade2 (Grafo* grafo, int no_inicial, int* visitados, int tam);

typedef struct _viz Viz;

struct _viz {
	int noj;
	float peso;
	Viz*  prox;
};

struct _grafo {
	int nv;			/* numero de nos ou vertices */
	int na;			/* numero de arestas */
	Viz** viz;		/* viz[i] aponta para a lista de arestas vizinhas do no i */
};


static Viz* criaViz(Viz* head, int noj, float peso) {
	/* insere vizinho no inicio da lista */

	Viz* no = (Viz*)malloc(sizeof(Viz));

	assert(no);

	no->noj = noj;
	no->peso = peso;
	no->prox = head;

	return no;
}

static Grafo* grafoCria(int nv, int na) {

	int i;

	Grafo* g = (Grafo*)malloc(sizeof(Grafo));
	g->nv = nv;
	g->na = na;
	g->viz = (Viz**)malloc(sizeof(Viz*) * nv);

	for (i = 0; i < nv; i++) {
		g->viz[i] = NULL;
	}

	return g;
}


Grafo* grafoLe (char* filename) {
	/* cria grafo nao orientado - supoe que arquivo esta correto! */

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

	fclose(arq);

	return novo;
}

Grafo* grafoLibera (Grafo* grafo) {

	if (grafo) {

		int i = 0;
		Viz* no, *aux;
		for (i = 0; i < grafo->nv; i++) {

			no = grafo->viz[i];

			while (no) {
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

void grafoMostra (char* title, Grafo* grafo) {

	int i;

	if (title) {
		printf("%s\n", title);
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

void grafoPercorreProfundidade (Grafo* grafo, int no_inicial) {

	int* visitados = (int*)malloc(sizeof(grafo->nv));

	printf("{");
	grafoPercorreProfundidade2(grafo, no_inicial, visitados, 0);
	printf("}\n");
}

void grafoPercorreProfundidade2 (Grafo* grafo, int no_inicial, int* visitados, int tam) {

	int j = no_inicial;

	for (int i = 0; i < tam; i++) {
		if (visitados[i] == no_inicial) {
			if (i - 1 >= 0)
				grafoPercorreProfundidade2(grafo, i - 1, visitados, tam);
			else
				return;
		}
	}

	tam++;
	visitados[j] = no_inicial;

	printf("%d, \n", j);

	while (grafo->viz[j] != NULL) {
		grafoPercorreProfundidade2(grafo, j, visitados, tam);
		j++;
	}

}

Grafo* criaArvoreGeradora (Grafo* grafo, int no_inicial) {

  return NULL;
}

void grafoPercorreLargura (Grafo* grafo, int no_inicial) {

}