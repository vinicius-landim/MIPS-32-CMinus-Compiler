#include "globals.h"
#include "util.h"
#include "parser.tab.h"


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
        t->scope = copyString(currentScope);
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
        t->scope = copyString(currentScope);
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

static const char* opStr(TokenType op) {
    switch (op) {
        case SOMA:        return "+";
        case SUB:         return "-";
        case MUL:         return "*";
        case DIV:         return "/";
        case MENOR:       return "<";
        case MENOR_IGUAL: return "<=";
        case MAIOR:       return ">";
        case MAIOR_IGUAL: return ">=";
        case IGUAL_IGUAL: return "==";
        case DIFERENTE:   return "!=";
        default:          return "?";
    }
}

static const char* typeStr(ExpType t) {
    switch (t) {
        case Integer: return "int";
        case Boolean: return "bool";
        case Void:    return "void";
        default:      return "";
    }
}

static void writeNodeLabel(FILE *out, TreeNode *node) {
    if (node->nodeKind == StmtK) {
        switch (node->kind.stmt) {
            case IfK:
                fprintf(out, "IF");
                break;
            case WhileK:
                fprintf(out, "WHILE");
                break;
            case ReadK:
                fprintf(out, "READ");
                break;
            case WriteK:
                fprintf(out, "WRITE");
                break;
            case CompoundK:
                fprintf(out, "COMPOUND");
                break;
            case FunctDeclK:
                fprintf(out, "FUN: %s", (node->attr.name != NULL) ? node->attr.name : "?");
                break;
            case ReturnK:
                fprintf(out, "RETURN");
                break;
            default:
                fprintf(out, "STMT");
                break;
        }
    } else {
        switch (node->kind.exp) {
            case OpK:
                fprintf(out, "OP: %s", opStr(node->attr.op));
                break;
            case ConstK:
                fprintf(out, "CONST: %d", node->attr.val);
                break;
            case IdK:
                if (node->child[0] != NULL) {
                    fprintf(out, "ID: %s[]", (node->attr.name != NULL) ? node->attr.name : "?");
                } else {
                    fprintf(out, "ID: %s", (node->attr.name != NULL) ? node->attr.name : "?");
                }
                break;
            case VarDeclK:
                fprintf(out, "VAR DECL: %s", (node->attr.name != NULL) ? node->attr.name : "?");
                break;
            case ArrDeclK:
                fprintf(out, "ARR DECL: %s", (node->attr.name != NULL) ? node->attr.name : "?");
                break;
            case ParamK:
                if (node->child[0] != NULL) {
                    fprintf(out, "PARAM: %s[]", (node->attr.name != NULL) ? node->attr.name : "?");
                } else {
                    fprintf(out, "PARAM: %s", (node->attr.name != NULL) ? node->attr.name : "?");
                }
                break;
            case AssignK:
                fprintf(out, "ASSIGN");
                break;
            case CallK:
                fprintf(out, "CALL: %s", (node->attr.name != NULL) ? node->attr.name : "?");
                break;
            default:
                fprintf(out, "EXP");
                break;
        }
    }

    if (node->type == Integer || node->type == Boolean || node->type == Void) {
        fprintf(out, "\\n(type=%s)", typeStr(node->type));
    }
    fprintf(out, "\\n(line=%d)", node->lineNo);

    if (node->scope != NULL) {
        fprintf(out, "\\n[scope: %s]", node->scope);
    }
}

static void printTreeGraphvizRec(FILE *out, TreeNode *node) {
    int i;

    if (node == NULL) return;

    fprintf(out, "  node%p [label=\"", (void*)node);
    writeNodeLabel(out, node);
    fprintf(out, "\"];\n");

    for (i = 0; i < MAXCHILDREN; i++) {
        if (node->child[i] != NULL) {
            fprintf(out, "  node%p -> node%p [label=\"c%d\"];\n", (void*)node, (void*)node->child[i], i);
            printTreeGraphvizRec(out, node->child[i]);
        }
    }

    if (node->sibling != NULL) {
        fprintf(out, "  node%p -> node%p [style=dashed, color=gray40, label=\"sib\"];\n", (void*)node, (void*)node->sibling);
        fprintf(out, "  { rank=same; node%p; node%p; }\n", (void*)node, (void*)node->sibling);
        printTreeGraphvizRec(out, node->sibling);
    }
}

void printTreeGraphviz(TreeNode *AST){
    FILE *out;

    if (AST == NULL) {
        fprintf(stderr, "AST vazia: nenhum arquivo Graphviz foi gerado.\n");
        return;
    }

    out = fopen("arvore.dot", "w");
    if (out == NULL) {
        fprintf(stderr, "Erro ao criar arquivo arvore.dot\n");
        return;
    }

    fprintf(out, "digraph AST {\n");
    fprintf(out, "  rankdir=TB;\n");
    fprintf(out, "  node [shape=box, style=\"rounded,filled\", fillcolor=\"lightgoldenrod1\", fontname=\"Consolas\"];\n");
    fprintf(out, "  edge [fontname=\"Consolas\"];\n");

    printTreeGraphvizRec(out, AST);

    fprintf(out, "}\n");
    fclose(out);

    printf("Arquivo Graphviz gerado: arvore.dot\n");
}