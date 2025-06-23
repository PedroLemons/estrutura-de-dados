#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

static int altura(NoBiblioteca *no) {
    if (no == NULL) return 0;
    return no->altura;
}

static int max(int a, int b) {
    return (a > b) ? a : b;
}

static NoBiblioteca* criar_na_biblioteca(Musica *musica) {
    NoBiblioteca* no = (NoBiblioteca*) malloc(sizeof(NoBiblioteca));
    no->dados_musica = musica;
    no->esquerda = NULL;
    no->direita = NULL;
    no->altura = 1; 
    return no;
}

static int obter_balanceamento(NoBiblioteca *no) {
    if (no == NULL) return 0;
    return altura(no->esquerda) - altura(no->direita);
}

// rotacoes dos nós - arvore binaria
static NoBiblioteca* rotacao_direita(NoBiblioteca *y) {
    NoBiblioteca *x = y->esquerda;
    NoBiblioteca *T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;

    return x;
}

static NoBiblioteca* rotacao_esquerda(NoBiblioteca *x) {
    NoBiblioteca *y = x->direita;
    NoBiblioteca *T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;

    return y;
}


NoBiblioteca* inserir_na_biblioteca(NoBiblioteca* raiz, Musica* musica) {
    if (raiz == NULL) {
        return criar_na_biblioteca(musica);
    }
    if (strcmp(musica->titulo, raiz->dados_musica->titulo) < 0) {
        raiz->esquerda = inserir_na_biblioteca(raiz->esquerda, musica);
    } else if (strcmp(musica->titulo, raiz->dados_musica->titulo) > 0) {
        raiz->direita = inserir_na_biblioteca(raiz->direita, musica);
    } else {
        printf("Musica com este titulo ja existe!\n");
        liberar_musica(musica);
        return raiz;
    }

    raiz->altura = 1 + max(altura(raiz->esquerda), altura(raiz->direita));

    int balance = obter_balanceamento(raiz);

    // esq-esq
    if (balance > 1 && strcmp(musica->titulo, raiz->esquerda->dados_musica->titulo) < 0) {
        return rotacao_direita(raiz);
    }

    // dir-dir
    if (balance < -1 && strcmp(musica->titulo, raiz->direita->dados_musica->titulo) > 0) {
        return rotacao_esquerda(raiz);
    }

    // esq-dir
    if (balance > 1 && strcmp(musica->titulo, raiz->esquerda->dados_musica->titulo) > 0) {
        raiz->esquerda = rotacao_esquerda(raiz->esquerda);
        return rotacao_direita(raiz);
    }

    // dir-esq
    if (balance < -1 && strcmp(musica->titulo, raiz->direita->dados_musica->titulo) < 0) {
        raiz->direita = rotacao_direita(raiz->direita);
        return rotacao_esquerda(raiz);
    }

    return raiz;
}

void exibir_biblioteca(NoBiblioteca *raiz) {
    if (raiz != NULL) {
        exibir_biblioteca(raiz->esquerda);
        printf("Titulo: %s, Artista: %s, Duracao: %d seg\n", 
               raiz->dados_musica->titulo, 
               raiz->dados_musica->artista, 
               raiz->dados_musica->duracao_segundos);
        exibir_biblioteca(raiz->direita);
    }
}

void liberar_biblioteca(NoBiblioteca *raiz) {
    if (raiz != NULL) {
        liberar_biblioteca(raiz->esquerda);
        liberar_biblioteca(raiz->direita);
        liberar_musica(raiz->dados_musica);
        free(raiz);
    }
}

NoBiblioteca* buscar_na_biblioteca(NoBiblioteca *raiz, const char *titulo) {
    if (raiz == NULL || strcmp(titulo, raiz->dados_musica->titulo) == 0) {
        return raiz;
    }

    if (strcmp(titulo, raiz->dados_musica->titulo) < 0) {
        return buscar_na_biblioteca(raiz->esquerda, titulo);
    } else {
        return buscar_na_biblioteca(raiz->direita, titulo);
    }
}