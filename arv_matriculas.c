#include <stdio.h>
#include <stdlib.h>
#include "gerenciamento.h"
#include <string.h>

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


Elemento* retorna_aluno(Elemento* lista_alunos, int matricula_aluno){
    Elemento* atual = lista_alunos;

    while (atual != NULL){
        if (atual->matricula == matricula_aluno){
            return atual;
        }
        atual = atual->prox;
    }

    return NULL;
}

No_matriculas* retorna_arvore_matriculas(Elemento* lista_alunos, int matricula_aluno){
    Elemento* aluno = retorna_aluno(lista_alunos, matricula_aluno);
    if (aluno == NULL){
        printf("Aluno não encontrado!\n");
        return NULL;
    }

    return aluno->arvore_matriculas;
}

void imprimir_pre_ordem_disciplinas_de_um_aluno_matriculado(No_disciplinas *raiz_disciplinas, No_matriculas *raiz_matriculas){
    if (raiz_disciplinas != NULL){
        imprimir_pre_ordem_disciplinas_de_um_aluno_matriculado(raiz_disciplinas->esq, raiz_matriculas);

        if (busca_matricula(raiz_matriculas, raiz_disciplinas->codigo_disciplina)){
            printf("║ %-11d ║ %-25s ║ %-6d ║ %-7d ║\n",raiz_disciplinas->carga_horaria,raiz_disciplinas->nome_disciplina,raiz_disciplinas->codigo_disciplina, raiz_disciplinas->periodo);
        }

        imprimir_pre_ordem_disciplinas_de_um_aluno_matriculado(raiz_disciplinas->dir, raiz_matriculas);
    }
}

void mostrar_disciplinas_de_um_aluno_matriculado(Elemento* lista_alunos, No_curso* arvore_cursos){
    int matricula_aluno;

    printf("Digite a matricula do aluno: ");
    scanf("%d", &matricula_aluno);

    Elemento* aluno = retorna_aluno(lista_alunos, matricula_aluno);

    No_curso *curso = retornar_curso(arvore_cursos, aluno->codigo_curso);
    if (curso == NULL){
        printf("Curso não encontrado!\n");
        return;
    }
    
    printf("╔═════════════╦═══════════════════════════╦════════╦═════════╗\n");
    printf("║  CARGA HOR  ║    NOME DA DISCIPLINA     ║ CÓDIGO ║ PERÍODO ║\n");
    printf("╠═════════════╬═══════════════════════════╬════════╬═════════╣\n");
    imprimir_pre_ordem_disciplinas_de_um_aluno_matriculado(curso->arvore_disciplinas, aluno->arvore_matriculas);
    printf("╚═════════════╩═══════════════════════════╩════════╩═════════╝\n");
    
}


// xiii


No_curso* buscar_no_curso(No_curso* raiz, int codigo_curso) {
    // Se a árvore estiver vazia ou se o código do curso for encontrado
    if (raiz == NULL || raiz->codigo_curso == codigo_curso) {
        return raiz;
    }

    // Se o código do curso a ser buscado for menor, percorre a subárvore esquerda
    if (codigo_curso < raiz->codigo_curso) {
        return buscar_no_curso(raiz->esq, codigo_curso);
    }

    // Se o código do curso a ser buscado for maior, percorre a subárvore direita
    return buscar_no_curso(raiz->dir, codigo_curso);
}


No_disciplinas* minimo_disciplina(No_disciplinas* raiz) {
    No_disciplinas* atual = raiz;
    
    // Percorre a subárvore esquerda para encontrar o menor valor
    while (atual != NULL && atual->esq != NULL) {
        atual = atual->esq;
    }

    return atual;
}



No_disciplinas* remover_disciplina_curso(No_disciplinas* raiz, int codigo_disciplina) {
    if (raiz == NULL) {
        return NULL;  // A disciplina não foi encontrada
    }

    // Percorre a árvore até encontrar o nó (disciplina) a ser removido
    if (codigo_disciplina < raiz->codigo_disciplina) {
        raiz->esq = remover_disciplina_curso(raiz->esq, codigo_disciplina);
    } else if (codigo_disciplina > raiz->codigo_disciplina) {
        raiz->dir = remover_disciplina_curso(raiz->dir, codigo_disciplina);
    } else {
        // Disciplina encontrada

        // Caso 1: Nó sem filhos (nó folha)
        if (raiz->esq == NULL && raiz->dir == NULL) {
            free(raiz);
            return NULL;
        }

        // Caso 2: Nó com um filho
        if (raiz->esq == NULL) {
            No_disciplinas* temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            No_disciplinas* temp = raiz->esq;
            free(raiz);
            return temp;
        }

        // Caso 3: Nó com dois filhos
        // Encontra o sucessor (menor valor da subárvore direita)
        No_disciplinas* sucessor = minimo_disciplina(raiz->dir);
        
        // Substitui os valores do nó atual com o sucessor
        raiz->codigo_disciplina = sucessor->codigo_disciplina;
        strcpy(raiz->nome_disciplina, sucessor->nome_disciplina);
        raiz->carga_horaria = sucessor->carga_horaria;
        raiz->periodo = sucessor->periodo;

        // Remove o sucessor da subárvore direita
        raiz->dir = remover_disciplina_curso(raiz->dir, sucessor->codigo_disciplina);
    }

    return raiz;
}



