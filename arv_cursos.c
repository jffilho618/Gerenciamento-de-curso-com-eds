#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gerenciamento.h"

No_curso* criarARVOREcursos(){
    return NULL;
}


No_curso* inserir_curso(No_curso *raiz, int valor, char nome_curso[50], int quant_periodos) {
    No_curso *novo = raiz;

    if (raiz == NULL) {
        novo = (No_curso*)malloc(sizeof(No_curso));
        novo->codigo_curso = valor;
        strcpy(novo->nome_curso, nome_curso);
        novo->quant_periodos = quant_periodos;
        novo->arvore_disciplinas = NULL;
        novo->esq = NULL;
        novo->dir = NULL;
    } else {
        if (valor < raiz->codigo_curso) {
            raiz->esq = inserir_curso(raiz->esq, valor, nome_curso, quant_periodos);
        } else {
            raiz->dir = inserir_curso(raiz->dir, valor, nome_curso, quant_periodos);
        }
    }

    return novo;
}


No_curso* CadastrarCurso(No_curso *raiz){
    int codigo_curso;
    srand(time(NULL));
    do
    {
        codigo_curso = rand() % 100 + 1;
    } while (busca_curso(raiz, codigo_curso));
    
    if (busca_curso(raiz, codigo_curso)){
        printf("Curso ja cadastrado!\n");
    }
    else{
        printf("Informe o nome do curso: ");
        char nome_curso[50];
        scanf(" %49[^\n]", nome_curso);
        printf("Informe a quantidade de periodos: ");
        int quant_periodos;
        scanf("%d", &quant_periodos);
        raiz = inserir_curso(raiz, codigo_curso, nome_curso, quant_periodos);
        printf("Curso cadastrado com sucesso\n");
    }
    return raiz;
}


int busca_curso(No_curso *raiz, int codigo_curso){
    int retorno = 0 ;
        
    if(raiz != NULL){
        if(raiz->codigo_curso == codigo_curso){
            retorno = 1;
        }else{
            if(codigo_curso < raiz->codigo_curso){
                return busca_curso(raiz->esq, codigo_curso);
            }else{
                return busca_curso(raiz->dir, codigo_curso);
            }
        }
    }
    return retorno;
}

No_curso *retornar_curso(No_curso *raiz, int codigo_curso){
    if(raiz == NULL){
        return NULL;
    }else{
        if(raiz->codigo_curso == codigo_curso){
            return raiz;
        }else{
            if(codigo_curso < raiz->codigo_curso){
                return retornar_curso(raiz->esq, codigo_curso);
            }else{
                return retornar_curso(raiz->dir, codigo_curso);
            }
        }
    }
}

void imprimir_pre_ordem(No_curso *raiz){
    if (raiz != NULL ) {
        printf("║ %-11d ║ %-25s ║ %-6d ║\n",raiz->quant_periodos,raiz->nome_curso,raiz->codigo_curso);
        imprimir_pre_ordem(raiz->esq);
        imprimir_pre_ordem(raiz->dir);
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


No_curso* libera_arvore(No_curso *raiz){
    if (raiz != NULL){
        libera_arvore(raiz->esq);
        libera_arvore(raiz->dir);
        free(raiz);
    }
    return NULL;
}

void mostrar_todos_os_cursos(No_curso *raiz){
    
        printf("╔═════════════╦═══════════════════════════╦════════╗\n");
        printf("║   PERÍODOS  ║       NOME DO CURSO       ║ CÓDIGO ║\n");
        printf("╠═════════════╬═══════════════════════════╬════════╣\n");
        imprimir_pre_ordem(raiz);
        
        printf("╚═════════════╩═══════════════════════════╩════════╝\n");
    
    
}