#ifndef GERENCIAMENTO_H
#define GERENCIAMENTO_H

typedef struct elemento{
    int info;
    struct  elemento *prox;
    struct elemento *ant;
}Elemento;

Elemento *criaLista(); 
Elemento *addInicio(Elemento *l); 
Elemento *addFinal(Elemento *l);
Elemento *addOrdenadoCrescente(Elemento *l);
Elemento *removerElemento(Elemento *l);
int tamanhoDaLista(Elemento *l);
void mostrarLista(Elemento *l); 
void menu();

typedef struct no{
    int valor;
    struct no *esq;
    struct no *dir;
}No;

No* criarARVORE();
No* inserir(No *raiz, int valor);
int tamanho(No *raiz);
int busca(No *raiz, int valor);
void imprimir_pre_ordem(No *raiz);
void imprimir_em_ordem(No *raiz);
void imprimir_pos_ordem(No *raiz);
No* remover(No *raiz,int valor);
No* buscar_no(No *raiz, int valor);
int altura(No *raiz);
int altura_no(No *raiz, int valor);
No* libera_arvore(No *raiz);


void menu_principal();
void questao1();
#endif