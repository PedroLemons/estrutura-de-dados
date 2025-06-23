#include <stdio.h>
#include <stdlib.h>
#include "playlist.h"

Playlist* criar_playlist() {
    Playlist* nova_playlist = (Playlist*) malloc(sizeof(Playlist));
    if (!nova_playlist) {
        perror("Falha ao alocar playlist");
        return NULL;
    }
    nova_playlist->cabeca = NULL;
    nova_playlist->cauda = NULL;
    nova_playlist->musica_atual = NULL;
    nova_playlist->tamanho = 0;
    return nova_playlist;
}

void adicionar_musica_playlist(Playlist* playlist, Musica* musica) {
    if (!playlist || !musica) return;

    NoPlaylist* novo_no = (NoPlaylist*) malloc(sizeof(NoPlaylist));
    if (!novo_no) {
        perror("Falha ao alocar no da playlist");
        return;
    }
    novo_no->dados_musica = musica;
    novo_no->proximo = NULL;

    if (playlist->cabeca == NULL) {
        novo_no->anterior = NULL;
        playlist->cabeca = novo_no;
        playlist->cauda = novo_no;
        playlist->musica_atual = novo_no; 
    } else {
        novo_no->anterior = playlist->cauda;
        playlist->cauda->proximo = novo_no;
        playlist->cauda = novo_no;
    }
    playlist->tamanho++;
    printf("Musica '%s' adicionada a playlist.\n", musica->titulo);
}

void exibir_playlist(const Playlist* playlist) {
    printf("\n--- Playlist Atual ---\n");
    if (playlist == NULL || playlist->cabeca == NULL) {
        printf("A playlist esta vazia.\n");
        return;
    }

    NoPlaylist* atual = playlist->cabeca;
    int i = 1;
    while (atual != NULL) {
        printf("%d. %s - %s", i, atual->dados_musica->titulo, atual->dados_musica->artista);
        if (atual == playlist->musica_atual) {
            printf("  <-- [TOCANDO AGORA]\n");
        } else {
            printf("\n");
        }
        atual = atual->proximo;
        i++;
    }
    printf("------------------------\n");
}

void liberar_playlist(Playlist* playlist) {
    if (!playlist) return;

    NoPlaylist* atual = playlist->cabeca;
    while (atual != NULL) {
        NoPlaylist* proximo_no = atual->proximo;
        free(atual);
        atual = proximo_no;
    }
    free(playlist);
}

void tocar_proxima_musica(Playlist* playlist) {
    if (playlist == NULL || playlist->musica_atual == NULL) {
        printf("Nenhuma musica tocando na playlist.\n");
        return;
    }
    if (playlist->musica_atual->proximo != NULL) {
        playlist->musica_atual = playlist->musica_atual->proximo;
    } else {
        printf("Fim da playlist. Reiniciando do comeco.\n");
        playlist->musica_atual = playlist->cabeca;
    }
    exibir_playlist(playlist);
}

void tocar_musica_anterior(Playlist* playlist) {
    if (playlist == NULL || playlist->musica_atual == NULL) {
        printf("Nenhuma musica tocando na playlist.\n");
        return;
    }
    if (playlist->musica_atual->anterior != NULL) {
        playlist->musica_atual = playlist->musica_atual->anterior;
    } else {
        printf("Inicio da playlist. Nao ha musica anterior.\n");
    }
    exibir_playlist(playlist);
}