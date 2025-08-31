/*O programa DealDetect tem como objetivo comparar preços de empresas e forncecer ao usuário o produto procurado com o valor mais baixo.
O programa ainda conta com a visualização de preços de uma empresa específica
O projeto utiliza arquivos.

O programa deve ser executado da seguinte maneira: gcc DealDetect-Detectar Ofertas.c
AUTOR: Mardones Pereira de Sousa // mardonessousa88@gmail.com            */
#include <stdio.h>
#include <string.h>

#define TAM_CHAR 50
#define MAX_EMPRESAS 100
#define MAX_PRODUTOS 100

struct produto {
    char nome[TAM_CHAR];
    float valorUnitario;
};

struct empresa {
    char nome[TAM_CHAR];
    char endereco[TAM_CHAR];
    struct produto produtos[MAX_PRODUTOS];
    int numProdutos;
};

int buscaEmpresa(const struct empresa empresas[], int numEmpresas, const char *nome) {
    for (int i = 0; i < numEmpresas; i++) {
        if (strcmp(empresas[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

void cadEmpresa(struct empresa empresas[], int *numEmpresas, FILE *arquivoEmpresas) {
    if (*numEmpresas >= MAX_EMPRESAS) {
        printf("Limite de empresas atingido.\n");
        return;
    }

    printf("Digite o nome da sua Empresa/Mercado:\n");
    scanf(" %[^\n]s", empresas[*numEmpresas].nome);

    if (buscaEmpresa(empresas, *numEmpresas, empresas[*numEmpresas].nome) != -1) {
        printf("Empresa com esse nome já cadastrada. Tente outro nome.\n");
        return;
    }

    printf("Digite o endereço de sua Empresa/Mercado:\n");
    scanf(" %[^\n]s", empresas[*numEmpresas].endereco);

    empresas[*numEmpresas].numProdutos = 0;
    fprintf(arquivoEmpresas, "%s %s\n", empresas[*numEmpresas].nome, empresas[*numEmpresas].endereco);
    (*numEmpresas)++;
}

void cadProduto(struct empresa empresas[], int numEmpresas, FILE *arquivoProdutos) {
    if (numEmpresas == 0) {
        printf("Nenhuma empresa cadastrada. Cadastre uma empresa antes de adicionar produtos.\n");
        return;
    }

    char nomeEmpresa[TAM_CHAR];
    printf("Digite o nome da empresa para cadastrar o produto:\n");
    scanf(" %[^\n]s", nomeEmpresa);

    int i;
    for (i = 0; i < numEmpresas; i++) {
        if (strcmp(empresas[i].nome, nomeEmpresa) == 0) {
            if (empresas[i].numProdutos < MAX_PRODUTOS) {
                struct produto *nomeProduto = &empresas[i].produtos[empresas[i].numProdutos];

                printf("Digite o nome do produto:\n");
                scanf(" %[^\n]s", nomeProduto->nome);

                printf("Digite o Valor Unitário:\n");
                scanf("%f", &nomeProduto->valorUnitario);

                FILE *arquivoEmpresa = fopen(empresas[i].nome, "a");
                fprintf(arquivoEmpresa, "%s %.2f\n", nomeProduto->nome, nomeProduto->valorUnitario);
                fclose(arquivoEmpresa);

                empresas[i].numProdutos++;
                printf("Produto cadastrado com sucesso!\n");
            } else {
                printf("Limite de produtos para a empresa atingido.\n");
            }
            return;
        }
    }

    printf("Empresa não encontrada.\n");
}

void consultarPrecos(struct empresa empresas[], int numEmpresas) {
    if (numEmpresas == 0) {
        printf("Nenhuma empresa cadastrada. Cadastre uma empresa antes de consultar preços.\n");
        return;
    }

    char nomeEmpresa[TAM_CHAR];
    printf("Digite o nome da empresa para consultar os preços:\n");
    scanf(" %[^\n]s", nomeEmpresa);

    int i;
    for (i = 0; i < numEmpresas; i++) {
        if (strcmp(empresas[i].nome, nomeEmpresa) == 0) {
            if (empresas[i].numProdutos > 0) {
                printf("Produtos da empresa %s:\n", empresas[i].nome);
                for (int j = 0; j < empresas[i].numProdutos; j++) {
                    printf("Produto: %s | Valor: %.2f\n", empresas[i].produtos[j].nome, empresas[i].produtos[j].valorUnitario);
                }
            } else {
                printf("Nenhum produto cadastrado para a empresa %s.\n", nomeEmpresa);
            }
            return;
        }
    }

    printf("Empresa não encontrada.\n");
}

void compararPrecos(struct empresa empresas[], int numEmpresas) {
    if (numEmpresas < 2) {
        printf("É necessário ter pelo menos duas empresas cadastradas para comparar preços.\n");
        return;
    }

    char nomeProduto[TAM_CHAR];
    printf("Digite o nome do produto que deseja comparar:\n");
    scanf(" %[^\n]s", nomeProduto);

    float menorPreco = -1;
    char empresaMaisBarata[TAM_CHAR];
    char enderecoMaisBarato[TAM_CHAR];

    for (int i = 0; i < numEmpresas; i++) {
        for (int j = 0; j < empresas[i].numProdutos; j++) {
            if (strcmp(empresas[i].produtos[j].nome, nomeProduto) == 0) {
                if (menorPreco == -1 || empresas[i].produtos[j].valorUnitario < menorPreco) {
                    menorPreco = empresas[i].produtos[j].valorUnitario;
                    strcpy(empresaMaisBarata, empresas[i].nome);
                    strcpy(enderecoMaisBarato, empresas[i].endereco);
                }
            }
        }
    }

    if (menorPreco == -1) {
        printf("Produto não encontrado em nenhuma empresa.\n");
    } else {
        printf("O produto %s é mais barato na empresa %s que está localizada no(a) %s por %.2f.\n", nomeProduto, empresaMaisBarata, enderecoMaisBarato, menorPreco);
    }
}

int main() {
    struct empresa empresas[MAX_EMPRESAS];
    int numEmpresas = 0;
    int num;

    FILE *arquivoEmpresas = fopen("empresas.dat", "a+");
    FILE *arquivoProdutos = fopen("produtos.dat", "a+");

    if (arquivoEmpresas == NULL || arquivoProdutos == NULL) {
        printf("Erro ao abrir arquivos.\n");
        return 1;
    }

    while (fscanf(arquivoEmpresas, "%s %s", empresas[numEmpresas].nome, empresas[numEmpresas].endereco) == 2) {
        numEmpresas++;
    }

    for (int i = 0; i < numEmpresas; i++) {
        FILE *arquivoEmpresa = fopen(empresas[i].nome, "r");

        while (fscanf(arquivoEmpresa, "%s %f", empresas[i].produtos[empresas[i].numProdutos].nome,
                      &empresas[i].produtos[empresas[i].numProdutos].valorUnitario) == 2) {
            empresas[i].numProdutos++;
        }

        fclose(arquivoEmpresa);
    }

    do {
        printf("Digite a opção que você deseja de acordo com o menu: \n");
        printf("1- Cadastrar Empresa.\n");
        printf("2- Cadastar Produto.\n");
        printf("3- Consultar Preços de uma Empresa.\n");
        printf("4- Comparar Preços de um Produto.\n");
        printf("5- Sair.\n");

        scanf("%d", &num);

        switch (num) {
            case 1:
                cadEmpresa(empresas, &numEmpresas, arquivoEmpresas);
                break;
            case 2:
                cadProduto(empresas, numEmpresas, arquivoProdutos);
                break;
            case 3:
                consultarPrecos(empresas, numEmpresas);
                break;
            case 4:
                compararPrecos(empresas, numEmpresas);
                break;
            case 5:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opção inválida. Escolha outra opção ou digite 5 para sair.\n");
        }
    } while (num != 5);

    fclose(arquivoProdutos);
    arquivoProdutos = fopen("produtos.dat", "w");

    for (int i = 0; i < numEmpresas; i++) {
        FILE *arquivoEmpresa = fopen(empresas[i].nome, "w");

        for (int j = 0; j < empresas[i].numProdutos; j++) {
            fprintf(arquivoEmpresa, "%s %.2f\n", empresas[i].produtos[j].nome, empresas[i].produtos[j].valorUnitario);
        }

        fclose(arquivoEmpresa);
    }

    fclose(arquivoEmpresas);
    fclose(arquivoProdutos);

    return 0;
}
