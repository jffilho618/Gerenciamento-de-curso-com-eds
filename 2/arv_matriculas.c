#include <stdio.h>
#include <stdlib.h>
#include "gerenciamento.h"
#include <string.h>

No_matriculas* criarARVORE_matriculas(){
    return NULL;
}


int inserirMatricula(No_matriculas** raiz, int codigo_disciplina){
    int resultado = 1; // Variável para armazenar o resultado

    if (*raiz == NULL){
        // Criamos o novo nó se a raiz é nula
        *raiz = (No_matriculas*)malloc(sizeof(No_matriculas));
        if (*raiz != NULL){
            (*raiz)->codigo_disciplina = codigo_disciplina;
            (*raiz)->esq = NULL;
            (*raiz)->dir = NULL;
            // Inserção bem-sucedida
        }
    }

    else if (codigo_disciplina < (*raiz)->codigo_disciplina)
        resultado = inserirMatricula(&(*raiz)->esq, codigo_disciplina);
    
    else if (codigo_disciplina > (*raiz)->codigo_disciplina)
        resultado = inserirMatricula(&(*raiz)->dir, codigo_disciplina);

    else{
        resultado = 0; // Disciplina já existe
    }

    return resultado;
}


int buscar_aluno(Elemento* lista_alunos, int matricula_aluno, Elemento** aluno_encontrado){
    int resultado = 0;
    *aluno_encontrado = NULL;

    Elemento* atual = lista_alunos;
    while (atual != NULL) {
        if (atual->matricula == matricula_aluno) {
            *aluno_encontrado = atual;
            resultado = 1;  // Aluno encontrado
        }
        atual = atual->prox;
    }

    return resultado;
}


int buscar_disciplina(No_disciplinas* raiz, int codigo_disciplina, No_disciplinas** disciplina_encontrada) {
    int resultado = 0;  // Variável para armazenar o resultado
    *disciplina_encontrada = NULL;  // Inicialmente, nenhuma disciplina encontrada

    if (raiz != NULL) {
        if (codigo_disciplina == raiz->codigo_disciplina) {
            *disciplina_encontrada = raiz;
            resultado = 1;  // Disciplina encontrada
        } else if (codigo_disciplina < raiz->codigo_disciplina) {
            resultado = buscar_disciplina(raiz->esq, codigo_disciplina, disciplina_encontrada);
        } else {
            resultado = buscar_disciplina(raiz->dir, codigo_disciplina, disciplina_encontrada);
        }
    }

    return resultado;
}



int buscar_disciplina_no_curso(No_curso* raiz_curso, int codigo_disciplina, No_disciplinas** disciplina_encontrada) {
    int resultado = 0;  // Variável para armazenar o resultado
    *disciplina_encontrada = NULL;  // Inicialmente, nenhuma disciplina encontrada

    while (raiz_curso != NULL) {
        if (buscar_disciplina(raiz_curso->arvore_disciplinas, codigo_disciplina, disciplina_encontrada)) {
            resultado = 1;  // Disciplina encontrada no curso
        }

        if (codigo_disciplina < raiz_curso->codigo_curso) {
            raiz_curso = raiz_curso->esq;
        } 
        
        else {
            raiz_curso = raiz_curso->dir;
        }
    }

    return resultado;
}



Elemento* cadastrarMatricula(Elemento* lista_alunos, No_curso* arvore_cursos){
    int matricula_aluno, codigo_disciplina;

    printf("Digite a matricula do aluno: ");
    scanf("%d", &matricula_aluno);

    Elemento* aluno = NULL;
    if (buscar_aluno(lista_alunos, matricula_aluno, &aluno)){ // Aluno encontrado!!

        printf("Digite o código da disciplina: ");
        scanf("%d", &codigo_disciplina);
        
        No_disciplinas* disciplina_encontrada = NULL;
        if (buscar_disciplina_no_curso(arvore_cursos, codigo_disciplina, &disciplina_encontrada)) { // Disciplina encontrada!!
            // printf("Disciplina não encontrada no curso do aluno!\n");
            // return lista_alunos;

            if (inserirMatricula(&(aluno->arvore_matriculas), codigo_disciplina)){
                printf("Matricula realizada com sucesso!\n");
            }
            else{
                printf("Aluno já cadastrado na disciplina!\n");
            }
        }

        else{
            printf("Disciplina não encontrada no curso do aluno!\n");
        }

    }

    else{
        printf("Aluno não encontrado!\n");
    }

    return lista_alunos;
}


Elemento* retorna_aluno(Elemento* lista_alunos, int matricula_aluno){
    Elemento* atual = lista_alunos;
    Elemento* aux = NULL;

    while (atual != NULL){
        if (atual->matricula == matricula_aluno){
            aux = atual;
        }
        atual = atual->prox;
    }

    return aux;
}

