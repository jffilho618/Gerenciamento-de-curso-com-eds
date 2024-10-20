#define _POSIX_C_SOURCE 199309L
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gerenciamento.h"
#include <windows.h>
#include "RNG64.h"

No_curso* criarARVOREcursos(){
    return NULL;
}


int busca_curso(No_curso *raiz, int codigo_curso){
    int retorno = 0 ;
        
    if(raiz != NULL){
        if(raiz->codigo_curso == codigo_curso){
            retorno = 1;
        }else{
            if(codigo_curso < raiz->codigo_curso){
                retorno = busca_curso(raiz->esq, codigo_curso);
            }else{
                retorno = busca_curso(raiz->dir, codigo_curso);
            }
        }
    }
    return retorno;
}

No_curso *retornar_curso(No_curso *raiz, int codigo_curso) {
    while (raiz != NULL && raiz->codigo_curso != codigo_curso) {
        if (codigo_curso < raiz->codigo_curso) {
            raiz = raiz->esq;
        } else {
            raiz = raiz->dir;
        }
    }
    return raiz;
}


void imprimir_pre_ordem(No_curso *raiz){
    if (raiz != NULL ) {
        printf("║ %-11d ║ %-49s ║ %-6d ║\n",raiz->quant_periodos,raiz->nome_curso,raiz->codigo_curso);
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
    
        printf("╔═════════════╦═══════════════════════════════════════════════════╦════════╗\n");
        printf("║   PERÍODOS  ║                    NOME DO CURSO                  ║ CÓDIGO ║\n");
        printf("╠═════════════╬═══════════════════════════════════════════════════╬════════╣\n");
        imprimir_pre_ordem(raiz);
        
        printf("╚═════════════╩═══════════════════════════════════════════════════╩════════╝\n");
    
    
}


int inserir_curso(No_curso **raiz, long long int codigo_curso, char nome_curso[50], int quant_periodos) {
    int resultado = 1; // Sucesso por padrão

    if (*raiz == NULL) {
        *raiz = (No_curso*)malloc(sizeof(No_curso));
        if (*raiz == NULL) {
            printf("Erro ao alocar memória para o novo nó.\n");
            resultado = 0; // Falha na alocação de memória
        } else {
            (*raiz)->codigo_curso = codigo_curso;
            strcpy((*raiz)->nome_curso, nome_curso);
            (*raiz)->quant_periodos = quant_periodos;
            (*raiz)->arvore_disciplinas = NULL;
            (*raiz)->esq = NULL;
            (*raiz)->dir = NULL;
            (*raiz)->altura = 0;
        }
    } else if (codigo_curso < (*raiz)->codigo_curso) {
        resultado = inserir_curso(&(*raiz)->esq, codigo_curso, nome_curso, quant_periodos);
        if (resultado) {
            if (fatorBalanceamentoCursos(*raiz) >= 2) {
                if (codigo_curso < (*raiz)->esq->codigo_curso) {
                    *raiz = rotacaoDireitaCursos(*raiz);
                } else {
                    *raiz = rotacaoDuplaDireitaCursos(*raiz);
                }
            }
        }
    } else if (codigo_curso > (*raiz)->codigo_curso) {
        resultado = inserir_curso(&(*raiz)->dir, codigo_curso, nome_curso, quant_periodos);
        if (resultado) {
            if (fatorBalanceamentoCursos(*raiz) >= 2) {
                if (codigo_curso > (*raiz)->dir->codigo_curso) {
                    *raiz = rotacaoEsquerdaCursos(*raiz);
                } else {
                    *raiz = rotacaoDuplaEsquerdaCursos(*raiz);
                }
            }
        }
    } else {
        resultado = 0;
    }

    if (resultado) {
        (*raiz)->altura = maior(alturaCursos((*raiz)->esq), alturaCursos((*raiz)->dir)) + 1;
    }

    return resultado;
}


int alturaCursos(No_curso *raiz) {
    if (raiz == NULL) {
        return -1;
    } else {
        return raiz->altura;
    }
}

int fatorBalanceamentoCursos(No_curso *raiz) {
    return labs(alturaCursos(raiz->esq) - alturaCursos(raiz->dir));
}

int maior(int x, int y) {
    return (x > y) ? x : y;
}

No_curso* rotacaoDireitaCursos(No_curso *raiz) {
    No_curso *aux = raiz->esq;
    raiz->esq = aux->dir;
    aux->dir = raiz;
    raiz->altura = maior(alturaCursos(raiz->esq), alturaCursos(raiz->dir)) + 1;
    aux->altura = maior(alturaCursos(aux->esq), raiz->altura) + 1;
    return aux;
}

No_curso* rotacaoEsquerdaCursos(No_curso *raiz) {
    No_curso *aux = raiz->dir;
    raiz->dir = aux->esq;
    aux->esq = raiz;
    raiz->altura = maior(alturaCursos(raiz->esq), alturaCursos(raiz->dir)) + 1;
    aux->altura = maior(alturaCursos(aux->dir), raiz->altura) + 1;
    return aux;
}

No_curso* rotacaoDuplaDireitaCursos(No_curso *raiz) {
    raiz->esq = rotacaoEsquerdaCursos(raiz->esq);
    return rotacaoDireitaCursos(raiz);
}

No_curso* rotacaoDuplaEsquerdaCursos(No_curso *raiz) {
    raiz->dir = rotacaoDireitaCursos(raiz->dir);
    return rotacaoEsquerdaCursos(raiz);
}


No_curso* cadastrarCurso(No_curso *raiz) {

    printf("Informe o codigo do curso: ");
    int codigo_curso;
    scanf("%d", &codigo_curso);

    printf("Informe o nome do curso: ");
    char nome_curso[50];
    scanf(" %49[^\n]", nome_curso);

    printf("Informe a quantidade de periodos: ");
    int quant_periodos;
    scanf("%d", &quant_periodos);
    
    LARGE_INTEGER frequency, start_time, end_time;
    long long total_nanos_sum = 0;

    // Obtém a frequência do contador de alta resolução
    QueryPerformanceFrequency(&frequency);

    
        
    QueryPerformanceCounter(&start_time);

    if (inserir_curso(&raiz, codigo_curso, nome_curso, quant_periodos)) {
        // Curso inserido com sucesso
        QueryPerformanceCounter(&end_time);

        // Calcular o tempo total de inserção em nanosegundos
        long long total_nanos = (end_time.QuadPart - start_time.QuadPart) * 1000000000 / frequency.QuadPart;

        // Acumular os tempos
        total_nanos_sum += total_nanos;

    } else {
        printf("Erro ao inserir o curso.\n");
    }
    

    // Exibir o tempo total de inserção
    printf("Tempo total de inserção: %lld nanossegundos\n", total_nanos_sum);
    
    return raiz;
}