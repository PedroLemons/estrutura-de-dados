#ifndef PILHA_H
#define PILHA_H

#include "musica.h"

// pilha
typedef struct NoPilha {
    Musica* dados_musica;
    struct NoPilha* proximo;
} NoPilha;

typedef struct {
    NoPilha* topo;
} Pilha;

Pilha* criar_pilha();
// push e pop
void empilhar(Pilha* p, Musica* m); 
Musica* desempilhar(Pilha* p);

int pilha_esta_vazia(const Pilha* p);
void exibir_pilha(const Pilha* p);
void liberar_pilha(Pilha* p);

#endif