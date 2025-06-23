#ifndef MUSICA_H
#define MUSICA_H

// estrutura de dados da musica
typedef struct Musica {
    char *titulo;
    char *artista;
    int duracao_segundos;
} Musica;

Musica* criar_musica(const char *titulo, const char *artista, int duracao);

void liberar_musica(Musica *musica);

#endif