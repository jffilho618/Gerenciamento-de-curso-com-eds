#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gerenciamento.h"

void menu_principal()
{
    printf("╔══════════════════════════════════════╗\n");
    printf("║         MENU TRANSPORTADORA          ║\n");
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
    printf("║         MENU TRANSPORTADORA          ║\n");
    printf("╠══════════════════════════════════════╣\n");
    printf("║ [1] ADICIONAR CURSO                  ║\n");
    printf("║ [2] ADICIONAR ALUNO                  ║\n");
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
                printf("%d -> ", aux->info);
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
        scanf("%d",&novo->info);
        novo->prox=NULL;
        l=novo;
        return l;
    }
    
    else
    {
        scanf("%d",&novo->info);
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
        scanf("%d",&novo->info);
        novo->ant=NULL;
        l=novo;
        return l;
    }
    
    else
    {
        Elemento *aux = l;
        scanf("%d", &novo->info);
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

    scanf("%d", &novo->info);

    if (l == NULL){
        l = novo;
        return l;
    }

    else if (novo->info<l->info)
    {
        novo->prox=l;
        l->ant=novo;
        return novo;




    }
    
    
    else {
        aux = l;
        while (aux->prox != NULL && aux->prox->info < novo->info) {
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
        if (l->info == valor) {
            free(l);
            return NULL;
        } else {
            printf("Valor inexistente!\n");
            return l;
        }
    }

    if (valor == l->info){
        remover = l;
        l->prox->ant=NULL;
        l = l->prox;
        free(remover);
        return l;
    }

    aux = l;
    while (aux->prox != NULL && aux->prox->info != valor) {
        aux = aux->prox;
    }

    if (aux->prox == NULL) {
        
       if(aux->info==valor){
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

No* criarARVORE(){
    return NULL;
}


No* inserir(No *raiz, int valor){
    if(raiz == NULL){
        No *novo = (No*)malloc(sizeof(No));
        novo->valor = valor;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }else{
        if(valor < raiz->valor){
            raiz->esq = inserir(raiz->esq, valor);
        }else{
            raiz->dir = inserir(raiz->dir, valor);
        }
    }
    return raiz;
}

int tamanho(No *raiz){
    if(raiz == NULL){
        return 0;
    }else{
        return 1 + tamanho(raiz->esq) + tamanho(raiz->dir);
    }
}

int busca(No *raiz, int valor){
    if(raiz == NULL){
        return 0;
    }else{
        if(raiz->valor == valor){
            return 1;
        }else{
            if(valor < raiz->valor){
                return busca(raiz->esq, valor);
            }else{
                return busca(raiz->dir, valor);
            }
        }
    }
}

void imprimir_pre_ordem(No *raiz){
    //10 5 3 1 7 20 15 30

    if (raiz != NULL) {
        printf("%d ", raiz->valor);
        imprimir_pre_ordem(raiz->esq);
        imprimir_pre_ordem(raiz->dir);
    }
}

void imprimir_em_ordem(No *raiz){
    // 1 3 5 7 10 15 20 30


    if(raiz != NULL){
        imprimir_em_ordem(raiz->esq);
        printf("%d ", raiz->valor);
        imprimir_em_ordem(raiz->dir);
        
    }
}

void imprimir_pos_ordem(No *raiz){
    //1 3 7 5 15 30 20 10


    if (raiz != NULL) {
        imprimir_pos_ordem(raiz->esq);
        imprimir_pos_ordem(raiz->dir);
        printf("%d ", raiz->valor);
    }
}


No* remover(No *raiz,int valor){
    if (raiz == NULL){
        printf("Valor nao encontrado\n");
        return NULL;
    }
    if (raiz->valor == valor){
        if (raiz->esq == NULL && raiz->dir == NULL){
            free(raiz);
            return NULL;
        }
        if (raiz->esq ==  NULL || raiz->dir == NULL){
            No *aux;
            if (raiz->esq == NULL){
                aux = raiz->dir;
            }else{
                aux = raiz->esq;
            }
            free(raiz);
            return aux;
        }
        No *aux = raiz->esq;
        while (aux->dir != NULL){
            aux = aux->dir;
        }
        raiz->valor = aux->valor;
        aux->valor = valor;
        raiz->esq = remover(raiz->esq, valor);
        return raiz;
    }
    if (valor < raiz->valor){
        raiz->esq = remover(raiz->esq, valor);
    }else{
        raiz->dir = remover(raiz->dir, valor);
    }
    return raiz;
}

No* buscar_no(No *raiz, int valor) {
    if (raiz == NULL || raiz->valor == valor) {
        return raiz;
    } else if (valor < raiz->valor) {
        return buscar_no(raiz->esq, valor);
    } else {
        return buscar_no(raiz->dir, valor);
    }
}
int altura(No *raiz) {
    if (raiz == NULL) {
        return -1; // Altura de uma árvore vazia é -1
    } else {
        int altura_esq = altura(raiz->esq);
        int altura_dir = altura(raiz->dir);
        return (altura_esq > altura_dir ? altura_esq : altura_dir) + 1;
    }
}
int altura_no(No *raiz, int valor) {
    No *no = buscar_no(raiz, valor);
    if (no == NULL) {
        return -1; // Nó não encontrado
    }
    return altura(no);
}


No* libera_arvore(No *raiz){
    if (raiz != NULL){
        libera_arvore(raiz->esq);
        libera_arvore(raiz->dir);
        free(raiz);
    }
    return NULL;
}
