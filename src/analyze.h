#ifndef _ANALYZE_H_
#define _ANALYZE_H_

#include "globals.h"

void buildSymtab(TreeNode *AST);
void typeCheck(TreeNode *AST);

#endif