#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gerenciamento.h"

No_disciplinas* criarARVORE_disciplinas(){
    return NULL;
}


No_disciplinas* inserir_disciplina(No_disciplinas *raiz, int valor, char nome_disciplina[50], int carga_horaria, int periodo){
    No_disciplinas *novo = raiz;
    if(raiz == NULL){
        novo = (No_disciplinas*)malloc(sizeof(No_disciplinas));
        novo->codigo_disciplina = valor;
        strcpy(novo->nome_disciplina, nome_disciplina);
        novo->carga_horaria = carga_horaria;
        novo->periodo = periodo;
        novo->esq = NULL;
        novo->dir = NULL;
    }else{
        if(valor < raiz->codigo_disciplina){
            raiz->esq = inserir_disciplina(raiz->esq, valor, nome_disciplina, carga_horaria, periodo);
        }else{
            raiz->dir = inserir_disciplina(raiz->dir, valor, nome_disciplina, carga_horaria, periodo);
        }
    }
    return novo;
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
        if (busca_curso(raiz_curso, codigo_curso)){

            No_curso *curso_exato = retornar_curso(raiz_curso, codigo_curso);
            No_disciplinas *raiz_disciplinas = curso_exato->arvore_disciplinas;
            

            do
            {
                codigo_disciplina = rand() % 100+1;
            } while (busca_disciplina(raiz_disciplinas, codigo_disciplina));
            
            
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

                int quant_periodos = busca_periodo_curso(raiz_curso, codigo_curso);

                if (periodo > quant_periodos || periodo < 1){
                    printf("Periodo invalido\n");
                    
                }

                else
                {
                    curso_exato->arvore_disciplinas = inserir_disciplina(curso_exato->arvore_disciplinas, codigo_disciplina, nome_disciplina, carga_horaria, periodo);

                    printf("Disciplina cadastrada com sucesso\n");
                }
                
            }
                
            
            
        }
        else{
            printf("Curso nao cadastrado\n");
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
                    return busca_disciplina(raiz->esq, codigo_disciplina);
                }else{
                    return busca_disciplina(raiz->dir, codigo_disciplina);
                }
            }
    }
    return retorno;
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
                No_disciplinas *arvore_disciplinas = retorna_arvore_disciplinas(raiz, codigo_curso);

                if (arvore_disciplinas == NULL){
                    printf("Nenhuma disciplina cadastrada !\n");
                    
                }
                else
                {
                    printf("╔═════════════╦═══════════════════════════╦════════╦═════════╗\n");
                    printf("║  CARGA HOR  ║    NOME DA DISCIPLINA     ║ CÓDIGO ║ PERÍODO ║\n");
                    printf("╠═════════════╬═══════════════════════════╬════════╬═════════╣\n");
                    imprimir_pre_ordem_disciplinas_de_um_periodo(arvore_disciplinas, periodo);
                
                    printf("╚═════════════╩═══════════════════════════╩════════╩═════════╝\n");
                }
            }
            

            
        }
        else{
            printf("Curso nao encontrado ! \n");
        }
        
    }

}