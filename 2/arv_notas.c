#include <stdio.h>
#include <stdlib.h>
#include "gerenciamento.h"

No_notas* criarARVORE_notas(){
    return NULL;
}


int inserirNota(No_notas** raiz, int codigo_disciplina, int semestre, float nota_final) {
    int resultado = 1;  // Variável para armazenar o resultado

    if (*raiz == NULL) {
        // Criamos o novo nó se a raiz é nula
        *raiz = (No_notas*)malloc(sizeof(No_notas));
        if (*raiz == NULL){
            printf("Erro ao alocar memória para o novo nó.\n");
            return 0; // Falha na alocação de memória
        }

        // Inicializa o novo nó
        (*raiz)->codigo_disciplina = codigo_disciplina;
        (*raiz)->semestre_cursado = semestre;
        (*raiz)->nota_final = nota_final;
        (*raiz)->esq = (*raiz)->dir = NULL;
        (*raiz)->altura = 0;
    } 

    else if (codigo_disciplina < (*raiz)->codigo_disciplina) {
        resultado = inserirNota(&(*raiz)->esq, codigo_disciplina, semestre, nota_final);
        if (resultado){
            if (fatorBalanceamentoNotas(*raiz) >= 2){
                if (codigo_disciplina < (*raiz)->esq->codigo_disciplina){
                    *raiz = rotacaoDireitaNotas(*raiz);
                } else {
                    *raiz = rotacaoDuplaDireitaNotas(*raiz);
                }
            }
        }
    } 

    else if (codigo_disciplina > (*raiz)->codigo_disciplina) {
        resultado = inserirNota(&(*raiz)->dir, codigo_disciplina, semestre, nota_final);
        if (resultado) {
            if (fatorBalanceamentoNotas(*raiz) >= 2) {
                if (codigo_disciplina > (*raiz)->dir->codigo_disciplina) {
                    *raiz = rotacaoEsquerdaNotas(*raiz);
                } else {
                    *raiz = rotacaoDuplaEsquerdaNotas(*raiz);
                }
            }
        }
    }

    else {
        resultado = 0; // Disciplina já existe
    }

    if (resultado) {
        (*raiz)->altura = maior(alturaNotas((*raiz)->esq), alturaNotas((*raiz)->dir)) + 1;
    }

    return resultado;  // Retorna 1 para sucesso, 0 para falha
}


int alturaNotas(No_notas *raiz) {
    if (raiz == NULL) {
        return -1;
    } else {
        return raiz->altura;
    }
}

int fatorBalanceamentoNotas(No_notas *raiz) {
    return labs(alturaNotas(raiz->esq) - alturaNotas(raiz->dir));
}


No_notas* rotacaoDireitaNotas(No_notas *raiz) {
    No_notas *aux = raiz->esq;
    raiz->esq = aux->dir;
    aux->dir = raiz;
    raiz->altura = maior(alturaNotas(raiz->esq), alturaNotas(raiz->dir)) + 1;
    aux->altura = maior(alturaNotas(aux->esq), raiz->altura) + 1;
    return aux;
}

No_notas* rotacaoEsquerdaNotas(No_notas *raiz) {
    No_notas *aux = raiz->dir;
    raiz->dir = aux->esq;
    aux->esq = raiz;
    raiz->altura = maior(alturaNotas(raiz->esq), alturaNotas(raiz->dir)) + 1;
    aux->altura = maior(alturaNotas(aux->dir), raiz->altura) + 1;
    return aux;
}

No_notas* rotacaoDuplaDireitaNotas(No_notas *raiz) {
    raiz->esq = rotacaoEsquerdaNotas(raiz->esq);
    return rotacaoDireitaNotas(raiz);
}

No_notas* rotacaoDuplaEsquerdaNotas(No_notas *raiz) {
    raiz->dir = rotacaoDireitaNotas(raiz->dir);
    return rotacaoEsquerdaNotas(raiz);
}


No_matriculas* minimo(No_matriculas* raiz) {
    No_matriculas* atual = raiz;
    
    while (atual != NULL && atual->esq != NULL) {
        atual = atual->esq;
    }
    
    return atual;
}


