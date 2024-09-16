#include <stdio.h>
#include <stdlib.h>
#include "gerenciamento.h"

No_matriculas* criarARVORE_matriculas(){
    return NULL;
}


No_matriculas* inserirMatricula(No_matriculas* raiz, int codigo_disciplina){
    if (raiz == NULL){
        No_matriculas* nova_matricula = (No_matriculas*)malloc(sizeof(No_matriculas));
        nova_matricula->codigo_disciplina = codigo_disciplina;
        nova_matricula->esq = nova_matricula->dir = NULL;
        return nova_matricula;
    }

    if (codigo_disciplina < raiz->codigo_disciplina)
        raiz->esq = inserirMatricula(raiz->esq, codigo_disciplina);
    
    else if (codigo_disciplina > raiz->codigo_disciplina)
        raiz->dir = inserirMatricula(raiz->dir, codigo_disciplina);

    return raiz;
}


Elemento* buscar_aluno(Elemento* lista_alunos, int matricula_aluno){
    Elemento* atual = lista_alunos;

    while (atual != NULL){
        printf("Verificando aluno com matrícula: %d\n", atual->matricula);
        if (atual->matricula == matricula_aluno){
            return atual;
        }
        atual = atual->prox;
    }

    return NULL;
}


No_disciplinas* buscar_disciplina(No_disciplinas* raiz, int codigo_disciplina) {
    if (raiz == NULL) {
        return NULL;  // Disciplina não encontrada
    }

    if (codigo_disciplina == raiz->codigo_disciplina) {
        return raiz;  // Disciplina encontrada
    } else if (codigo_disciplina < raiz->codigo_disciplina) {
        return buscar_disciplina(raiz->esq, codigo_disciplina);  // Busca na subárvore esquerda
    } else {
        return buscar_disciplina(raiz->dir, codigo_disciplina);  // Busca na subárvore direita
    }
}



No_disciplinas* buscar_disciplina_no_curso(No_curso* raiz_curso, int codigo_disciplina) {
    if (raiz_curso == NULL) {
        return NULL;  // Se não houver cursos
    }

    // Percorrer a árvore de cursos para encontrar o curso correto
    No_curso* curso_atual = raiz_curso;
    while (curso_atual != NULL) {
        // Verifica se o curso contém a disciplina
        No_disciplinas* disciplina_encontrada = buscar_disciplina(curso_atual->arvore_disciplinas, codigo_disciplina);
        if (disciplina_encontrada != NULL) {
            return disciplina_encontrada;  // Disciplina encontrada no curso
        }

        // Continua a busca na árvore de cursos
        if (codigo_disciplina < curso_atual->codigo_curso) {
            curso_atual = curso_atual->esq;
        } else {
            curso_atual = curso_atual->dir;
        }
    }

    return NULL;  // Se não encontrar a disciplina
}



Elemento* cadastrarMatricula(Elemento* lista_alunos, No_curso* arvore_cursos){
    int matricula_aluno, codigo_disciplina;

    printf("Digite a matricula do aluno: ");
    scanf("%d", &matricula_aluno);

    Elemento* aluno = buscar_aluno(lista_alunos, matricula_aluno);
    if (aluno == NULL){
        printf("Aluno não encontrado!\n");
        return lista_alunos;
    }

    printf("Digite o código da disciplina: ");
    scanf("%d", &codigo_disciplina);

    No_disciplinas* disciplina_encontrada = buscar_disciplina_no_curso(arvore_cursos, codigo_disciplina);
    if (disciplina_encontrada == NULL) {
        printf("Disciplina não encontrada no curso do aluno!\n");
        return lista_alunos;
    }

    if (busca_matricula(aluno->arvore_matriculas, codigo_disciplina) == 0){
        aluno->arvore_matriculas = inserirMatricula(aluno->arvore_matriculas, codigo_disciplina);
        printf("Matricula realizada com sucesso!\n");
    }
    else{
        printf("Aluno já cadastrado na disciplina!\n");
    }

    return lista_alunos;
}