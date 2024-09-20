#include "gerenciamento.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(){

    int op1,op2,op3;
    Elemento *lista_alunos = criaLista_alunos();
    No_curso *arv_cursos = criarARVOREcursos();
    No_disciplinas *arv_disciplinas = criarARVORE_disciplinas();
    srand(time(NULL));

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
                            lista_alunos = Cadastrar_aluno(lista_alunos, arv_cursos);
                            break;
                        case 3:
                            arv_cursos = Cadastrar_disciplina(arv_cursos);
                            break;
                        case 4:
                            lista_alunos = cadastrarMatricula(lista_alunos, arv_cursos);
                            break;
                        case 5:
                            lista_alunos = cadastrarNota(lista_alunos);
                            break;
                        case 6:
                            alunos_de_um_curso(lista_alunos);
                            break;
                        case 7:
                            mostrar_todos_os_cursos(arv_cursos);
                            break;
                        case 8:
                            mostrar_disciplinas_de_um_curso(arv_cursos);
                            break;
                        case 9:
                            mostrar_disciplinas_de_um_periodo(arv_cursos);
                            break;
                        case 10:
                            mostrar_disciplinas_de_um_aluno_matriculado(lista_alunos, arv_cursos);
                            break;  
                        case 11:
                            mostrarNotasDePeriodo(lista_alunos);
                            break;
                        case 12:
                            mostrarNotaDeDisciplina(lista_alunos, arv_cursos);
                            break;
                        case 13:
                            remover_disciplina_se_possivel(arv_cursos, lista_alunos);
                            break;
                        case 14:
                            remover_disciplina_matricula(lista_alunos);
                            break;
                        case 15:
                            mostrar_historico_aluno(lista_alunos, arv_cursos);
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
                menu_testes();
                scanf("%d", &op3);
                switch(op3){
                    case 1:
                        //teste_insercao();
                        arv_cursos = cadastra_curso_automatico(arv_cursos);
                        printf("Cursos cadastrados com sucesso!\n");
                        break;
                    case 2:
                        printa_tamanho(arv_cursos);
                        break;
                    case 0:
                        break;
                    default:
                        printf("Opção inválida!\n");
                        break;
                }
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