#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gerenciamento.h"

No_curso* criarARVOREcursos(){
    return NULL;
}


No_curso* inserir_curso(No_curso *raiz, int valor, char nome_curso[50], int quant_periodos){
    if(raiz == NULL){
        No_curso *novo = (No_curso*)malloc(sizeof(No_curso));
        novo->codigo_curso = valor;
        strcpy(novo->nome_curso, nome_curso);
        novo->quant_periodos = quant_periodos;
        novo->arvore_disciplinas = NULL;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }else{
        if(valor < raiz->codigo_curso){
            raiz->esq = inserir_curso(raiz->esq, valor, nome_curso, quant_periodos);
        }else{
            raiz->dir = inserir_curso(raiz->dir, valor, nome_curso, quant_periodos);
        }
    }
    return raiz;
}

No_curso* CadastrarCurso(No_curso *raiz){
    int codigo_curso;
    srand(time(NULL));
    printf("Digite o codigo do curso: ");
    scanf("%d", &codigo_curso);
    if (busca_curso(raiz, codigo_curso)){
        printf("Curso ja cadastrado\n");
    }
    else{
        printf("Informe o nome do curso: ");
        char nome_curso[50];
        scanf("%s", nome_curso);
        printf("Informe a quantidade de periodos: ");
        int quant_periodos;
        scanf("%d", &quant_periodos);
        raiz = inserir_curso(raiz, codigo_curso, nome_curso, quant_periodos);
        printf("Curso cadastrado com sucesso\n");
    }
    return raiz;
}

int tamanho(No_curso *raiz){
    if(raiz == NULL){
        return 0;
    }else{
        return 1 + tamanho(raiz->esq) + tamanho(raiz->dir);
    }
}

int busca_curso(No_curso *raiz, int valor){
    if(raiz == NULL){
        return 0;
    }else{
        if(raiz->codigo_curso == valor){
            return 1;
        }else{
            if(valor < raiz->codigo_curso){
                return busca_curso(raiz->esq, valor);
            }else{
                return busca_curso(raiz->dir, valor);
            }
        }
    }
}

void imprimir_pre_ordem(No_curso *raiz){
    //10 5 3 1 7 20 15 30

    if (raiz != NULL) {
        printf("%d ", raiz->codigo_curso);
        imprimir_pre_ordem(raiz->esq);
        imprimir_pre_ordem(raiz->dir);
    }
}

void imprimir_em_ordem(No_curso *raiz){
    // 1 3 5 7 10 15 20 30


    if(raiz != NULL){
        imprimir_em_ordem(raiz->esq);
        printf("%d ", raiz->codigo_curso);
        imprimir_em_ordem(raiz->dir);
        
    }
}

void imprimir_pos_ordem(No_curso *raiz){
    //1 3 7 5 15 30 20 10


    if (raiz != NULL) {
        imprimir_pos_ordem(raiz->esq);
        imprimir_pos_ordem(raiz->dir);
        printf("%d ", raiz->codigo_curso);
    }
}


No_curso* remover(No_curso *raiz,int valor){
    if (raiz == NULL){
        printf("Valor nao encontrado\n");
        return NULL;
    }
    if (raiz->codigo_curso == valor){
        if (raiz->esq == NULL && raiz->dir == NULL){
            free(raiz);
            return NULL;
        }
        if (raiz->esq ==  NULL || raiz->dir == NULL){
            No_curso *aux;
            if (raiz->esq == NULL){
                aux = raiz->dir;
            }else{
                aux = raiz->esq;
            }
            free(raiz);
            return aux;
        }
        No_curso *aux = raiz->esq;
        while (aux->dir != NULL){
            aux = aux->dir;
        }
        raiz->codigo_curso = aux->codigo_curso;
        aux->codigo_curso = valor;
        raiz->esq = remover(raiz->esq, valor);
        return raiz;
    }
    if (valor < raiz->codigo_curso){
        raiz->esq = remover(raiz->esq, valor);
    }else{
        raiz->dir = remover(raiz->dir, valor);
    }
    return raiz;
}

No_curso* buscar_no(No_curso *raiz, int valor) {
    if (raiz == NULL || raiz->codigo_curso == valor) {
        return raiz;
    } else if (valor < raiz->codigo_curso) {
        return buscar_no(raiz->esq, valor);
    } else {
        return buscar_no(raiz->dir, valor);
    }
}
int altura(No_curso *raiz) {
    if (raiz == NULL) {
        return -1; // Altura de uma árvore vazia é -1
    } else {
        int altura_esq = altura(raiz->esq);
        int altura_dir = altura(raiz->dir);
        return (altura_esq > altura_dir ? altura_esq : altura_dir) + 1;
    }
}
int altura_no(No_curso *raiz, int valor) {
    No_curso *no = buscar_no(raiz, valor);
    if (no == NULL) {
        return -1; // Nó não encontrado
    }
    return altura(no);
}


No_curso* libera_arvore(No_curso *raiz){
    if (raiz != NULL){
        libera_arvore(raiz->esq);
        libera_arvore(raiz->dir);
        free(raiz);
    }
    return NULL;
}