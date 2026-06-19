#ifndef _SYMTAB_H_
#define _SYMTAB_H_
#include "globals.h"

typedef enum {SYMB_VAR, SYMB_ARR, SYMB_FUNC} SymbolKind;
typedef struct LineListNode *LineList;

typedef struct ParamListNode {
    ExpType type;
    struct ParamListNode *next;
} *ParamList;

typedef struct SymbolNode {
	char *name;
	char *scope;
	ExpType type;
	SymbolKind kind;
	int memloc;

	//atributos de função
	int numParams;
	ParamList params;

	LineList lines;
	struct SymbolNode *next;
} *Symbol;

typedef struct ScopeNode {
	char *name;
	Symbol h_symbols;
	struct ScopeNode *parent;
    struct ScopeNode *next;
} *Scope;

extern Scope currentScope;
extern Scope globalScope; 

Scope pushScope(char *name);
void popScope();
Symbol st_insert(char *name, ExpType type, SymbolKind kind, int lineNo, int loc);
void st_add_line(Symbol s_node, int lineNo);
void st_add_param(Symbol func_node, ExpType paramType);
Symbol st_lookup(char *name);
Symbol st_lookup_scope(char *name);
Symbol st_lookup_global(char *name);

void printSymTab(FILE *listing);

#endif