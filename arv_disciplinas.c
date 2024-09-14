#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gerenciamento.h"

No_disciplinas* criarARVORE_disciplinas(){
    return NULL;
}


No_disciplinas* inserir_disciplina(No_disciplinas *raiz, int valor, char nome_disciplina[50], int carga_horaria, int periodo){
    if(raiz == NULL){
        No_disciplinas *novo = (No_disciplinas*)malloc(sizeof(No_disciplinas));
        novo->codigo_disciplina = valor;
        strcpy(novo->nome_disciplina, nome_disciplina);
        novo->carga_horaria = carga_horaria;
        novo->periodo = periodo;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }else{
        if(valor < raiz->codigo_disciplina){
            raiz->esq = inserir_disciplina(raiz->esq, valor, nome_disciplina, carga_horaria, periodo);
        }else{
            raiz->dir = inserir_disciplina(raiz->dir, valor, nome_disciplina, carga_horaria, periodo);
        }
    }
    return raiz;
}

No_disciplinas* Cadastrar_disciplina(No_disciplinas *raiz, No_curso *raiz_curso){
    int codigo_curso;
    srand(time(NULL));

    if (raiz_curso == NULL) {
        printf("Nenhum curso cadastrado\n");
        return raiz;
    }
    
    printf("Digite o codigo do curso: ");
    scanf("%d", &codigo_curso);
    if (busca_curso(raiz_curso, codigo_curso)){
        printf("Digite o código da disciplina: ");
        int codigo_disciplina;
        scanf("%d", &codigo_disciplina);

        if (busca_disciplina(raiz, codigo_disciplina)){
            printf("Disciplina já cadastrada\n");
            return raiz;
        }
        printf("Digite o nome da disciplina: ");
        char nome_disciplina[50];
        scanf("%s", nome_disciplina);
        printf("Digite a carga horaria da disciplina: ");
        int carga_horaria;
        scanf("%d", &carga_horaria);

        if (!verifica_carga_horaria(carga_horaria)){
            printf("Carga horaria invalida\n");
            return raiz;
        }

        printf("Digite o periodo da disciplina: ");
        int periodo;
        scanf("%d", &periodo);

        int quant_periodos = busca_periodo_curso(raiz_curso, codigo_curso);

        if (periodo > quant_periodos || periodo < 1){
            printf("Periodo invalido\n");
            return raiz;
        }
        raiz = inserir_disciplina(raiz, codigo_disciplina, nome_disciplina, carga_horaria, periodo);
        printf("Disciplina cadastrada com sucesso\n");
    }
    else{
        printf("Curso nao cadastrado\n");
        return raiz;
    }
    return raiz;
}



int busca_disciplina(No_disciplinas *raiz, int valor){
    if(raiz == NULL){
        return 0;
    }else{
        if(raiz->codigo_disciplina == valor){
            return 1;
        }else{
            if(valor < raiz->codigo_disciplina){
                return busca_disciplina(raiz->esq, valor);
            }else{
                return busca_disciplina(raiz->dir, valor);
            }
        }
    }
}

int busca_periodo_curso(No_curso *raiz, int valor){
    if(raiz == NULL){
        return 0;
    }else{
        if(raiz->codigo_curso == valor){
            return raiz->quant_periodos;
        }else{
            if(valor < raiz->codigo_curso){
                return busca_curso(raiz->esq, valor);
            }else{
                return busca_curso(raiz->dir, valor);
            }
        }
    }
}

int verifica_carga_horaria(int valor){
    if (valor % 15 ==0 && valor >= 30 && valor <= 90){
        return 1;
    }
    return 0;
}

