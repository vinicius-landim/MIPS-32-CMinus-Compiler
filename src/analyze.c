#include "globals.h"
#include "symtab.h"
#include "util.h"

static int location = 0; 
static int blockCounter = 0;
static int hasMain = 0;

static ExpType currentFuncType = Void; 
static int hasReturn = 0; 
static char* currentFuncName = NULL;
static Symbol currentFuncSymbol = NULL;

//Primeiro procedimento: Tratamento de declaracões e escopos (PRÉ-ORDEM)
// Erros Semânticos: Valida main (falta e ordem), duplicatas (vars/funcs/params), void em variáveis e uso sem declaração;
static void insertNode(TreeNode *t) {
    char newScopeName[256]; //Buffer para nomes de escopo de blocos
    if(currentScope != NULL) {
        t->scope = copyString(currentScope->name); 
    }

    if(hasMain && (currentScope == globalScope)) {
        //após a declaracão da main, não é permitido haver novas declaracões. (ausência de protótipos na linguagem C-)
        if((t->nodeKind == StmtK && t->kind.stmt == FunctDeclK) || (t->nodeKind == ExpK && (t->kind.exp == VarDeclK || t->kind.exp == ArrDeclK))) {
            fprintf(stderr, "ERRO SEMANTICO: Declaracao de '%s' invalida. A funcao 'main' deve ser a ultima declaracao do arquivo - LINHA: %d\n", t->attr.name, t->lineNo);
        }
    }

    switch (t->nodeKind) {
        case StmtK:
            switch (t->kind.stmt) {
                case FunctDeclK: {
                    if(st_lookup_scope(t->attr.name) != NULL){
                        fprintf(stderr, "ERRO SEMANTICO: Funcao '%s' ja declarada - LINHA: %d\n", t->attr.name, t->lineNo);
                        currentFuncSymbol = st_lookup_scope(t->attr.name); //fallback
                    } else {
                        currentFuncSymbol = st_insert(t->attr.name, t->type, SYMB_FUNC, t->lineNo, location++);
                        if(strcmp(t->attr.name, "main") == 0)
                            hasMain = 1;
                    }
                    pushScope(t->attr.name);
                    blockCounter = 0;
                    break;
                }

                case CompoundK: {
                    blockCounter++;
                    sprintf(newScopeName, "%s:block%d", currentScope->name, blockCounter);
                    pushScope(newScopeName);
                    break;
                }

                default: break;
            }
            break;

        case ExpK:
            switch (t->kind.exp) {
                case VarDeclK: {
                    if(t->type == Void) {
                        printf("ERRO SEMANTICO: Variavel '%s' nao pode ser do tipo 'void'\n - LINHA: %d\n", t->attr.name, t->lineNo);
                    } else if(st_lookup_scope(t->attr.name) != NULL) {
                        printf("ERRO SEMANTICO: Variavel '%s' ja declarada neste escopo. - LINHA: %d\n", t->attr.name, t->lineNo);
                    } else {
                        st_insert(t->attr.name, t->type, SYMB_VAR, t->lineNo, location++);
                    }
                    break;
                }
                case ArrDeclK: {
                    if(t->type == Void) {
                        printf("ERRO SEMANTICO: Variavel '%s' nao pode ser do tipo 'void'\n - LINHA: %d\n", t->attr.name, t->lineNo);
                    } else if(st_lookup_scope(t->attr.name) != NULL) {
                        printf("ERRO SEMANTICO: Variavel '%s' ja declarada neste escopo. - LINHA: %d\n", t->attr.name, t->lineNo);
                    } else {
                        st_insert(t->attr.name, t->type, SYMB_ARR, t->lineNo, location++);
                    }
                    break;
                }
                case ParamK: {
                    if(t->type == Void) {
                        // t->attr.name == NULL é o caso do void isolado, como em int main(void)
                        if(t->attr.name != NULL) {
                            fprintf(stderr, "ERRO SEMANTICO: Parametro '%s' nao pode ser do tipo 'void' - LINHA: %d\n", t->attr.name, t->lineNo);
                            //fallback
                            st_insert(t->attr.name, Integer, SYMB_VAR, t->lineNo, location++);
                            st_add_param(currentFuncSymbol, Integer);
                        }
                    } 
                    else if(st_lookup_scope(t->attr.name) != NULL) {
                        fprintf(stderr, "ERRO SEMANTICO: Parametro '%s' ja declarado nesta funcao - LINHA: %d\n", t->attr.name, t->lineNo);
                    } else {
                        st_insert(t->attr.name, t->type, SYMB_VAR, t->lineNo, location++);
                        st_add_param(currentFuncSymbol, t->type);

                    }
                    break;
                }
                case ParamArrK: {
                    if(t->type == Void) {
                        fprintf(stderr, "ERRO SEMANTICO: Parametro de vetor '%s' nao pode ser do tipo 'void' - LINHA: %d\n", t->attr.name, t->lineNo);
                        //fallback
                        st_insert(t->attr.name, Integer, SYMB_ARR, t->lineNo, location++);
                        st_add_param(currentFuncSymbol, Integer);
                    } else if(st_lookup_scope(t->attr.name) != NULL) {
                        fprintf(stderr, "ERRO SEMANTICO: Parametro '%s' ja declarado nesta funcao - LINHA: %d\n", t->attr.name, t->lineNo);
                    } else {
                        st_insert(t->attr.name, t->type, SYMB_ARR, t->lineNo, location++);
                        st_add_param(currentFuncSymbol, t->type);
                    }
                    break;
                }
                case VarK: {
                    Symbol s_node = st_lookup(t->attr.name);
                    if(s_node == NULL) {
                        fprintf(stderr,"ERRO SEMANTICO: Variavel '%s' nao declarada - LINHA: %d\n",t->attr.name, t->lineNo);
                        t->type = Integer; // fallback
                    } else {
                        t->type = s_node->type;
                        st_add_line(s_node, t->lineNo);
                    }
                    break;
                }
                case ArrK: {
                    Symbol s_node = st_lookup(t->attr.name);
                    if(s_node == NULL) {
                        fprintf(stderr, "ERRO SEMANTICO: Variavel '%s' nao declarada - LINHA: %d\n", t->attr.name, t->lineNo);
                    } else {
                        if(s_node->kind != SYMB_ARR)
                            fprintf(stderr,"ERRO SEMANTICO: Variavel '%s' nao é um vetor - LINHA: %d\n",t->attr.name, t->lineNo);

                        t->type = s_node->type;
                        st_add_line(s_node, t->lineNo);
                    }
                    break;
                }
                case CallK: {
                    Symbol s_node = st_lookup_global(t->attr.name);

                    if(s_node == NULL) {
                        fprintf(stderr,"ERRO SEMANTICO: Funcao '%s' nao declarada - LINHA: %d\n",t->attr.name, t->lineNo);
                        t->type = Integer; //fallback
                    } else {
                        if(s_node->kind != SYMB_FUNC)
                            fprintf(stderr,"ERRO SEMANTICO: '%s' nao é uma funcao - LINHA: %d\n",t->attr.name, t->lineNo);

                        t->type = s_node->type;
                        st_add_line(s_node, t->lineNo);
                    }
                    break;
                }

                default: break;
            }
            break;

        default: break;
    }
}

