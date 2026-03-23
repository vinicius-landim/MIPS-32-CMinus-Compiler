%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include "util.h"

extern FILE *yyin;
extern int linha;
extern int yylex(void); // Chamada do scanner
extern char *yytext;

void yyerror(const char *s);

TreeNode *AST = NULL;
%}

%union {
    TreeNode *tree;
    int val;
    char *name;
    ExpType type;
}

//Tokens Valorados
%token<val> NUM
%token<name> ID

//Palavras reservadas
%token IF ELSE INT RETURN VOID WHILE

//Símbolos Especiais
%token SOMA SUB MUL DIV
%token MENOR MENOR_IGUAL MAIOR MAIOR_IGUAL IGUAL_IGUAL DIFERENTE
%token ATRIBUICAO PONTO_VIRGULA VIRGULA
%token ABRE_PARENTESE FECHA_PARENTESE
%token ABRE_COLCHETE FECHA_COLCHETE
%token ABRE_CHAVE FECHA_CHAVE

/* %token ERROR */

// Declaração de tipos para não-terminais (tipagem de retorno $$)
%type <val> relacional soma mult
%type <type> tipo_especificador
%type <tree> programa declaracao_lista declaracao var_declaracao
%type <tree> fun_declaracao params param_lista param
%type <tree> composto_decl local_declaracoes statement_lista statement
%type <tree> expressao_decl selecao_decl iteracao_decl retorno_decl
%type <tree> expressao var simples_expressao soma_expressao termo fator
%type <tree> ativacao args arg_lista

%right ELSE // Solução Dangling Else

%%

/* Gramática (LOUDEN, 2004, p.494) 
1. programa -> declaração-lista
2. declaração-lista -> declaração-lista declaração | declaração
3. declaração -> var-declaração | fun-declaração
4. var-declaração -> tipo-especificador ID ; | tipo-especificador ID [ NUM ] ;
5. tipo-especificador -> int | void
6. fun-declaração -> tipo-especificador ID( params )composto-decl
7. params -> param-lista | void
8. param-lista -> param-lista,param | param
9. param -> tipo-especificador ID | tipo-especificador ID []
10. composto-decl -> { local-declarações statement-lista }
11. local-declarações -> local-declarações var-declaração | vazio
12. statement-lista -> statement-lista statement | vazio
13. statement -> expressão-decl | composto-decl | seleção-decl  | iteração-decl | retorno-decl
14. expressão-decl -> expressão ; | ;
15. seleção-decl ->if ( expressão ) statement  | if ( expressão ) statement else statement
16. iteração-decl -> while ( expressão ) statement
17. retorno-decl -> return ; | return expressão ;
18. expressão -> var = expressão | simples-expressão
19. var -> ID | ID [ expressão ]
20. simples-expressão -> soma-expressão relacional soma-expressão  | soma-expressão
21. relacional -> <= | < | > | >= | == | !=
22. soma-expressão -> soma-expressão soma termo | termo
23. soma -> + | -
24. termo -> termo mult fator | fator
25. mult -> * | /
26. fator -> ( expressão ) | var | ativação | NUM
27. ativação -> ID ( args )
28. args -> arg-lista | vazio
29. arg-lista -> arg-lista,expressão | expressão
*/

//1. programa -> declaração-lista
programa: 
      declaracao_lista { 
            AST = $1; //raíz da AST
      }
;

//2. declaração-lista -> declaração-lista declaração | declaração
declaracao_lista: 
      declaracao_lista declaracao {
            TreeNode *t = $1;
            // Lista encadeada de declarações no escopo
            if (t != NULL){
                  while (t->sibling != NULL)
                        t = t->sibling;
                  t->sibling = $2;
                  $$ = $1;
            }
            else {
                  // Caso for uma primeira declaração, será um novo nó com o item de 'declaracao'
                  $$ = $2;
            }
      }
    | declaracao {
            // Caso for uma primeira declaração, será um novo nó com o item de 'declaracao'
            $$ = $1;
     }
;

//3. declaração -> var-declaração | fun-declaração
declaracao: 
      var_declaracao {$$ = $1;}
    | fun_declaracao {$$ = $1};
;
//4. var-declaração -> tipo-especificador ID ; | tipo-especificador ID [ NUM ] ;
var_declaracao: 
      tipo_especificador ID PONTO_VIRGULA {
            //Criação do nó da variável
            $$ = newExpNode(VarDeclK);
            $$->type = $1;
            $$->attr.name = copyString($2);
      }
    | tipo_especificador ID ABRE_COLCHETE NUM FECHA_COLCHETE PONTO_VIRGULA {
            //Criação do nó do vetor
            $$ = newExpNode(ArrDeclK);
            $$->type = $1;
            $$->attr.name = copyString($2);
            //Tamanho do vetor salvo como filho da variável
            $$->child[0] = newExpNode(ConstK);
            $$->child[0]->attr.val = $4;
    }
