#ifndef GERENCIAMENTO_H
#define GERENCIAMENTO_H

#include <stdio.h>
#include <stdlib.h>
typedef struct no_notas{
    int codigo_disciplina;
    int semestre_cursado;
    float nota_final;
    struct no_notas *esq;
    struct no_notas *dir;
}No_notas;

typedef struct no_matriculas{
    int codigo_disciplina;
    struct no_matriculas *esq;
    struct no_matriculas *dir;
}No_matriculas;

typedef struct no_disciplinas{
    int codigo_disciplina;
    char nome_disciplina[50];
    int carga_horaria;
    int periodo;
    struct no_disciplinas *esq;
    struct no_disciplinas *dir;
}No_disciplinas;

typedef struct no_curso{
    int codigo_curso;
    char nome_curso[50];
    int quant_periodos;
    No_disciplinas *arvore_disciplinas;
    struct no_curso *esq;
    struct no_curso *dir;
    int altura;
}No_curso;

typedef struct elemento{
    int matricula;
    char nome[50];
    int codigo_curso;
    No_notas *arvore_notas;
    No_matriculas *arvore_matriculas;
    struct  elemento *prox;
    struct elemento *ant;
}Elemento;


No_disciplinas* criarARVORE_disciplinas();
int inserir_disciplina(No_disciplinas **raiz, int valor, char nome_disciplina[50], int carga_horaria, int periodo);
No_curso* Cadastrar_disciplina(No_curso *raiz_curso);
int busca_disciplina(No_disciplinas *raiz, int valor);
int verifica_carga_horaria(int valor);
void imprimir_pre_ordem_disciplinas(No_disciplinas *raiz);
void mostrar_disciplinas_de_um_periodo(No_curso *raiz);
void imprimir_pre_ordem_disciplinas_de_um_aluno_matriculado(No_disciplinas *raiz_disciplinas, No_matriculas *raiz_matriculas);
void imprimir_pre_ordem_disciplinas_de_um_periodo(No_disciplinas *raiz, int periodo);
No_disciplinas* retorna_arvore_disciplinas(No_curso *raiz, int codigo_curso);
void mostrar_disciplinas_de_um_curso(No_curso *Raiz);


No_curso* criarARVOREcursos();
int inserir_curso(No_curso **raiz, long long int codigo_curso, char nome_curso[50], int quant_periodos);
No_curso* CadastrarCurso(No_curso *raiz);
int tamanho(No_curso *raiz);
int busca_curso(No_curso *raiz, int codigo_curso);
int retorna_periodo_curso(No_curso *raiz, int codigo_curso);
No_curso *retornar_curso(No_curso *raiz, int codigo_curso);
void mostrar_todos_os_cursos(No_curso *raiz);
void imprimir_pre_ordem(No_curso *raiz);
void imprimir_em_ordem(No_curso *raiz);
void imprimir_pos_ordem(No_curso *raiz);
No_curso* remover(No_curso *raiz,int codigo_curso);
No_curso* buscar_no(No_curso *raiz, int codigo_curso);
No_curso* libera_arvore(No_curso *raiz);
void printa_tamanho(No_curso *raiz);



Elemento *criaLista_alunos(); 
Elemento *addInicio(Elemento *l); 
Elemento *addFinal(Elemento *l);
Elemento *addOrdenado_alfabetico(Elemento *l, int matricula, char nome[50], int codigo_curso);
Elemento* Cadastrar_aluno(Elemento *l, No_curso *raiz);
Elemento *removerElemento(Elemento *l);
Elemento *retorna_aluno(Elemento *l, int matricula);        
int tamanhoDaLista(Elemento *l);
void mostrarLista(Elemento *l);
void alunos_de_um_curso(Elemento *l);
int busca_matricula_aluno(Elemento *l, int matricula);


