#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

Pilha* criar_pilha() {
    Pilha* p = (Pilha*) malloc(sizeof(Pilha));
    p->topo = NULL;
    return p;
}

void empilhar(Pilha* p, Musica* m) {
    if (!p || !m) return;
    NoPilha* novo_no = (NoPilha*) malloc(sizeof(NoPilha));
    novo_no->dados_musica = m;
    novo_no->proximo = p->topo;
    p->topo = novo_no;
}

Musica* desempilhar(Pilha* p) {
    if (pilha_esta_vazia(p)) {
        return NULL;
    }
    NoPilha* no_removido = p->topo;
    Musica* musica_dados = no_removido->dados_musica;

    p->topo = p->topo->proximo;
    
    free(no_removido);
    return musica_dados;
}

int pilha_esta_vazia(const Pilha* p) {
    return (p == NULL || p->topo == NULL);
}

void exibir_pilha(const Pilha* p) {
    printf("\n--- Historico de Musicas (Mais recentes primeiro) ---\n");
    if (pilha_esta_vazia(p)) {
        printf("Historico vazio.\n");
        return;
    }
    NoPilha* atual = p->topo;
    while(atual != NULL) {
        printf("<- %s - %s\n", atual->dados_musica->titulo, atual->dados_musica->artista);
        atual = atual->proximo;
    }
}

void liberar_pilha(Pilha* p) {
    if (!p) return;
    while (!pilha_esta_vazia(p)) {
        desempilhar(p);
    }
    free(p);
}