;
//5. tipo-especificador -> int | void
tipo_especificador: 
      INT  {$$ = Integer;}
    | VOID {$$ = Void;}
;
//6. fun-declaração -> tipo-especificador ID ( params ) composto-decl
fun_declaracao: 
      tipo_especificador ID ABRE_PARENTESE params FECHA_PARENTESE composto_decl {
            //Nó raíz da função
            $$ = newExpNode(FunctK);
            $$->type = $1
            $$->attr.name = copyString($2);
            //Nós filhos: Lista de parâmetros (Esq) e o Corpo da função (Dir)
            $$->child[0] = $4;
            $$->child[1] = $6;
      }
;
//7. params -> param-lista | void 
params: 
      param_lista {$$ = $1;}
    | VOID {$$ = NULL;} //Função sem parâmetros (i.e: int main(void) )
;
//8. param-lista -> param-lista , param | param 
param_lista: 
      param_lista VIRGULA param {
            TreeNode *t = $1;
            if (t != NULL){
                  while (t->sibling != NULL)
                        t = t->sibling;
            } else {
                  $$ = $3;
            }
      }
    | param {$$ = $1;}
;
//9. param -> tipo-especificador ID | tipo-especificador ID [ ] 
param: 
      tipo_especificador ID {
            $$ = newExpNode(ParamK);
            $$->type = $1;
            $$->attr.name = copyString($2);
       }
    | tipo_especificador ID ABRE_COLCHETE FECHA_COLCHETE {
            $$ = newExpNode(ParamK);
            $$->type = $1;
            $$->attr.name = copyString($2);
            //Criação de um filho "vazio" para diferenciar parâmetro como função
            $$->child[0] = newExpNode(ConstK);
            $$->child[0]->attr.val = 0;
    }
;

//10. composto-decl -> { local-declarações statement-lista } 
// Bloco de código do escopo
composto_decl: 
      ABRE_CHAVE local_declaracoes statement_lista FECHA_CHAVE {
            // Nó que define o escopo
            $$ = newStmtNode(CompoundK);
            $$->child[0] = $2; //Esq: lista de declarações
            $$->child[1] = $3; //Dir: lista de instruções (statements)
      }
;

//11. local-declarações -> local-declarações var-declaração | vazio 
local_declaracoes: 
      local_declaracoes var_declaracao {
            TreeNode *t = $1;
            if (t!=NULL){
                  while (t->siblings != NULL)
                        t = t->sibling;
                  t->sibling = $2;
                  $$ = $1;
            } else {
                  $$ = $2;
            }
      }
    | /* Vazio */ {$$ = NULL;}
;

//12. statement-lista -> statement-lista statement | vazio 
statement_lista: 
      statement_lista statement {
            TreeNode *t = $1;
            if (t != NULL){
                  while(t->sibling != NULL)
                        t = t->sibling;
                  t->sibling = $2;
                  $$ = $1;
            } else {
                  $$ = $2;
            }
      }
    | /* vazio */ {$$ = NULL};
;

//13. statement -> expressão-decl | composto-decl | seleção-decl | iteração-decl | retorno-decl 
statement: 
      expressao_decl {$$ = $1;}
    | composto_decl {$$ = $1;}
    | selecao_decl {$$ = $1;}
    | iteracao_decl {$$ = $1;}
    | retorno_decl {$$ = $1;}
;

//14. expressão-decl -> expressão ; | ; 
expressao_decl: 
      expressao PONTO_VIRGULA {$$ = $1;} //A subárvore foi criada em 'expressao'
    | PONTO_VIRGULA {$$ = NULL};
;

//15. seleção-decl -> if ( expressão ) statement | if ( expressão ) statement else statement 
selecao_decl: 
      IF ABRE_PARENTESE expressao FECHA_PARENTESE statement {
            $$ = newStmtNode(IfK); //Pai: IF
            $$->child[0] = $3; //Filho 1: expressão
            $$->child[1] = $5; //Filho 2: instruções
      }
    | IF ABRE_PARENTESE expressao FECHA_PARENTESE statement ELSE statement {
            $$ = newStmtNode(IfK); //Pai: IF
            $$->child[0] = $3; //Filho 1: expressão condicional
            $$->child[1] = $5; //Filho 2: instruções then
            $$->child[2] = $7; //Filho 3: instruções else
    }
;

//16. iteração-decl -> while ( expressão ) statement 
iteracao_decl: 
      WHILE ABRE_PARENTESE expressao FECHA_PARENTESE statement {
            $$ = newStmtNode(WhileK);
            $$->child[0] = $3; //Filho 1: expressão condicional
            $$->child[1] = $5; //Filho 2: instruções
      }
