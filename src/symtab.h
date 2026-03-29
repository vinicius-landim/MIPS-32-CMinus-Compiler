#ifndef _SYMTAB_H_
#define _SYMTAB_H_
#include "globals.h"

typedef enum {SYM_VAR, SYM_ARR, SYM_FUNC} SymbolKind;

void st_insert (char *name, char *scope, ExpType type, SymbolKind kind, int lineNo, int loc);

BucketList st_lookup(char *name, char *scope);

//void printSymTab

#endif