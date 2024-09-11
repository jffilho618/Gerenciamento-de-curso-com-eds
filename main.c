#include "gerenciamento.h"
#include <stdio.h>
#include <stdlib.h>

int main(){

    int op1;
    Elemento *lista_alunos = criaLista();


    do{ 
        menu_principal();
        scanf("%d", &op1);
        switch (op1){
            case 1:
                questao1();
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