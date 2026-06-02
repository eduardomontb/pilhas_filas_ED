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

#define GRN "\e[0;32m"
#define RED "\e[0;31m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define RESETE "\e[0m"

typedef struct no {
    int id;
    int tamanho_bytes;
    struct no* proximo;
} No;

typedef struct fila {
    No *inicio;
    No *fim;
    int total_pacotes;
} Fila;

void criarFila(Fila* f) {
    f->inicio = NULL;
    f->fim = NULL;
    f->total_pacotes = 0;
}

void enfileirar(Fila *f, int id, int tam) {
    No *novo = (No*) malloc(sizeof(No));
    if(novo) {
        novo->id = id;
        novo->tamanho_bytes = tam;
        novo->proximo = NULL;

        if(f->inicio == NULL) {
            f->inicio = novo;
            f->fim = novo;
        } else {
            f->fim->proximo = novo;
            f->fim = novo;
        }
        f->total_pacotes++;
    } else {
        printf("Erro ao alocar memoria!\n");
    }
}

void desenfileirar(Fila *f, int *id, int *tam) {
    if(f->inicio == NULL) {
        return;
    }
    No *remover = f->inicio;
    f->inicio = remover->proximo;
    f->total_pacotes--;

    if(f->inicio == NULL) {
        f->fim = NULL;
    }

    *id = remover->id;
    *tam = remover->tamanho_bytes;
    free(remover);
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void desenharFilaOrigem(Fila *f) {
    gotoxy(2, 8);
    printf("ORIGEM (" RED "%d" RESETE " pacotes)", f->total_pacotes);
    
    gotoxy(2, 9);
    if (f->inicio == NULL){
        printf("                         ");
    } else{
        No *atual = f->inicio;
        int contador = 0;
        
        while(atual != NULL && contador < 4){
            printf("[%d] ", atual->id);
            atual = atual->proximo;
            contador++;
        }
         if (atual != NULL){
            printf("...                 "); 
        }else{
            printf("                    "); 
        }
    }
}

void desenharFilaDestino(Fila *f) {
    gotoxy(60, 8);
    printf("DESTINO (" GRN "%d" RESETE " pacotes)", f->total_pacotes);
    
    gotoxy(60, 9);
    if (f->inicio == NULL) {
        printf("                    ");
    } else {
        No *atual = f->inicio;
        int contador = 0;
        
        while (atual != NULL && contador < 4) {
            printf("[%d] ", atual->id);
            atual = atual->proximo;
            contador++;
        }
        
        if (atual != NULL) {
            printf("..."); 
        } else {
            printf("   "); 
        }
    }
}

int main() {
    Fila fila_origem, fila_destino;
    criarFila(&fila_origem);
    criarFila(&fila_destino);

    int tamArq, tamPac = 1024, id = 1;

    gotoxy(20, 2);
    printf("*****************************************");
    gotoxy(20, 3);
    printf("*                                       *");
    gotoxy(20, 4);
    printf("* SIMULADOR DE DISTRIBUICAO DE ARQUIVOS *");
    gotoxy(20, 5);
    printf("*                                       *");
    gotoxy(20, 6);
    printf("*****************************************");  
    gotoxy(10, 8);
    printf("> Informe o tamanho do arquivo a ser enviado:           (" RED "em bytes" RESETE ") ");
    
    gotoxy(56, 8);
    scanf("%d", &tamArq);
    getchar();

    while(tamArq > 0) {
        
        int tamPacAtual;

        if(tamArq >= tamPac) {
            tamPacAtual = tamPac;
        } else {
            tamPacAtual = tamArq;
        }

        enfileirar(&fila_origem, id, tamPacAtual);
        tamArq -= tamPacAtual;
        id++;
    }

    gotoxy(18, 10);
    printf("*********************************************");
    gotoxy(18, 11);
    printf("* O arquivo foi dividido em     pacote(s)   *");
    gotoxy(18, 12);
    printf("* Todos os pacotes estao na fila de " GRN "ORIGEM" RESETE "  *");
    gotoxy(18, 13);
    printf("*********************************************");
    
    gotoxy(46, 11);
    printf(RED "%d" RESETE, fila_origem.total_pacotes);

    gotoxy(20, 15);
    printf("> Pressione " YEL "ENTER" RESETE " para comecar a simulacao visual...");
    getchar();

    system("cls");

    gotoxy(20, 2);
    printf("*****************************************");
    gotoxy(20, 3);
    printf("*                                       *");
    gotoxy(20, 4);
    printf("*      ACOMPANHAR ENVIO DE PACOTES      *");
    gotoxy(20, 5);
    printf("*                                       *");
    gotoxy(0, 6);
    printf("*********************************************************************************");  
    gotoxy(0, 7);
    printf("*                                                                               *");
    gotoxy(0, 8);
    printf("*                                                                               *");
    gotoxy(0, 9);
    printf("*                                                                               *");
    gotoxy(0, 10);
    printf("*                                                                               *");
    gotoxy(0, 11);
    printf("*********************************************************************************");
    
    while(fila_origem.total_pacotes > 0) {
        int idAtual, tamAtual;
        
        desenfileirar(&fila_origem, &idAtual, &tamAtual);
        
        desenharFilaOrigem(&fila_origem);
        desenharFilaDestino(&fila_destino);
        
        gotoxy(14, 12);
        printf("* Transmitindo Pacote ID:   | Tamanho:       bytes  *");
        gotoxy(14, 13);
        printf("*****************************************************");

        gotoxy(41,12);
        printf(BLU "%d" RESETE, idAtual);
        gotoxy(54,12);
        printf(BLU "%d" RESETE, tamAtual);

        for(int x = 22; x <= 60; x++) {
            gotoxy(x, 9);
            printf("[P%d]", idAtual); 
            
            Sleep(150); 
            
            gotoxy(x, 9);
            printf("     "); 
        }
        
        enfileirar(&fila_destino, idAtual, tamAtual);
        
        desenharFilaDestino(&fila_destino);
    }

    gotoxy(18, 15);
    printf("pressionne " YEL "ENTER" RESETE " para finalizar a simulacao...");
    getchar();
    
    gotoxy(20, 18);
    printf("*****************************************");
    gotoxy(20, 19);
    printf("*                                       *");
    gotoxy(20, 20);
    printf("*  !!!ENVIO CONCLUIDO COM SUCESSO!!!    *");
    gotoxy(20, 21);
    printf("*                                       *");
    gotoxy(20, 22);
    printf("*****************************************");  
    
    gotoxy(18, 24);
    printf(" > Total de %d pacote(s) chegaram ao destino.", fila_destino.total_pacotes);
   
    return 0;
}