;

//17. retorno-decl -> return ; | return expressão ; 
retorno_decl: 
      RETURN PONTO_VIRGULA {
            $$ = newStmtNode(ReturnK);
            // Return; => Filhos nulos
      }
    | RETURN expressao PONTO_VIRGULA {
            $$ = newStmtNode(ReturnK);
            $$->child[0] = $2;
    }
;

//18. expressão -> var = expressão | simples-expressão 
expressao: 
      var ATRIBUICAO expressao {
            $$ = newExpNode(AssignK);
            $$->child[0] = $1;
            $$->child[1] = $3;
      }
    | simples_expressao {$$ = $1;}
;

//19. var -> ID | ID [ expressão ] 
var: 
      ID {
            //Uso de variável já declarada
            $$ = newExpNode(IdK);
            $$->attr.name = copyString($1);
      }
    | ID ABRE_COLCHETE expressao FECHA_COLCHETE {
            $$ = newExpNode(IdK);
            $$->attr.name = copyString($1);
            $$->child[0] = $3; //índice dado pela expressão

    }
;

//20. simples-expressão -> soma-expressão relacional soma-expressão | soma-expressão 
simples_expressao: 
      soma_expressao relacional soma_expressao {
            //Operação lógica/relacional (i.e: a < b, x==5)
            $$ = newExpNode(OpK);
            $$->attr.op = $2;
            $$->child[0] = $1;
            $$->child[1] = $3;
      }
    | soma_expressao {$$ = $1;}
;

//21. relacional -> <= | < | > | >= | == | != 
relacional: 
      MENOR_IGUAL {$$ = MENOR_IGUAL;}
    | MENOR {$$ = MENOR;}
    | MAIOR {$$ = MAIOR;}
    | MAIOR_IGUAL {$$ = MAIOR_IGUAL;}
    | IGUAL_IGUAL {$$ = IGUAL_IGUAL;}
    | DIFERENTE {$$ = DIFERENTE;}
;

//22. soma-expressão -> soma-expressão soma termo | termo 
soma_expressao: 
      soma_expressao soma termo {
            //Operação de adição/subtração
            $$ = newExpNode(OpK); //soma -> + | -
            $$->attr.op = $2;
            /* Garantia de Precedencia e Associatividade:
             * child[0] recebe $1 (recursivo à esquerda), forçando contas como 10-5-2 a virarem (10-5)-2.
             * child[1] recebe $3 (termo travado), garantindo que multiplicacoes fiquem
             * mais profundas na arvore e sejam resolvidas ANTES desta soma. */
            $$->child[0] = $1;
            $$->child[1] = $3;
      }
    | termo {$$ = $1};
;

//23. soma -> + | - 
soma: 
      SOMA {$$ = SOMA;}
    | SUB {$$ = SUB;}
;

//24. termo -> termo mult fator | fator 
termo: 
      termo mult fator {
            $$ = newExpNode(OpK);
            $$->attr.op = $2;
            $$->child[0] = $1;
            $$->child[1] = $3;
      }
    | fator {$$ = $1;}
;

//25. mult -> * | / 
mult: 
      MUL {$$ = MUL;}
    | DIV {$$ = DIV;}
;

//26. fator -> ( expressão ) | var | ativação | NUM 
fator: 
      ABRE_PARENTESE expressao FECHA_PARENTESE {
            $$ = $2; //Parênteses força o Bison à priorizar a conta
      }
    | var {$$ = $1;}
    | ativacao {$$ = $1;}
    | NUM {
            $$ = newExpNode(ConstK);
            $$->attr.val = $1;
    }
;

//27. ativação -> ID ( args ) 
ativacao: 
      ID ABRE_PARENTESE args FECHA_PARENTESE {
            $$ = newExpNode(CallK);
            $$->attr.name = copyString($1);
            $$->child[0] = $3;
      }
;

//28. args -> arg-lista | vazio 
args: 
      arg_lista {$$ = $1;}
    | /* vazio */ {$$ = NULL;}
;

//29. arg-lista -> arg-lista , expressão | expressão 
arg_lista: 
      arg_lista VIRGULA expressao {
            //Lista de argumentos para ativação
            TreeNode *t = $1;
            if (t!=NULL){
                  while(t->sibling != NULL)
                        t = t->sibling;
                  t->sibling = $3;
                  $$ = $1;
            } else {
                  $$ = $3;
            }
      }
    | expressao {$$ = $1;}
;

%%

void yyerror(const char *s) {
    fprintf(stderr, "ERRO SINTATICO: token inesperado '%s' - LINHA: %d\n", yytext, linha);
}