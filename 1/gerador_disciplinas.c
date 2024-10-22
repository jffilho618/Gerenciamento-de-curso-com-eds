#include <stdio.h>
#include <stdlib.h>

void gerarDisciplinas(int quantidade) {
    FILE *arquivo = fopen("disciplinas.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    // Expansão do vetor com mais disciplinas de diversas áreas de TI
    char *nomes_base[] = {
        "Algoritmos", "Estrutura de Dados", "Cálculo", "Álgebra Linear", "Banco de Dados", 
        "Redes de Computadores", "Sistemas Operacionais", "Engenharia de Software", 
        "Inteligência Artificial", "Matemática Discreta", "Compiladores", 
        "Análise de Algoritmos", "Teoria da Computação", "Computação Gráfica", 
        "Sistemas Distribuídos", "Segurança da Informação", "Interação Humano-Computador", 
        "Processamento de Imagens", "Projeto de Sistemas de Software", "Redes Neurais",
        "Aprendizado de Máquina", "Mineração de Dados", "Computação em Nuvem", 
        "Internet das Coisas", "Robótica", "Criptografia", "Realidade Virtual", 
        "Programação Paralela", "Programação Funcional", "Blockchain e Aplicações",
        "Arquitetura de Computadores", "Circuitos Digitais", "Desenvolvimento Web",
        "Desenvolvimento Mobile", "Engenharia de Requisitos", "Gestão de Projetos",
        "Modelagem de Processos de Negócio", "Governança de TI", "Auditoria de Sistemas",
        "Gestão de Serviços de TI", "Sistemas de Informação Gerencial", "Modelagem de Dados",
        "Tópicos Avançados em Redes", "Tópicos Especiais em Segurança da Informação",
        "Administração de Servidores", "Virtualização de Servidores", "Qualidade de Software",
        "Métricas de Software", "Desenvolvimento Ágil", "Inovação Tecnológica",
        "Gerenciamento de Redes", "Segurança em Redes de Computadores", "Data Science",
        "Big Data", "Pesquisa Operacional", "Redes Sem Fio", "Criptografia Aplicada",
        "Engenharia de Sistemas", "Sistemas de Controle", "Linguagens de Programação",
        "Testes de Software", "Desenvolvimento de Jogos", "Design de Interação",
        "Análise de Sistemas", "Modelagem UML", "Administração de Bancos de Dados",
        "Tecnologias Web", "Gestão de Configurações", "Tópicos Especiais em Banco de Dados",
        "Inteligência Coletiva", "Gestão da Inovação", "Segurança de Aplicações Web",
        "Visualização de Dados", "Tecnologias Emergentes", "Interface de Usuário"
    };
    int nomes_base_tamanho = sizeof(nomes_base) / sizeof(nomes_base[0]);

    // Gera disciplinas com dados variáveis
    for (int i = 1; i <= quantidade; i++) {
        int codigo = 200 + i;  // Gera um código único
        int carga_horaria = 60;  // Mesma carga horária para todas
        int periodo = (i % 8) + 1;  // Período varia de 1 a 8
        int codigo_curso = 23249;  // Código fixo do curso

        // Seleciona um nome de disciplina aleatório
        char *nome_disciplina = nomes_base[i % nomes_base_tamanho];

        // Grava a disciplina no arquivo
        fprintf(arquivo, "%d;%s;%d;%d;%d\n", codigo, nome_disciplina, carga_horaria, periodo, codigo_curso);
    }

    fclose(arquivo);
    printf("Arquivo com %d disciplinas gerado com sucesso!\n", quantidade);
}

int main() {
    int quantidade = 2000;  // Defina a quantidade desejada de disciplinas
    gerarDisciplinas(quantidade);
    return 0;
}
