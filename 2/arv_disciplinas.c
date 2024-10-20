#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gerenciamento.h"

No_disciplinas* criarARVORE_disciplinas(){
    return NULL;
}


int inserir_disciplina(No_disciplinas **raiz, int codigo_disciplina, char nome_disciplina[50], int carga_horaria, int periodo) {
    int resultado = 1;  // Variável para armazenar o resultado

    if (*raiz == NULL) {
        // Criamos o novo nó se a raiz é nula
        *raiz = (No_disciplinas*)malloc(sizeof(No_disciplinas));
        if (*raiz == NULL){
            printf("Erro ao alocar memória para o novo nó.\n");
            resultado = 0; // Falha na alocação de memória
        }
        else {
            (*raiz)->codigo_disciplina = codigo_disciplina;
            strcpy((*raiz)->nome_disciplina, nome_disciplina);
            (*raiz)->carga_horaria = carga_horaria;
            (*raiz)->periodo = periodo;
            (*raiz)->esq = NULL;
            (*raiz)->dir = NULL;
            (*raiz)->altura = 0;
              // Inserção bem-sucedida
        }
    } else if (codigo_disciplina < (*raiz)->codigo_disciplina) {
        resultado = inserir_disciplina(&(*raiz)->esq, codigo_disciplina, nome_disciplina, carga_horaria, periodo);
        if (resultado){
            if (fatorBalanceamentoDisciplinas(*raiz) >= 2){ // tenho que fazer essa para disciplina
                if (codigo_disciplina < (*raiz)->esq->codigo_disciplina){
                    *raiz = rotacaoDireitaDisciplinas(*raiz); // mesma coisa pra essa
                }
                else {
                    *raiz = rotacaoDuplaDireitaDisciplinas(*raiz); // mesma coisa pra essa
                }
            }
        }
    } else if (codigo_disciplina > (*raiz)->codigo_disciplina) {
        resultado = inserir_disciplina(&(*raiz)->dir, codigo_disciplina, nome_disciplina, carga_horaria, periodo);
        if (resultado) {
            if (fatorBalanceamentoDisciplinas(*raiz) >= 2) {
                if (codigo_disciplina > (*raiz)->dir->codigo_disciplina) {
                    *raiz = rotacaoEsquerdaDisciplinas(*raiz); // mesma coisa pra essa
                } else {
                    *raiz = rotacaoDuplaEsquerdaDisciplinas(*raiz); // mesma coisa pra essa
                }
            }
        }
    } else {
        resultado = 0;  // Disciplina já existe
    }

    if (resultado) {
        (*raiz)->altura = maior(alturaDisciplinas((*raiz)->esq), alturaDisciplinas((*raiz)->dir)) + 1; // mesma coisa pra função da altura
    }

    return resultado;  // Apenas um retorno
}


int alturaDisciplinas(No_disciplinas *raiz) {
    if (raiz == NULL) {
        return -1;
    } else {
        return raiz->altura;
    }
}

int fatorBalanceamentoDisciplinas(No_disciplinas *raiz) {
    return labs(alturaDisciplinas(raiz->esq) - alturaDisciplinas(raiz->dir));
}


No_disciplinas* rotacaoDireitaDisciplinas(No_disciplinas *raiz) {
    No_disciplinas *aux = raiz->esq;
    raiz->esq = aux->dir;
    aux->dir = raiz;
    raiz->altura = maior(alturaDisciplinas(raiz->esq), alturaDisciplinas(raiz->dir)) + 1;
    aux->altura = maior(alturaDisciplinas(aux->esq), raiz->altura) + 1;
    return aux;
}

No_disciplinas* rotacaoEsquerdaDisciplinas(No_disciplinas *raiz) {
    No_disciplinas *aux = raiz->dir;
    raiz->dir = aux->esq;
    aux->esq = raiz;
    raiz->altura = maior(alturaDisciplinas(raiz->esq), alturaDisciplinas(raiz->dir)) + 1;
    aux->altura = maior(alturaDisciplinas(aux->dir), raiz->altura) + 1;
    return aux;
}

