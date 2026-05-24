    /*

          Faça um programa baseado no conceito de pilhas para somar dois números.

    */
    
#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int valor;
    struct no *prox;
}No;

typedef struct pilha{
    No *topo;
}Pilha;

void criarPilha(Pilha *p){
    p->topo = NULL;
}

void empilhar(Pilha *p, int valor){

    No *novo = (No*)malloc(sizeof(No));

    if(novo == NULL){
        printf("Erro ao alocar memoria!\n");
        return;
    }

    novo->valor = valor;
    novo->prox = p->topo;
    p->topo = novo;
    
}

int desempilhar(Pilha *p){

    if(p->topo == NULL){
        printf("pilha vazia!\n");
        return 0;
    }

    No *remover = p->topo;
    int valorRemovido = remover->valor;
    p->topo = remover->prox;
    free(remover);

    return valorRemovido;
}

void imprimirPilha(Pilha *p){

    if(p->topo == NULL){
        printf("\t   >pilha vazia!\n");
        return;
    }

    No *aux = p->topo;

    printf("\n");
    printf("\t         ----- Pilha -----\n");

    while(aux != NULL){
        printf("\t                 %d\n", aux->valor);
        aux = aux->prox;
    }

    printf("\t         --- Fim pilha ---\n");

    printf("\n\t   Pressione ENTER para continuar...");
    getchar();
    getchar();
    
}

void somarPilhas(Pilha *p1, Pilha *p2, Pilha *resultado){

    if(p1->topo == NULL || p2->topo == NULL){
        printf("Uma das pilhas esta vazia!\n");
        return;
    }

    int decimal = 0;

    while(p1->topo != NULL || p2->topo != NULL || decimal != 0){

        int v1 = desempilhar(p1);
        int v2 = desempilhar(p2);
        
        int soma = v1 + v2 + decimal;

        int resto = soma % 10;

        decimal = soma / 10;

        empilhar(resultado, resto);
    }
}

int main(){

    No *remover;

    Pilha pilha1, pilha2, resultado;

    criarPilha(&pilha1);
    criarPilha(&pilha2);
    criarPilha(&resultado);

    int op, valor;

    do{
        system("cls");
        printf("\t+------------- MENU ------------+\n");
        printf("\t|  Empilhar................[1]  |\n");
        printf("\t|  Desempilhar.............[2]  |\n");
        printf("\t|  Somar pilhas............[3]  |\n");
        printf("\t|  Imprimir pilha..........[4]  |\n");
        printf("\t|  Imprimir resultado......[5]  |\n");
        printf("\t|  Sair....................[6]  |\n");
        printf("\t+-------------------------------+\n");

        printf("\t> Informe a opcao: ");
        scanf("%d",&op);
        getchar();

        switch(op){

            case 1:
                printf("\n\n");
                printf("\t   +----- menu empilhar -----+\n");
                printf("\t   | Pilha 1.............[1] |\n");
                printf("\t   | Pilha 2.............[2] |\n");
                printf("\t   +-------------------------+\n");
                printf("\t   > Informe a pilha: ");
                scanf("%d", &op);
                printf("\t   > Informe o valor: ");
                scanf("%d", &valor);

                if(op == 1){
                    empilhar(&pilha1, valor);
                }else if(op == 2){
                    empilhar(&pilha2, valor);
                }else {
                    printf("\t> Opcao invalida!\n");
                }

                break;

            case 2:
                printf("\n\n");
                printf("\t   +---- menu desempilhar ----+\n");
                printf("\t   | Pilha 1..............[1] |\n");
                printf("\t   | Pilha 2..............[2] |\n");
                printf("\t   +--------------------------+\n");

                printf("\t   > Informe a pilha: ");
                scanf("%d", &op);

                if (op == 1){
                    valor = desempilhar(&pilha1);
                    if(valor != 0){
                        printf("\t   > Valor desempilhado: %d\n", valor);
                    }else{
                        printf("\t   > Pilha 1 esta vazia!\n");
                    }
                }else if (op == 2){
                    valor = desempilhar(&pilha2);
                    if(valor != 0){
                        printf("\t   > Valor desempilhado: %d\n", valor);
                    }else{
                        printf("\t   > Pilha 2 esta vazia!\n");
                    }
                }else{
                    printf("\t   > Opcao invalida!\n");
                }
                
                break;

            case 3:
                somarPilhas(&pilha1, &pilha2, &resultado);
                break;

            case 4:
                printf("\n\n");
                printf("\t   +----- menu imprimir -----+\n");   
                printf("\t   | Pilha 1.............[1] |\n"); 
                printf("\t   | Pilha 2.............[2] |\n");
                printf("\t   +-------------------------+\n");
                printf("\t   > Informe a pilha: ");
                scanf("%d", &op);
                
                if(op == 1){
                    imprimirPilha(&pilha1);
                }else if(op == 2){
                    imprimirPilha(&pilha2);
                }else{
                    printf("\t   > Opcao invalida!\n");
                }

                break;

            case 5:
                imprimirPilha(&resultado);
                break;

            case 6:
                printf("\t   > Saindo...\n");;
                break;

            default:

                printf("\t      > Opcao invalida!\n");
        }

    }while(op != 6);

    return 0;
}
