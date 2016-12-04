#include "grafo.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{	
	Grafo* g1 = arvoreCustoMinimo("grafo1.dat");
	Grafo* g2 = arvoreCustoMinimo("grafo2.dat");

	printf("Grafo 1:\n");
	printf("Arvore de custo minimo:\n");
	grafoMostra(g1);
	printf("\n");
	printf("Tem ciclo?\n");
	printf("R: %d\n", tem_ciclo("grafo1.dat"));
	printf("\n");
	printf("Numero de componentes conexos:\n");
	printf("R: %d\n", num_componentes("grafo1.dat"));
	printf("\n");
	printf("Numero de nos do maior componente conexo:\n");
	printf("R: %d\n", nv_maior_componente("grafo1.dat"));
	printf("\n");

	printf("*****************************\n\n");

	printf("Grafo 2:\n");
	printf("Arvore de custo minimo:\n");
	grafoMostra(g2);
	printf("\n");
	printf("Tem ciclo?\n");
	printf("R: %d\n", tem_ciclo("grafo2.dat"));
	printf("\n");
	printf("Numero de componentes conexos:\n");
	printf("R: %d\n", num_componentes("grafo2.dat"));
	printf("\n");
	printf("Numero de nos do maior componente conexo:\n");
	printf("R: %d\n", nv_maior_componente("grafo2.dat"));
	printf("\n");

	return 0;
}
