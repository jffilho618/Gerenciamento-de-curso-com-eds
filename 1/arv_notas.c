#include <stdio.h>
#include <stdlib.h>
#include "gerenciamento.h"

No_notas* criarARVORE_notas(){
    return NULL;
}


int inserirNota(No_notas** raiz, int codigo_disciplina, int semestre, float nota_final) {
    int resultado = 0;  // Variável para armazenar o resultado

    if (*raiz == NULL) {
        *raiz = (No_notas*)malloc(sizeof(No_notas));
        if (*raiz != NULL) {
            (*raiz)->codigo_disciplina = codigo_disciplina;
            (*raiz)->semestre_cursado = semestre;
            (*raiz)->nota_final = nota_final;
            (*raiz)->esq = (*raiz)->dir = NULL;
            resultado = 1;  // Inserção bem-sucedida
        }
    } 

    else if (codigo_disciplina < (*raiz)->codigo_disciplina) {
        resultado = inserirNota(&(*raiz)->esq, codigo_disciplina, semestre, nota_final);
    } 

    else if (codigo_disciplina > (*raiz)->codigo_disciplina) {
        resultado = inserirNota(&(*raiz)->dir, codigo_disciplina, semestre, nota_final);
    }

    return resultado;  // Retorna 1 para sucesso, 0 para falha
}


No_matriculas* minimo(No_matriculas* raiz) {
    No_matriculas* atual = raiz;
    
    while (atual != NULL && atual->esq != NULL) {
        atual = atual->esq;
    }
    
    return atual;
}


int remover_matricula(No_matriculas** raiz, int codigo_disciplina) {
    int resultado = 0;  // Variável para armazenar o resultado

    if (*raiz != NULL) {
        if (codigo_disciplina < (*raiz)->codigo_disciplina) {
            resultado = remover_matricula(&(*raiz)->esq, codigo_disciplina);
        } 
        
        else if (codigo_disciplina > (*raiz)->codigo_disciplina) {
            resultado = remover_matricula(&(*raiz)->dir, codigo_disciplina);
        } 
        
        else {
            // Matricula encontrada e será removida
            No_matriculas* temp = NULL;

            // Caso 1: Nó sem filhos (nó folha)
            if ((*raiz)->esq == NULL && (*raiz)->dir == NULL) {
                free(*raiz);
                *raiz = NULL;
                resultado = 1;
            }

            // Caso 2: Nó com um filho
            else if ((*raiz)->esq == NULL) {
                temp = (*raiz)->dir;
                free(*raiz);
                *raiz = temp;
                resultado = 1;  // Remoção bem-sucedida
            }
            else if ((*raiz)->dir == NULL) {
                temp = (*raiz)->esq;
                free(*raiz);
                *raiz = temp;
                resultado = 1;  // Remoção bem-sucedida
            }
            // Caso 3: Nó com dois filhos
            else {
                temp = minimo((*raiz)->dir);
                (*raiz)->codigo_disciplina = temp->codigo_disciplina;
                resultado = remover_matricula(&(*raiz)->dir, temp->codigo_disciplina);
            }
        }

        return resultado;  // Retorna 1 se a remoção for bem-sucedida, 0 caso contrário
    }

}


int busca_matricula(No_matriculas* raiz, int codigo_disciplina, No_matriculas** matricula_encontrada) {
    int resultado = 0;  // Variável para armazenar o resultado
    *matricula_encontrada = NULL;  // Inicialmente, nenhuma matrícula encontrada

    while (raiz != NULL) {
        if (codigo_disciplina == raiz->codigo_disciplina) {
            *matricula_encontrada = raiz;  // Matricula encontrada
            resultado = 1;  // Sucesso
            break;
        }

        if (codigo_disciplina < raiz->codigo_disciplina) {
            raiz = raiz->esq;
        } else {
            raiz = raiz->dir;
        }
    }

    return resultado;  // Retorna 1 para sucesso, 0 para falha
}



