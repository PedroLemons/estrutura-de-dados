#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "musica.h" 

// lista duplamente encadeada
typedef struct NoPlaylist {
    Musica* dados_musica; 
    struct NoPlaylist* proximo;
    struct NoPlaylist* anterior;
} NoPlaylist;

// playlist
typedef struct {
    NoPlaylist* cabeca;            // Ponteiro para o inicio da lista
    NoPlaylist* cauda;             // Ponteiro para o fim da lista
    NoPlaylist* musica_atual;      // Ponteiro para a musica atual
    int tamanho;
} Playlist;


Playlist* criar_playlist();

void adicionar_musica_playlist(Playlist* playlist, Musica* musica);
void exibir_playlist(const Playlist* playlist);
void liberar_playlist(Playlist* playlist);
void tocar_proxima_musica(Playlist* playlist);
void tocar_musica_anterior(Playlist* playlist);


#endif