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
        t->scope = NULL;
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
        t->scope = NULL;
        t->type = Void;
    }
    return t;
}

char * copyString(const char * s) {
    int n;
    char * t;

    if(s == NULL) return NULL;
    
    n = strlen(s) + 1;
    t = malloc(n);
    
    if(t == NULL) {
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
        case Void:    return "void";
        default:      return "";
    }
}

static void writeNodeLabel(FILE *out, TreeNode *node) {
    if (node->nodeKind == StmtK) {
        switch (node->kind.stmt) {
            case IfK:
                fprintf(out, "if");
                break;
            case WhileK:
                fprintf(out, "while");
                break;
            case ReadK:
                fprintf(out, "read");
                break;
            case WriteK:
                fprintf(out, "write");
                break;
            case CompoundK:
                fprintf(out, "{ }");
                break;
            case FunctBodyK:
                fprintf(out, "{ }");
                break;
            case FunctDeclK:
                fprintf(out, "Fun: %s()", (node->attr.name != NULL) ? node->attr.name : "?");
                break;
            case ReturnK:
                fprintf(out, "return");
                break;
            default: 
                fprintf(out, "STMT");
                break;
        }
    } else {
        switch (node->kind.exp) {
            case OpK:
                fprintf(out, "%s", opStr(node->attr.op));
                break;
            case ConstK:
                fprintf(out, "%d", node->attr.val);
                break;
            case VarK:
                fprintf(out, "%s", (node->attr.name != NULL) ? node->attr.name : "?");
                break;
            case ArrK:
                fprintf(out, "%s[]", (node->attr.name != NULL) ? node->attr.name : "?");
                break;
            case VarDeclK:
                fprintf(out, "Var: %s", (node->attr.name != NULL) ? node->attr.name : "?");
                break;
            case ArrDeclK:
                fprintf(out, "Arr: %s[]", (node->attr.name != NULL) ? node->attr.name : "?");
                break;
            case ParamK:
                fprintf(out, "Param: %s", (node->attr.name != NULL) ? node->attr.name : "?");
                break;
            case ParamArrK:
                fprintf(out, "Param: %s[]", (node->attr.name != NULL) ? node->attr.name : "?");
                break;
            case AssignK:
                fprintf(out, "=");
                break;
            case CallK:
                fprintf(out, "Call: %s()", (node->attr.name != NULL) ? node->attr.name : "?");
                break;
            default:
                fprintf(out, "EXP");
                break;
        }
    }

    int isDecl = (node->nodeKind == StmtK && node->kind.stmt == FunctDeclK) ||
                 (node->nodeKind == ExpK && (node->kind.exp == VarDeclK || node->kind.exp == ArrDeclK || node->kind.exp == ParamK || node->kind.exp == ParamArrK));

    if (isDecl) {
        if (node->type == Integer || node->type == Void) {
            fprintf(out, "\\n(%s)", typeStr(node->type));
        }
        if (node->scope != NULL) {
            fprintf(out, "\\n[%s]", node->scope);
        }
    }
}

static void printTreeGraphvizRec(FILE *out, TreeNode *node) {
    int i;
    if (node == NULL) return;

    const char* fillColor = "lightgray";
    const char* shape = "box";
    
    if (node->nodeKind == StmtK) {
        if (node->kind.stmt == FunctDeclK) fillColor = "lightcoral";
        else fillColor = "lightblue";
    } else if (node->nodeKind == ExpK) {
        
        if (node->kind.exp == OpK) {
            fillColor = "plum"; 
            shape = "circle";
        }
        else if (node->kind.exp == ConstK) {
            fillColor = "lightgrey";
            shape = "ellipse";
        }
        else if (node->kind.exp == AssignK) {
            fillColor = "gold";
            shape = "circle";
        } 
        else if (node->kind.exp == CallK) {
            fillColor = "aquamarine";
        } 
        else if (node->kind.exp == VarDeclK || node->kind.exp == ArrDeclK || node->kind.exp == ParamK || node->kind.exp == ParamArrK) {
            fillColor = "palegreen";
        } 
        else { 
            fillColor = "lightyellow"; 
            shape = "ellipse";
        }
    }

    fprintf(out, "  node%p [shape=\"%s\", fillcolor=\"%s\", label=\"", (void*)node, shape, fillColor);
    writeNodeLabel(out, node);
    fprintf(out, "\"];\n");

    //impressão filhos
    for (i = 0; i < MAXCHILDREN; i++) {
        if (node->child[i] != NULL) {
            fprintf(out, "  node%p -> node%p;\n", (void*)node, (void*)node->child[i]);
            printTreeGraphvizRec(out, node->child[i]);
        }
    }

    //impressão irmãos
    if (node->sibling != NULL) {
        fprintf(out, "  node%p -> node%p [style=dashed, color=gray40];\n", (void*)node, (void*)node->sibling);
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