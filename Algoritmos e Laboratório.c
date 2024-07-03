#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura para armazenar informações de uma venda
typedef struct {
    int numeroVenda;
    int codigoCliente;
    char nomeCliente[50];
    char dataCompra[11]; // dd/mm/aaaa + \0
    char nomeProduto[50];
    char marca[50]; // Adicionado campo para armazenar a marca do produto
    int codigoProduto;
    int quantidade;
    float precoUnitario;
    float precoTotal;
} Venda;

// Função para calcular o preço total da compra e aplicar desconto se necessário
float calcularPrecoTotal(int quantidade, float precoUnitario) {
    float precoTotal = quantidade * precoUnitario;
    if (quantidade >= 3) {
        precoTotal *= 0.9; // Aplica desconto de 10% se a quantidade for 3 ou mais
    }
    return precoTotal;
}

// Função para realizar o login
int fazerLogin() {
    char login[50];
    char senha[50];

    printf("Login: ");
    scanf("%s", login);

    printf("Senha: ");
    scanf("%s", senha);

    if (strcmp(login, "Algoritmos") == 0 && strcmp(senha, "1234") == 0) {
        return 1; // Login e senha corretos
    } else {
        printf("Login ou senha incorretos. Encerrando o programa.\n");
        return 0; // Login ou senha incorretos
    }
}

// Função para verificar se um código de cliente e nome de cliente já estão cadastrados
int verificarCodigoCliente(Venda *vendas, int totalVendas, int codigoCliente, char *nomeCliente) {
    for (int i = 0; i < totalVendas; i++) {
        if (vendas[i].codigoCliente == codigoCliente) {
            if (strcmp(vendas[i].nomeCliente, nomeCliente) == 0) {
                return 1; // O código do cliente e o nome correspondente já estão cadastrados
            } else {
                return 2; // O código do cliente está cadastrado, mas o nome não corresponde
            }
        }
    }
    return 0; // O código do cliente e/ou nome correspondente não estão cadastrados
}

// Função para cadastrar uma nova venda
void cadastrarVenda(Venda *vendas, int *totalVendas) {
    printf("\n==================================\n");
    printf("Informe os Dados da Compra\n");

    // Gera automaticamente o número da venda
    int numeroVenda;
    if (*totalVendas == 0) {
        // Se não houver vendas registradas, o número da primeira venda será 1
        numeroVenda = 1;
    } else {
        // Caso contrário, o número da nova venda será o número da última venda + 1
        numeroVenda = vendas[*totalVendas - 1].numeroVenda + 1;
    }

    // Captura dos dados da venda
    printf("Numero da Venda: %d\n", numeroVenda);
    vendas[*totalVendas].numeroVenda = numeroVenda;

    int codigoCliente;
    char nomeCliente[50];
    int clienteExistente = 0;
    do {
        printf("Codigo do Cliente: ");
        scanf("%d", &codigoCliente);

        printf("Nome do Cliente: ");
        scanf(" %[^\n]", nomeCliente);

        int codigoStatus = verificarCodigoCliente(vendas, *totalVendas, codigoCliente, nomeCliente);
        if (codigoStatus == 1) {
            clienteExistente = 1;
            printf("\n>> Cliente encontrado no registro. Prosseguindo com o cadastro.\n");
        } else if (codigoStatus == 2) {
            printf("\n>> O codigo do cliente informado ja esta registrado, mas o nome nao corresponde.\n");
            printf(">> Por favor, insira um novo codigo de cliente.\n\n");
        } else {
            printf("\n>> Cliente nao encontrado no registro. Prosseguindo com o cadastro.\n");
            clienteExistente = 1; // Para permitir o cadastro de um novo cliente
        }
    } while (!clienteExistente);

    vendas[*totalVendas].codigoCliente = codigoCliente;
    strcpy(vendas[*totalVendas].nomeCliente, nomeCliente);

    printf("Data da Compra (dd/mm/aaaa): ");
    scanf("%s", vendas[*totalVendas].dataCompra);

    printf("Codigo do Produto: ");
    scanf("%d", &vendas[*totalVendas].codigoProduto);

    printf("Nome do Produto: ");
    scanf(" %[^\n]", vendas[*totalVendas].nomeProduto);

    printf("Marca: "); // Adicionado campo para inserção da marca do produto
    scanf(" %[^\n]", vendas[*totalVendas].marca);

    printf("Quantidade: ");
    scanf("%d", &vendas[*totalVendas].quantidade);

    printf("Preco Unitario: ");
    scanf("%f", &vendas[*totalVendas].precoUnitario);

    // Cálculo do preço total da compra
    vendas[*totalVendas].precoTotal = calcularPrecoTotal(vendas[*totalVendas].quantidade, vendas[*totalVendas].precoUnitario);

    // Exibe o valor total da compra para o cliente
    printf("Valor Total da Compra: R$ %.2f\n", vendas[*totalVendas].precoTotal);

    printf("Informacoes de Compra Salvas\n\n");

    (*totalVendas)++;
}

