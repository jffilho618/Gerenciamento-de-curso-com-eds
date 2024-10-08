#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gerenciamento.h"
#include <sys/time.h>
#include "RNG64.h"
#include <windows.h>
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"


void menu_principal()
{
    printf("\n");
    printf("╔═══════════════════════TRABALHO═════════════════════╗\n");
    printf("║ [1] SISTEMA AVL                                    ║\n");
    printf("║ [2] TESTES DE TEMPO NA ARVORE DE BUSCA             ║\n");
    printf("║ [3] SOBRE                                          ║\n");
    printf("║ [0] SAIR                                           ║\n");
    printf("╚════════════════════════════════════════════════════╝\n\n");
}

void questao1()
{
    printf("\n");
    printf("╔════════════════════════MENU════════════════════════╗\n");
    printf("║ [1] CADASTRAR CURSO                                ║\n");
    printf("║ [2] CADASTRAR ALUNO                                ║\n");
    printf("║ [3] CADASTRAR DISCIPLINA                           ║\n");
    printf("║ [4] CADASTRAR MATRICULA                            ║\n");
    printf("║ [5] CADASTRAR NOTA                                 ║\n");
    printf("║ [6] MOSTRAR TODOS ALUNOS DE UM CURSO               ║\n");
    printf("║ [7] MOSTRAR TODOS OS CURSOS                        ║\n");
    printf("║ [8] MOSTRAR DISCIPLINAS DE UM CURSO                ║\n");
    printf("║ [9] MOSTRAR DISCIPLINAS DE UM PERIODO              ║\n");
    printf("║ [10] MOSTRAR DISCIPLINAS DE UM ALUNO               ║\n");
    printf("║ [11] MOSTRAR NOTAS DE UM PERÍODO                   ║\n");
    printf("║ [12] MOSTRAR NOTAS DE DISCIPLINA                   ║\n");
    printf("║ [13] REMOVER UMA DISCIPLINA CURSO                  ║\n");
    printf("║ [14] REMOVER UMA DISCIPLINA ARV. MAT.              ║\n");
    printf("║ [15] MOSTRAR HISTORICO                             ║\n");
    printf("║ [0] SAIR                                           ║\n");
    printf("╚════════════════════════════════════════════════════╝\n\n");
}

void menu_testes(){
    printf("╔════════════════════════TESTES══════════════════════╗\n");
    printf("║ [1] PREENCHER ARVORE CURSOS ALEATORIOS AVL         ║\n");
    printf("║ [2] PREENCHER ARVORE CURSOS CRESCENTES  AVL        ║\n");
    printf("║ [3] PREENCHER ARVORE CURSOS DECRESCENTES  AVL      ║\n");
    printf("║ [4] TESTE DE INSERCAO AVL                          ║\n");
    printf("║ [5] TAMANHO DA ARVORE                              ║\n");
    printf("║ [6] PREENCHER ARVORE DISCIPLINAS ALEATORIAS AVL    ║\n");
    printf("║ [7] PREENCHER ARVORE DISCIPLINAS CRESCENTES  AVL   ║\n");
    printf("║ [8] PREENCHER ARVORE DISCIPLINAS DECRESCENTES AVL  ║\n");
    printf("║ [9] TESTE BUSCA AVL                                ║\n");
    printf("║ [0] SAIR                                           ║\n");
    printf("╚════════════════════════════════════════════════════╝\n\n");
}


No_curso* teste_insercao_ARVBB(No_curso *raiz) {

    FILE *arq;
    arq = fopen("tempos_decrescentes.txt", "a");

    int vet[] = {131, 23249, 2956, 10231, 592, 8321, 6234, 1237, 18239, 4123};
    printf("Informe o nome do curso: ");
    char nome_curso[50];
    scanf(" %49[^\n]", nome_curso);

    printf("Informe a quantidade de periodos: ");
    int quant_periodos;
    scanf("%d", &quant_periodos);
    
    LARGE_INTEGER frequency, start_time, end_time;
    long long total_nanos_sum = 0;

    // Obtém a frequência do contador de alta resolução
    QueryPerformanceFrequency(&frequency);

    for (int i = 0; i < 10; i++) {
        int codigo_curso = vet[i];
        
        QueryPerformanceCounter(&start_time);

        if (inserir_curso_avl(&raiz, codigo_curso, nome_curso, quant_periodos)) {
            // Curso inserido com sucesso
            QueryPerformanceCounter(&end_time);

            // Calcular o tempo total de inserção em nanosegundos
            long long total_nanos = (end_time.QuadPart - start_time.QuadPart) * 1000000000 / frequency.QuadPart;

            // Acumular os tempos
            total_nanos_sum += total_nanos;

        } else {
            printf("erro");
        }
    }

    // Exibir o tempo total de inserção
    printf("Tempo total de inserção: %lld nanossegundos\n", total_nanos_sum);
    printf("Tempo total de inserção: %f microssegundos\n", total_nanos_sum / 1000.0);
    float milisegundos = total_nanos_sum / 1000000.0;
    printf("Tempo total de inserção: %f milissegundos\n", milisegundos);
    printf("Tempo total de inserção: %f segundos\n", total_nanos_sum / 1000000000.0);


    fprintf(arq, "%f\n", milisegundos);
    fclose(arq);
    
    return raiz;
}

