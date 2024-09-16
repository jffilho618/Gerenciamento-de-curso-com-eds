#include <stdio.h>
#include <stdlib.h>
#include "gerenciamento.h"

No_notas* criarARVORE_notas(){
    return NULL;
}


No_notas* inserirNota(No_notas* raiz, int codigo_disciplina, int semestre, float nota_final){
    if (raiz == NULL){
        No_notas* nova_nota = (No_notas*)malloc(sizeof(No_notas));
        nova_nota->codigo_disciplina = codigo_disciplina;
        nova_nota->semestre_cursado = semestre;
        nova_nota->nota_final = nota_final;
        nova_nota->esq = nova_nota->dir = NULL;
        return nova_nota;
    }

    if (codigo_disciplina < raiz->codigo_disciplina)
        raiz->esq = inserirNota(raiz->esq, codigo_disciplina, semestre, nota_final);
    
    else if (codigo_disciplina > raiz->codigo_disciplina)
        raiz->dir = inserirNota(raiz->dir, codigo_disciplina, semestre, nota_final);

    return raiz;
}


No_matriculas* minimo(No_matriculas* raiz) {
    No_matriculas* atual = raiz;
    
    while (atual != NULL && atual->esq != NULL) {
        atual = atual->esq;
    }
    
    return atual;
}


No_matriculas* remover_matricula(No_matriculas* raiz, int codigo_disciplina){
    if (raiz == NULL) 
        return NULL;

    if (codigo_disciplina < raiz->codigo_disciplina)
        raiz->esq = remover_matricula(raiz->esq, codigo_disciplina);
    
    else if (codigo_disciplina > raiz->codigo_disciplina)
        raiz->dir = remover_matricula(raiz->dir, codigo_disciplina);

    else{
        if (raiz->esq == NULL){
            No_matriculas* temp = raiz->dir;
            free(raiz);
            return temp;
        }

        else if (raiz->dir == NULL){
            No_matriculas* temp = raiz->esq;
            free(raiz);
            return temp;
        }

        No_matriculas* temp = minimo(raiz->dir);
        raiz->codigo_disciplina = temp->codigo_disciplina;
        raiz->dir = remover_matricula(raiz->dir, temp->codigo_disciplina);
    }

    return raiz;
}


No_matriculas* busca_matricula(No_matriculas* raiz, int codigo_disciplina) {
    if (raiz == NULL) {
        return NULL;  // Matricula não encontrada
    }

    if (codigo_disciplina == raiz->codigo_disciplina) {
        return raiz;  // Matricula encontrada
    } else if (codigo_disciplina < raiz->codigo_disciplina) {
        return busca_matricula(raiz->esq, codigo_disciplina);  // Busca na subárvore esquerda
    } else {
        return busca_matricula(raiz->dir, codigo_disciplina);  // Busca na subárvore direita
    }
}



Elemento* cadastrarNota(Elemento* lista_alunos){
    int matricula_aluno, codigo_disciplina, semestre;
    float nota_final;

    printf("Digite a matricula do aluno: ");
    scanf("%d", &matricula_aluno);

    Elemento* aluno = buscar_aluno(lista_alunos, matricula_aluno);

    if (aluno == NULL){
        printf("Aluno não encontrado!\n");
        return lista_alunos;
    }

    printf("Digite o código da disciplina: ");
    scanf("%d", &codigo_disciplina);

    if (busca_matricula(aluno->arvore_matriculas, codigo_disciplina)){
        printf("Digite o semestre em que a disciplina foi cursada: ");
        scanf("%d", &semestre);
        printf("Digite a nota final da disciplina: ");
        scanf("%f", &nota_final);

        aluno->arvore_notas = inserirNota(aluno->arvore_notas, codigo_disciplina, semestre, nota_final);
        aluno->arvore_matriculas = remover_matricula(aluno->arvore_matriculas, codigo_disciplina);
        printf("Nota cadastrada e disciplina movida para o histórico de notas!\n");
    }

    else{
        printf("Aluno não está matriculado nesta disciplina!\n");
    }

    return lista_alunos;
}


void mostrarNotasDePeriodo(Elemento* lista_alunos){
    int matricula_aluno, periodo;

    printf("Digite a matrícula do aluno: ");
    scanf("%d", &matricula_aluno);
    printf("Digite o período: ");
    scanf("%d", &periodo);

    Elemento* aluno = buscar_aluno(lista_alunos, matricula_aluno);
    if (aluno == NULL) {
        printf("Aluno não encontrado!\n");
        return;
    }

    No_notas* notas = aluno->arvore_notas;
    int encontrou = 0;

    while (notas != NULL){
        if (notas->semestre_cursado == periodo){
            printf("Disciplina: %d, Nota: %.2f\n", notas->codigo_disciplina, notas->nota_final);
            encontrou = 1;
        }

        if (periodo < notas->semestre_cursado){
            notas = notas->esq;
        }
        else{
            notas = notas->dir;
        }
    }

    if (!encontrou){
        printf("Nenhuma disciplina encontrada para o período!\n");
    }
}



void mostrarNotaDeDisciplina(Elemento* lista_alunos, No_curso* arvore_cursos){
    int matricula_aluno, codigo_disciplina;

    printf("Digite a matrícula do aluno: ");
    scanf("%d", &matricula_aluno);
    printf("Digite o código da disciplina: ");
    scanf("%d", &codigo_disciplina);

    Elemento* aluno = buscar_aluno(lista_alunos, matricula_aluno);
    if (aluno == NULL) {
        printf("Aluno não encontrado!\n");
        return;
    }

    No_notas *notas = aluno->arvore_notas;
    No_disciplinas* disciplina = buscar_disciplina_no_curso(arvore_cursos, codigo_disciplina);

    if (disciplina == NULL) {
        printf("Disciplina não encontrada no curso!\n");
        return;
    }

    while (notas != NULL) {
        if (notas->codigo_disciplina == codigo_disciplina) {
            printf("Disciplina: %s\n", disciplina->nome_disciplina);
            printf("Período: %d, Carga Horária: %d\n", disciplina->periodo, disciplina->carga_horaria);
            printf("Nota: %.2f\n", notas->nota_final);
            return;
        }
        
        if (codigo_disciplina < notas->codigo_disciplina) {
            notas = notas->esq;
        } else {
            notas = notas->dir;
        }
    }

    printf("Nota para a disciplina %d não encontrada.\n", codigo_disciplina);

}