#include "globals.h"
#include "symtab.h"
#include "util.h"

static int location = 0; 
static int blockCounter = 0;

// Tratamento de declarações e escopos
static void insertNode(TreeNode *t) {
    char newScopeName[256]; //Buffer para nomes de escopo de blocos
    if (currentScope != NULL) {
        t->scope = copyString(currentScope->name); 
    }

    switch (t->nodeKind) {
        case StmtK:
            switch (t->kind.stmt) {
                case FunctDeclK:
                    if(st_lookup_scope(t->attr.name) != NULL){
                        fprintf(stderr, "ERRO SEMÂNTICO: Função '%s' já declarada - LINHA: %d", t->attr.name, t->lineNo);
                    } else {
                        st_insert(t->attr.name, t->type, SYMB_FUNC, t->lineNo, location++);
                    }
                    pushScope(t->attr.name);
                    blockCounter = 0;
                    break;
                
                case CompoundK:
                    blockCounter++;
                    sprintf(newScopeName, "%s:block%d", currentScope->name, blockCounter);
                    pushScope(newScopeName);
                    break;

                default:
                    break;
            }
            break;

        case ExpK:
            switch (t->kind.exp) {
                case VarDeclK: {
                    if (t->type == Void) {
                        printf("ERRO SEMÂNTICO: Variável '%s' não pode ser do tipo 'void'\n - LINHA: %d\n", t->attr.name, t->lineNo);
                    } else if (st_lookup_scope(t->attr.name) != NULL) {
                        printf("ERRO SEMÂNTICO: Variável '%s' já declarada. - LINHA: %d\n", t->attr.name, t->lineNo);
                    } else {
                        st_insert(t->attr.name, t->type, SYMB_VAR, t->lineNo, location++);
                    }
                    break;
                }
                case ArrDeclK: {
                    if (t->type == Void) {
                        printf("ERRO SEMÂNTICO: Variável '%s' não pode ser do tipo 'void'\n - LINHA: %d\n", t->attr.name, t->lineNo);
                    } else if (st_lookup_scope(t->attr.name) != NULL) {
                        printf("ERRO SEMÂNTICO: Variável '%s' já declarada. - LINHA: %d\n", t->attr.name, t->lineNo);
                    } else {
                        st_insert(t->attr.name, t->type, SYMB_ARR, t->lineNo, location++);
                    }
                    break;
                }
                case ParamK: {
                    //ignora o "void" de int main(void)
                    if (t->type != Void) {
                        st_insert(t->attr.name, t->type, SYMB_VAR, t->lineNo, location++);
                    }
                    break;
                }
                case ParamArrK: {
                    st_insert(t->attr.name, t->type,SYMB_ARR, t->lineNo, location++);
                    break;
                }
                default:
                    break;
            }
            break;
    }
}

//retorno ao escopo pai do nó de FunctDecl e CompundK inserido 
static void leaveScope(TreeNode *t) {
    if (t->nodeKind == StmtK) {
        if (t->kind.stmt == FunctDeclK || t->kind.stmt == CompoundK)
            popScope();
    }
}

//Percurso pré-ordem
static void buildSymtabRec(TreeNode *t) {
    if (t != NULL) {
        insertNode(t);

        for (int i = 0; i < MAXCHILDREN; i++) {
            buildSymtabRec(t->child[i]);
        }
        leaveScope(t);
        buildSymtabRec(t->sibling); // Vai para o irmão
    }
}
void buildSymtab(TreeNode *AST) {
    pushScope("global");
    
    st_insert("input", Integer, SYMB_FUNC, 0, location++);
    st_insert("output", Void, SYMB_FUNC, 0, location++);

    buildSymtabRec(AST); 
}