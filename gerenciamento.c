#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gerenciamento.h"
#include <sys/time.h>
#include "RNG64.h"


void menu_principal()
{
    printf("\n");
    printf("╔════════════════TRABALHO══════════════╗\n");
    printf("║ [1] SISTEMA DESBALANCEADO            ║\n");
    printf("║ [2] TESTE DESBALANCEADO              ║\n");
    printf("║ [3] SISTEMA BALANCEADO               ║\n");
    printf("║ [4] TESTE BALANCEAMENTO              ║\n");
    printf("║ [5] SOBRE                            ║\n");
    printf("║ [0] SAIR                             ║\n");
    printf("╚══════════════════════════════════════╝\n\n");
}

void questao1()
{
    printf("\n");
    printf("╔═════════════════MENU═════════════════╗\n");
    printf("║ [1] CADASTRAR CURSO                  ║\n");
    printf("║ [2] CADASTRAR ALUNO                  ║\n");
    printf("║ [3] CADASTRAR DISCIPLINA             ║\n");
    printf("║ [4] CADASTRAR MATRICULA              ║\n");
    printf("║ [5] CADASTRAR NOTA                   ║\n");
    printf("║ [6] MOSTRAR TODOS ALUNOS DE UM CURSO ║\n");
    printf("║ [7] MOSTRAR TODOS OS CURSOS          ║\n");
    printf("║ [8] MOSTRAR DISCIPLINAS DE UM CURSO  ║\n");
    printf("║ [9] MOSTRAR DISCIPLINAS DE UM PERIODO║\n");
    printf("║ [10] MOSTRAR DISCIPLINAS DE UM ALUNO ║\n");
    printf("║ [11] MOSTRAR NOTAS DE UM PERÍODO     ║\n");
    printf("║ [12] MOSTRAR NOTAS DE DISCIPLINA     ║\n");
    printf("║ [13] REMOVER UMA DISCIPLINA CURSO    ║\n");
    printf("║ [14] REMOVER UMA DISCIPLINA ARV. MAT.║\n");
    printf("║ [15] MOSTRAR HISTORICO               ║\n");
    printf("║ [0] SAIR                             ║\n");
    printf("╚══════════════════════════════════════╝\n\n");
}

void menu_testes(){
    printf("╔═════════════════TESTES═══════════════╗\n");
    printf("║ [1] TESTE DE INSERCAO                ║\n");
    printf("║ [2] TAMANHO DA ARVORE                ║\n");
    printf("║ [0] SAIR                             ║\n");
    printf("╚══════════════════════════════════════╝\n\n");
}

No_curso* cadastra_curso_automatico(No_curso *Raiz) {
    rng64_randomize(); // Inicializa o gerador de números aleatórios
    FILE *arq;
    long long int codigo_curso;
    char nome_curso[50];
    int quant_periodos;
    arq = fopen("cursos.txt", "r");
    if (arq == NULL) {
        printf("Não foi possível abrir o arquivo cursos.txt.\n");
        
    }

    else{
        rng64_intrange_spec range;
        rng64_set_intrange(&range, 1, 1000000000);
        // Medir o tempo de inserção
        struct timeval start_time, end_time;
        gettimeofday(&start_time, NULL);
        for (int i = 0; i < 10000000; i++) {
            fscanf(arq, "%s", nome_curso);
            quant_periodos = 8 + (rand() % 3);
            do
            {
            } while (!inserir_curso(&Raiz, rng64_intrange(&range), nome_curso, quant_periodos));
            
            
        }
        fclose(arq);
        gettimeofday(&end_time, NULL);

        // Calcular o tempo total de inserção
        double time_taken = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 10000000000.0;
        printf("Tempo de inserção: %f segundos\n", time_taken);
    }

    return Raiz;
}



int tamanho(No_curso *raiz){
    if(raiz == NULL){
        return 0;
    }else{
        return 1 + tamanho(raiz->esq) + tamanho(raiz->dir);
    }
}

void printa_tamanho(No_curso *raiz){
    printf("Tamanho da arvore: %d\n", tamanho(raiz));
}

