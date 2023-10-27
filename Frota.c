// testa se o sistema é Windows, pois o "cls" funciona somente no Windows,
// senão utiliza o "clear" que é o comando para limpar a tela no Linux
#ifdef __WIN32
#define limpar_tela "cls"
#else
#define limpar_tela "clear"
#endif

// inclusão de bibliotecas
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "funcoes.h"
#include "cadastrocliente.h"
#include "cadastromotorista.h"
#include "contasareceber.h"
#include "fornecedor.h"
#include "produtos.h"
#include "pagar.h"

// definição da struct empresa
typedef struct empresa
{
	// campos da struct empresa
	int icodigo;
	char sTipo_Pessoa[1]; // F-Física / J-Jurídica
	char sRazao_Scial[100];
	char sFantasia[100];
	char sCNPJ_CPF[14];
	char sInscEst_RG[30];
	char sInsc_Mun[20];
	char sEndereco[100];
	char sNumero[5];
	char sComplemento[20];
	char sBairro[30];
	char sCidade[30];
	char sUF[2];
	char sCEP[8];
	char sFone1[12];
	char sFone2[12];
	char sFone3[12];
	char sNome_Contato[30];
	char sRegime_Tributario[50];
	char sEmail[100];
	char sSite[50];
	char sAtivo[1]; // S - Sim / N - Não
} st_empresa;

// protótipos de funções

/**
 * Exibe o menu com todas as opções do programa
 * retorno: um caractere do número correspondente a opção
 */
char menu();

/**
 * Cadastra uma Empresa
 */
void cadastrar_empresa();

//==========================================================================

int main(void)
{
	setlocale(LC_ALL, "portuguese");

	char resp;

	// loop infinito do programa
	while (1)
	{
		// obtém a escolha do usu�rio
		resp = menu();

		// testa o valor de "resp"
		if (resp == '1')
			// msg_em_desenvolvimento();
			cadastrar_empresa();
		else if (resp == '2')
			msg_em_desenvolvimento();
		// cadastrar_cliente();
		else if (resp == '3')
			msg_em_desenvolvimento();
		// listar_filmes();
		else if (resp == '4')
			msg_em_desenvolvimento();
		// listar_clientes();
		else if (resp == '5')
			msg_em_desenvolvimento();
		// pesquisar_filme();
		else if (resp == '6')
			msg_em_desenvolvimento();
		// pesquisar_cliente();
		else if (resp == '7')
			msg_em_desenvolvimento();
		// alugar_filme();
		else if (resp == '8')
			msg_em_desenvolvimento();
		// entregar_filme();
		else if (resp == '9')
			msg_em_desenvolvimento();
		// excluir_filme();
		else if (resp == '10')
			msg_em_desenvolvimento();
		else if (resp == '11')
			msg_em_desenvolvimento();
		else if (resp == '12')
			msg_em_desenvolvimento();
		else if (resp == '13')
			msg_em_desenvolvimento();
		else if (resp == '14')
			msg_em_desenvolvimento();
		else if (resp == '0') // se for igual a 0, então sai do loop while
			break;
		else
		{
			printf("\nOpcao invalida! Pressione <Enter> para continuar...");
			scanf("%*c");
			// uma forma de "limpar" o buffer de entrada
			fseek(stdin, 0, SEEK_END); // não recomendável o uso
		}
		system(limpar_tela);
	}
	printf("\nBye! Visite: www.GeeksBR.com ;-)\n");
	return 0;
}

