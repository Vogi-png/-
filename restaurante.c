/* 

(não foi utilizado arquivo bin)
Exercídio de Extensão II - 
Feito por:
  - Giovanna Leal
  - Caio Vitor
  */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

// Informação dos Produtos
struct prato
{
    char titulo[100];
    int regnum;
    float preco;
};

struct bebida
{
    char titulo[100];
    int regnum;
    float preco;
};
struct bebida beba;

// Informação da Compra
struct compra
{
    struct prato produto;
    int quantidade;
};

// Struct para pratos cobrados por Self-service --------------------------------
struct selfserv
{
    char titulo[100];
    float peso;
    float preco;
};

struct tempo
{
    int dia;
    int mes;
    int ano;
};
struct tempo temp;

// Strucy para informações do relatório
typedef struct dados
{
    int cliente;      // total de clientes
    float total;      // soma de tudo
    float totalD[31]; // no dia
    float totalM[12]; // no mês
    float totalkg;
    float drink;
    struct venda
    {
        struct tempo dataCompra;
        float precoTotal;
        float pesoTotal;
    } vendas[100];   // Assumindo que pode haver até 100 vendas
    int totalVendas; // Total de vendas realizadas
} dados;
dados info;


struct selfserv refeicao;
// Float para quentinha (preço fixo) -------------------------------------------
float Quentinha = 20.5;
// -----------------------------------------------------------------------------

void beber()
{
    int respbb;
    struct bebida beba1 = {"Água ", 0, 2};
    struct bebida beba2 = {"Guaraná", 2, 5};
    struct bebida beba3 = {"Cerveja", 2, 7.50};
    struct bebida beba4 = {"Suco de Laranja", 0, 12.30};

    printf("\n================================================\n");
    printf("=== B E B I D A S ===\n\n");
    printf(" [1] - %s:  R$ %.2f\n", beba1.titulo, beba1.preco);
    printf(" [2] - %s:  R$ %.2f\n", beba2.titulo, beba2.preco);
    printf(" [3] - %s:  R$ %.2f\n", beba3.titulo, beba3.preco);
    printf(" [4] - %s:  R$ %.2f\n", beba4.titulo, beba4.preco);

    int resp;
    printf(" >> Escolha o produto: ");
    scanf("%d", &respbb);
    printf("================================================\n");

    switch (respbb)
    {
    case 1:
        info.drink = beba1.preco + info.drink;
        break;
    case 2:
        info.drink = beba2.preco + info.drink;
        break;
    case 3:
        info.drink = beba3.preco + info.drink;
        break;
    case 4:
        info.drink = beba4.preco + info.drink;
        break;
    }
}

// Função para calcular o acumulado do preço por dia e mês
void calcularAcumulado(float precoCompra)
{
    info.total += precoCompra; // Adiciona o preço da compra ao total acumulado

    // Adiciona o preço da compra ao total acumulado do dia
    info.totalD[temp.dia] += precoCompra;

    // Adiciona o preço da compra ao total acumulado do mês
    info.totalM[temp.mes - 1] += precoCompra;
}

// Função para ordenar as vendas por preço total em ordem decrescente
void ordenarVendasPorPreco(struct venda *vendas, int totalVendas)
{
    // Algoritmo de ordenação de seleção
    for (int i = 0; i < totalVendas - 1; i++)
    {
        int max_index = i;
        for (int j = i + 1; j < totalVendas; j++)
        {
            if (vendas[j].precoTotal > vendas[max_index].precoTotal)
            {
                max_index = j;
            }
        }
        // Troca as vendas de posição
        struct venda temp = vendas[max_index];
        vendas[max_index] = vendas[i];
        vendas[i] = temp;
    }
}

// Enum para representar as opções do menu de entrada
enum OpcaoMenu
{
    QUENTINHAS = 1,
    SELF_SERVICE = 2,
    LISTA_VENDAS = 3,
    RELATORIO_DIARIO = 4,
    RELATORIO_MENSAL = 5,
    SAIR = 0
};

