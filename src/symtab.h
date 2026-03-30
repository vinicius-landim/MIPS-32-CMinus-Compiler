#ifndef _SYMTAB_H_
#define _SYMTAB_H_
#include "globals.h"

typedef enum {SYMB_VAR, SYMB_ARR, SYMB_FUNC} SymbolKind;
typedef struct LineListNode *LineList;

typedef struct SymbolNode {
	char *name;
	ExpType type;
	SymbolKind kind;
	int memloc;
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

void pushScope(char *name);
void popScope();
void st_insert(char *name, ExpType type, SymbolKind kind, int lineNo, int loc);
Symbol st_lookup(char *name);
Symbol st_lookup_scope(char *name);

void printSymTab(FILE *listing);

#endif