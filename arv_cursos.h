#ifndef ARV_CURSOS_H
#define ARV_CURSOS_H
#include <stdio.h>
#include <stdlib.h>
#include "gerenciamento.h"

typedef struct no_curso{
    int codigo_curso;
    char nome_curso[50];
    int quant_periodos;
    No_disciplinas *arvore_disciplinas;
    struct no_curso *esq;
    struct no_curso *dir;
}No_curso;

No_curso* criarARVOREcursos();
No_curso* inserir_curso(No_curso *raiz, int valor, char nome_curso[50], int quant_periodos);
No_curso* CadastrarCurso(No_curso *raiz);
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
#endif