int totalClientesNoDia = 0; // Variável global para armazenar o total de clientes no dia
int totalClientesNoMes = 0; // Variável global para armazenar o total de clientes no mês
// Função p/ relatório por pesquisa mensal
void relatorioMensal()
{
    int mesPesquisa, anoPesquisa;
    float totalMensal = 0;

    printf("\nDigite o mês para o relatório (MM): ");
    scanf("%d", &mesPesquisa);
    printf("Digite o ano para o relatório (AAAA): ");
    scanf("%d", &anoPesquisa);

    totalClientesNoDia = 0; // Inicializa o total de clientes no dia como zero
    totalClientesNoMes = 0; // Inicializa o total de clientes no mês como zero

    printf("\nRelatório de Vendas para %02d/%d:\n", mesPesquisa, anoPesquisa);
    printf("-------------------------------------------------\n");

    int vendasNoMes = 0;
    for (int i = 0; i < info.totalVendas; i++)
    {
        if (info.vendas[i].dataCompra.mes == mesPesquisa &&
            info.vendas[i].dataCompra.ano == anoPesquisa)
        {
            printf("Data: %02d/%02d/%d - Preço Total: R$ %.2f\n",
                   info.vendas[i].dataCompra.dia, info.vendas[i].dataCompra.mes, info.vendas[i].dataCompra.ano, info.vendas[i].precoTotal);
            totalMensal += info.vendas[i].precoTotal;
            vendasNoMes++;

            // Incrementa o total de clientes no dia
            totalClientesNoDia++;
        }
    }

    if (vendasNoMes > 0)
    {
        printf("-------------------------------------------------\n");
        printf("Total de vendas em %02d/%d: R$ %.2f\n", mesPesquisa, anoPesquisa, totalMensal);
        printf("Total de clientes no mês: %d\n", totalClientesNoDia); // Exibe o total de clientes no dia
    }
    else
    {
        printf("Nenhuma venda registrada para este mês.\n");
    }
}

// Função p/ Relatório Diário
void relatorioDiario()
{
    int diaPesquisa, mesPesquisa, anoPesquisa;
    float totalDiario = 0;
    float pesoTotalDiario = 0; // Variável para acumular o peso total

    printf("\nDigite o dia para o relatório (DD): ");
    scanf("%d", &diaPesquisa);
    printf("Digite o mês para o relatório (MM): ");
    scanf("%d", &mesPesquisa);
    printf("Digite o ano para o relatório (AAAA): ");
    scanf("%d", &anoPesquisa);

    totalClientesNoDia = 0; // Inicializa o total de clientes no dia como zero
    totalClientesNoMes = 0; // Inicializa o total de clientes no mês como zero

    printf("\nRelatório de Vendas para %02d/%02d/%d:\n", diaPesquisa, mesPesquisa, anoPesquisa);
    printf("-------------------------------------------------\n");

    // Ordenar as vendas por preço total em ordem decrescente
    ordenarVendasPorPreco(info.vendas, info.totalVendas);

    int vendasNoDia = 0;
    for (int i = 0; i < info.totalVendas; i++)
    {
        if (info.vendas[i].dataCompra.dia == diaPesquisa &&
            info.vendas[i].dataCompra.mes == mesPesquisa &&
            info.vendas[i].dataCompra.ano == anoPesquisa)
        {
            printf("Data: %02d/%02d/%d - Preço Total: R$ %.2f, Peso Total: %.2f kg\n",
                   info.vendas[i].dataCompra.dia, info.vendas[i].dataCompra.mes, info.vendas[i].dataCompra.ano,
                   info.vendas[i].precoTotal, info.vendas[i].pesoTotal);
            totalDiario += info.vendas[i].precoTotal;
            pesoTotalDiario += info.vendas[i].pesoTotal; // Acumula o peso total
            vendasNoDia++;

            // Incrementa o total de clientes no dia
            totalClientesNoDia++;
        }
    }

    if (vendasNoDia > 0)
    {
        printf("-------------------------------------------------\n");
        printf("Total de vendas em %02d/%02d/%d: R$ %.2f\n", diaPesquisa, mesPesquisa, anoPesquisa, totalDiario);
        printf("Peso total das vendas: %.2f kg\n", pesoTotalDiario); // Mostra o peso total
        printf("Total de clientes no dia: %d\n", totalClientesNoDia); // Exibe o total de clientes no dia
    }
    else
    {
        printf("Nenhuma venda registrada para esta data.\n");
    }
}

