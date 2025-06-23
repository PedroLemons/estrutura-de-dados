#include <stdio.h>
#include <stdlib.h>
#include "biblioteca.h"
#include "playlist.h"
#include "fila.h"
#include "pilha.h"

void limpar_buffer_entrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void tocar_musica_atual(Playlist* playlist, Pilha* historico) {
    if (playlist == NULL || playlist->musica_atual == NULL) {
        printf("Nenhuma musica selecionada na playlist.\n");
        return;
    }
    empilhar(historico, playlist->musica_atual->dados_musica);
    printf("\n-->> TOCANDO AGORA: %s - %s <<--\n", 
           playlist->musica_atual->dados_musica->titulo, 
           playlist->musica_atual->dados_musica->artista);
}

void exibir_menu() {
    printf("\n--- Biblioteca de Musicas ---\n");
    printf("1. Adicionar Musica\n");
    printf("2. Listar todas as Musicas (em ordem alfabetica)\n");
    
    printf("--- Playlist ---\n");
    printf("3. Adicionar musica a Playlist\n");
    printf("4. Exibir Playlist\n");
    printf("5. Tocar Proxima Musica da Playlist\n");
    printf("6. Tocar Musica Anterior da Playlist\n")

    printf("--- Outras Funcoes ---\n");
    printf("7. Adicionar musica a fila 'Tocar a Seguir'\n");
    printf("8. Exibir Fila 'Tocar a Seguir'\n");
    printf("9. Exibir Historico de Musicas\n");

    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

int main() {
    NoBiblioteca* biblioteca = NULL; 
    Playlist* minha_playlist = criar_playlist();
    Fila* fila_tocar_a_seguir = criar_fila();
    Pilha* historico = criar_pilha();
    int opcao;
    char titulo[100], artista[100];
    int duracao;

    do {
        exibir_menu();
        scanf("%d", &opcao);
        limpar_buffer_entrada();

        Musica* proxima_a_tocar = NULL;
        NoBiblioteca* no_encontrado = NULL;

        switch (opcao) {
            case 1:
                printf("Digite o titulo: ");
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = 0;

                printf("Digite o artista: ");
                fgets(artista, sizeof(artista), stdin);
                artista[strcspn(artista, "\n")] = 0;

                printf("Digite a duracao em segundos: ");
                scanf("%d", &duracao);
                limpar_buffer_entrada();

                Musica *nova_musica = criar_musica(titulo, artista, duracao);
                if (nova_musica) {
                    biblioteca = inserir_na_biblioteca(biblioteca, nova_musica);
                }
                break;
            case 2:
                if (biblioteca == NULL) {
                    printf("A biblioteca esta vazia.\n");
                } else {
                    printf("\n--- Musicas na Biblioteca ---\n");
                    imprimir_em_ordem(biblioteca);
                }
                break;
            case 3:
                printf("Digite o titulo da musica para adicionar a playlist: ");
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = 0;
                no_encontrado = buscar_na_biblioteca(biblioteca, titulo);
                if(no_encontrado) {
                    adicionar_musica_playlist(minha_playlist, no_encontrado->dados_musica);
                } else {
                    printf("Musica nao encontrada na biblioteca.\n");
                }
                break;
            case 4:
                exibir_playlist(minha_playlist);
                break;
            case 5:
                printf("\n--- Tocando proxima... ---\n");
                if (!fila_esta_vazia(fila_tocar_a_seguir)) {
                    printf("(Prioridade: Fila 'Tocar a Seguir')\n");
                    proxima_a_tocar = desenfileirar(fila_tocar_a_seguir);
                     empilhar(historico, proxima_a_tocar);
                     printf("\n-->> TOCANDO AGORA (DA FILA): %s - %s <<--\n", proxima_a_tocar->titulo, proxima_a_tocar->artista);

                } else if (minha_playlist != NULL && minha_playlist->cabeca != NULL) {
                    tocar_proxima_musica(minha_playlist);
                    tocar_musica_atual(minha_playlist, historico);
                } else {
                    printf("Playlist e Fila estao vazias.\n");
                }
                break;
            case 6:
                tocar_musica_anterior(minha_playlist);
                tocar_musica_atual(minha_playlist, historico);
                break;
            case 7:
                printf("Digite o titulo da musica para adicionar a fila 'Tocar a Seguir': ");
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = 0;
                no_encontrado = buscar_na_biblioteca(biblioteca, titulo);
                if(no_encontrado) {
                    enfileirar(fila_tocar_a_seguir, no_encontrado->dados_musica);
                    printf("'%s' adicionada a fila.\n", no_encontrado->dados_musica->titulo);
                } else {
                    printf("Musica nao encontrada na biblioteca.\n");
                }
                break;
            case 8:
                exibir_fila(fila_tocar_a_seguir);
                break;
            case 9:
                exibir_pilha(historico);
                break;
            case 0:
                printf("Saindo e liberando memoria...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
    
// liberacao de memoria
    liberar_pilha(historico);
    liberar_fila(fila_tocar_a_seguir);
    liberar_playlist(minha_playlist);
    liberar_biblioteca(biblioteca);
    
    printf("Programa finalizado.\n");
    return 0;
}