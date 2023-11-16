#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef PAGAR_H
#define PAGAR_H

#define MAX_CONTAS 100

struct ContaPagar {
    char dataLancamento[11];
    char empresa[100];
    char fornecedor[100];
    char numeroDocumento[20];
    char dataDocumento[11];
    int parcela;
    float valorParcela;
    char dataVencimento[11];
    char dataPagamento[11];
    char tipoDocumento[50];
    char centroCusto[50];
    char complementoDocumento[40];
    char historico[300];
    char banco[50];
};

void gerenciarContas();
void cadastrarContaPagar(struct ContaPagar contas[], int *quantidade);
void excluirUltimaConta(struct ContaPagar contas[], int *quantidade);
void exibirContasCadastradas(struct ContaPagar contas[], int quantidade);
void lerData(char *destino);
float lerNumeroFloat();
int lerNumeroInteiro();
void exibirContaPagar(struct ContaPagar conta);

#endif



void gerenciarContas() {
    struct ContaPagar contas[MAX_CONTAS];
    int quantidade = 0;
    int opcao;

    do {
        printf("\nOpções:\n");
        printf("1. Adicionar uma nova conta\n");
        printf("2. Exibir contas cadastradas\n");
        printf("3. Excluir a ultima conta\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarContaPagar(contas, &quantidade);
                break;
            case 2:
                exibirContasCadastradas(contas, quantidade);
                break;
            case 3:
                excluirUltimaConta(contas, &quantidade);
                break;
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);
}

void cadastrarContaPagar(struct ContaPagar contas[], int *quantidade) {
    if (*quantidade < MAX_CONTAS) {
        printf("Cadastro de Conta a Pagar:\n");
        struct ContaPagar *conta = &contas[*quantidade];

        printf("Informe a data do lançamento (dd/mm/aaaa): ");
        lerData(conta->dataLancamento);

        printf("Informe o nome da empresa: ");
        scanf(" %[^\n]s", conta->empresa);

        printf("Informe o nome do fornecedor: ");
        scanf(" %[^\n]s", conta->fornecedor);

        printf("Informe o número do documento: ");
        scanf(" %[^\n]s", conta->numeroDocumento);

        printf("Informe a data do documento (dd/mm/aaaa): ");
        lerData(conta->dataDocumento);

        printf("Informe o número da parcela: ");
        conta->parcela = lerNumeroInteiro();

        printf("Informe o valor da parcela: ");
        conta->valorParcela = lerNumeroFloat();

        printf("Informe a data de vencimento (dd/mm/aaaa): ");
        lerData(conta->dataVencimento);

        printf("Informe a data do pagamento (dd/mm/aaaa): ");
        lerData(conta->dataPagamento);

        printf("Informe o tipo de documento: ");
        scanf(" %[^\n]s", conta->tipoDocumento);

        printf("Informe o centro de custo: ");
        scanf(" %[^\n]s", conta->centroCusto);

        printf("Informe o complemento do documento (máximo de 40 caracteres): ");
        scanf(" %[^\n]s", conta->complementoDocumento);

        printf("Informações do histórico (máximo de 300 caracteres): ");
        scanf(" %[^\n]s", conta->historico);

        printf("Informações do banco do documento: ");
        scanf(" %[^\n]s", conta->banco);

        (*quantidade)++;
        printf("Conta cadastrada com sucesso!\n");
    } else {
        printf("Limite máximo de contas atingido.\n");
    }
}

void excluirUltimaConta(struct ContaPagar contas[], int *quantidade) {
    if (*quantidade > 0) {
        (*quantidade)--;
        printf("Última conta cadastrada excluída com sucesso.\n");
    } else {
        printf("Não há contas cadastradas para excluir.\n");
    }
}

void exibirContasCadastradas(struct ContaPagar contas[], int quantidade) {
    printf("\nContas Cadastradas:\n");
    for (int i = 0; i < quantidade; i++) {
        printf("Conta %d:\n", i + 1);
        exibirContaPagar(contas[i]);
    }
}

int validarData(const char *data) {
    int dia, mes, ano;
    if (sscanf(data, "%2d/%2d/%4d", &dia, &mes, &ano) == 3) {
        if (dia >= 1 && dia <= 31 && mes >= 1 && mes <= 12) {
            return 1;
        }
    }
    return 0;
}

void lerData(char *destino) {
    do {
        scanf("%10s", destino);
        if (validarData(destino)) {
            break;
        } else {
            printf("Formato de data inválido. Informe novamente (dd/mm/aaaa): ");
        }
    } while (1);
}



float lerNumeroFloat() {
    float numero;
    char buffer[50];
    int valido;

    do {
        valido = 1;
        scanf("%s", buffer);

        for (int i = 0; i < strlen(buffer); i++) {
            if (!isdigit(buffer[i]) && buffer[i] != '.') {
                valido = 0;
                printf("Entrada inválida. Informe novamente: ");
                break;
            }
        }

        if (valido) {
            numero = atof(buffer);
        }

    } while (!valido);

    return numero;
}

int lerNumeroInteiro() {
    int numero;
    char buffer[50];
    int valido;

    do {
        valido = 1;
        scanf("%s", buffer);

        for (int i = 0; i < strlen(buffer); i++) {
            if (!isdigit(buffer[i])) {
                valido = 0;
                printf("Entrada inválida. Informe novamente: ");
                break;
            }
        }

        if (valido) {
            numero = atoi(buffer);
        }

    } while (!valido);

    return numero;
}

void exibirContaPagar(struct ContaPagar conta) {
    printf("\nInformações da Conta Cadastrada:\n");
    printf("Data do Lançamento: %s\n", conta.dataLancamento);
    printf("Empresa: %s\n", conta.empresa);
    printf("Fornecedor: %s\n", conta.fornecedor);
    printf("Número do Documento: %s\n", conta.numeroDocumento);
    printf("Data do Documento: %s\n", conta.dataDocumento);
    printf("Parcela: %d\n", conta.parcela);
    printf("Valor da Parcela: R$%.2f\n", conta.valorParcela);
    printf("Data de Vencimento: %s\n", conta.dataVencimento);
    printf("Data do Pagamento: %s\n", conta.dataPagamento);
    printf("Tipo de documento: %s\n", conta.tipoDocumento);
    printf("Centro de Custo: %s\n", conta.centroCusto);
    printf("Complemento do Documento: %s\n", conta.complementoDocumento);
    printf("Histórico: %s\n", conta.historico);
    printf("Banco do Documento: %s\n", conta.banco);
}
