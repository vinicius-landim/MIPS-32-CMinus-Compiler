#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"
#include "util.h"

Scope currentScope = NULL;
Scope globalScope = NULL;
Scope scopeHistory = NULL;

//Lista com número da linha de todas as ocorrências de uma variável
typedef struct LineListNode{
    int lineNo;
    struct LineListNode *next; // listar todas as ocorrências de uma mesma variável
} *LineList;

Scope pushScope(char *name){
    Scope newScope = (Scope)malloc(sizeof(struct ScopeNode));
    newScope->name = copyString(name);
    newScope->h_symbols = NULL;
    newScope->parent = currentScope;
    currentScope = newScope;

    //push histórico para impressão: inserção ao final da lista
    newScope->next = NULL;
    if (scopeHistory == NULL)
        scopeHistory = newScope;
    else {
        //atualizar next do último nó
        Scope temp = scopeHistory;
        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newScope;
    }
    return newScope;
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

Symbol st_lookup_global(char *name){
    if(globalScope == NULL)
        return NULL;
    Symbol s_node = globalScope->h_symbols;
    while(s_node != NULL){
        if(strcmp(name, s_node->name) == 0)
            return s_node;
        s_node = s_node->next;
    }
    return NULL;
}

//impressão
static const char* typeToString(ExpType type) {
    switch(type) {
        case Void: return "void";
        case Integer: return "int";
        default: return "unknown";
    }
}

static const char* kindToString(SymbolKind kind) {
    switch(kind) {
        case SYMB_VAR: return "Variavel";
        case SYMB_ARR: return "Vetor";
        case SYMB_FUNC: return "Funcao";
        default: return "unknown";
    }
}

void printSymTab(FILE * listing) {
    fprintf(listing, "Nome do Simbolo   |  Tipo      |  Classificacao  |  Escopo          |  Loc  |  Linhas\n");
    fprintf(listing, "-----------------------------------------------------------------------------------------\n");

    Scope scp = scopeHistory; 
    while (scp != NULL) {
        Symbol sym = scp->h_symbols;
        
        //barre todas as variáveis/funções dentro do escopo
        while (sym != NULL) {
            fprintf(listing, "%-17s |  ", sym->name);
            fprintf(listing, "%-8s  |  ", typeToString(sym->type));
            fprintf(listing, "%-13s  |  ", kindToString(sym->kind));
            fprintf(listing, "%-14s  |  ", scp->name);
            fprintf(listing, "%-3d  |  ", sym->memloc);

            //imprime todas as linhas onde o símbolo apareceu
            LineList line = sym->lines;
            while (line != NULL) {
                fprintf(listing, "%d ", line->lineNo);
                line = line->next;
            }
            fprintf(listing, "\n");

            sym = sym->next;
        }
        scp = scp->next;
    }
}