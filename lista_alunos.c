#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gerenciamento.h"

Elemento *criaLista_alunos(){
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

Elemento *addOrdenado_alfabetico(Elemento *l, int matricula, char nome[50], int codigo_curso) {
    Elemento *aux, *novo = (Elemento*) malloc(sizeof(Elemento));
    
    // Verificar se houve falha na alocação de memória
    if (novo == NULL) {
        printf("Erro ao alocar memória\n");
        exit(1);
    }

    // Inicializar o novo elemento
    novo->matricula = matricula;
    strcpy(novo->nome, nome);
    novo->codigo_curso = codigo_curso;
    novo->prox = NULL;
    novo->ant = NULL;
    novo->arvore_notas = NULL;
    novo->arvore_matriculas = NULL;

    // Se a lista estiver vazia, retorna o novo elemento como a cabeça
    if (l == NULL) {
        return novo;
    }

    // Se o nome do novo elemento for menor que o primeiro da lista, insere no início
    if (strcmp(novo->nome, l->nome) < 0) {
        novo->prox = l;
        l->ant = novo;
        return novo;
    }

    // Caso contrário, percorre a lista para encontrar a posição correta
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

    return l;
}

Elemento* Cadastrar_aluno(Elemento *l, No_curso *raiz){
    char nome[50];

    if (raiz == NULL) {
        printf("Nenhum curso cadastrado\n");
        return l;
    }

    printf("Digite o nome do aluno: ");
    scanf("%s", nome);
    int codigo_curso;
    printf("Digite o codigo do curso: ");
    scanf("%d", &codigo_curso);
    printf("Digite a matricula do aluno: ");
    int matricula;
    scanf("%d", &matricula);

    if (busca_curso(raiz, codigo_curso)){
        l = addOrdenado_alfabetico(l, matricula, nome, codigo_curso);
    }
    else{
        printf("Curso nao cadastrado\n");
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
}