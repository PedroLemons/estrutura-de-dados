#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "musica.h"

// alocacao com malloc
Musica* criar_musica(const char *titulo, const char *artista, int duracao) {
    Musica *nova_musica = (Musica*) malloc(sizeof(Musica));
    if (nova_musica == NULL) {
        perror("Erro ao alocar memoria para musica");
        return NULL;
    }

// aloca e copia titulo e artista para a estrutura
    nova_musica->titulo = strdup(titulo);
    nova_musica->artista = strdup(artista);

    if (nova_musica->titulo == NULL || nova_musica->artista == NULL) {
        perror("Erro ao alocar memoria para titulo/artista");
        free(nova_musica->titulo);
        free(nova_musica->artista);
        free(nova_musica);
        return NULL;
    }

// retorna o ponteiro para a nova musica criada
    nova_musica->duracao_segundos = duracao;
    return nova_musica;
}

// liberacao de memoria
void liberar_musica(Musica *musica) {
    if (musica != NULL) {
        free(musica->titulo);
        free(musica->artista);
        free(musica);
    }
}