#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listas.c"
#include "menus.c"

int main()
{
    int opcao, op, op2, op3, num_categorias = 0;
    lista *iniciolista = NULL;
    lista *fimlista = NULL;
    lista_vendas *iniciolista_vendas = NULL;
    lista_vendas *fimlista_vendas = NULL;
    lista_clientes *iniciolistaclientes = NULL;
    lista_clientes *fimlistaclientes = NULL;
    int num_produtos = 0;
    int num_vendas, num_clientes = 0;
    int id_cliente, id_produto = -1;
    categoria categorias[100];
    ler_categorias(categorias, &num_categorias);
    ler_produtos(&iniciolista, &fimlista, &num_produtos, categorias);
    ler_clientes(&iniciolistaclientes, &fimlistaclientes, &num_clientes);
    do
    {
        opcao = menu();
        switch (opcao)
        {
        case 1:
            do
            {
                op = menugerirCategoriaseProdutos();
                switch (op)
                {
                case 1:
                    do
                    {
                        op2 = menugerircategorias();
                        switch (op2)
                        {
                        case 1:
                            adicionar_categoria(categorias, &num_categorias);
                            printf("%d", num_categorias);
                            break;
                        case 2:
                            listar_categorias(categorias, num_categorias);
                            break;
                        case 3:
                            remover_categoria(categorias, &num_categorias);
                            break;
                        case 4:
                            atualizar_categoria(categorias, &num_categorias, iniciolista);
                            break;
                        default:
                            break;
                        }
                    } while (op2 != 0);

                    break;
                case 2:
                    do
                    {
                        op2 = menugerirprodutos();
                        switch (op2)
                        {
                        case 1:
                            adicionar_produto(&iniciolista, &fimlista, &num_produtos, categorias, &num_categorias);
                            break;
                        case 2:
                            op3 = menulistarpor();
                            switch (op3)
                            {
                            case 1:
                                ordenar_produtos_alfabetica(&iniciolista, &fimlista);
                                listar_produtos(iniciolista);
                                ordenar_produtos_ids(&iniciolista, &fimlista);
                                break;
                            case 2:
                                ordenar_preco_desc(&iniciolista, &fimlista);
                                listar_produtos(iniciolista);
                                ordenar_produtos_ids(&iniciolista, &fimlista);
                                break;
                            default:
                                break;
                            }
                            break;
                        case 3:
                            remover_produto(&iniciolista, &fimlista, &num_clientes);
                            break;
                        case 4:
                            atualizar_produto(iniciolista, categorias, &num_categorias);
                            break;
                        case 5:
                            retirar_stock(iniciolista);
                            break;
                        case 6:
                            adicionar_stock(iniciolista);
                            break;
                        default:
                            break;
                        }

                    } while (op2 != 0);
                    break;
                case 3:
                    // listar categorias e produtos
                    listar_produtos_categoria(iniciolista, categorias, num_categorias);
                    break;
                case 4:
                    // gerar relatorio dos produtos
                    gerar_relatorio_produtos_categoria(iniciolista, categorias, num_categorias);
                default:
                    break;
                }
            } while (op != 0);
            break;
        case 2:
            // menugerirVendaseClientes()
            do
            {
                op = menugerirVendaseClientes();
                switch (op)
                {
                case 1:
                    do
                    {
                        op2 = menugerirClientes();
                        switch (op2)
                        {
                        case 1:
                            adicionar_cliente(&iniciolistaclientes, &fimlistaclientes, &num_clientes);
                            break;
                        case 2:
                            do
                            {
                                op3 = menulistarclientes();
                                switch (op3)
                                {
                                case 1:
                                    ordenar_clientes_alfabetica(&iniciolistaclientes, &fimlistaclientes);
                                    listar_clientes(iniciolistaclientes);
                                    ordenar_clientes_id(&iniciolistaclientes,&fimlistaclientes);
                                    break;
                                case 2:
                                    procurar_cliente(iniciolistaclientes);
                                    break;
                                default:
                                    break;
                                }

                            } while (op3 != 0);
                            break;
                        case 3:
                            remover_cliente(&iniciolistaclientes, &fimlistaclientes, &num_clientes);
                            break;
                        case 4:
                            atualizar_cliente(iniciolistaclientes);
                            break;
                        default:
                            break;
                        }
                    } while (op2 != 0);
                    break;
                case 2:
                    // menugerirvendas
                    do
                    {
                        op2 = menugerirVendas();
                        switch (op2)
                        {
                        case 1:
                            id_cliente = encontrar_id_cliente(iniciolistaclientes);
                            if (id_cliente == -1)
                            {
                                printf("Cliente nao encontrado\n");
                                break;
                            }
                            id_produto = encontrar_id_produto(iniciolista);
                            if (id_produto == -1)
                            {
                                printf("Produto nao encontrado\n");
                                break;
                            }
                            int quantidade;
                            int desconto;
                            int verificacao;
                            do
                            {
                                
                                printf("insira a quantidade a comprar: ");
                                scanf("%d", &quantidade);
                                verificacao = verificar_quantidade(iniciolista, id_produto, quantidade);
                                if (verificacao == 0)
                                {
                                    printf("Quantidade indisponivel ou sem stock\n");
                                }
                            } while (verificacao != 0) ;
                            do
                            {
                                printf("insira o desconto: (0-100)");
                                scanf("%d", &desconto);
                            }
                            while (desconto < 0 || desconto > 100)
                                ;
                            float precoproduto;
                            precoproduto = encontrar_preco_produto(iniciolista, id_produto);
                            adicionar_venda(&iniciolista_vendas, &fimlista_vendas, &num_vendas, id_cliente, id_produto, quantidade, desconto, precoproduto);
                            retirar_quantidade(iniciolista,quantidade,id_produto);

                            break;
                        case 2:
                            listar_vendas(iniciolista_vendas);
                            break;
                        case 3:
                            // remover_venda(&iniciolista_vendas,&fimlista_vendas,&num_vendas);
                            break;
                        case 4:
                            // atualizar_venda(iniciolista_vendas,iniciolista,iniciolistaclientes);
                            break;
                        default:
                            break;
                        }
                    } while (op2 != 0);

                    break;
                }
            } while (op != 0);
            break;
        case 0:
            printf("A sair...\n");
            guardar_categorias(categorias, num_categorias);
            guardar_produtos(iniciolista);
            guardar_clientes(iniciolistaclientes);
            break;
        default:
            break;
        }
    } while (opcao != 0);
    return 0;
}
