#include "globals.h"
#include "util.h"


//Louden(2004, p.507-9)
TreeNode* newStmtNode(StmtKind kind) {
    TreeNode* t = (TreeNode*) malloc(sizeof(TreeNode));
    int i;
    
    if (t == NULL) {
        fprintf(stderr, "Erro de memoria na lineNo %d\n", lineNo);
        exit(1);
    } else {
        for (i = 0; i < MAXCHILDREN; i++) t->child[i] = NULL;
        t->sibling = NULL;
        t->nodeKind = StmtK;
        t->kind.stmt = kind;
        t->lineNo = lineNo;
    }
    return t;
}

TreeNode* newExpNode(ExpKind kind) {
    TreeNode *t = (TreeNode*) malloc(sizeof(TreeNode));
    int i;
    
    if (t == NULL) {
        fprintf(stderr, "Erro de memoria na lineNo %d\n", lineNo);
        exit(1);
    } else {
        for (i = 0; i < MAXCHILDREN; i++) t->child[i] = NULL;
        t->sibling = NULL;
        t->nodeKind = ExpK;
        t->kind.exp = kind;
        t->lineNo = lineNo;
        t->type = Void;
    }
    return t;
}

char * copyString(const char * s) {
    int n;
    char * t;

    if (s == NULL) return NULL;
    
    n = strlen(s) + 1;
    t = malloc(n);
    
    if (t == NULL) {
        fprintf(stderr, "Erro de memoria na lineNo %d\n", lineNo);
        exit(1);
    } else {
        strcpy(t, s);
    }
    return t;
}


void printTree(TreeNode * tree) {/* TODO */ } //graphviz