// iv) Cadastrar uma matrícula, onde a mesma é uma árvore organizada e contendo somente um código de
// uma disciplina do curso do aluno. 
No_matriculas* criarARVORE_matriculas();
No_matriculas* inserirMatricula(No_matriculas* raiz, int codigo_disciplina);
Elemento* cadastrarMatricula(Elemento* lista_alunos, No_curso* arvore_cursos);
Elemento* buscar_aluno(Elemento* lista_alunos, int matricula_aluno);
No_disciplinas* buscar_disciplina_no_curso(No_curso* raiz_curso, int codigo_disciplina);
No_disciplinas* buscar_disciplina(No_disciplinas* raiz, int codigo_disciplina);
No_matriculas* remover_matricula(No_matriculas* raiz, int codigo_disciplina);
No_matriculas* retorna_arvore_matriculas(Elemento* lista_alunos, int matricula_aluno);
void mostrar_disciplinas_de_um_aluno_matriculado(Elemento* lista_alunos, No_curso* arvore_cursos);


// v) Cadastrar Notas, permitir o cadastro de notas somente de disciplinas que estejam na árvore de
// matricula, e quando a nota for cadastrada a disciplina deve ser removida da árvore de matricula para
// árvore de notas. 
No_notas* criarARVORE_notas();
No_notas* inserirNota(No_notas* raiz, int codigo_disciplina, int semestre, float nota_final);
Elemento* cadastrarNota(Elemento* lista_alunos);
No_matriculas* minimo(No_matriculas* raiz);
No_matriculas* busca_matricula(No_matriculas* raiz, int codigo_disciplina);


// xi) Mostrar todas as notas de disciplinas de um determinado período de um determinado aluno.
void mostrarNotasDePeriodo(Elemento* lista_alunos);


// xii) Mostrar a nota de uma disciplina de um determinado aluno, mostrando o período e a carga horária da
// disciplina. 
void mostrarNotaDeDisciplina(Elemento* lista_alunos, No_curso* arvore_cursos);


//xiii)Remover uma disciplina de um determinado curso desde que não tenha nenhum aluno matriculado na
// mesma
void remover_disciplina_se_possivel(No_curso* arvore_cursos, Elemento* lista_alunos);
No_curso* buscar_no_curso(No_curso* raiz, int codigo_curso);
No_disciplinas* remover_disciplina_curso(No_disciplinas* raiz, int codigo_disciplina);
No_disciplinas* minimo_disciplina(No_disciplinas* raiz);


// xiv)Permita remover uma disciplina da árvore de matrícula de um determinado aluno. 
void remover_disciplina_matricula(Elemento* lista_alunos);


// xv) Mostrar o histórico de um determinado aluno, contendo o nome do curso, as disciplinas e sua respectiva
// nota organizadas pelo período que a disciplina está cadastrada no curso. 
void mostrar_historico_aluno(Elemento* lista_alunos, No_curso* arvore_cursos);
No_disciplinas* buscar_disciplina_historico(No_disciplinas* raiz, int codigo_disciplina);


 
void menu();
void menu_principal();
void questao1();
void menu_testes();
No_curso* cadastra_curso_automatico_aleatorio(No_curso *raiz);
No_curso* cadastra_curso_automatico_crescente(No_curso *raiz);
No_curso* cadastra_curso_automatico_decrescente(No_curso *raiz);
No_curso* teste_insercao_ARVBB(No_curso *raiz);





No_curso* cadastrar_curso_avl(No_curso *raiz);
No_curso* cadastra_curso_automatico_aleatorio_avl(No_curso *raiz);
No_curso* cadastra_curso_automatico_crescente_avl(No_curso *raiz);
No_curso* cadastra_curso_automatico_decrescente_avl(No_curso *raiz);
int inserir_curso_avl(No_curso **raiz, long long int codigo_curso, char nome_curso[50], int quant_periodos);
int altura(No_curso *raiz);
int fatorBalanceamento(No_curso *raiz);
int maior(int x, int y);
No_curso* rotacaoDireita(No_curso *raiz);
No_curso* rotacaoEsquerda(No_curso *raiz);
No_curso* rotacaoDuplaDireita(No_curso *raiz);
No_curso* rotacaoDuplaEsquerda(No_curso *raiz);





#endif