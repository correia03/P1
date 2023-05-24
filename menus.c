#include <stdio.h>
#include <stdlib.h>

int menu() {
    int m = -1;

    while (m < 0) {
        printf("\t1- Gerir Categorias e Produtos: \n");
        printf("\t2- Gerir clientes e vendas: \n");
        printf("\t3- Criar Relatorio de stock do inventario: \n");
        printf("\t4- Produto fora de Stock:\n");
        printf("\t0- Sair. \n");

        printf("Escolha uma Opcao:");
        scanf("%d", &m);

        if (m < 0 || m > 4) {
            printf("Opcao invalida. Tente novamente.\n");
        }
    }

    return m;
}
int menugerirCategoriaseVendas() {
    int op = 0;
    do {
        printf("\t1- gerir Categoria\n");
        printf("\t2- gerir Produtos\n");
        printf("\t0- Voltar\n");

        printf("Escolha uma Opcao: ");
        scanf("%d", &op);

        if (op < 0 || op > 2) {
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (op < 0 || op > 2);

    return op;
}
int menugerircategorias() {
    int op = 0;

    do {
        printf("\t1- Adicionar Categoria\n");
        printf("\t2- listar categorias\n");
        printf("\t3- remover categorias\n");
        printf("\t0- Voltar\n");

        printf("Escolha uma Opcao: ");
        scanf("%d", &op);

        if (op < 0 || op > 3) {
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (op < 0 || op > 3);

    return op;
}
int menugerirprodutos() {
    int op = 0;

    do {
        printf("\t1- Adicionar produto\n");
        printf("\t2- listar produto\n");
        printf("\t3- produto\n");
        printf("\t0- Voltar\n");

        printf("Escolha uma Opcao: ");
        scanf("%d", &op);

        if (op < 0 || op > 3) {
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (op < 0 || op > 3);

    return op;
}
int menugerirVendaseClientes(){
    int op = 0;

    do {
        printf("\t1- Gerir Clientes\n");
        printf("\t2- Gerir Venda\n");
        printf("\t0- Voltar\n");

        printf("Escolha uma Opcao: ");
        scanf("%d", &op);

        if (op < 0 || op > 2) {
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (op < 0 || op > 2);

    return op;
}
int menugerirClientes(){
    int op = 0;

    do {
        printf("\t1- Adicionar Cliente\n");
        printf("\t2- Listar Clientes\n");
        printf("\t3- Remover Cliente\n");
        printf("\t4- Alterar Cliente\n");
        printf("\t0- Voltar\n");

        printf("Escolha uma Opcao: ");
        scanf("%d", &op);

        if (op < 0 || op > 4) {
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (op < 0 || op > 4);

    return op;
}
int menugerirVendas(){
    int op = 0;

    do {
        printf("\t1- Adicionar Venda\n");
        printf("\t2- Listar Vendas\n");
        printf("\t3- Remover Venda\n");
        printf("\t0- Voltar\n");

        printf("Escolha uma Opcao: ");
        scanf("%d", &op);

        if (op < 0 || op > 3) {
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (op < 0 || op > 3);

    return op;
}