void cadastrarNota(Elemento* lista_alunos, No_curso* arvore_cursos) {
    int matricula_aluno, codigo_disciplina, semestre;
    float nota_final;

    printf("Digite a matricula do aluno: ");
    scanf("%d", &matricula_aluno);

    Elemento* aluno = NULL;
    if (buscar_aluno(lista_alunos, matricula_aluno, &aluno)){ // Aluno encontrado

        printf("Digite o código da disciplina: ");
        scanf("%d", &codigo_disciplina);

        No_matriculas* matricula = NULL;
        if (busca_matricula(aluno->arvore_matriculas, codigo_disciplina, &matricula)){
            printf("Digite o semestre em que a disciplina foi cursada: ");
            scanf("%d", &semestre);
            printf("Digite a nota final da disciplina: ");
            scanf("%f", &nota_final);

            int resultado_inserir = inserirNota(&(aluno->arvore_notas), codigo_disciplina, semestre, nota_final);
            int resultado_remover = remover_matricula(&(aluno->arvore_matriculas), codigo_disciplina);
            
            if (resultado_inserir) {
                if (resultado_remover) {
                    printf("Nota cadastrada e disciplina movida para o histórico de notas!\n");
                } else {
                    printf("Erro ao remover a disciplina da matrícula!\n");
                }
            } 
            else {
                printf("Erro ao cadastrar a nota!\n");
            }
        }

        else{
            printf("Aluno não está matriculado nesta disciplina!\n");
        }
    }

    else{
        printf("Aluno não encontrado!\n");
    }

    
}

void exibir_notas(No_notas* notas, int periodo, int* encontrou) {
    if (notas != NULL) {
        if (notas->semestre_cursado == periodo){
                printf("Disciplina: %d, Nota: %.2f\n", notas->codigo_disciplina, notas->nota_final);
                *encontrou = 1;
            }

        exibir_notas(notas->esq, periodo, encontrou);
        exibir_notas(notas->dir, periodo, encontrou);
    }
}

void mostrarNotasDePeriodo(Elemento* lista_alunos){
    int matricula_aluno, periodo;

    printf("Digite a matrícula do aluno: ");
    scanf("%d", &matricula_aluno);
    printf("Digite o período: ");
    scanf("%d", &periodo);

    Elemento* aluno = NULL;
    if (buscar_aluno(lista_alunos, matricula_aluno, &aluno)) {

        No_notas* notas = aluno->arvore_notas;
        int encontrou = 0;

        exibir_notas(notas, periodo, &encontrou);

        if (!encontrou){
            printf("Nenhuma disciplina encontrada para o período!\n");
        }
    }

    else{
        printf("Aluno não encontrado!\n");
    }
    
}


void mostrarNotaDeDisciplina(Elemento* lista_alunos, No_curso* arvore_cursos){
    int matricula_aluno, codigo_disciplina;

    printf("Digite a matrícula do aluno: ");
    scanf("%d", &matricula_aluno);
    printf("Digite o código da disciplina: ");
    scanf("%d", &codigo_disciplina);

    Elemento* aluno = NULL;
    if (buscar_aluno(lista_alunos, matricula_aluno, &aluno)) {

        No_notas *notas = aluno->arvore_notas;

        No_disciplinas* disciplina = NULL;
        if (buscar_disciplina_no_curso(arvore_cursos, codigo_disciplina, &disciplina)) {

            while (notas != NULL) {
                if (notas->codigo_disciplina == codigo_disciplina) {
                    printf("Disciplina: %s\n", disciplina->nome_disciplina);
                    printf("Período: %d, Carga Horária: %d\n", disciplina->periodo, disciplina->carga_horaria);
                    printf("Nota: %.2f\n", notas->nota_final);
                }
                
                if (codigo_disciplina < notas->codigo_disciplina) {
                    notas = notas->esq;
                } 
                
                else {
                    notas = notas->dir;
                }
            }

            printf("Nota para a disciplina %d não encontrada.\n", codigo_disciplina);
        }

        else{
            printf("Disciplina não encontrada no curso!\n");
        }
        
    }

    else{
        printf("Aluno não encontrado!\n");
    }

}