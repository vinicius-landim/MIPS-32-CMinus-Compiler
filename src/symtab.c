#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"
#include "util.h"

Scope currentScope = NULL;

//Lista com número da linha de todas as ocorrências de uma variável
typedef struct LineListNode{
    int lineNo;
    struct LineListNode *next; // listar todas as ocorrências de uma mesma variável
} *LineList;

void pushScope(char *name){
    Scope newScope = (Scope)malloc(sizeof(struct ScopeNode));
    newScope->name = copyString(name);
    newScope->h_symbols = NULL;
    newScope->parent = currentScope;
    currentScope = newScope;
}

void popScope(){
    if (currentScope != NULL){
        // Scope temp = currentScope;
        currentScope = currentScope->parent;
    }
}

void st_insert(char *name, ExpType type, SymbolKind kind, int lineNo, int loc){
    Symbol s_node = currentScope->h_symbols;
    while(s_node != NULL && (strcmp(name, s_node->name) != 0))
        s_node = s_node->next;

    if (s_node == NULL){
        Symbol newSymble = (Symbol)malloc(sizeof(struct SymbolNode));
        newSymble->name = name;
        newSymble->type = type;
        newSymble->kind = kind;
        newSymble->memloc = loc;
        newSymble->lines = (LineList)malloc(sizeof(struct LineListNode));
        newSymble->lines->lineNo = lineNo;
        newSymble->lines->next = NULL;

        newSymble->next = currentScope->h_symbols;
        currentScope->h_symbols = newSymble;
    } else {
        LineList line_node = s_node->lines;
        while (line_node->next !=  NULL)
            line_node = line_node->next;
        line_node->next = (LineList)malloc(sizeof(struct LineListNode));
        line_node->next->lineNo = lineNo;
        line_node->next->next = NULL;
    }
}

Symbol st_lookup(char *name){
    Scope scp_node = currentScope;
    while (scp_node != NULL){
        Symbol s_node = scp_node->h_symbols;
        while(s_node != NULL){
            if(strcmp(name, s_node->name) == 0)
                return s_node;
            s_node = s_node->next;
        }
        scp_node = scp_node->parent;
    }
    return NULL;
}

Symbol st_lookup_scope(char *name){
    if(currentScope == NULL)
        return NULL;
    Symbol s_node = currentScope->h_symbols;
    while (s_node != NULL){
        if(strcmp(name, s_node->name) == 0)
            return s_node;
        s_node = s_node->next;
    }
    return NULL;
}