#include <stdio.h>
#include <stdlib.h>

int menu() {
    int m = -1;
    while (m < 0) {
        printf("\t-----------------------------------------------------------\n");
        printf("\t1- Gerir Categorias e Produtos: \n");
        printf("\t2- Gerir clientes e vendas: \n");
        printf("\t3- Criar Relatorio de stock do inventario: \n");
        printf("\t4- Produto fora de Stock:\n");
        printf("\t0- Sair. \n");
        printf("\t-----------------------------------------------------------\n");

        printf("Escolha uma Opcao:");
        scanf("%d", &m);

        if (m < 0 || m > 4) {
            printf("Opcao invalida. Tente novamente.\n");
        }
    }

    return m;
}
int menugerirCategoriaseProdutos() {
    int op = 0;
    do {
        printf("\t-----------------------------------------------------------\n");
        printf("\t1- gerir Categoria\n");
        printf("\t2- gerir Produtos\n");
        printf("\t3- listar categorias e produtos associados\n");
        printf("\t4- gerar relatorio de produtos");
        printf("\t0- Voltar\n");
        printf("\t-----------------------------------------------------------\n");

        printf("Escolha uma Opcao: ");
        scanf("%d", &op);

        if (op < 0 || op > 4) {
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (op < 0 || op > 4);

    return op;
}
int menugerircategorias() {
    int op = 0;
    do {
        printf("\t-----------------------------------------------------------\n");
        printf("\t1- Adicionar Categoria\n");
        printf("\t2- listar categorias\n");
        printf("\t3- remover categorias\n");
        printf("\t4- Atualizar categoria\n");
        printf("\t0- Voltar\n");
        printf("\t-----------------------------------------------------------\n");

        printf("Escolha uma Opcao: ");
        scanf("%d", &op);

        if (op < 0 || op > 4) {
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (op < 0 || op > 4);

    return op;
}
int menugerirprodutos() {
    int op = 0;
    do {
        printf("\t-----------------------------------------------------------\n");
        printf("\t1- Adicionar produto\n");
        printf("\t2- listar produtos\n");
        printf("\t3- remover produto\n");
        printf("\t4- Atualizar produto\n");
        printf("\t5- retirar stock de um produto\n");
        printf("\t6- adicionar stock de um produto\n");
        printf("\t0- Voltar\n");
        printf("\t-----------------------------------------------------------\n");

        printf("Escolha uma Opcao: ");
        scanf("%d", &op);

        if (op < 0 || op > 6) {
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (op < 0 || op > 6);

    return op;
}
int menugerirVendaseClientes(){
    int op = 0;
    do {
        printf("\t-----------------------------------------------------------\n");
        printf("\t1- Gerir Clientes\n");
        printf("\t2- Gerir Venda\n");
        printf("\t0- Voltar\n");
        printf("\t-----------------------------------------------------------\n");

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
        printf("\t-----------------------------------------------------------\n");
        printf("\t1- Adicionar Cliente\n");
        printf("\t2- Listar Clientes\n");
        printf("\t3- Remover Cliente\n");
        printf("\t4- Alterar Cliente\n");
        printf("\t0- Voltar\n");
        printf("\t-----------------------------------------------------------\n");

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
        printf("\t-----------------------------------------------------------\n");
        printf("\t1- Adicionar Venda\n");
        printf("\t2- Listar Vendas\n");
        printf("\t3- Remover Venda\n");
        printf("\t0- Voltar\n");
        printf("\t-----------------------------------------------------------\n");

        printf("Escolha uma Opcao: ");
        scanf("%d", &op);

        if (op < 0 || op > 3) {
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (op < 0 || op > 3);

    return op;
}

int menulistarpor(){
    int op = 0;

    do {
        printf("\t-----------------------------------------------------------\n");
        printf("\t1- Listar por nome\n");
        printf("\t2- Listar por preco\n");
        printf("\t0- Voltar\n");
        printf("\t-----------------------------------------------------------\n");

        printf("Escolha uma Opcao: ");
        scanf("%d", &op);

        if (op < 0 || op > 2) {
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (op < 0 || op > 2);

    return op;
}
int menulistarclientes(){
    int op = 0;

    do {
        printf("\t-----------------------------------------------------------\n");
        printf("\t1- Listar todos por ordem alfabetica\n");
        printf("\t2- Listar um determinado cliente pelo NIF\n");
        printf("\t0- Voltar\n");
        printf("\t-----------------------------------------------------------\n");  
        printf("Escolha uma Opcao: ");
        scanf("%d", &op);

        if (op < 0 || op > 2) {
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (op < 0 || op > 2);

    return op;
}