// Função para exibir o menu principal
void exibirMenuPrincipal() {
    printf("\n==================================\n");

    printf("\nMenu Principal\n");
    printf("1. Registrar Venda\n");
    printf("2. Listar Vendas\n");
    printf("3. Relatorio Diario de Compras\n");
    printf("4. Alterar Venda\n");
    printf("5. Excluir Venda\n");
    printf("6. Sair\n");
    printf("Escolha uma opcao: ");
}

// Função para listar todas as vendas realizadas
void listarVendas(Venda *vendas, int totalVendas) {
    printf("\n==================================\n");

    printf("\nLista de Vendas\n");
    float faturamentoBruto = 0;
    for (int i = 0; i < totalVendas; i++) {
        printf("Numero da Venda: %d\n", vendas[i].numeroVenda);
        printf("Codigo do Cliente: %d\n", vendas[i].codigoCliente);
        printf("Nome do Cliente: %s\n", vendas[i].nomeCliente);
        printf("Data da Compra: %s\n", vendas[i].dataCompra);
        printf("Codigo do Produto: %d\n", vendas[i].codigoProduto);
        printf("Nome do Produto: %s\n", vendas[i].nomeProduto);
        printf("Marca: %s\n", vendas[i].marca);
        printf("Quantidade: %d\n", vendas[i].quantidade);
        printf("Preco Unitario: %.2f\n", vendas[i].precoUnitario);
        printf("Preco Total: R$ %.2f\n", vendas[i].precoTotal);
        printf("\n");

        // Soma ao faturamento bruto
        faturamentoBruto += vendas[i].precoTotal;
    }
    printf("Faturamento Bruto Total: R$ %.2f\n", faturamentoBruto);
}

