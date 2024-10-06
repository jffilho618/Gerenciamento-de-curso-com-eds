#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gerenciamento.h"

Elemento *criaLista_alunos(){
    return NULL;
}

Elemento *addOrdenado_alfabetico(Elemento *l, int matricula, char nome[50], int codigo_curso) {
    Elemento *aux, *novo = (Elemento*) malloc(sizeof(Elemento));
    Elemento *inicio = l;  // Variável para armazenar o início da lista

    // Verificar se houve falha na alocação de memória
    if (novo == NULL) {
        printf("Erro ao alocar memória\n");
    }

    else{
        // Inicializar o novo elemento
        novo->matricula = matricula;
        strcpy(novo->nome, nome);
        novo->codigo_curso = codigo_curso;
        novo->prox = NULL;
        novo->ant = NULL;
        novo->arvore_notas = NULL;
        novo->arvore_matriculas = NULL;

        // Se a lista estiver vazia, o novo elemento será o primeiro
        if (l == NULL) {
            inicio = novo;
        } else if (strcmp(novo->nome, l->nome) < 0) {
            // Inserir no início se o novo elemento for menor que o primeiro da lista
            novo->prox = l;
            l->ant = novo;
            inicio = novo;
        } else {
            // Percorre a lista para encontrar a posição correta
            aux = l;
            while (aux->prox != NULL && strcmp(aux->prox->nome, novo->nome) < 0) {
                aux = aux->prox;
            }

            // Inserção no meio ou no final
            novo->prox = aux->prox;
            if (aux->prox != NULL) {
                aux->prox->ant = novo;
            }
            aux->prox = novo;
            novo->ant = aux;
        }
    }

    // Retorna o início da lista, que pode ser o novo elemento ou a lista original
    return inicio;
}

int busca_matricula_aluno(Elemento *l, int matricula){
    Elemento *aux = l;
    int retorno = 0;
    while (aux != NULL)
    {
        if (aux->matricula == matricula)
        {
            retorno = 1;
        }
        aux = aux->prox;
    }
    return retorno;
}


Elemento* Cadastrar_aluno(Elemento *l, No_curso *raiz){
    char nome[50];

    if (raiz == NULL) {
        printf("Nenhum curso cadastrado\n");
    }

    else{
        int codigo_curso;
        printf("Digite o codigo do curso: ");
        scanf("%d", &codigo_curso);

        if (busca_curso(raiz, codigo_curso)){
            printf("Digite o nome do aluno: ");
            scanf(" %49[^\n]", nome);
            
            int matricula;
            do
            {
                matricula = rand () % 10000000 + 1;
            } while (busca_matricula_aluno(l, matricula));
            
            l = addOrdenado_alfabetico(l, matricula, nome, codigo_curso);
        }
        else{
            printf("Curso nao cadastrado !\n");
        }

        
    }

    return l;
}


Elemento* removerElemento(Elemento *l) {
    Elemento *aux, *remover = NULL;

    if (l == NULL) {
        printf("Lista vazia\n");
    }

    else{
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


void alunos_de_um_curso(Elemento *l)
{
    Elemento *aux = l;
    int codigo_curso;
    printf("Informe o código do curso: ");
    scanf("%d", &codigo_curso);
    if (aux)
    {

        printf("╔═════════════╦═══════════════════════════╦════════╗\n");
        printf("║  MATRICULA  ║           NOME            ║ CÓDIGO ║\n");
        printf("╠═════════════╬═══════════════════════════╬════════╣\n");
        while (aux)
        {
            if (aux->codigo_curso == codigo_curso)
            {
                printf("║ %-11d ║ %-25s ║ %-6d ║\n", aux->matricula, aux->nome, aux->codigo_curso);
            }
            aux = aux->prox;
        }
        printf("╚═════════════╩═══════════════════════════╩════════╝\n");
        printf("\n");
        
    }
    else
    {
        printf("Nenhum Aluno Cadastrado !\n");
    }
}

