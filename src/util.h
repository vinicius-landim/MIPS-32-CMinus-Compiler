#ifndef _UTIL_H_
#define _UTIL_H_

#include "globals.h"

TreeNode * newStmtNode(StmtKind kind);
TreeNode * newExpNode(ExpKind kind);

char * copyString(const char * s);

void printTreeGraphviz(TreeNode *tree);
#endif 