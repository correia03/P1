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
    categoria categorias[100];
    ler_categorias(categorias, &num_categorias);
    ler_produtos(&iniciolista, &fimlista, &num_produtos, categorias);
    ler_clientes(&iniciolistaclientes,&fimlistaclientes, &num_clientes);
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
                                ordenar_produtos_alfabetica(&iniciolista,&fimlista);
                                listar_produtos(iniciolista);
                                ordenar_produtos_ids(&iniciolista,&fimlista);
                                break;
                            case 2:
                                ordenar_preco_desc(&iniciolista,&fimlista);
                                listar_produtos(iniciolista);
                                ordenar_produtos_ids(&iniciolista,&fimlista);
                            break;
                            default:
                                break;
                            }
                            break;
                        case 3:
                            remover_produto(&iniciolista,&fimlista,&num_clientes);
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
                 //listar categorias e produtos 
                    listar_produtos_categoria(iniciolista,categorias,num_categorias);
                    break;
                case 4:
                    //gerar relatorio dos produtos
                    gerar_relatorio_produtos_categoria(iniciolista,categorias,num_categorias);
                default:
                    break;
                }
            } while (op != 0);
            break;
        case 2:
        //menugerirVendaseClientes()
            do{
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
                            adicionar_cliente(&iniciolistaclientes,&fimlistaclientes,&num_clientes);
                            break;
                        case 2:
                            do
                            {
                                op3 = menulistarpor();
                                switch (op3)
                                {
                                case 1:
                                    ordenar_clientes_alfabetica(&iniciolistaclientes,&fimlistaclientes);
                                    listar_clientes(iniciolistaclientes);
                                    break;
                                case 2:
                                    procurar_cliente(iniciolistaclientes)
                                    break;
                                default:
                                    break;
                                }
                                
                            } while (op3 != 0 );
                            break;
                        case 3:
                            remover_cliente(&iniciolistaclientes,&fimlistaclientes,&num_clientes);
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

                    break;
                }
            }while (op != 0);
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