No_matriculas* retorna_arvore_matriculas(Elemento* lista_alunos, int matricula_aluno, No_matriculas** arvore_matriculas){
    int resultado = 0;  // Variável para armazenar o resultado
    *arvore_matriculas = NULL;  // Inicialmente, nenhuma árvore de matrículas encontrada

    Elemento* aluno = retorna_aluno(lista_alunos, matricula_aluno);
    if (aluno) {
        *arvore_matriculas = aluno->arvore_matriculas;  // Retorna a árvore de matrículas
        resultado = 1;  // Sucesso
    } else {
        printf("Aluno não encontrado!\n");
    }

    return *arvore_matriculas;  // Retorna 1 para sucesso, 0 para falha

}

void imprimir_pre_ordem_disciplinas_de_um_aluno_matriculado(No_disciplinas *raiz_disciplinas, No_matriculas *raiz_matriculas){
    if (raiz_disciplinas != NULL){
        imprimir_pre_ordem_disciplinas_de_um_aluno_matriculado(raiz_disciplinas->esq, raiz_matriculas);

        No_matriculas* matricula = NULL;
        if (busca_matricula(raiz_matriculas, raiz_disciplinas->codigo_disciplina, &matricula)){
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
    if (curso != NULL){
        // printf("Curso não encontrado!\n");
        // return;

        printf("╔═════════════╦═══════════════════════════╦════════╦═════════╗\n");
        printf("║  CARGA HOR  ║    NOME DA DISCIPLINA     ║ CÓDIGO ║ PERÍODO ║\n");
        printf("╠═════════════╬═══════════════════════════╬════════╬═════════╣\n");
        imprimir_pre_ordem_disciplinas_de_um_aluno_matriculado(curso->arvore_disciplinas, aluno->arvore_matriculas);
        printf("╚═════════════╩═══════════════════════════╩════════╩═════════╝\n");
    }
    
    else{
        printf("Curso não encontrado!\n");
    }
    
}


// xiii


int buscar_no_curso(No_curso* raiz, int codigo_curso, No_curso** curso_encontrado) {
    // Se a árvore estiver vazia ou se o código do curso for encontrado
    int resultado = 0;  // Variável para armazenar o resultado
    *curso_encontrado = NULL;  // Inicialmente, nenhum curso encontrado

    while (raiz != NULL) {
        if (codigo_curso == raiz->codigo_curso) {
            *curso_encontrado = raiz;  // Curso encontrado
            resultado = 1;  // Sucesso
        }

        // Se o código do curso for menor, percorre a subárvore esquerda
        if (codigo_curso < raiz->codigo_curso) {
            raiz = raiz->esq;
        }
        // Se o código do curso for maior, percorre a subárvore direita
        else {
            raiz = raiz->dir;
        }
    }

    return resultado;  // Retorna 1 se o curso for encontrado, 0 caso contrário
}


No_disciplinas* minimo_disciplina(No_disciplinas* raiz) {
    No_disciplinas* atual = raiz;
    
    // Percorre a subárvore esquerda para encontrar o menor valor
    while (atual != NULL && atual->esq != NULL) {
        atual = atual->esq;
    }

    return atual;
}



int remover_disciplina_curso(No_disciplinas** raiz, int codigo_disciplina) {
    int resultado = 0;

    if (*raiz != NULL) {
        // Percorre a árvore até encontrar o nó (disciplina) a ser removido
        if (codigo_disciplina < (*raiz)->codigo_disciplina) {
            resultado = remover_disciplina_curso(&(*raiz)->esq, codigo_disciplina);
        } 
        
        else if (codigo_disciplina > (*raiz)->codigo_disciplina) {
            resultado = remover_disciplina_curso(&(*raiz)->dir, codigo_disciplina);
        } 
        
        else {
            // Disciplina encontrada

            // No_disciplinas* temp = NULL;

            // Caso 1: Nó sem filhos (nó folha)
            if ((*raiz)->esq == NULL && (*raiz)->dir == NULL) {
                free(*raiz);
                *raiz = NULL;
                resultado = 1;
            }

            // Caso 2: Nó com um filho
            else if ((*raiz)->esq == NULL) {
                No_disciplinas* temp = (*raiz)->dir;
                free(*raiz);
                *raiz = temp;
                resultado = 1;
            } else if ((*raiz)->dir == NULL) {
                No_disciplinas* temp = (*raiz)->esq;
                free(*raiz);
                *raiz = temp;
                resultado = 1;
            }

            // Caso 3: Nó com dois filhos
            else{
                No_disciplinas* temp = minimo_disciplina((*raiz)->dir);
                (*raiz)->codigo_disciplina = temp->codigo_disciplina;
                resultado = remover_disciplina_curso(&(*raiz)->dir, temp->codigo_disciplina);
            }

        }
    }

    return resultado;
}



int buscar_disciplina_historico(No_disciplinas* raiz, int codigo_disciplina, No_disciplinas** disciplina_encontrada) {
    int resultado = 0;  // Variável para armazenar o resultado
    *disciplina_encontrada = NULL;  // Inicialmente, nenhuma disciplina encontrada

    while (raiz != NULL) {
        if (codigo_disciplina == raiz->codigo_disciplina) {
            *disciplina_encontrada = raiz;  // Disciplina encontrada
            resultado = 1;  // Sucesso
            break;
        }

        // Se o código da disciplina for menor, busca na subárvore esquerda
        if (codigo_disciplina < raiz->codigo_disciplina) {
            raiz = raiz->esq;
        }
        // Se o código da disciplina for maior, busca na subárvore direita
        else {
            raiz = raiz->dir;
        }
    }

    return resultado;  // Retorna 1 para sucesso, 0 para falha
}



void remover_disciplina_se_possivel(No_curso* arvore_cursos, Elemento* lista_alunos) {
    int codigo_curso, codigo_disciplina;

    printf("Digite o código do curso: ");
    scanf("%d", &codigo_curso);
    printf("Digite o código da disciplina: ");
    scanf("%d", &codigo_disciplina);

    // Busca o curso na árvore
    No_curso* curso = NULL;
    if (buscar_no_curso(arvore_cursos, codigo_curso, &curso)) { // Curso encontrado!!

        // Verificando se algum aluno está matriculado na disciplina
        Elemento* aluno_atual = lista_alunos;
        while (aluno_atual != NULL) {
            No_matriculas* matricula_encontrada = NULL;
            if (busca_matricula(aluno_atual->arvore_matriculas, codigo_disciplina, &matricula_encontrada)) {
                printf("Disciplina não pode ser removida, há alunos matriculados.\n");
            }
            aluno_atual = aluno_atual->prox;
        }

        // Verificando se a disciplina existe antes da remoção
        No_disciplinas* disciplina_encontrada = NULL;
        if (buscar_disciplina_historico(curso->arvore_disciplinas, codigo_disciplina, &disciplina_encontrada)) {

            // Removendo a disciplina da árvore de disciplinas
            if (remover_disciplina_curso(&(curso->arvore_disciplinas), codigo_disciplina)) {
                printf("Disciplina removida com sucesso.\n");
            } 
            
            else {
                printf("Erro ao remover a disciplina.\n");
            }
        }

        else{
            printf("Disciplina não encontrada no curso.\n");
        }
    }

    else{
        printf("Curso não encontrado.\n");
    }
    
}



// xiv

void remover_disciplina_matricula(Elemento* lista_alunos) {
    int matricula_aluno, codigo_disciplina;

    // Coletando as informações
    printf("Digite a matrícula do aluno: ");
    scanf("%d", &matricula_aluno);
    printf("Digite o código da disciplina: ");
    scanf("%d", &codigo_disciplina);

    // Busca o aluno na lista
    Elemento* aluno = NULL;
    if (buscar_aluno(lista_alunos, matricula_aluno, &aluno)) { // Aluno encontrado
        
        // Verifica se a disciplina está na árvore de matrículas do aluno
        No_matriculas* matricula = NULL;
        if (busca_matricula(aluno->arvore_matriculas, codigo_disciplina, &matricula)) { // Disciplina encontrada
            
            // Remove a disciplina da árvore de matrículas
            if(remover_matricula(&(aluno->arvore_matriculas), codigo_disciplina)){
                printf("Disciplina removida da matrícula do aluno.\n");
            }
            else{
                printf("Erro ao remover a disciplina!\n");
            }
        }

        else{
            printf("Disciplina não encontrada na árvore de matrículas do aluno.\n");
        }
        
    }

    else{
        printf("Aluno não encontrado!\n");
    }  
}


// xv

void mostrar_historico_aluno(Elemento* lista_alunos, No_curso* arvore_cursos) {
    int matricula_aluno;

    // Coletando as informações
    printf("Digite a matrícula do aluno: ");
    scanf("%d", &matricula_aluno);

    // Busca o aluno na lista
    Elemento* aluno = NULL;
    if (buscar_aluno(lista_alunos, matricula_aluno, &aluno)) { // Aluno encontrado

        // Busca o curso do aluno
        No_curso* curso = NULL;
        if (buscar_no_curso(arvore_cursos, aluno->codigo_curso, &curso)) { // Curso encontrado

            // Exibindo o histórico do aluno
            printf("Histórico do aluno %s (Matrícula: %d) - Curso: %s\n", aluno->nome, aluno->matricula, curso->nome_curso);
            printf("Período | Código Disciplina | Nome Disciplina | Nota | Carga Horária\n");
            printf("--------------------------------------------------------------\n");

            // Percorre a árvore de notas do aluno
            No_notas* notas = aluno->arvore_notas;
            while (notas != NULL) {
                No_disciplinas* disciplina = NULL;
                if (buscar_disciplina_historico(curso->arvore_disciplinas, notas->codigo_disciplina, &disciplina)) {
                    printf("%d | %d | %s | %.2f | %d\n", disciplina->periodo, disciplina->codigo_disciplina, disciplina->nome_disciplina, notas->nota_final, disciplina->carga_horaria);
                }

                notas = (notas->esq != NULL) ? notas->esq : notas->dir;
            }
        }

        else{
            printf("Curso não encontrado!\n");
        }
        
    }

    else{
        printf("Aluno não encontrado!\n");
    }
    
}