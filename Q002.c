/*

    Faça um programa para simular uma distribuição de arquivos. Esses arquivos devem ser divididos em pacotes e
    enviados ao destino por um canal de comunicação. Cada pacote tem um tamanho máximo em bytes e o canal
    transporta apenas um pacote por vez. Sendo assim, o usuário informará o tamanho do arquivo a ser transmitido,
    então o simulador calculará quantos pacotes serão necessários para transportar pelo canal de um ponto de origem
    a outro de destino, bem como mostrará visualmente essa transferência dos pacotes.

*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct no{
    int id;
    int tamanho_bytes;
    struct no* proximo;
}No;

typedef struct fila{
    No *inicio;
    No *fim;
    int total_pacotes;
}Fila;

void criarFila(Fila* f){
    f->inicio = NULL;
    f->fim = NULL;
    f->total_pacotes = 0;
}

void enfileirar(Fila *f, int id, int tam){

    No *novo = (No*) malloc(sizeof(No));

   if(novo){
    novo->id = id;
    novo->tamanho_bytes = tam;
    novo->proximo = NULL;

    if(f->inicio == NULL){
        f->inicio = novo;
        f->fim = novo;
    }else{
        f->fim->proximo = novo;
        f->fim = novo;
    }
    f->total_pacotes++;
   }else{
    printf("Erro ao alocar memoria!\n");
   }

}

No* desenfileirar(Fila *f){

    if(f->inicio == NULL){
        printf("fila vazia!\n");
        return NULL;
    }

    No *remover = f->inicio;
    f->inicio = remover->proximo;
    f->total_pacotes--;

    if(f->inicio == NULL){
        f->fim = NULL;
    }

    return remover;
}

int main(){

    Fila fila;
    criarFila(&fila);

    int tamArq, tamPac = 1024;

    printf("\t+---------------------------------------+\n");
    printf("\t| Simulador de Distribuicao de Arquivos |\n");
    printf("\t+---------------------------------------+\n\n");
    printf("> Informe o tamanho do arquivo a ser transmitido (em bytes):\n> ");     
    scanf("%d", &tamArq);
    getchar();

    int resto = tamArq;
    int id = 1;

    while(resto > 0){
    
        int tamPacAtual;

        if(resto >= tamPac){
            tamPacAtual = tamPac;
        }else{
            tamPacAtual = resto;
        }

        enfileirar(&fila, id, tamPacAtual);
        resto -= tamPacAtual;
        id++;
    }

    int total = fila.total_pacotes;
    printf("\nO arquivo foi dividido em %d pacote(s).\n", total);
    printf("Todos os pacotes estao na fila de transmissao.\n");
    printf("Pressione ENTER para comecar a enviar pelo canal...");
    getchar();

    printf("\n");

    while(fila.total_pacotes > 0){
        No *pacote = desenfileirar(&fila);
        printf("| Enviando pacote ID: %d, Tamanho: %d bytes |\n", pacote->id, pacote->tamanho_bytes);
        printf("[CANAL]: Transportando pacote %d/%d (%d bytes)...\n", pacote->id, total, pacote->tamanho_bytes);
       printf("\n[PROCESSO]: [");
        for(int i = 0; i < 35; i++){
            printf("|");
            
            Sleep(120);      
        }
        printf("]\n");

        free(pacote);
        printf("\n[DESTINO]: Recebido!\n");

        printf("\nPressione ENTER para o proximo pacote");
        getchar();

        printf("\n\n");
    }
    
    printf("Todos os pacotes chegaram ao destino! Transferencia concluida.\n");
   
    return 0;
}
