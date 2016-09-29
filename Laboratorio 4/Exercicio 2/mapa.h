#ifndef _MAPA_H
#define _MAPA_H

typedef struct smapa Mapa;

Mapa* cria (void);
Mapa* insere (Mapa* m, int chave, int novodado);
int busca (Mapa *m, int chave);
void destroi (Mapa *m);
void debug_mostra_mapa(Mapa *m);

typedef struct smapa Mapa;

#endif
