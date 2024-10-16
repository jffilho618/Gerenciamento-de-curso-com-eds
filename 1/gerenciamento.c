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
    printf("║ [1] SISTEMA ABB                                    ║\n");
    printf("║ [2] TESTES DE TEMPO NA ABB                         ║\n");
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
    printf("║ [1] PREENCHER ARVORE CURSOS ALEATORIOS ABB         ║\n");
    printf("║ [2] PREENCHER ARVORE CURSOS CRESCENTE  ABB         ║\n");
    printf("║ [3] PREENCHER ARVORE CURSOS DECRESCENTE  ABB       ║\n");
    printf("║ [4] TESTE DE INSERCAO ABB                          ║\n");
    printf("║ [5] TAMANHO DA ARVORE                              ║\n");
    printf("║ [6] PRENCHER ALUNOS E DISCIPLINAS ABB              ║\n");
    printf("║ [7] TESTE DE BUSCA ABB                             ║\n");
    printf("║ [0] SAIR                                           ║\n");
    printf("╚════════════════════════════════════════════════════╝\n\n");
}

No_curso* cadastra_curso_automatico_aleatorio(No_curso *Raiz) {
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

No_curso* cadastra_curso_automatico_crescente(No_curso *Raiz) {
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
                if (inserir_curso(&Raiz, i+1, nome_curso, quant_periodos)) {
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

No_curso* cadastra_curso_automatico_decrescente(No_curso *Raiz) {
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
                if (inserir_curso(&Raiz, i+1, nome_curso, quant_periodos)) {
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

        if (inserir_curso(&raiz, codigo_curso, nome_curso, quant_periodos)) {
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


// Função para ler o arquivo de dados (alunos, disciplinas, matrículas)
void cadastrarAlunosEmCurso(Elemento** lista_alunos, No_curso** arvore_cursos) {
    FILE *file_alunos, *file_disciplinas;
    int codigo_curso = 23249;  // Código fixo do curso

    if (inserir_curso(arvore_cursos, codigo_curso, "Ciencia da Computacao", 8)) {
        printf("Curso inserido com sucesso.\n");
    } else {
        printf("Erro ao inserir o curso.\n");
        return;
    }

    // Abrindo o arquivo de alunos
    file_alunos = fopen("alunos.txt", "r");
    if (file_alunos == NULL) {
        printf("Erro ao abrir o arquivo de alunos.\n");
        return;
    }

    // Lendo os dados de alunos
    char line[256];
    while (fgets(line, sizeof(line), file_alunos)) {
        int matricula;
        char nome[50];
        sscanf(line, "%d;%[^;];%d", &matricula, nome, &codigo_curso);
        printf("Cadastrando aluno: %s, matrícula: %d\n", nome, matricula); // Depuração
        *lista_alunos = addOrdenado_alfabetico(*lista_alunos, matricula, nome, codigo_curso);
    }
    fclose(file_alunos);
    printf("Todos os alunos foram cadastrados.\n"); // Depuração

    // Abrindo o arquivo de disciplinas
    file_disciplinas = fopen("disciplinas.txt", "r");
    if (file_disciplinas == NULL) {
        printf("Erro ao abrir o arquivo de disciplinas.\n");
        return;
    }

    // Lendo os dados de disciplinas e inserindo no curso
    while (fgets(line, sizeof(line), file_disciplinas)) {
        int codigo_disciplina, carga_horaria, periodo;
        char nome_disciplina[50];
        sscanf(line, "%d;%[^;];%d;%d;%d", &codigo_disciplina, nome_disciplina, &carga_horaria, &periodo, &codigo_curso);

        printf("Inserindo disciplina: %s (código: %d) no curso %d\n", nome_disciplina, codigo_disciplina, codigo_curso);  // Depuração
        No_curso* curso = NULL;
        if (buscar_no_curso(*arvore_cursos, codigo_curso, &curso)) {
            inserir_disciplina(&(curso->arvore_disciplinas), codigo_disciplina, nome_disciplina, carga_horaria, periodo);
        } else {
            printf("Curso %d não encontrado!\n", codigo_curso);
        }
    }
    fclose(file_disciplinas);
    printf("Todas as disciplinas foram cadastradas no curso.\n");  // Depuração

    // Matricular aluno específico em todas as disciplinas após cadastrá-las
    int matricula_aluno_especifico = 7581;  // Exemplo de aluno a ser matriculado em todas as disciplinas
    Elemento* aluno = NULL;
    if (!buscar_aluno(*lista_alunos, matricula_aluno_especifico, &aluno)) {
        printf("Aluno com matrícula %d não encontrado.\n", matricula_aluno_especifico);
        return;
    }

    // Matricular o aluno em todas as disciplinas agora que elas já foram inseridas
    file_disciplinas = fopen("disciplinas.txt", "r");
    if (file_disciplinas == NULL) {
        printf("Erro ao abrir o arquivo de disciplinas.\n");
        return;
    }

    while (fgets(line, sizeof(line), file_disciplinas)) {
        int codigo_disciplina;
        sscanf(line, "%d;%*[^;];%*d;%*d;%*d", &codigo_disciplina);  // Lê apenas o código da disciplina

        printf("Matriculando aluno %d na disciplina (código: %d)\n",matricula_aluno_especifico, codigo_disciplina);  // Depuração
        *lista_alunos = cadastrarMatriculaAutomatico(*lista_alunos, *arvore_cursos, matricula_aluno_especifico, codigo_disciplina);
    }
    fclose(file_disciplinas);

    // Cadastrando notas aleatórias para o aluno nas disciplinas
    cadastrarNotasAleatorias(aluno, *arvore_cursos);
    printf("Aluno com matrícula %d foi matriculado em todas as disciplinas e recebeu notas aleatórias.\n", matricula_aluno_especifico);
}



void medirTempoBuscaNota(Elemento* lista_alunos, No_curso* arvore_cursos, int matricula_aluno, int codigo_disciplina) {
    LARGE_INTEGER frequency, start_time, end_time;
    long long total_nanos_sum = 0;

    // Obtém a frequência do contador de alta resolução
    QueryPerformanceFrequency(&frequency);

    // Repetir a busca 30 vezes para calcular a média
    for (int i = 0; i < 30; i++) {
        QueryPerformanceCounter(&start_time);

        // Chama a função de busca da nota
        mostrarNotaDeDisciplinaAutomatico(lista_alunos, arvore_cursos, matricula_aluno, codigo_disciplina);

        QueryPerformanceCounter(&end_time);

        // Calcular o tempo total de busca em nanosegundos
        long long total_nanos = (end_time.QuadPart - start_time.QuadPart) * 1000000000 / frequency.QuadPart;
        total_nanos_sum += total_nanos;
    }

    // Calcula a média
    long long media_nanos = total_nanos_sum / 30;
    printf("Tempo médio de busca da nota: %lld nanosegundos\n", media_nanos);
}


Elemento* cadastrarMatriculaAutomatico(Elemento* lista_alunos, No_curso* arvore_cursos, int matricula_aluno, int codigo_disciplina) {
    Elemento* aluno = NULL;

    // Busca o aluno pela matrícula
    if (buscar_aluno(lista_alunos, matricula_aluno, &aluno)) { // Aluno encontrado
        No_disciplinas* disciplina_encontrada = NULL;
        
        // Busca a disciplina no curso
        if (buscar_disciplina_no_curso(arvore_cursos, codigo_disciplina, &disciplina_encontrada)) { // Disciplina encontrada
            // Verifica se o aluno já está matriculado na disciplina
            if (inserirMatricula(&(aluno->arvore_matriculas), codigo_disciplina)) {
                printf("Matricula realizada com sucesso!\n");
            } else {
                printf("Aluno já cadastrado na disciplina!\n");
            }
        } else {
            printf("Disciplina não encontrada no curso do aluno!\n");
        }
    } else {
        printf("Aluno não encontrado!\n");
    }

    return lista_alunos;
}


void cadastrarNotasAleatorias(Elemento* aluno, No_curso* arvore_cursos) {
    No_matriculas* matriculas = aluno->arvore_matriculas;

    srand(time(NULL));  // Inicializa a seed para geração de números aleatórios
    while (matriculas != NULL) {
        // Gera uma nota aleatória entre 0 e 10
        float nota_aleatoria = (float)(rand() % 1001) / 100.0;

        // Cadastra a nota aleatória para a disciplina
        printf("Cadastrando nota %.2f para a disciplina %d.\n", nota_aleatoria, matriculas->codigo_disciplina);

        if(inserirNota(&(aluno->arvore_notas), matriculas->codigo_disciplina, 1 + (rand() % 8), nota_aleatoria)) {
            // Remove a matrícula da disciplina
            matriculas = matriculas->esq;
            matriculas = matriculas->dir;
        }
        
        else {
            printf("Erro ao cadastrar a nota.\n");
        }

         
    }
}

void cadastrarNotaAutomatica(Elemento* aluno, No_curso* arvore_cursos, int codigo_disciplina, float nota) {
    No_disciplinas* disciplina = NULL;
    if (buscar_disciplina_no_curso(arvore_cursos, codigo_disciplina, &disciplina)) {
        // Gera um semestre aleatório (para fins de demonstração)
        int semestre = 1 + (rand() % 8);  // Semestre entre 1 e 8
        inserirNota(&(aluno->arvore_notas), codigo_disciplina, semestre, nota);
        remover_matricula(&(aluno->arvore_matriculas), codigo_disciplina);
        printf("Nota %.2f cadastrada para a disciplina %s (código %d).\n", nota, disciplina->nome_disciplina, codigo_disciplina);
    }
    else {
        printf("Disciplina não encontrada no curso do aluno.\n");
    }
}