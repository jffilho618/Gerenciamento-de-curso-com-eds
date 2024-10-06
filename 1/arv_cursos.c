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


int inserir_curso(No_curso **raiz, long long int codigo, char nome[50], int periodos) {
    int resultado = 1; // Sucesso por padrão

    if (*raiz == NULL) {
        *raiz = (No_curso*)malloc(sizeof(No_curso));
        if (*raiz == NULL) {
            printf("Erro ao alocar memória para o novo nó.\n");
            resultado = 0; // Falha na alocação de memória
        } else {
            (*raiz)->codigo_curso = codigo;
            strcpy((*raiz)->nome_curso, nome);
            (*raiz)->quant_periodos = periodos;
            (*raiz)->arvore_disciplinas = NULL;
            (*raiz)->esq = NULL;
            (*raiz)->dir = NULL;
            
        }
    } else if (codigo < (*raiz)->codigo_curso) {
        resultado = inserir_curso(&(*raiz)->esq, codigo, nome, periodos);
    } else if (codigo > (*raiz)->codigo_curso) {
        resultado = inserir_curso(&(*raiz)->dir, codigo, nome, periodos);
    } else {
        resultado = 0;
    }

    return resultado;
}



No_curso* CadastrarCurso(No_curso *raiz) {

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
