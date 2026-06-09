#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define GRN "\e[0;32m"
#define RED "\e[0;31m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"

#define RESETE "\e[0m"

typedef struct no{

    int valor;
    struct no *prox;
}No;

No *aux;

int contC = 30;

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void empilhar(No *p, int valor){

    No *novo = (No*) malloc(sizeof(No));

    if(novo == NULL){
        printf("Erro ao alocar memoria!\n");
        return;
    }

    novo->valor = valor;
    novo->prox = p->prox;
    p->prox = novo;

}

int desempilhar(No *p){

    if(p->prox == NULL){
        printf("pilha vazia!\n");
        return 0;
    }

    aux = p->prox;
    int valorRemovido = aux->valor;
    p->prox = aux->prox;
    free(aux);

    return valorRemovido;
}

void imprimirPilha(No *p){

    int contL = 14;
    if(p->prox == NULL){
        printf("\npilha vazia");
        return;
    }else{
        aux = p->prox;
        
        while(aux != NULL){
            gotoxy(contC, contL);
            printf("%d\n", aux->valor);
            aux = aux->prox;
            contL++;
        }
    }

    contC = contC + 6;
}

void preencherPilha(No *p, int valor){

    No temp;
    temp.prox = NULL;

    if (valor == 0){
        empilhar(p, 0);
        return;
    }else{
        while(valor > 0){
            int resto = valor % 10;
            empilhar(&temp, resto);
            valor = valor / 10;
        }

        while(temp.prox != NULL){
            int digito = desempilhar(&temp);
            empilhar(p, digito);
        }
    }
}

void somar(No *p1, No *p2, No *r){

    if(p1->prox == NULL && p2->prox == NULL){
        printf("As duas pilhas estao vazias!\n");
        return;
    }

    int sobe = 0, soma, resto;

    while(p1->prox != NULL || p2->prox != NULL || sobe != 0){

        int v1 = 0;
        if (p1->prox != NULL) {
            v1 = desempilhar(p1);
        }
        int v2 = 0;
        if (p2->prox != NULL) {
            v2 = desempilhar(p2);
        }

        soma = v1 + v2 + sobe;
        resto = soma % 10;
        sobe = soma / 10;
        empilhar(r, resto);
    }

}

void imprimirResultado(No *p){

    if(p->prox == NULL){
        printf("\npilha vazia!");
    }else{
        aux = p->prox;
        while(aux){
            printf("%d", aux->valor);
            aux = aux->prox;
        }
    }
}

void visual(){

    gotoxy(20,3);
    printf(CYN "***********************************");
    gotoxy(20,4);
    printf("*      "BLU "CALCULADORA DE PILHAS" RESETE"      "CYN "*");
    gotoxy(20,5);
    printf("***********************************");
    gotoxy(20,6);
    printf("***********************************");
    gotoxy(20,7);
    printf("*       "YEL "DIGITE DOIS NUMEROS" RESETE"       "CYN "*");
    gotoxy(20,8);
    printf("*   "GRN "P1:" RESETE"                           "CYN "*");
    gotoxy(20,9);
    printf("*   "RED "P2:" RESETE"                           "CYN "*");
    gotoxy(20,10);
    printf("*                                 *");
    gotoxy(20,11);
    printf("***********************************" RESETE);

}

int main(){

    No p1, p2, r;

    p1.prox = NULL;
    p2.prox = NULL;
    r.prox = NULL;

    int num1, num2;

    visual();

    gotoxy(28, 8);
    scanf("%d", &num1);
    
    gotoxy(28, 9);
    scanf("%d", &num2);
    
    preencherPilha(&p1, num1);
    gotoxy(contC, 12);
    printf(GRN"v"RESETE);
    imprimirPilha(&p1);
   
   

    preencherPilha(&p2, num2);
    gotoxy(contC, 12);
    printf(RED"v"RESETE);
    imprimirPilha(&p2);

    somar(&p1,&p2,&r);
    gotoxy(33, 14);
    printf("+");
    gotoxy(39, 14);
    printf("=");

    gotoxy(20,10);
    printf(CYN"*   "MAG "R:" RESETE"                            "CYN "*" RESETE);
    gotoxy(28, 10);
    imprimirResultado(&r);

    gotoxy(contC, 12);
    printf(MAG "v" RESETE);
    imprimirPilha(&r);
    
}