// Função para gerar o relatório diário de compras
void relatorioDiarioCompras(Venda *vendas, int totalVendas) {
    char data[11];
    printf("\n-------------------------------\n");

    printf("\nInforme a data (dd/mm/aaaa): ");
    scanf("%s", data);

    printf("\n==================================\n");

    printf("\nRelatorio Diario de Compras - Data: %s\n", data);
    float faturamentoBruto = 0;
    int totalItensVendidos = 0;
    char nomesClientesUnicos[100][50] = {0}; // Array para armazenar os nomes dos clientes únicos

    // Matriz para armazenar os itens vendidos
    int itensVendidos[100][2]; // Cada linha: {codigoProduto, quantidadeVendida}
    for (int i = 0; i < 100; i++) {
        itensVendidos[i][0] = 0; // Inicializa o código do produto como 0 (representando vazio)
        itensVendidos[i][1] = 0; // Inicializa a quantidade vendida como 0
    }
    // Array para armazenar os códigos de clientes únicos
    int clientesUnicos[100] = {0}; // Inicializa todos os elementos como 0
    int totalClientesUnicos = 0;
    for (int i = 0; i < totalVendas; i++) {
        if (strcmp(vendas[i].dataCompra, data) == 0) {
            printf("Numero da Venda: %d\n", vendas[i].numeroVenda);
            printf("Codigo do Cliente: %d\n", vendas[i].codigoCliente);
            printf("Nome do Cliente: %s\n", vendas[i].nomeCliente);
            printf("Data da Compra: %s\n", vendas[i].dataCompra);
            printf("Nome do Produto: %s\n", vendas[i].nomeProduto);
            printf("Marca: %s\n", vendas[i].marca); // Alterado para exibir a marca
            printf("Quantidade: %d\n", vendas[i].quantidade); // Alterado para exibir a quantidade
            printf("Preco Unitario: %.2f\n", vendas[i].precoUnitario);
            printf("Preco Total: R$ %.2f\n", vendas[i].precoTotal);
            printf("\n");

            // Soma ao faturamento bruto
            faturamentoBruto += vendas[i].precoTotal;

            // Atualiza o total de clientes únicos
            int clienteRepetido = 0;
            for (int j = 0; j < totalClientesUnicos; j++) {

                    if (vendas[i].codigoCliente == clientesUnicos[j] && strcmp(vendas[i].nomeCliente, nomesClientesUnicos[j]) == 0) {
                        clienteRepetido = 1;
                        break;
                    }
            }
            if (!clienteRepetido) {
                clientesUnicos[totalClientesUnicos] = vendas[i].codigoCliente;
                strcpy(nomesClientesUnicos[totalClientesUnicos], vendas[i].nomeCliente);
                totalClientesUnicos++;
             }


            // Atualiza o total de itens vendidos
            totalItensVendidos += vendas[i].quantidade;
            // Contar o número total de clientes
            int totalClientes = 0;
            for (int i = 0; i < totalVendas; i++) {

                int clienteRepetido = 0;
                for (int j = 0; j < i; j++) {
                     if (vendas[i].codigoCliente == vendas[j].codigoCliente) {
                         clienteRepetido - 1;
                         break;
                     }
                }
                if (!clienteRepetido) {
                     totalClientes++;
                }
            }

            // Atualiza a matriz de itens vendidos
            for (int j = 0; j < 100; j++) {
                if (itensVendidos[j][0] == vendas[i].codigoProduto) {
                    itensVendidos[j][1] += vendas[i].quantidade; // Atualiza a quantidade vendida
                    break;
                } else if (itensVendidos[j][0] == 0) {
                    itensVendidos[j][0] = vendas[i].codigoProduto; // Armazena o código do produto
                    itensVendidos[j][1] = vendas[i].quantidade; // Armazena a quantidade vendida
                    break;
                }
            }
        }
    }

    printf("\n-------------------------------\n");

    printf("Faturamento Bruto Total: R$ %.2f\n", faturamentoBruto);
    printf("\nInformacoes Gerais\n");
    printf("Quantidade de Clientes: %d\n", totalClientesUnicos);
    printf("Quantidade de Itens Vendidos: %d\n", totalItensVendidos);

    // Ordena a matriz de itens vendidos por quantidade vendida (ordem decrescente)
    for (int i = 0; i < 99; i++) {
        for (int j = i + 1; j < 100; j++) {
            if (itensVendidos[i][1] < itensVendidos[j][1]) {
                // Troca os elementos de posição
                int tempCodigo = itensVendidos[i][0];
                int tempQuantidade = itensVendidos[i][1];
                itensVendidos[i][0] = itensVendidos[j][0];
                itensVendidos[i][1] = itensVendidos[j][1];
                itensVendidos[j][0] = tempCodigo;
                itensVendidos[j][1] = tempQuantidade;
            }
        }
    }

    printf("\nTabela de Produtos Mais Vendidos aos Menos Vendidos:\n");
    printf("Nome:\t\t\tMarca:\t\tQuantidade Vendida:\n"); // Modificado para exibir Nome, Marca e Quantidade
    for (int i = 0; i < 100; i++) {
        if (itensVendidos[i][0] != 0) {
            for (int j = 0; j < totalVendas; j++) {
                if (itensVendidos[i][0] == vendas[j].codigoProduto) {
                    printf("%s\t\t\t%s\t\t%-15d\n", vendas[j].nomeProduto, vendas[j].marca, itensVendidos[i][1]); // Ajuste para alinhar à esquerda
                    break;
                }
            }
        } else {
            break; // Sai do loop quando não houver mais produtos na lista
        }
    }
}

