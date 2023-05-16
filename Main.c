#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listas.c"
#include "menus.c"

int main()
{
    int opcao, op, op2, num_categorias = 0;
    lista *iniciolista = NULL;
    lista *fimlista = NULL;
    int num_produtos = 0;
    categoria categorias[10];
    ler_categorias(categorias, &num_categorias);
    // ler produtos chamar função void ler_produtos(lista **iniciolista, lista **fimlista, int *num_produtos, categoria *categorias, int *num_categorias)
    ler_produtos(&iniciolista, &fimlista, &num_produtos, categorias, &num_categorias);
    do
    {
        opcao = menu();
        switch (opcao)
        {
        case 1:
            do
            {
                op = menugerir();
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
                            ordenar_produtos(iniciolista);
                            listar_produtos(iniciolista);
                            break;
                        case 3:
                            remover_produto(&iniciolista,&fimlista);
                            break;
                        default:
                            break;
                        }
                        break;
                    } while (op2 != 0);
                default:
                    break;
                }
            } while (op != 0);
            break;
        case 0:
            printf("A sair...\n");
            guardar_categorias(categorias, num_categorias);
            // guardar produtos chamar a funçao void guardar_produtos(lista *iniciolista)
            guardar_produtos(iniciolista);
            break;
        default:
            break;
        }
    } while (opcao != 0);
    return 0;
}
