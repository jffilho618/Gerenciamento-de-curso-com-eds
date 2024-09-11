#ifndef GERENCIAMENTO_H
#define GERENCIAMENTO_H
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
    char periodo[10];
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
}No_curso;

No_curso* criarARVORE();
No_curso* inserir(No_curso *raiz, int valor);
int tamanho(No_curso *raiz);
int busca(No_curso *raiz, int valor);
void imprimir_pre_ordem(No_curso *raiz);
void imprimir_em_ordem(No_curso *raiz);
void imprimir_pos_ordem(No_curso *raiz);
No_curso* remover(No_curso *raiz,int valor);
No_curso* buscar_no(No_curso *raiz, int valor);
int altura(No_curso *raiz);
int altura_no(No_curso *raiz, int valor);
No_curso* libera_arvore(No_curso *raiz);

typedef struct elemento{
    int matricula;
    char nome[50];
    int codigo_curso;
    No_notas *arvore_notas;
    No_matriculas *arvore_matriculas;
    struct  elemento *prox;
    struct elemento *ant;
}Elemento;

Elemento *criaLista(); 
Elemento *addInicio(Elemento *l); 
Elemento *addFinal(Elemento *l);
Elemento *addOrdenadoCrescente(Elemento *l);
Elemento *removerElemento(Elemento *l);
int tamanhoDaLista(Elemento *l);
void mostrarLista(Elemento *l); 
void menu();

void menu_principal();
void questao1();
#endif