/*Autor: Mardones Sousa - mardonessousa88@gmail.com
Projeto 1 da disciplina de Linguagem de Programação
Compilar: gcc bomdia.c*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h> // Para a função isalpha

char *escolherPalavraAleatoria(char *palavras[], int tamanho) {
    srand(time(NULL));
    int indice_aleatorio = rand() % tamanho;
    return palavras[indice_aleatorio];
}

void inicializarPalavraAtual(char *palavra_secreta, char *palavra_atual) {
    int tamanho = strlen(palavra_secreta);
    for (int i = 0; i < tamanho; i++) {
        palavra_atual[i] = '-';
    }
    palavra_atual[tamanho] = '\0';
}

int adivinharLetra(char *palavra_secreta, char *palavra_atual, char letra) {
    int acertou = 0;
    int tamanho = strlen(palavra_secreta);

    for (int i = 0; i < tamanho; i++) {
        if (palavra_secreta[i] == letra) {
            palavra_atual[i] = letra;
            acertou = 1;
        }
    }

    return acertou;
}

void jogarJogoDaForca(char *palavras[], int tamanho) {
    char *palavra_secreta = escolherPalavraAleatoria(palavras, tamanho);
    char *palavra_atual = (char*)malloc(strlen(palavra_secreta) + 1);
    if (palavra_atual == NULL) {
        printf("Erro ao alocar memória para palavra_atual\n");
        exit(1);
    }

    int tentativas = 12; 
    char letra;

    inicializarPalavraAtual(palavra_secreta, palavra_atual);

    while (tentativas > 0) {
        printf("Palavra atual: %s\n", palavra_atual);
        printf("Você tem %d tentativas restantes!\n", tentativas);
        printf("Digite uma letra: ");
        scanf(" %c", &letra);

        if (!isalpha(letra)) {
            printf("Por favor, insira apenas letras do alfabeto.\n");
            continue; 
        }

        if (!adivinharLetra(palavra_secreta, palavra_atual, letra)) {
            printf("Letra não encontrada na palavra secreta.\n");
        } else {
            printf("Letra encontrada na palavra secreta!\n");
        }

        tentativas--; 

        if (strcmp(palavra_atual, palavra_secreta) == 0) {
            printf("Parabéns, você adivinhou a palavra: %s\n", palavra_secreta);
            break;
        }
    }

    if (tentativas == 0) {
        printf("Suas tentativas acabaram. A palavra secreta era: %s\n", palavra_secreta);
    }

    free(palavra_atual);
}

int main(int argc, char *argv[]) {
    char *palavras_fixas[] = {"cadeira", "faculdade", "maria", "tesoura", "papel", "roupa", "pessoa", "igreja", "programa", "escola", "clube", "festa", "carro", "moto", "lazer"};
    int tamanho_fixas = sizeof(palavras_fixas) / sizeof(palavras_fixas[0]);

    int tamanho = tamanho_fixas;

    jogarJogoDaForca(palavras_fixas, tamanho);

    return 0;
}