// Função Principal
int main(void)
{
    float embalagem;
    embalagem = 0.5;
    float k;
    char respb;
    int ope;
    setlocale(LC_ALL, "portuguese"); // Configurar o idioma
    entrada:
    printf("\n================================================\n");
    printf("   >> == M E N U   de   E N T R A D A == <<\n");
    printf(" [1] - Quentinhas\n");
    printf(" [2] - Self-service\n");
    printf(" [3] - Lista de Vendas\n");
    printf(" [4] - Relatório Diário\n");
    printf(" [5] - Relatório Mensal\n");
    printf(" [0] - Sair\n");
    scanf("%d", &ope);
    printf("================================================\n\n");
    setlocale(LC_ALL, "portuguese"); // Configurar o idioma

    if (ope == QUENTINHAS)
    {
        setlocale(LC_ALL, "portuguese");
        float totalVendas = 0;

        while (1)
        {
            printf("\t >> SEJA BEM-VINDO(A) <<\n\n");

            // cardápio das quentinhas
            struct prato prato1 = {"Arroz, feijão e frango grelhado ", 0, 20};
            struct prato prato2 = {"Macarrão c/ molho de tomate", 2, 20};
            struct prato prato3 = {"Tutu com legumes (prato vegetariano)", 2, 20};
            struct prato prato4 = {"Estrogonofe", 0, 20};

            // Variáveis para armazenar as compras
            struct compra compras[100]; // Assumindo que o cliente pode fazer até 100 compras
            int totalCompras = 0;       // Total de compras realizadas

            char continuar;

            do
            {
                printf("\n================================================\n");
                printf("=== P R O D U T O S    D A     L O J A ===\n\n");
                printf(" [1] - %s:  R$ %.2f\n", prato1.titulo, prato1.preco);
                printf(" [2] - %s:  R$ %.2f\n", prato2.titulo, prato2.preco);
                printf(" [3] - %s:  R$ %.2f\n", prato3.titulo, prato3.preco);
                printf(" [4] - %s:  R$ %.2f\n", prato4.titulo, prato4.preco);

                int resp;
                printf(" >> Escolha o produto: ");
                scanf("%d", &resp);
                printf("================================================\n");

                // Verificar se a opção escolhida é válida
                if (resp < 1 || resp > 4)
                {
                    printf("Opção inválida!\n");
                    break; // Reinicia o loop sem processar o restante do código
                }

                // Adicionar o produto escolhido à lista de compras
                compras[totalCompras].quantidade = 1; // Começa com uma unidade
                switch (resp)
                {
                case 1:
                    compras[totalCompras].produto = prato1;
                    break;
                case 2:
                    compras[totalCompras].produto = prato2;
                    break;
                case 3:
                    compras[totalCompras].produto = prato3;
                    break;
                case 4:
                    compras[totalCompras].produto = prato4;
                    break;
                }

                // Perguntar se deseja adicionar mais algum produto
                printf(" >> Deseja adicionar mais algum produto? (S/N): ");
                scanf(" %c", &continuar);

                // Se o cliente deseja continuar, incrementa o total de compras
                if (continuar == 'S' || continuar == 's')
                {
                    totalCompras++;
                }

                printf(" >> Adicionar Alguma Bebida? (S/N)");
                scanf("%s", &respb);

                repit:
                if (respb == 'S' || respb == 's')
                {
                    beber();
                }

            } while (continuar == 'S' || continuar == 's');

            ("\n================================================");
            printf("\n=== = R E C I B O = ===\n\n");
            float totalCompraCliente = 0;
            for (int i = 0; i <= totalCompras; i++)
            {
                struct compra c = compras[i];
                printf("+ Produto: %s\n", c.produto.titulo);
                printf("- Quantidade: %d\n", c.quantidade);
                printf("- Preço unitário: R$ %.2f\n", c.produto.preco);
                float subtotal = c.produto.preco * c.quantidade;
                subtotal = subtotal + embalagem;
                printf("- Subtotal: R$ %.2f\n", subtotal);
                totalCompraCliente += subtotal;
                printf ("- Embalagem: R$ %.2f\n\n", embalagem);
            }
            if (respb == 'S' || respb == 's'){
                printf("> Adicionado bebida: %.2f\n", info.drink);
            }
            totalCompraCliente += info.drink ;
            printf("> Total da compra: R$ %.2f\n", totalCompraCliente);

            printf("================================================");

            // Perguntar se deseja registrar outra compra
            printf("\n >> Deseja confirmar essa compra? (S/N): ");
            scanf(" %s", &continuar);
            if (continuar == 'S' || continuar == 's')
            {

                // Solicitar cada parte da data de forma explícita
                printf(">> Por favor, insira a data da compra:\n");

                printf("Digite o dia (DD): ");
                scanf("%d", &temp.dia);

                printf("Digite o mês (MM): ");
                scanf("%d", &temp.mes);

                printf("Digite o ano (AAAA): ");
                scanf("%d", &temp.ano);

                printf("Data registrada: %d/%d/%d\n", temp.dia, temp.mes, temp.ano);

                // Armazenar a venda na estrutura info.vendas
                info.vendas[info.totalVendas].dataCompra.dia = temp.dia;
                info.vendas[info.totalVendas].dataCompra.mes = temp.mes;
                info.vendas[info.totalVendas].dataCompra.ano = temp.ano;
                info.vendas[info.totalVendas].precoTotal = totalCompraCliente;

                // Atualizar o total de vendas
                info.totalVendas++;

                calcularAcumulado(totalCompraCliente);
                info.cliente++;
                return main();
             } else {
                printf("cancelando...");
                return main();
            }
        }
    }
    else if (ope == SELF_SERVICE)
    {
        setlocale(LC_ALL, "portuguese");
        printf(">> Digite o peso da refeição em KG: ");
        scanf("%f", &refeicao.peso);
        float totalg = refeicao.peso * 4; // Supondo que o preço por kg seja 4
        info.totalkg = totalg;

        printf("Adicionar Alguma Bebida? (S/N): ");
        scanf(" %c", &respb); // Assegure-se de incluir espaço antes de %c para consumir qualquer newline deixado no buffer de entrada

        if (respb == 'S' || respb == 's')
        {
            beber(); // Chama a função que permite ao usuário escolher uma bebida
        }

        // Calcular o total final após adicionar bebidas, se alguma foi escolhida
        float totalFinal;

        printf("\n================================================");
        printf("\n=== = R E C I B O = ===\n\n");
        printf("Preco da Refeição: %.2f\n", totalg);
        if (respb == 'S' || respb == 's'){
            printf("Adicionado bebida: R$ %.2f\n", info.drink);
            totalFinal = totalg + info.drink;
        }
        printf("Total: R$ %.2f\n", totalFinal);

        printf("================================================");

        char continuar;
        printf("\nDeseja registrar essa compra? (S/N): ");
        scanf(" %c", &continuar);

        if (continuar == 'S' || continuar == 's')
        {
            printf(">> Por favor, insira a data da compra:\n");
            printf("Digite o dia (DD): ");
            scanf("%d", &temp.dia);
            printf("Digite o mês (MM): ");
            scanf("%d", &temp.mes);
            printf("Digite o ano (AAAA): ");
            scanf("%d", &temp.ano);

            // Armazenar a venda na estrutura info.vendas
            info.vendas[info.totalVendas].dataCompra.dia = temp.dia;
            info.vendas[info.totalVendas].dataCompra.mes = temp.mes;
            info.vendas[info.totalVendas].dataCompra.ano = temp.ano;
            info.vendas[info.totalVendas].precoTotal = totalFinal;
            info.vendas[info.totalVendas].pesoTotal = refeicao.peso;

            // Atualizar o total de vendas
            info.totalVendas++;
            calcularAcumulado(totalFinal);
            info.cliente++;

            printf("Compra registrada com sucesso!\n");
        }

        return main();
    }
    else if (ope == LISTA_VENDAS)
    {
        setlocale(LC_ALL, "portuguese");
        printf("\n================================================\n");
        printf("=== = R E L A T Ó R I O   de   V E N D A S = === \n");
        printf("    > Total de clientes: %d\n", info.cliente);
        printf("    > Total de vendas acumuladas: R$ %.2f\n", info.total);
        printf("================================================\n");

        // Ordenar as vendas por preço total em ordem decrescente
        ordenarVendasPorPreco(info.vendas, info.totalVendas);

        // Imprimir a lista de datas de vendas em ordem decrescente em relação ao preço
        printf("\n >> Lista de datas de vendas:\n");
        for (int i = 0; i < info.totalVendas; i++)
        {
            printf("Data: %d/%d/%d - Preço total: R$ %.2f\n", info.vendas[i].dataCompra.dia, info.vendas[i].dataCompra.mes, info.vendas[i].dataCompra.ano, info.vendas[i].precoTotal);
        }
        return main();
    }
    else if (ope == RELATORIO_DIARIO)
    {
        relatorioDiario();
        return main();
    }
    else if (ope == RELATORIO_MENSAL)
    {
        relatorioMensal();
        return main();
    }
    else if (ope == SAIR)
    {
        return 0;
    }
    else
    {
        setlocale(LC_ALL, "portuguese");
        printf("Opção inválida!\n");
        return main();
    }
}
