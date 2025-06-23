#ifndef FILA_H
#define FILA_H

#include "musica.h"

// fila
typedef struct NoFila {
    Musica* dados_musica;
    struct NoFila* proximo;
} NoFila;

typedef struct {
    NoFila* inicio;
    NoFila* fim; 
} Fila;

Fila* criar_fila();
void enfileirar(Fila* f, Musica* m);
Musica* desenfileirar(Fila* f);
int fila_esta_vazia(const Fila* f);
void exibir_fila(const Fila* f);
void liberar_fila(Fila* f);

#endif