// Função para alterar uma venda existente
void alterarVenda(Venda *vendas, int totalVendas) {
    int numeroVenda;
    printf("\n==================================\n");

    printf("\nDigite o numero da venda que deseja alterar: ");
    scanf("%d", &numeroVenda);

    int encontrou = 0;
    for (int i = 0; i < totalVendas; i++) {
        if (vendas[i].numeroVenda == numeroVenda) {
            encontrou = 1;
            printf("\nDados da Venda a ser Alterada:\n");
            printf("Numero da Venda: %d\n", vendas[i].numeroVenda);
            printf("Codigo do Cliente: %d\n", vendas[i].codigoCliente);
            printf("Nome do Cliente: %s\n", vendas[i].nomeCliente);
            printf("Data da Compra: %s\n", vendas[i].dataCompra);
            printf("Codigo do Produto: %d\n", vendas[i].codigoProduto);
            printf("Nome do Produto: %s\n", vendas[i].nomeProduto);
            printf("Marca: %s\n", vendas[i].marca);
            printf("Quantidade: %d\n", vendas[i].quantidade);
            printf("Preco Unitario: %.2f\n", vendas[i].precoUnitario);
            printf("Preco Total: R$ %.2f\n", vendas[i].precoTotal);
            printf("\n");

            // Espaçamento de linhas
            printf("\n");
            printf("\n-------------------------------\n");
            // Solicitar novos dados
            printf("Digite os novos dados a seguir:\n");
            printf("Codigo do Cliente: ");
            scanf("%d", &vendas[i].codigoCliente);

            printf("Nome do Cliente: ");
            scanf(" %[^\n]", vendas[i].nomeCliente);

            printf("Data da Compra (dd/mm/aaaa): ");
            scanf("%s", vendas[i].dataCompra);

            printf("Codigo do Produto: ");
            scanf("%d", &vendas[i].codigoProduto);

            printf("Nome do Produto: ");
            scanf(" %[^\n]", vendas[i].nomeProduto);

            printf("Marca: ");
            scanf(" %[^\n]", vendas[i].marca);

            printf("Quantidade: ");
            scanf("%d", &vendas[i].quantidade);

            printf("Preco Unitario: ");
            scanf("%f", &vendas[i].precoUnitario);

            // Recalcular o preço total da compra
            vendas[i].precoTotal = calcularPrecoTotal(vendas[i].quantidade, vendas[i].precoUnitario);

            printf("\nVenda alterada com sucesso!\n");
            return; // Retorna ao menu principal após a alteração
        }
    }

    if (!encontrou) {
        printf("\nVenda nao encontrada!\n");

        char opcao;
        do {
            printf("Deseja tentar novamente? (S/N): ");
            scanf(" %c", &opcao);
            if (opcao == 'S' || opcao == 's') {
                printf("\nDigite o numero da venda que deseja alterar: ");
                scanf("%d", &numeroVenda);
                for (int i = 0; i < totalVendas; i++) {
                    if (vendas[i].numeroVenda == numeroVenda) {
                        encontrou = 1;
                        printf("\nDados da Venda a ser Alterada:\n");
                        printf("Numero da Venda: %d\n", vendas[i].numeroVenda);
                        printf("Codigo do Cliente: %d\n", vendas[i].codigoCliente);
                        printf("Nome do Cliente: %s\n", vendas[i].nomeCliente);
                        printf("Data da Compra: %s\n", vendas[i].dataCompra);
                        printf("Codigo do Produto: %d\n", vendas[i].codigoProduto);
                        printf("Nome do Produto: %s\n", vendas[i].nomeProduto);
                        printf("Marca: %s\n", vendas[i].marca);
                        printf("Quantidade: %d\n", vendas[i].quantidade);
                        printf("Preco Unitario: %.2f\n", vendas[i].precoUnitario);
                        printf("Preco Total: R$ %.2f\n", vendas[i].precoTotal);
                        printf("\n");

                        // Espaçamento de linhas
                        printf("\n");

                        // Solicitar novos dados
                        printf("Digite os novos dados a seguir:\n");
                        printf("Codigo do Cliente: ");
                        scanf("%d", &vendas[i].codigoCliente);

                        printf("Nome do Cliente: ");
                        scanf(" %[^\n]", vendas[i].nomeCliente);

                        printf("Data da Compra (dd/mm/aaaa): ");
                        scanf("%s", vendas[i].dataCompra);

                        printf("Codigo do Produto: ");
                        scanf("%d", &vendas[i].codigoProduto);

                        printf("Nome do Produto: ");
                        scanf(" %[^\n]", vendas[i].nomeProduto);

                        printf("Marca: ");
                        scanf(" %[^\n]", vendas[i].marca);

                        printf("Quantidade: ");
                        scanf("%d", &vendas[i].quantidade);

                        printf("Preco Unitario: ");
                        scanf("%f", &vendas[i].precoUnitario);

                        // Recalcular o preço total da compra
                        vendas[i].precoTotal = calcularPrecoTotal(vendas[i].quantidade, vendas[i].precoUnitario);

                        printf("\nVenda alterada com sucesso!\n");
                        return; // Retorna ao menu principal após a alteração
                    }
                }
                if (!encontrou) {
                    printf("\nVenda nao encontrada!\n");
                }
            } else if (opcao == 'N' || opcao == 'n') {
                printf("\nRetornando ao menu principal...\n");
                return; // Retorna ao menu principal após a tentativa de alteração sem sucesso
            } else {
                printf("\nOpcao invalida!\n");
            }
        } while (opcao != 'N' && opcao != 'n');
    }
}

