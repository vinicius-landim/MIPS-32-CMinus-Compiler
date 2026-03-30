#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#include "util.h"
#include "analyze.h" 

extern FILE *yyin;
extern int yyparse(void);
extern TreeNode *AST;

int lineNo = 1;
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

    //análise léxica e sintática
    parseStatus = yyparse();

    fclose(source);
    source = NULL;

    if (parseStatus != 0)
        return 1;

    if (AST != NULL) {
		
		//análise semântica
        buildSymtab(AST);
        // typeCheck(AST);
        printTreeGraphviz(AST);
        // printSymTab(stdout); 
    }

    return 0;
}