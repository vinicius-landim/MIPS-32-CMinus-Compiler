#include "globals.h"
#include "symtab.h"

static int location = 0; //contador para localizações em memória de variáveis ?????

static void insertNode(TreeNode *t){
    switch(t->nodeKind){
        case StmtK:
            switch(t->kind.stmt){
                case IfK: //TODO
                case WhileK: //TODO
                case ReadK:
                case WriteK: //TODO: Necessário?
                case CompoundK: //TODO
                case FunctDeclK: //TODO: Verificar existência no escopo
                case ReturnK: //TODO: Retorno deve ser do mesmo tipo
                default: break;
            }
        
        case ExpK:
            switch(t->kind.exp){
                case OpK: //TODO
                case ConstK: //TODO
                case IdK:
                    if(!st_lookup(t->attr.name)){
                        fprintf(stderr, "ERRO Semântico: a variável %s não foi declarada", t->attr.name);
                        break;
                    }
                case VarDeclK: //TODO: Verificar redeclações de variáveis no mesmo escopo
                    //Inserir na tabela de símbolos:
                    if(!st_lookup(t->attr.name)){
                        if(t->type == Void){
                            fprintf(stderr, "ERRO Semântico: Declarações de variáveis não podem ser do tipo \"void\"");
                            break;
                        }
                        st_insert(t->attr.name, t->lineNo, location++);
                    } else{
                        if(t->type == Void){
                            fprintf(stderr, "ERRO Semântico: Declarações de variáveis não podem ser do tipo \"void\"");
                            break;
                        }
                        st_insert(t->attr.name, t->lineNo, 0); //já presente na tabela (TODO: Verificar o porque de location = 0)
                    }

                case ArrDeclK: //TODO: Verificar redeclações de variáveis no mesmo escopo
                    if(!st_lookup(t->attr.name)){
                        st_insert(t->attr.name, t->lineNo, location++);
                        fprintf(stderr, "ERRO Semântico: Declarações de vetores não podem ser do tipo \"void\"");
                            break;
                    } else {
                        if(t->type == Void){
                            fprintf(stderr, "ERRO Semântico: Declarações de variáveis não podem ser do tipo \"void\"");
                            break;
                        }
                        st_insert(t->attr.name, t->lineNo, 0);
                    } 
                case ParamK:
                case AssignK: //TODO
                case CallK: //TODO: Verificar existência de main() no escopo e incluir input() e output()
                    if(!st_lookup(t->attr.name)){
                        fprintf("ERRO Semântico: a função %s não foi declarada", t->attr.name);
                        break;
                    }
                default: break;
            }
    }
}