void salvarDados(Venda *vendas, int totalVendas) {
    FILE *file = fopen("vendas.bin", "wb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para salvar os dados.\n");
        return;
    }
    fwrite(&totalVendas, sizeof(int), 1, file); // Salva a quantidade de vendas
    fwrite(vendas, sizeof(Venda), totalVendas, file); // Salva os dados das vendas
    fclose(file);
    printf("Dados salvos com sucesso!\n");
}

void carregarDados(Venda *vendas, int *totalVendas) {
    FILE *file = fopen("vendas.bin", "rb");
    if (file == NULL) {
        printf("Nenhum dado para carregar ou erro ao abrir o arquivo.\n");
        *totalVendas = 0;
        return;
    }
    fread(totalVendas, sizeof(int), 1, file); // Lê a quantidade de vendas
    fread(vendas, sizeof(Venda), *totalVendas, file); // Lê os dados das vendas
    fclose(file);
    printf("Dados carregados com sucesso!\n");
}


// Função para excluir uma venda
void excluirVenda(Venda *vendas, int *totalVendas) {
    int numeroVenda;
    char opcao;

    printf("\n==================================\n");

    printf("\nDigite o numero da venda que deseja excluir: ");
    scanf("%d", &numeroVenda);

    int encontrou = 0;
    for (int i = 0; i < *totalVendas; i++) {
        if (vendas[i].numeroVenda == numeroVenda) {
            encontrou = 1;
            printf("\nDados da Venda a ser Excluida:\n");
            printf("Numero da Venda: %d\n", vendas[i].numeroVenda);
            printf("Codigo do Cliente: %d\n", vendas[i].codigoCliente);
            printf("Nome do Cliente: %s\n", vendas[i].nomeCliente);
            printf("Data da Compra: %s\n", vendas[i].dataCompra);
            printf("Nome do Produto: %s\n", vendas[i].nomeProduto);
            printf("Marca: %s\n", vendas[i].marca);
            printf("Codigo do Produto: %d\n", vendas[i].codigoProduto);
            printf("Quantidade: %d\n", vendas[i].quantidade);
            printf("Preco Unitario: %.2f\n", vendas[i].precoUnitario);
            printf("Preco Total: R$ %.2f\n", vendas[i].precoTotal);
            printf("\n");

            printf("Deseja realmente excluir a venda (S/N): ");
            scanf(" %c", &opcao);
            if (opcao == 'S' || opcao == 's') {
                // Remover a venda da lista
                for (int j = i; j < *totalVendas - 1; j++) {
                    vendas[j] = vendas[j + 1];
                }
                (*totalVendas)--;
                printf("\nVenda excluida com sucesso!\n");
            } else if (opcao == 'N' || opcao == 'n') {
                printf("\nRetornando ao menu principal...\n");
            } else {
                printf("\nOpcao invalida!\n");
            }
            return; // Retorna ao menu principal após a exclusão
        }
    }

    if (!encontrou) {
        printf("\nVenda nao encontrada!\n");
    }
}


int main() {
    if (!fazerLogin()) {
        return 0; // Encerra o programa se o login não for bem-sucedido
    }Venda vendas[100];
    int totalVendas = 0;

    carregarDados(vendas, &totalVendas);

    int opcao;
    do {
        exibirMenuPrincipal();
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                cadastrarVenda(vendas, &totalVendas);
                salvarDados(vendas, totalVendas);
                break;
            case 2:
                listarVendas(vendas, totalVendas);
                break;
            case 3:
                relatorioDiarioCompras(vendas, totalVendas);
                break;
            case 4:
                alterarVenda(vendas, totalVendas);
                salvarDados(vendas, totalVendas);
                break;
            case 5:
                excluirVenda(vendas, &totalVendas);
                salvarDados(vendas, totalVendas);
                break;
            case 6:
                printf("\nEncerrando o programa...\n");
                salvarDados(vendas, totalVendas);
                break;
            default:
                printf("\nOpcao invalida! Por favor, escolha uma opcao valida.\n");
        }
    } while (opcao != 6);

    return 0;
}
