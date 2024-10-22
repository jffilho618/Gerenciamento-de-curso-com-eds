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
        // Aloca memória para o novo nó
        *raiz = (No_curso*)malloc(sizeof(No_curso));
        if (*raiz == NULL) {
            return 0; // Falha na alocação de memória
        } else {
            (*raiz)->codigo_curso = codigo_curso;
            strcpy((*raiz)->nome_curso, nome_curso);
            (*raiz)->quant_periodos = quant_periodos;
            (*raiz)->arvore_disciplinas = NULL; // Inicializado como NULL
            (*raiz)->esq = NULL;
            (*raiz)->dir = NULL;
            (*raiz)->altura = 0;
        }
    } else if (codigo_curso < (*raiz)->codigo_curso) {
        // Inserção na subárvore esquerda
        resultado = inserir_curso(&(*raiz)->esq, codigo_curso, nome_curso, quant_periodos);
        if (resultado) {
            // Verifica o fator de balanceamento e realiza rotações se necessário
            if (fatorBalanceamentoCursos(*raiz) >= 2) {
                if ((*raiz)->esq != NULL && codigo_curso < (*raiz)->esq->codigo_curso) {
                    *raiz = rotacaoDireitaCursos(*raiz);
                } else {
                    *raiz = rotacaoDuplaDireitaCursos(*raiz);
                }
            }
        }
    } else if (codigo_curso > (*raiz)->codigo_curso) {
        // Inserção na subárvore direita
        resultado = inserir_curso(&(*raiz)->dir, codigo_curso, nome_curso, quant_periodos);
        if (resultado) {
            // Verifica o fator de balanceamento e realiza rotações se necessário
            if (fatorBalanceamentoCursos(*raiz) >= 2) {
                if ((*raiz)->dir != NULL && codigo_curso > (*raiz)->dir->codigo_curso) {
                    *raiz = rotacaoEsquerdaCursos(*raiz);
                } else {
                    *raiz = rotacaoDuplaEsquerdaCursos(*raiz);
                }
            }
        }
    } else {
        resultado = 0; // Código de curso duplicado
    }

    // Atualiza a altura se a inserção foi bem-sucedida
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
    // Verifica se a raiz ou a subárvore esquerda é nula
    if (raiz == NULL || raiz->esq == NULL) {
        // Se não for possível rotacionar, retorna a raiz original
        return raiz;
    }
    
    No_curso *aux = raiz->esq;  // Auxiliar aponta para a subárvore esquerda
    
    // Certifique-se de que a subárvore esquerda (aux) existe antes de prosseguir
    if (aux == NULL) {
        printf("Erro: Tentativa de rotação à direita com subárvore esquerda nula.\n");
        return raiz;
    }

    // Realiza a rotação
    raiz->esq = aux->dir;  // A subárvore direita de aux vai para a esquerda de raiz
    aux->dir = raiz;       // Coloca a raiz original como filho direito de aux

    // Atualiza as alturas
    raiz->altura = maior(alturaCursos(raiz->esq), alturaCursos(raiz->dir)) + 1;
    aux->altura = maior(alturaCursos(aux->esq), alturaCursos(aux->dir)) + 1;

    return aux; // Retorna o novo nó raiz
}


No_curso* rotacaoEsquerdaCursos(No_curso *raiz) {
    if (raiz == NULL || raiz->dir == NULL) {
        // Se o nó raiz ou sua subárvore direita for nula, não é possível fazer rotação
        return raiz;
    }
    
    No_curso *aux = raiz->dir;
    
    // Certifique-se de que a subárvore direita existe antes de tentar acessá-la
    if (aux == NULL) {
        printf("Erro: Tentativa de rotação à esquerda com subárvore direita nula.\n");
        return raiz;
    }

    // Realiza a rotação
    raiz->dir = aux->esq;  // Mover a subárvore esquerda do aux para a direita da raiz
    aux->esq = raiz;       // Colocar a raiz atual como filho esquerdo do aux

    // Atualiza as alturas
    raiz->altura = maior(alturaCursos(raiz->esq), alturaCursos(raiz->dir)) + 1;
    aux->altura = maior(alturaCursos(aux->esq), alturaCursos(aux->dir)) + 1;

    return aux; // Retorna o novo nó raiz
}


