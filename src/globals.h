#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXCHILDREN 3

typedef int TokenType;
extern int lineNo; 
extern FILE* source;

// LOUDEN (2014, p.505)
typedef enum {Void, Integer} ExpType;
typedef enum {StmtK, ExpK} NodeKind;
typedef enum {IfK, WhileK, ReadK, WriteK, CompoundK, FunctDeclK, FunctBodyK, ReturnK} StmtKind;
typedef enum {OpK, ConstK, VarK, ArrK, VarDeclK, ArrDeclK, ParamK, ParamArrK, AssignK, CallK} ExpKind;
typedef struct treeNode{
    struct treeNode *child[MAXCHILDREN];
    struct treeNode *sibling;
    int lineNo;
    NodeKind nodeKind;
    union {StmtKind stmt; ExpKind exp;} kind;
    union {TokenType op; int val; char *name;} attr;
    ExpType type;
    char *scope;
} TreeNode;

#endif