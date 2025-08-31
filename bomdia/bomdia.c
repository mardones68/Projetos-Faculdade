/*Autor: Mardones Sousa - mardonessousa88@gmail.com
Projeto 1 da disciplina de Linguagem de Programação
Compilar: gcc bomdia.c*/

#include <stdio.h>
#include <string.h>

// Função para exibir a documentação do software
void exibirDocumentacao() {
    printf("DOCUMENTACAO DE SOFTWARE\n");
        printf("-------------------------\n");
        printf("Este software e um programa de linha de comando que fornece um menu de opcoes multilingue.\n"
                "Ele permite que o usuario escolha entre varias opcoes, incluindo:\n"
                "- Exibicao da documentacao do software\n"
                "- Exibicao da versao do software\n"
                "- Selecao de idiomas.\n");
        printf("Para usar este programa, siga as instrucoes abaixo:\n");
        printf("1- Execute o programa no terminal.\n"
                "2- Voce vera o MENU DE OPCOES exibido no terminal.\n"
                "3- Voce pode inserir uma das seguintes opcoes de linha de comando e pressionar Enter:");
                printf("\n");
        printf("--help ou -h     : Documentacao do software.\n");
        printf("--version ou -v  : Versao do software.\n");
        printf("--pt ou -1       : Idioma portugues.\n");
        printf("--en ou -2       : Idioma ingles.\n");
        printf("--es ou -3       : Idioma espanhol.\n");
        printf("--fr ou -4       : Idioma frances.\n");
        printf("--it ou -5       : Idioma italiano.\n");
        printf("--co ou -6       : Idioma coreano.\n");
        printf("--jp ou -7       : Idioma japones.\n");
        printf("--ru ou -8       : Idioma russo.\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) { //aqui ocorre a leitura
        /*  está verificando se o programa foi executado com exatamente dois argumentos da linha de comando,
         incluindo o nome do programa.*/
        printf("Erro: Opcao nao informada. Use 'bomdia --help' para obter a documentacao.\n");
        return 1;
    }
    /*O elemento argv[0] contém o nome do programa (o primeiro argumento), argv[1] contém o segundo argumento
     (a opção fornecida pelo usuário) e assim por diante.*/
     //ponteiro: (armazena o endereço de memória)
    char *opcao = argv[1]; //aqui ocoore o "scanf"

    if (strcmp(opcao, "--help") == 0 || strcmp(opcao, "-h") == 0) {
        // Exibir documentação
        exibirDocumentacao();
    } else if (strcmp(opcao, "--version") == 0 || strcmp(opcao, "-v") == 0) {
        // Exibir a versão do software
        printf("Versão 1.0\n");
    } else if (strcmp(opcao, "--pt") == 0 || strcmp(opcao, "-1") == 0) {
        // Exibir "Bom dia!" em português
        printf("Bom dia!\n");
    } else if (strcmp(opcao, "--en") == 0 || strcmp(opcao, "-2") == 0) {
        // Exibir "Bom dia!" em inglês
        printf("Good morning!\n");
    } else if (strcmp(opcao, "--es") == 0 || strcmp(opcao, "-3") == 0) {
        // Exibir "Bom dia!" em espanhol
        printf("Buenos días!\n");
    } else if (strcmp(opcao, "--fr") == 0 || strcmp(opcao, "-4") == 0) {
        // Exibir "Bom dia!" em francês
        printf("Bonjour!\n");
    } else if (strcmp(opcao, "--it") == 0 || strcmp(opcao, "-5") == 0) {
        // Exibir "Bom dia!" em italiano
        printf("Buongiorno!\n");
    } else if (strcmp(opcao, "--co") == 0 || strcmp(opcao, "-6") == 0) {
        // Exibir "Bom dia!" em coreano
        printf("안녕하세요!\n");
    } else if (strcmp(opcao, "--jp") == 0 || strcmp(opcao, "-7") == 0) {
        // Exibir "Bom dia!" em japonês
        printf("おはよう!\n");
    } else if (strcmp(opcao, "--ru") == 0 || strcmp(opcao, "-8") == 0) {
        // Exibir "Bom dia!" em russo
        printf("Доброе утро!\n");
    } else {
        // Opção desconhecida
        printf("Erro: Opcao nao reconhecida. Use 'bomdia --help' para obter ajuda.\n");
        return 1;
    }

    return 0;
}
