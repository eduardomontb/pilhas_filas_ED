#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define GRN "\e[0;32m"
#define RED "\e[0;31m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define RESETE "\e[0m"

typedef struct fila{
    int id;
    int tamB;
    struct fila *prox;
}Fila;

Fila *aux;

int totalPacotes = 0, totalP_destino = 0;

void enfileirar(Fila *f, int id, int tam){
   Fila *novo = malloc(sizeof(Fila));

   if(novo == NULL){
    printf("Erro ao alocar memoria!");

   }else{
        novo->id = id;
        novo->tamB = tam;
        novo->prox = NULL;
        if(f->prox == NULL){
            f->prox = novo;
        }else{
            aux = f->prox;
            while(aux->prox != NULL){
                aux = aux->prox;
            }
            aux->prox = novo;
        }
   }
}

void desenfileirar(Fila *f, int *id, int *tam){
    Fila *remover = NULL;
    
    if(f->prox == NULL){
        return;
    }else{
    
    remover = f->prox;
    f->prox = remover->prox;
    totalPacotes--;
    *id = remover->id;
    *tam = remover->tamB;
    free(remover);
    }
 
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void desenharFilaOrigem(Fila *f) {
    gotoxy(2, 8);
    printf("ORIGEM (" RED "%d" RESETE " pacotes)", totalPacotes);
    
    gotoxy(2, 9);
    if (f->prox == NULL){
        printf("                         ");
    } else{
        aux = f->prox;
        int contV = 0;
        
        while(aux != NULL && contV < 4){
            printf("[%d] ", aux->id);
            aux = aux->prox;
            contV++;
        }
         if (aux != NULL){
            printf("...                 "); 
        }else{
            printf("                    "); 
        }
    }
}

void desenharFilaDestino(Fila *f){
    gotoxy(60, 8);
    printf("DESTINO (" GRN "%d" RESETE " pacotes)", totalP_destino);
    
    gotoxy(60, 9);
    if (f->prox == NULL) {
        printf("                    ");
    } else {
        aux = f->prox;
        int contV = 0;
        while (aux != NULL && contV < 4){
            printf("[%d] ", aux->id);
            aux = aux->prox;
            contV++;
        }
        
        if (aux != NULL) {
            printf("..."); 
        } else {
            printf("   "); 
        }
    }
}

int main(){

    Fila filaOrigem, filaDestino;
    
    filaOrigem.prox = NULL;
    filaDestino.prox = NULL;
    
    int tamArq, tamPac, id = 1, totalTemp;

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
    gotoxy(10, 9);
    printf("> Informe o tamnho maximo dos pacotes: ");
    
    gotoxy(56, 8);
    scanf("%d", &tamArq);
    getchar();

    gotoxy(49, 9);
    scanf("%d", &tamPac);
    getchar();

    while(tamArq > 0){
        
        int tamPacAtual;

        if(tamArq >= tamPac){
            tamPacAtual = tamPac;
        }else{
            tamPacAtual = tamArq;
        }

        enfileirar(&filaOrigem, id, tamPacAtual);
        tamArq -= tamPacAtual;
        id++;
        totalPacotes++;
    }

    totalTemp = totalPacotes;
    gotoxy(18, 11);
    printf("*********************************************");
    gotoxy(18, 12);
    printf("* O arquivo foi dividido em     pacote(s)   *");
    gotoxy(18, 13);
    printf("* Todos os pacotes estao na fila de " GRN "ORIGEM" RESETE "  *");
    gotoxy(18, 14);
    printf("*********************************************");
    
    gotoxy(46, 12);
    printf(RED "%d" RESETE, totalPacotes);

    gotoxy(18, 17);
    printf("Pressione " YEL "ENTER" RESETE " para comecar a simulacao visual...");
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
    printf("*-------------------------------------------------------------------------------*");
    gotoxy(0, 8);
    printf("*                                                                               *");
    gotoxy(0, 9);
    printf("*                                                                               *");
    gotoxy(0, 10);
    printf("*-------------------------------------------------------------------------------*");
    gotoxy(0, 11);
    printf("*********************************************************************************");
    
    while(totalPacotes > 0){
        int idAtual, tamAtual;
        
        desenfileirar(&filaOrigem, &idAtual, &tamAtual);
        
        desenharFilaOrigem(&filaOrigem);
        desenharFilaDestino(&filaDestino);
        
        gotoxy(14, 12);
        printf("* Transmitindo Pacote ID:   | Tamanho:       bytes  *");
        gotoxy(14, 13);
        printf("*****************************************************");

        gotoxy(40,12);
        printf(BLU "%d" RESETE, idAtual);
        gotoxy(53,12);
        printf(BLU "%d" RESETE, tamAtual);

        for(int x = 22; x <= 60; x++) {
            gotoxy(x, 9);
            printf(GRN ">[P%d]>>" RESETE, idAtual); 
            
            Sleep(150); 
            
            gotoxy(x, 9);
            printf("     "); 
        }
        totalP_destino++;
        enfileirar(&filaDestino, idAtual, tamAtual);
        
        desenharFilaDestino(&filaDestino);
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
    printf(" > Total de %d pacote(s) chegaram ao destino.", totalTemp);
   
    return 0;
}
