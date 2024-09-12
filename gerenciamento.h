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