int tamanho(No_curso *raiz){
    int retorno = 0;
    if(raiz == NULL){
        retorno = 0;
    }else{
        retorno = 1 + tamanho(raiz->esq) + tamanho(raiz->dir);
    }
}

void printa_tamanho(No_curso *raiz){
    printf("Tamanho da arvore: %d\n", tamanho(raiz));
}


No_curso* cadastra_curso_automatico_aleatorio_avl(No_curso *Raiz) {
    rng64_randomize(); // Inicializa o gerador de números aleatórios
    FILE *arq;
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
        for (int i = 0; i < 26000; i++) {
            fscanf(arq, "%s", nome_curso);
            quant_periodos = 8 + (rand() % 3);
            do
            {
            } while (!inserir_curso_avl(&Raiz, rng64_intrange(&range), nome_curso, quant_periodos));
            
            
        }
        fclose(arq);
        gettimeofday(&end_time, NULL);

        // Calcular o tempo total de inserção
        double time_taken = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 10000000000.0;
        printf("Tempo de inserção: %f segundos\n", time_taken);
    }

    return Raiz;
}

No_curso* cadastra_curso_automatico_crescente_avl(No_curso *Raiz) {
    rng64_randomize(); // Inicializa o gerador de números aleatórios
    FILE *arq;
    char nome_curso[50];
    int quant_periodos;
    arq = fopen("cursos.txt", "r");
    if (arq == NULL) {
        printf("Não foi possível abrir o arquivo cursos.txt.\n");
        
    }

    else{
        // Medir o tempo de inserção
        struct timeval start_time, end_time;
        gettimeofday(&start_time, NULL);
        for (int i = 0; i < 25000; i++) {
            //printf("i: %d\n", i+1);
            fscanf(arq, "%s", nome_curso);
            quant_periodos = 8 + (rand() % 3);
            
            if (i+1!=131 && i+1!=23249 && i+1!=2956 && i+1!=10231 && i+1!=592 && i+1!=8321 && i+1!=6234 && i+1!=1237 && i+1!=18239 && i+1!=4123){
                if (inserir_curso_avl(&Raiz, i+1, nome_curso, quant_periodos)) {
                    //printf("Curso inserido com sucesso\n");
                } else {
                    //printf("O curso já está cadastrado\n");
                }
            }
            
            
        }
        fclose(arq);
        gettimeofday(&end_time, NULL);

        // Calcular o tempo total de inserção
        double time_taken = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 10000000000.0;
        printf("Tempo de inserção: %f segundos\n", time_taken);
    }

    return Raiz;
}

No_curso* cadastra_curso_automatico_decrescente_avl(No_curso *Raiz) {
    rng64_randomize(); // Inicializa o gerador de números aleatórios
    FILE *arq;
    char nome_curso[50];
    int quant_periodos;
    arq = fopen("cursos.txt", "r");
    if (arq == NULL) {
        printf("Não foi possível abrir o arquivo cursos.txt.\n");
        
    }

    else{
        // Medir o tempo de inserção
        struct timeval start_time, end_time;
        gettimeofday(&start_time, NULL);
        for (int i = 25000; i > 0 ; i--) {
            //printf("i: %d\n", i-1);
            fscanf(arq, "%s", nome_curso);
            quant_periodos = 8 + (rand() % 3);
            if (i+1!=131 && i+1!=23249 && i+1!=2956 && i+1!=10231 && i+1!=592 && i+1!=8321 && i+1!=6234 && i+1!=1237 && i+1!=18239 && i+1!=4123){
                if (inserir_curso_avl(&Raiz, i+1, nome_curso, quant_periodos)) {
                    //printf("Curso inserido com sucesso\n");
                } else {
                    //printf("O curso já está cadastrado\n");
                }
            }
            
        }
        fclose(arq);
        gettimeofday(&end_time, NULL);

        // Calcular o tempo total de inserção
        double time_taken = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000000.0;
        printf("Tempo de insercao: %f segundos\n", time_taken);
    }

    return Raiz;
}
