#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include "musica.h"

// arvore AVL
typedef struct NoBiblioteca {
    Musica *dados_musica;
    struct NoBiblioteca *esquerda;
    struct NoBiblioteca *direita;
    int altura; 
} NoBiblioteca;

NoBiblioteca* inserir_na_biblioteca(NoBiblioteca *raiz, Musica *musica);
NoBiblioteca* buscar_na_biblioteca(NoBiblioteca *raiz, const char *titulo);

void exibir_biblioteca(NoBiblioteca *raiz);

void liberar_biblioteca(NoBiblioteca *raiz);

#endif