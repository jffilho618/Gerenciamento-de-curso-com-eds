#ifndef LISTA_ALUNOS_H
#define LISTA_ALUNOS_H
#include <stdio.h>
#include <stdlib.h>
#include "gerenciamento.h"
#include "arv_cursos.h"


typedef struct elemento{
    int matricula;
    char nome[50];
    int codigo_curso;
    No_notas *arvore_notas;
    No_matriculas *arvore_matriculas;
    struct  elemento *prox;
    struct elemento *ant;
}Elemento;

Elemento *criaLista_alunos(); 
Elemento *addInicio(Elemento *l); 
Elemento *addFinal(Elemento *l);
Elemento *addOrdenado_alfabetico(Elemento *l, int matricula, char nome[50], int codigo_curso);
Elemento* Cadastrar_aluno(Elemento *l, No_curso *raiz);
Elemento *removerElemento(Elemento *l);
int tamanhoDaLista(Elemento *l);
void mostrarLista(Elemento *l);
void alunos_de_um_curso(Elemento *l);

#endif