No_disciplinas* buscar_disciplina_historico(No_disciplinas* raiz, int codigo_disciplina) {
    if (raiz == NULL) {
        return NULL;  
    }

    if (codigo_disciplina == raiz->codigo_disciplina) {
        return raiz;
    }

    if (codigo_disciplina < raiz->codigo_disciplina) {
        return buscar_disciplina_historico(raiz->esq, codigo_disciplina);
    }

    return buscar_disciplina_historico(raiz->dir, codigo_disciplina);
}



void remover_disciplina_se_possivel(No_curso* arvore_cursos, Elemento* lista_alunos) {
    int codigo_curso, codigo_disciplina;

    printf("Digite o código do curso: ");
    scanf("%d", &codigo_curso);
    printf("Digite o código da disciplina: ");
    scanf("%d", &codigo_disciplina);

    // Busca o curso na árvore
    No_curso* curso = buscar_no_curso(arvore_cursos, codigo_curso);
    if (curso == NULL) {
        printf("Curso não encontrado.\n");
        return;
    }

    // Verificando se algum aluno está matriculado na disciplina
    Elemento* aluno_atual = lista_alunos;
    while (aluno_atual != NULL) {
        if (busca_matricula(aluno_atual->arvore_matriculas, codigo_disciplina) != NULL) {
            printf("Disciplina não pode ser removida, há alunos matriculados.\n");
            return;
        }
        aluno_atual = aluno_atual->prox;
    }

    // Verificando se a disciplina existe antes da remoção
    if (buscar_disciplina_historico(curso->arvore_disciplinas, codigo_disciplina) == NULL) {
        printf("Disciplina não encontrada no curso.\n");
        return;
    }

    // Removendo a disciplina da árvore de disciplinas
    curso->arvore_disciplinas = remover_disciplina_curso(curso->arvore_disciplinas, codigo_disciplina);
    printf("Disciplina removida com sucesso.\n");
}



// xiv

void remover_disciplina_matricula(Elemento* lista_alunos) {
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

    if (busca_matricula(aluno->arvore_matriculas, codigo_disciplina) == NULL) {
        printf("Disciplina não encontrada na árvore de matrículas do aluno.\n");
        return;
    }

    aluno->arvore_matriculas = remover_matricula(aluno->arvore_matriculas, codigo_disciplina);
    printf("Disciplina removida da matrícula do aluno.\n");
}


// xv

void mostrar_historico_aluno(Elemento* lista_alunos, No_curso* arvore_cursos) {
    int matricula_aluno;

    printf("Digite a matrícula do aluno: ");
    scanf("%d", &matricula_aluno);

    Elemento* aluno = buscar_aluno(lista_alunos, matricula_aluno);
    if (aluno == NULL) {
        printf("Aluno não encontrado!\n");
        return;
    }

    No_curso* curso = buscar_no_curso(arvore_cursos, aluno->codigo_curso);
    if (curso == NULL) {
        printf("Curso não encontrado!\n");
        return;
    }

    printf("Histórico do aluno %s (Matrícula: %d) - Curso: %s\n", aluno->nome, aluno->matricula, curso->nome_curso);
    printf("Período | Código Disciplina | Nome Disciplina | Nota | Carga Horária\n");
    printf("--------------------------------------------------------------\n");

    No_notas* notas = aluno->arvore_notas;
    while (notas != NULL) {
        No_disciplinas* disciplina = buscar_disciplina_historico(curso->arvore_disciplinas, notas->codigo_disciplina);
        if (disciplina != NULL) {
            printf("%d | %d | %s | %.2f | %d\n", disciplina->periodo, disciplina->codigo_disciplina, disciplina->nome_disciplina, notas->nota_final, disciplina->carga_horaria);
        }

        notas = (notas->esq != NULL) ? notas->esq : notas->dir;
    }
}