/*int remover_matricula(No_matriculas** raiz, int codigo_disciplina) {
    int resultado = 0;  // Variável para armazenar o resultado

    if (*raiz != NULL) {
        if (codigo_disciplina < (*raiz)->codigo_disciplina) {
            resultado = remover_matricula(&(*raiz)->esq, codigo_disciplina);
        } else if (codigo_disciplina > (*raiz)->codigo_disciplina) {
            resultado = remover_matricula(&(*raiz)->dir, codigo_disciplina);
        } else {
            // Matricula encontrada e será removida
            No_matriculas* temp = NULL;

            // Caso 1: Nó sem filhos (nó folha)
            if ((*raiz)->esq == NULL && (*raiz)->dir == NULL) {
                free(*raiz);
                *raiz = NULL;
                resultado = 1;  // Remoção bem-sucedida
            }

            // Caso 2: Nó com um filho
            else if ((*raiz)->esq == NULL) {
                temp = (*raiz)->dir;
                free(*raiz);
                *raiz = temp;
                resultado = 1;  // Remoção bem-sucedida
            } else if ((*raiz)->dir == NULL) {
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

        // Passo 1: Se a remoção foi bem-sucedida, atualizar a altura
        if (*raiz != NULL) {
            (*raiz)->altura = maior(alturaMatriculas((*raiz)->esq), alturaMatriculas((*raiz)->dir)) + 1;

            // Passo 2: Verificar o fator de balanceamento e ajustar se necessário
            // int fator_balanceamento = fatorBalanceamentoMatriculas(*raiz);

            // Caso 1: Desbalanceado à esquerda
            if (fatorBalanceamentoMatriculas(*raiz) >= 2) {
                if (alturaMatriculas((*raiz)->esq->esq) >= alturaMatriculas((*raiz)->esq->dir)) {
                    // Rotação simples à direita
                    *raiz = rotacaoDireitaMatriculas(*raiz);
                } else {
                    // Rotação dupla à direita
                    *raiz = rotacaoDuplaDireitaMatriculas(*raiz);
                }
            }

            // Caso 2: Desbalanceado à direita
            else if (fatorBalanceamentoMatriculas(*raiz) >= 2) {
                if (alturaMatriculas((*raiz)->dir->dir) >= alturaMatriculas((*raiz)->dir->esq)) {
                    // Rotação simples à esquerda
                    *raiz = rotacaoEsquerdaMatriculas(*raiz);
                } else {
                    // Rotação dupla à esquerda
                    *raiz = rotacaoDuplaEsquerdaMatriculas(*raiz);
                }
            }
        }
    }

    // Retorna o resultado, 1 se a remoção foi bem-sucedida, 0 caso contrário
    return resultado;
}*/


int remover_matricula(No_matriculas** raiz, int codigo_disciplina) {
    int resultado = 0;  // Variável para armazenar o resultado

    if (*raiz != NULL) {
        if (codigo_disciplina < (*raiz)->codigo_disciplina) {
            resultado = remover_matricula(&(*raiz)->esq, codigo_disciplina);
        } else if (codigo_disciplina > (*raiz)->codigo_disciplina) {
            resultado = remover_matricula(&(*raiz)->dir, codigo_disciplina);
        } else {
            // Matricula encontrada e será removida
            No_matriculas* temp = NULL;

            // Caso 1: Nó sem filhos (nó folha)
            if ((*raiz)->esq == NULL && (*raiz)->dir == NULL) {
                free(*raiz);
                *raiz = NULL;
                resultado = 1;  // Remoção bem-sucedida
            }

            // Caso 2: Nó com um filho
            else if ((*raiz)->esq == NULL) {
                temp = (*raiz)->dir;
                free(*raiz);
                *raiz = temp;
                resultado = 1;  // Remoção bem-sucedida
            } else if ((*raiz)->dir == NULL) {
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

        // Se a remoção foi bem-sucedida, devemos balancear a árvore
        if (*raiz != NULL) {
            // Atualizar a altura do nó atual
            (*raiz)->altura = maior(alturaMatriculas((*raiz)->esq), alturaMatriculas((*raiz)->dir)) + 1;

            // Verificar o fator de balanceamento do nó atual
            int fator_balanceamento = fatorBalanceamentoMatriculas(*raiz);

            // Caso 1: Desbalanceado à esquerda
            if (fator_balanceamento > 1) {
                if (fatorBalanceamentoMatriculas((*raiz)->esq) >= 0) {
                    // Rotação simples à direita
                    *raiz = rotacaoDireitaMatriculas(*raiz);
                } else {
                    // Rotação dupla à direita
                    *raiz = rotacaoDuplaDireitaMatriculas(*raiz);
                }
            }

            // Caso 2: Desbalanceado à direita
            if (fator_balanceamento < -1) {
                if (fatorBalanceamentoMatriculas((*raiz)->dir) <= 0) {
                    // Rotação simples à esquerda
                    *raiz = rotacaoEsquerdaMatriculas(*raiz);
                } else {
                    // Rotação dupla à esquerda
                    *raiz = rotacaoDuplaEsquerdaMatriculas(*raiz);
                }
            }
        }
    }

    // Retorna o resultado, 1 se a remoção foi bem-sucedida, 0 caso contrário
    return resultado;
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

void mostrarNotaDeDisciplinaAutomatico(Elemento* lista_alunos, No_curso* arvore_cursos, int matricula_aluno, int codigo_disciplina) {
    Elemento* aluno = NULL;
    if (buscar_aluno(lista_alunos, matricula_aluno, &aluno)) {
        No_notas* notas = aluno->arvore_notas;
        No_disciplinas* disciplina = NULL;

        if (buscar_disciplina_no_curso(arvore_cursos, codigo_disciplina, &disciplina)) {
            while (notas != NULL) {
                if (notas->codigo_disciplina == codigo_disciplina) {
                    return;
                }

                if (codigo_disciplina < notas->codigo_disciplina) {
                    notas = notas->esq;
                } else {
                    notas = notas->dir;
                }
            }
            printf("Nota para a disciplina %d não encontrada.\n", codigo_disciplina);
        } else {
            printf("Disciplina não encontrada no curso!\n");
        }
    } else {
        printf("Aluno não encontrado!\n");
    }
}


No_notas* retorna_arvore_de_notas(Elemento* lista_alunos, int matricula_aluno) {
    
    Elemento* aux = lista_alunos;
    while (aux != NULL) {
        if (aux->matricula == matricula_aluno) {
           return aux->arvore_notas; 
        }
        aux = aux->prox;
    }
}