No_curso* rotacaoDuplaDireitaCursos(No_curso *raiz) {
    if (raiz == NULL) {
        return raiz;
    }
    
    if (raiz->esq != NULL) {
        raiz->esq = rotacaoEsquerdaCursos(raiz->esq);
    }
    
    return rotacaoDireitaCursos(raiz);
}


No_curso* rotacaoDuplaEsquerdaCursos(No_curso *raiz) {
    if (raiz == NULL) {
        return raiz;
    }

    if (raiz->dir != NULL) {
        raiz->dir = rotacaoDireitaCursos(raiz->dir);
    }

    return rotacaoEsquerdaCursos(raiz);
}




No_curso* minimo_curso(No_curso* raiz) {
    No_curso* atual = raiz;
    
    // Percorre a subárvore esquerda para encontrar o menor valor
    while (atual != NULL && atual->esq != NULL) {
        atual = atual->esq;
    }

    return atual;
}

int remover_curso(No_curso** raiz, int codigo_curso) {
    if (raiz == NULL || *raiz == NULL) {
        // A árvore ou subárvore está vazia, nada para remover
        return 0;
    }

    int resultado = 0;

    // Passo 1: Encontrar o nó a ser removido
    if (codigo_curso < (*raiz)->codigo_curso) {
        resultado = remover_curso(&(*raiz)->esq, codigo_curso);
    } else if (codigo_curso > (*raiz)->codigo_curso) {
        resultado = remover_curso(&(*raiz)->dir, codigo_curso);
    } else {
        // Disciplina encontrada
        if ((*raiz)->esq == NULL && (*raiz)->dir == NULL) {
            // Caso 1: Nó sem filhos
            free(*raiz);
            *raiz = NULL;
            resultado = 1;
        } else if ((*raiz)->esq == NULL) {
            // Caso 2: Nó com apenas um filho à direita
            No_curso* temp = (*raiz)->dir;
            free(*raiz);
            *raiz = temp;
            resultado = 1;
        } else if ((*raiz)->dir == NULL) {
            // Caso 2: Nó com apenas um filho à esquerda
            No_curso* temp = (*raiz)->esq;
            free(*raiz);
            *raiz = temp;
            resultado = 1;
        } else {
            // Caso 3: Nó com dois filhos
            No_curso* temp = minimo_curso((*raiz)->dir); // Encontra o sucessor
            (*raiz)->codigo_curso = temp->codigo_curso;
            resultado = remover_curso(&(*raiz)->dir, temp->codigo_curso);
        }
    }

    // Passo 2: Balancear a árvore se um nó foi removido
    if (*raiz != NULL) {
        // Atualiza a altura do nó atual
        (*raiz)->altura = maior(alturaCursos((*raiz)->esq), alturaCursos((*raiz)->dir)) + 1;

        // Verifica o fator de balanceamento
        int fator_balanceamento = fatorBalanceamentoCursos(*raiz);

        // Caso 1: Desbalanceado à esquerda
        if (fator_balanceamento >= 2) {
            if ((*raiz)->esq != NULL && alturaCursos((*raiz)->esq->esq) >= alturaCursos((*raiz)->esq->dir)) {
                // Rotação simples à direita
                *raiz = rotacaoDireitaCursos(*raiz);
            } else {
                // Rotação dupla à direita
                *raiz = rotacaoDuplaDireitaCursos(*raiz);
            }
        }

        // Caso 2: Desbalanceado à direita
        else if (fator_balanceamento <= -2) {
            if ((*raiz)->dir != NULL && alturaCursos((*raiz)->dir->dir) >= alturaCursos((*raiz)->dir->esq)) {
                // Rotação simples à esquerda
                *raiz = rotacaoEsquerdaCursos(*raiz);
            } else {
                // Rotação dupla à esquerda
                *raiz = rotacaoDuplaEsquerdaCursos(*raiz);
            }
        }
    }

    // Retorna 1 se a remoção foi bem-sucedida, 0 caso contrário
    return resultado;
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