// fun��o que exibe o menu e retorna a opção escolhida pelo usu�rio
char menu()
{
	char resp[2];

	printf("\n--[ KNOWLEDGE System Solutions  ]-------------------------------------------");
	printf("\n--[ Sistema de Gest�o de Frotas ]-------------------------------------------");
	printf("\n\n 1 - Cadastrar Empresas\n");
	printf(" 2 - Cadastrar Clientes\n");
	printf(" 3 - Cadastrar Fornecedores\n");
	printf(" 4 - Cadastrar Motoristas\n");
	printf(" 5 - Cadastrar Produtos\n");
	printf(" 6 - Cadastrar Lançamentos a Pagar\n");
	printf(" 7 - Cadastrar Lançamentos a Receber\n");
	printf(" 8 - Listar todas as Empresas\n");
	printf(" 9 - Listar todos os Clientes\n");
	printf("10 - Listar todos os Fornecedores\n");
	printf("11 - Listar todos os Motoristas\n");
	printf("12 - Listar todos os Produtos\n");
	printf("13 - Listar todos os Lançamentos a Pagar\n");
	printf("14 - Listar todos os Lançamentos a Receber\n");
	printf(" 0 - Sair\n");
	printf("\nDigite o numero da opcao: ");
	scanf("%1s%*c", resp); // o *c pega o Enter e descarta

	// uma forma de "limpar" o buffer de entrada
	fseek(stdin, 0, SEEK_END); // não recomendável o uso

	// se chegou aqui, é porque a opção � válida
	return resp[0];
}

//---------------------------------------------------------
void cadastrar_empresa()
{

	// abre o arquivo para escrita
	// a+b => acrescenta dados ao final do arquivo ou cria
	// um arquivo bin�ria para leitura e escrita
	FILE *arq_empresa = fopen("empresa.bin", "a+b");

	// testa a abertura do arquivo
	if (arq_empresa == NULL)
	{
		printf("\nFalha ao abrir arquivo(s)!\n");
		exit(1); // aborta o programa
	}

	/*
		NÃO é interessante que o usuário digite o Código da empresa, esse
		Código tem que ser gerado automático, então temos que pegar o
		Código da última empresa cadastrada
	*/
	int cont_bytes = 0;

	// cont_bytes irá guardar o n�mero total de bytes
	// seta o ponteiro do arquivo para o final do arquivo
	fseek(arq_empresa, 0, SEEK_END);

	// pegamos a quantidade de bytes com a função ftell
	cont_bytes = ftell(arq_empresa);

	st_empresa empresa;

	if (cont_bytes == 0)
	{
		// se for 0, então não existe empresa cadastrada
		// coloca o Código começando de 1
		empresa.icodigo = 1;
	}
	else
	{
		st_empresa ultima_empresa;

		// utiliza a função fseek para posicionar o arquivo
		// cont_bytes - sizeof(st_empresa) serve para posicionar
		// para que possamos pegar o código da última empresa cadastrada
		fseek(arq_empresa, cont_bytes - sizeof(st_empresa), SEEK_SET);

		// ler os dados da empresa
		fread(&ultima_empresa, sizeof(st_empresa), 1, arq_empresa);

		// o Código da empresa é o código da última empresa acrescido em 1
		empresa.icodigo = ultima_empresa.icodigo + 1;
	}

	// obtém o nome da empresa
	// ^\n indica para pegar até a quebra de linha (enter)
	// %*c descarta o enter
	printf("\nTipo de pessoa (F - F�sica / J - Jur�dica): ");
	scanf("%99[^\n]%*c", empresa.sTipo_Pessoa);

	printf("\nRaz�o Social: ");
	scanf("%99[^\n]%*c", empresa.sRazao_Scial);

	fseek(stdin, 0, SEEK_END); // não recomend�vel o uso

	// se o ponteiro não estiver no final do arquivo nada é escrito
	fseek(arq_empresa, 0, SEEK_END);
	// escreve no arquivo
	fwrite(&empresa, sizeof(st_empresa), 1, arq_empresa);

	// fecha o arquivo
	fclose(arq_empresa);

	/*
	// campos da struct empresa
	char sRazao_Scial[100];
	char sFantasia[100];
	char sCNPJ_CPF[14];
	char sInscEst_RG[30];
	char sInsc_Mun[20];
	char sEndereco[100];
	char sNumero[5];
	char sComplemento[20];
	char sBairro[30];
	char sCidade[30];
	char sUF[2];
	char sCEP[8];
	char sFone1[12];
	char sFone2[12];
	char sFone3[12];
	char sNome_Contato[30];
	char sRegime_Tributario[50];
	char sEmail[100];
	char sSite[50];
	char sAtivo[1]; // S - Sim / N - N�o
	*/

	// uma forma de "limpar" o buffer de entrada
	fseek(stdin, 0, SEEK_END); // não recomendável o uso
}
//---------------------------------------------------------
