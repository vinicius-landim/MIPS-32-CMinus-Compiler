#include "globals.h"
#include "symtab.h"

static int location = 0; // ??????

static void insertNode(TreeNode *t){
    switch(t->nodeKind){
        case StmtK:
            switch(t->kind.stmt){
                case IfK: //TODO
                case WhileK: //TODO
                case ReadK:
                case WriteK: //TODO
                case CompoundK: //TODO
                case FunctDeclK: //TODO
                case ReturnK: //TODO
                default: break;
            }
        
        case ExpK:
            switch(t->kind.exp){
                case OpK: //TODO
                case ConstK: //TODO
                case IdK: //TODO
                case VarDeclK:
                    //Inserir na tabela de símbolos:
                    if(!st_lookup(t->attr.name))
                        st_insert(t->attr.name, t->lineNo, location++);
                    else
                        break; //já presente na tabela
                case ArrDeclK: //TODO
                case ParamK:
                case AssignK: //TODO
                case CallK: //TODO
                default: break;
            }
    }
}

void buildSymbTab(TreeNode *t){
    if (t != NULL) {
        insertNode(t); 
        for (int i = 0; i < MAXCHILDREN; i++) {
            buildSymtab(t->child[i]);
        }
        buildSymtab(t->sibling);
    }
}

void typeCheck(TreeNode *t) {
    if (t != NULL) {
        for (int i = 0; i < MAXCHILDREN; i++) {
            typeCheck(t->child[i]);
        }
        checkNode(t); 
        typeCheck(t->sibling);
    }
}