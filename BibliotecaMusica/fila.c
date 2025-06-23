#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

Fila* criar_fila() {
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->inicio = f->fim = NULL;
    return f;
}

void enfileirar(Fila* f, Musica* m) {
    if (!f || !m) return;
    NoFila* novo_no = (NoFila*) malloc(sizeof(NoFila));
    novo_no->dados_musica = m;
    novo_no->proximo = NULL;

    if (fila_esta_vazia(f)) {
        f->inicio = f->fim = novo_no;
    } else { 
        f->fim->proximo = novo_no;
        f->fim = novo_no;
    }
}

Musica* desenfileirar(Fila* f) {
    if (fila_esta_vazia(f)) {
        return NULL;
    }
    NoFila* no_removido = f->inicio;
    Musica* musica_dados = no_removido->dados_musica;
    
    f->inicio = f->inicio->proximo;
    if (f->inicio == NULL) {
        f->fim = NULL;
    }
    
    free(no_removido);
    return musica_dados;
}

int fila_esta_vazia(const Fila* f) {
    return (f == NULL || f->inicio == NULL);
}

void exibir_fila(const Fila* f) {
    printf("--- Fila 'Tocar a Seguir' ---\n");
    if (fila_esta_vazia(f)) {
        printf("Fila vazia.\n");
        return;
    }
    NoFila* atual = f->inicio;
    while (atual != NULL) {
        printf("-> %s - %s\n", atual->dados_musica->titulo, atual->dados_musica->artista);
        atual = atual->proximo;
    }
}

void liberar_fila(Fila* f) {
    if (!f) return;
    while (!fila_esta_vazia(f)) {
        desenfileirar(f);
    }
    free(f);
}