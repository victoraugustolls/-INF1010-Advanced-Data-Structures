#include "mapa.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct smapa {
    int chave;
    int conteudo;
    short int bf;
    struct smapa* esq;
    struct smapa* dir;
} Mapa;

static Mapa* cria_no(int c, int novodado);
static Mapa* insere2(Mapa *m, int chave, int novodado, int *flag);
static Mapa* verifica_dir(Mapa *m);
static Mapa* verifica_esq(Mapa *m);
static Mapa* rotaciona_dir(Mapa *m);
static Mapa* rotaciona_esq(Mapa *m);

static Mapa* cria_no(int c, int novodado) {
    Mapa *m = (Mapa*)malloc(sizeof(Mapa));
    if (m != NULL) {
        m->esq = m->dir = NULL;
        m->chave = c;
        m->conteudo = novodado;
        m->bf = 0;
    }
    return m;
}

Mapa* cria() {
    return NULL;
}

Mapa* insere (Mapa* m, int chave, int novodado) {
    int flag = 0;
    return insere2(m, chave, novodado, &flag);
}

static Mapa* insere2(Mapa *m, int chave, int novodado, int *flag) {
    if (m == NULL) {
        m = cria_no(chave, novodado);
        *flag = 1;
    }
    else if (chave < m->chave) {
        m->esq = insere2(m->esq, chave, novodado, flag);
        if (*flag) {
            switch (m->bf) {
                case 1:
                    m->bf = 0;
                    *flag = 0;
                    break;
                case 0:
                    m->bf = -1;
                    break;
                case -1:
                    m = verifica_esq(m);
                    *flag = 0;
                    break;
            }
        }
    }
    else if (chave > m->chave) {
        m->dir = insere2(m->dir, chave, novodado, flag);
        if(*flag) {
            switch (m->bf) {
                case 1:
                    m = verifica_dir(m);
                    *flag = 0;
                    break;
                case 0:
                    m->bf = 1;
                    break;
                case -1:
                    m->bf = 0;
                    *flag = 0;
                    break;
            }
        }
    }
    return m;
}

static Mapa* verifica_esq(Mapa *m) {
    if (m->esq->bf == -1) {
        return rotaciona_dir(m);
    }
    else if (m->esq->bf == 1) {
        m->esq = rotaciona_esq(m->esq);
        return rotaciona_dir(m);
    }
    return NULL;
}

static Mapa* verifica_dir(Mapa *m) {
    if (m->dir->bf == 1) {
        return rotaciona_esq(m);
    }
    else if (m->dir->bf == -1) {
        m->dir = rotaciona_dir(m->dir);
        return rotaciona_esq(m);
    }
    return NULL;
}

static Mapa* rotaciona_dir(Mapa *m) {
    Mapa* esq = m->esq;
    Mapa *x = esq->dir;
    if (x != NULL) {
        m->esq = x;
    }
    else {
        m->esq = NULL;
    }
    esq->dir = m;
    esq->bf = m ->bf = 0;
    return esq;
}

static Mapa* rotaciona_esq(Mapa *m) {
    Mapa* dir = m->dir;
    Mapa *x = dir->esq;
    if (x != NULL) {
        m->dir = x;
    }
    else {
        m->dir = NULL;
    }
    dir->esq = m;
    dir->bf = m->bf = 0;
    return dir;
}

int busca (Mapa *m, int chave) {
    if (m == NULL) {
        return INT_MAX;
    }
    else if (m->chave == chave) {
        return m->conteudo;
    }
    else if (chave < m->chave) {
        return busca(m->esq, chave);
    }
    else if (chave > m->chave) {
        return busca(m->dir, chave);
    }
    else {
        return INT_MAX;
    }
}

Mapa* remove2 (Mapa *m, int chave) {
    if (m == NULL) {
        return NULL;
    }
    else if (chave < m->chave) {
        m->dir = remove2(m->dir, chave);
    }
    else if (chave > m->chave) {
        m->esq = remove2(m->esq, chave);
    }
    else {
        if (m->esq == NULL && m->dir == NULL) {
            free(m);
            return NULL;
        }
        else if (m->dir == NULL) {
            Mapa* aux = m;
            m = m->esq;
            free(aux);
        }
        else if (m->esq == NULL) {
            Mapa* aux = m;
            m = m->dir;
            free(aux);
        }
        else {
            Mapa* aux = m->dir;
            while (aux->esq != NULL) {
                aux = aux->esq;
            }
            m->conteudo = aux->conteudo;
            aux->chave = chave;
            m->dir = remove2(m->dir, chave);
        }
    }
    return m;
}

void destroi (Mapa *m) {
    if (m != NULL) {
        destroi(m->esq);
        destroi(m->dir);
        free(m);
    }
}

void debug_mostra_mapa (Mapa* m) {
    if (m != NULL) {
        printf("Chave: %d / Conteudo: %d / BF: %d\n", m->chave, m->conteudo, m->bf);
        debug_mostra_mapa(m->esq);
        debug_mostra_mapa(m->dir);
    }
}