No_disciplinas* rotacaoDuplaDireitaDisciplinas(No_disciplinas *raiz) {
    raiz->esq = rotacaoEsquerdaDisciplinas(raiz->esq);
    return rotacaoDireitaDisciplinas(raiz);
}

No_disciplinas* rotacaoDuplaEsquerdaDisciplinas(No_disciplinas *raiz) {
    raiz->dir = rotacaoDireitaDisciplinas(raiz->dir);
    return rotacaoEsquerdaDisciplinas(raiz);
}



No_curso* Cadastrar_disciplina(No_curso *raiz_curso){
    int codigo_curso;
    int codigo_disciplina;
    srand(time(NULL));

    if (raiz_curso == NULL) {
        printf("Nenhum curso cadastrado\n");
    }
    
    else
    {
        printf("Digite o codigo do curso: ");
        scanf("%d", &codigo_curso);
        

        No_curso *curso_exato = retornar_curso(raiz_curso, codigo_curso);
        

        if (curso_exato == NULL)
        {
            printf("Curso nao encontrado\n");
        }
        
        
        else{
            printf("Digite o codigo da disciplina: ");
            scanf("%d", &codigo_disciplina);
            printf("Digite o nome da disciplina: ");
            char nome_disciplina[50];
            scanf(" %[^\n]", nome_disciplina);
            printf("Digite a carga horaria da disciplina: ");
            int carga_horaria;
            scanf("%d", &carga_horaria);

            if (!verifica_carga_horaria(carga_horaria)){
                printf("Carga horaria invalida\n");
            }

            else
            {
                printf("Digite o periodo da disciplina: ");
                int periodo;
                scanf("%d", &periodo);

                int quant_periodos = retorna_periodo_curso(raiz_curso, codigo_curso);

                if (periodo > quant_periodos || periodo < 1){
                    printf("Periodo invalido\n");
                    
                }

                else
                {
                    if (inserir_disciplina(&(curso_exato->arvore_disciplinas), codigo_disciplina, nome_disciplina, carga_horaria, periodo)){
                        printf("Disciplina cadastrada com sucesso\n");
                    }
                    else{
                        printf("Erro ao cadastrar disciplina!\n");
                    }
                }
                
            }
        }     
        
    }
    
    return raiz_curso;
}



int busca_disciplina(No_disciplinas *raiz, int codigo_disciplina){
    int retorno = 0;
    
    if(raiz != NULL){
            if(raiz->codigo_disciplina == codigo_disciplina){
                retorno = 1;
            }else{
                if(codigo_disciplina < raiz->codigo_disciplina){
                    retorno = busca_disciplina(raiz->esq, codigo_disciplina);
                }else{
                    retorno = busca_disciplina(raiz->dir, codigo_disciplina);
                }
            }
    }
    return retorno;
}

int retorna_periodo_curso(No_curso *raiz, int valor) {
    int retorno = -1; 

    if (raiz != NULL) {
        if (raiz->codigo_curso == valor) {
            retorno = raiz->quant_periodos;  
        } else if (valor < raiz->codigo_curso) {
            retorno = retorna_periodo_curso(raiz->esq, valor);  
        } else {
            retorno = retorna_periodo_curso(raiz->dir, valor);  
        }
    }

    return retorno;  
}


int verifica_carga_horaria(int valor){
    int retorno = 0;
    if (valor % 15 ==0 && valor >= 30 && valor <= 90){
        retorno = 1;
    }
    return retorno;
}

void imprimir_pre_ordem_disciplinas(No_disciplinas *raiz){
    if (raiz != NULL) {
        printf("║ %-11d ║ %-25s ║ %-6d ║ %-7d ║\n",raiz->carga_horaria,raiz->nome_disciplina,raiz->codigo_disciplina, raiz->periodo);
        imprimir_pre_ordem_disciplinas(raiz->esq);
        imprimir_pre_ordem_disciplinas(raiz->dir);
    }
}

