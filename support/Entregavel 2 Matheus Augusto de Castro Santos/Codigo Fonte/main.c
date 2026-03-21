#include "globals.h"
#include "scan.h"
#include "parse.h"
#include "util.h"
#include "analyze.h"
#include "codigoIntermediario.h"
#include <string.h>


int main(int argc, char **argv){

	source = fopen(argv[1],"r");
	if(source == NULL)
	{
		printf("\nNão foi possível abrir o arquivo de entrada\n");
		exit(0);
	}
	TreeNode *arvoreSintatica;
	printf("Iniciando análise...\n");
	arvoreSintatica = parse();
	if(arvoreSintatica != NULL)
	{
		//printTreeR(arvoreSintatica);
		printf("Árvore sintática criada...\n");
		buildSymtab(arvoreSintatica);
		printf("Tabela de simbolos criada...\n");
		printTreeR(arvoreSintatica);//printando a arvore sintatica depois da tabela de simbolos pq durante a analise semantica ainda existe a troca de escopos
	
	}
	gerarIntermediario(arvoreSintatica);


}
