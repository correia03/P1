#include <stdio.h>


int menu() {
	
	int m = 0;
	
	while(m>=0) {
		system("cls");
		printf("\t1- Gerir Produtos: \n");
		
		printf("\t2- Criar Relatorio de stock do inventario: \n");

        printf("/t3- Produto fora de Stock:");

		printf("\t0- Sair. \n");
		
		printf("Escolha uma Opcao:");
		scanf("%d", &m);
		
    }
    return m;
}