//topo da pilha atualizado para esconder escopos que nao podem ser acessados 
static void leaveScope(TreeNode *t) {
    if(t->nodeKind == StmtK) {
        if(t->kind.stmt == FunctDeclK || t->kind.stmt == CompoundK)
            popScope();
    }
}

//percurso pré-ordem (Pai -> Filhos -> Irmao)
static void buildSymtabRec(TreeNode *t) {
    if(t != NULL) {
        insertNode(t);

        for(int i = 0; i < MAXCHILDREN; i++) {
            buildSymtabRec(t->child[i]);
        }
        leaveScope(t);
        buildSymtabRec(t->sibling); // Vai para o irmao
    }
}

void buildSymtab(TreeNode *AST) {
    globalScope = pushScope("global");
    
    st_insert("input", Integer, SYMB_FUNC, 0, location++);
    Symbol out_node = st_insert("output", Void, SYMB_FUNC, 0, location++);
    st_add_param(out_node, Integer);

    buildSymtabRec(AST); 

    if(hasMain == 0)
        fprintf(stderr, "ERRO SEMANTICO: O programa nao possui a funcao 'main'.\n");
}

//Segundo procedimento: Verificacao de tipos (PÓS-ORDEM)
//Erros semânticos: checagem de tipos (ops/indexes(arr)/condições), compatibilidade em atribuições/chamadas(args) e valida regras de return.
static void checkNode(TreeNode *t) {
    switch (t->nodeKind) {
        case ExpK:
            switch (t->kind.exp) {
                case OpK: {
                    if((t->child[0]->type != Integer || t->child[1]->type != Integer))
                        fprintf(stderr, "ERRO SEMANTICO: Operandos de '%s' devem ser do tipo 'int' - LINHA: %d\n",  opStr(t->attr.op), t->lineNo);
                    
                        t->type = Integer; // resultado int
                    break;
                }
                case ConstK:{
                    t->type = Integer;
                    break;
                }
                case ArrK: {
                    if(t->child[0]->type != Integer)
                        fprintf(stderr,"ERRO SEMANTICO: Índice do vetor '%s' deve ser do tipo 'int' - LINHA: %d\n",t->attr.name, t->lineNo);
                    break;
                }
                case AssignK: {
                    if(t->child[0]->type != Integer || t->child[1]->type != Integer) 
                        fprintf(stderr,"ERRO SEMANTICO: Tipos incompatíveis na atribuicao - LINHA: %d\n",t->lineNo);
        
                    t->type = t->child[0]->type;
                    break;
                }
                case CallK: {
                    //verificação de parâmetros
                    Symbol s_node = st_lookup(t->attr.name);
                    if(s_node != NULL && s_node->kind == SYMB_FUNC) {
                        TreeNode *arg = t->child[0];
                        ParamList param = s_node->params;
                        int countParams = 1;

                        while (arg != NULL && param != NULL){
                            if(arg->type != param->type)
                                fprintf(stderr, "ERRO SEMANTICO: Tipo incompatível no argumento %d da função '%s' - LINHA: %d\n", countParams, s_node->name, t->lineNo);

                            arg = arg->sibling;
                            param = param->next;
                            countParams++;
                        }
                        if(arg != NULL || param != NULL) 
                            fprintf(stderr, "ERRO SEMANTICO: Total de argumentos incorreto para função '%s' - LINHA: %d\n", s_node->name, t->lineNo);
                    }
                    break;
                }
                default: break;
            }
            break;

        case StmtK:
            switch (t->kind.stmt) {
                case IfK: {
                    if(t->child[0]->type != Integer)
                        fprintf(stderr,"ERRO SEMANTICO: A condição do 'if' deve ser do tipo 'int' - LINHA: %d\n",t->lineNo);
                    break;
                }

                case WhileK: {
                    if(t->child[0]->type != Integer)
                        fprintf(stderr,"ERRO SEMANTICO: A condição do 'while' deve ser do tipo 'int' - LINHA: %d\n",t->lineNo);
                    break;
                }

                case ReturnK: {
                    if(currentFuncType == Void) {
                        if(t->child[0] != NULL) {
                            fprintf(stderr, "ERRO SEMANTICO: Funcao 'void' nao deve retornar um valor - LINHA: %d\n", t->lineNo);
                        }
                    } else {
                        //Louden (p.495, 2004) funções int devem retornar valores
                        hasReturn = 1; // registra-se que a função tem pelo menos um retorno

                        if(t->child[0] == NULL) {
                            fprintf(stderr, "ERRO SEMANTICO: Retorno vazio em funcao do tipo 'int' - LINHA: %d\n", t->lineNo);
                        } else if(t->child[0]->type != Integer) {
                            fprintf(stderr, "ERRO SEMANTICO: O valor retornado deve ser do tipo 'int' - LINHA: %d\n", t->lineNo);
                        }
                    }
                    break;
                }

                default: break;
            }
            break;

        default: break;
    }
}

//percurso Pós-ordem (Filhos -> Pai -> Irmao)
static void typeCheckRec(TreeNode *t) {
    if(t != NULL) {
        // ao encontrar uma declaração de função, guarda o contexto
        if(t->nodeKind == StmtK && t->kind.stmt == FunctDeclK) {
            currentFuncType = t->type;
            currentFuncName = t->attr.name;
            hasReturn = 0; //reinicar total de returns
        }

        for(int i = 0; i < MAXCHILDREN; i++) {
            typeCheckRec(t->child[i]);
        }

        checkNode(t);

        //após processar todos os filhos, verifica se uma função int cumpriu o requisito de return
        if(t->nodeKind == StmtK && t->kind.stmt == FunctDeclK) {
            if(currentFuncType == Integer && hasReturn == 0) {
                fprintf(stderr, "ERRO SEMANTICO: A funcao '%s' eh do tipo 'int' e deve possuir um retorno - LINHA: %d\n", t->attr.name, t->lineNo);
            }
        }

        typeCheckRec(t->sibling);
    }
}

void typeCheck(TreeNode *AST) {
    typeCheckRec(AST);
}