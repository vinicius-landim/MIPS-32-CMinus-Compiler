#include "globals.h"
#include "util.h"

extern FILE *yyin;
extern int yyparse(void);
extern TreeNode *AST;

int lineNo = 1;
char currentScope[256] = "global";
FILE *source = NULL;

int main(int argc, char **argv) {
	int parseStatus;

	if (argc < 2) {
		fprintf(stderr, "Uso: %s <arquivo_entrada>\n", argv[0]);
		return 1;
	}

	source = fopen(argv[1], "r");
	if (source == NULL) {
		fprintf(stderr, "Erro ao abrir arquivo de entrada: '%s'\n", argv[1]);
		return 1;
	}

	yyin = source;
	lineNo = 1;

	parseStatus = yyparse();

	fclose(source);
	source = NULL;

	if (parseStatus != 0) {
		fprintf(stderr, "Falha na compilacao: erros sintaticos encontrados.\n");
		return 1;
	}

	printf("Analise concluida com sucesso.\n");

	if (AST != NULL) {
		printTreeGraphviz(AST);
	}

	return 0;
}
