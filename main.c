#include "gerenciamento.h"
#include "arv_cursos.h"
#include <stdio.h>
#include <stdlib.h>

int main(){

    int op1,op2;
    Elemento *lista_alunos = criaLista();
    No_curso *arv_cursos = criarARVOREcursos();

    do{ 
        menu_principal();
        scanf("%d", &op1);
        switch (op1){
            case 1:
                
                do{

                    questao1();
                    scanf("%d",&op2);
                    switch(op2){
                        case 1:
                            arv_cursos = CadastrarCurso(arv_cursos);
                            break;
                        case 2:
                            //lista_alunos = CadastrarAluno(lista_alunos);
                            break;
                        case 3:
                            //lista_alunos = CadastrarDisciplina(lista_alunos);
                            break;
                        case 4:
                            //lista_alunos = CadastrarMatricula(lista_alunos);
                            break;
                        case 0:
                            break;
                        default:
                            printf("Opção inválida!\n");
                            break;
                    }
                }while(op2!=0);
                break;
            case 2:
                //questao2();
                break;
            case 3:
                //sobre();
                break;
            case 0:
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    }while(op1 != 0);
}