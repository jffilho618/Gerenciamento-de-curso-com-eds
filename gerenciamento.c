#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gerenciamento.h"
#include "arv_cursos.h"

void menu_principal()
{
    printf("╔══════════════════════════════════════╗\n");
    printf("║                 SIGAA                ║\n");
    printf("╠══════════════════════════════════════╣\n");
    printf("║ [1] QUESTÃO 1                        ║\n");
    printf("║ [2] QUESTÃO 2                        ║\n");
    printf("║ [3] SOBRE                            ║\n");
    printf("║ [0] SAIR                             ║\n");
    printf("╚══════════════════════════════════════╝\n\n");
}

void questao1()
{
    printf("╔══════════════════════════════════════╗\n");
    printf("║                 SIGAA                ║\n");
    printf("╠══════════════════════════════════════╣\n");
    printf("║ [1] CADASTRAR CURSO                  ║\n");
    printf("║ [2] CADASTRAR ALUNO                  ║\n");
    printf("║ [3]                                  ║\n");
    printf("║ [4]                                  ║\n");
    printf("║ [0] SAIR                             ║\n");
    printf("╚══════════════════════════════════════╝\n\n");
}

Elemento *criaLista(){
    return NULL;
}

void mostrarLista(Elemento *l){
    if (l == NULL)
        printf("Lista vazia ");
    else{
        Elemento *aux = l;
        if (aux){
            printf("\n");
            do {
                printf("%d -> ", aux->matricula);
                aux = aux->prox; /* avança para o próximo nó */
            } while (aux != NULL);
            printf("\n");
        }
    }
}

Elemento *addInicio(Elemento *l){
    Elemento *novo = (Elemento*) malloc(sizeof(Elemento));
    novo->ant=NULL;
    if (l==NULL)
    {
        scanf("%d",&novo->matricula);
        novo->prox=NULL;
        l=novo;
        return l;
    }
    
    else
    {
        scanf("%d",&novo->matricula);
        novo->prox = l;
        l->ant=novo;
        return novo;
    }
    
}

Elemento *addFinal(Elemento *l){
    Elemento *novo = (Elemento*) malloc(sizeof(Elemento));
    novo->prox=NULL;
    if (l==NULL)
    {
        scanf("%d",&novo->matricula);
        novo->ant=NULL;
        l=novo;
        return l;
    }
    
    else
    {
        Elemento *aux = l;
        scanf("%d", &novo->matricula);
        while (aux->prox!=NULL)
        {
            aux=aux->prox;
        }
        aux->prox=novo;
        novo->ant=aux;
        return l;
    }

}

Elemento *addOrdenadoCrescente(Elemento *l) {
    Elemento *aux, *novo = (Elemento*) malloc(sizeof(Elemento));
    novo->prox=NULL,novo->ant=NULL;
    if (novo == NULL) {
        printf("Erro ao alocar memória\n");
        exit(1);
    }

    scanf("%d", &novo->matricula);

    if (l == NULL){
        l = novo;
        return l;
    }

    else if (novo->matricula<l->matricula)
    {
        novo->prox=l;
        l->ant=novo;
        return novo;
    }
    
    
    else {
        aux = l;
        while (aux->prox != NULL && aux->prox->matricula < novo->matricula) {
            aux = aux->prox;

        }

        if (aux->prox==NULL)
        {
            aux->prox=novo;
            novo->ant=aux;
        }
        
        else
        {
            novo->prox=aux->prox; 
            novo->ant=aux;
            aux->prox->ant=novo;
            aux->prox=novo;

        }
        
        return l;
    }
}


Elemento* removerElemento(Elemento *l) {
    Elemento *aux, *remover = NULL;

    if (l == NULL) {
        printf("Lista vazia\n");
        return l;
    }

    int valor;
    printf("Digite o valor a ser removido: ");
    scanf("%d", &valor);

    if (l->prox == NULL) {
        if (l->matricula == valor) {
            free(l);
            return NULL;
        } else {
            printf("Valor inexistente!\n");
            return l;
        }
    }

    if (valor == l->matricula){
        remover = l;
        l->prox->ant=NULL;
        l = l->prox;
        free(remover);
        return l;
    }

    aux = l;
    while (aux->prox != NULL && aux->prox->matricula != valor) {
        aux = aux->prox;
    }

    if (aux->prox == NULL) {
        
       if(aux->matricula==valor){
           remover=aux;
           aux->ant->prox=NULL;
           free(remover);
           return l;
       }
       else{
           printf("Valor inexistente!\n");
           return l;
       }
    }




    remover = aux->prox;
    aux->prox = remover->prox;
    if (remover->prox != NULL) {
        remover->prox->ant = aux;
    
    }
    free(remover);

    return l;
}


int tamanhoDaLista(Elemento *l){
    int cont = 0;
    Elemento *aux = l;
    while (aux != NULL)
    {
        cont++;
        aux = aux->prox;
    }
    return cont;
}