No_disciplinas* retorna_arvore_disciplinas(No_curso *raiz, int codigo_curso){
    No_disciplinas *retorno = NULL;

    if (raiz != NULL) {
        if (raiz->codigo_curso == codigo_curso) {
            retorno = raiz->arvore_disciplinas;
        } else if (codigo_curso < raiz->codigo_curso) {
            retorno = retorna_arvore_disciplinas(raiz->esq, codigo_curso);
        } else {
            retorno = retorna_arvore_disciplinas(raiz->dir, codigo_curso);
        }
    }

    return retorno;
}


void mostrar_disciplinas_de_um_curso(No_curso *raiz){

    if (raiz == NULL){
        printf("Nenhum curso cadastrado !\n");
    }

    else
    {

        int codigo_curso;
        printf("Digite o codigo do curso: ");
        scanf("%d", &codigo_curso);

        if (busca_curso(raiz, codigo_curso)){
            No_disciplinas *arvore_disciplinas = retorna_arvore_disciplinas(raiz, codigo_curso);


            printf("╔═════════════╦═══════════════════════════╦════════╦═════════╗\n");
            printf("║  CARGA HOR  ║    NOME DA DISCIPLINA     ║ CÓDIGO ║ PERÍODO ║\n");
            printf("╠═════════════╬═══════════════════════════╬════════╬═════════╣\n");
            imprimir_pre_ordem_disciplinas(arvore_disciplinas);
            
            printf("╚═════════════╩═══════════════════════════╩════════╩═════════╝\n");
        }
        else{
            printf("Curso nao encontrado ! \n");
        }
        
    }
    

    
}

void imprimir_pre_ordem_disciplinas_de_um_periodo(No_disciplinas *raiz, int periodo){
    if (raiz != NULL){
        if (raiz->periodo == periodo){
            printf("║ %-11d ║ %-25s ║ %-6d ║ %-7d ║\n",raiz->carga_horaria,raiz->nome_disciplina,raiz->codigo_disciplina, raiz->periodo);
        }
        imprimir_pre_ordem_disciplinas_de_um_periodo(raiz->esq, periodo);
        imprimir_pre_ordem_disciplinas_de_um_periodo(raiz->dir, periodo);
    }
}

void mostrar_disciplinas_de_um_periodo(No_curso *raiz){

    if (raiz == NULL){
        printf("Nenhum curso cadastrado !\n");
    }

    else
    {

        int codigo_curso;
        printf("Digite o codigo do curso: ");
        scanf("%d", &codigo_curso);

        if (busca_curso(raiz, codigo_curso)){

            No_curso *curso = retornar_curso(raiz, codigo_curso);
            int periodo;
            printf("Digite o periodo: ");
            scanf("%d", &periodo);
            if (periodo < 1 || periodo > curso->quant_periodos)
            {
                printf("Periodo invalido !\n");
            }
            
            else{

                if (curso->arvore_disciplinas == NULL){
                    printf("Nenhuma disciplina cadastrada !\n");
                    
                }
                else
                {
                    printf("╔═════════════╦═══════════════════════════╦════════╦═════════╗\n");
                    printf("║  CARGA HOR  ║    NOME DA DISCIPLINA     ║ CÓDIGO ║ PERÍODO ║\n");
                    printf("╠═════════════╬═══════════════════════════╬════════╬═════════╣\n");
                    imprimir_pre_ordem_disciplinas_de_um_periodo(curso->arvore_disciplinas, periodo);
                
                    printf("╚═════════════╩═══════════════════════════╩════════╩═════════╝\n");
                }
            }
            

            
        }
        else{
            printf("Curso nao encontrado ! \n");
        }
        
    }

}