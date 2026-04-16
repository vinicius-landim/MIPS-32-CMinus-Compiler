#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include "symtab.h"
#include "util.h"
#include "cgen.h" 

#define EMPTY_OPND emptyOperand()

Quad* headQuad = NULL;
Quad* currentQuad = NULL;

static int tempOffset = 0;
static int labelOffset = 0;

static void cGen(TreeNode *t);

static Operand newTemp() {
    Operand tempOpnd;
    tempOpnd.kind = OPND_TEMP;
    char *tempName = (char*)malloc(10*sizeof(char));
    tempOffset++;
    sprintf(tempName, "$t%d", tempOffset);
    tempOpnd.content.name = tempName;
    return tempOpnd;
}

static Operand newLabel() {
    Operand labelOpnd;
    labelOpnd.kind = OPND_LABEL;
    char *labelName = (char*)malloc(10*sizeof(char));
    labelOffset++;
    sprintf(labelName, "L%d", labelOffset);
    labelOpnd.content.name = labelName;
    return labelOpnd;
}

static Operand emptyOperand() {
    Operand emptyOpnd;
    emptyOpnd.kind = OPND_EMPTY;
    emptyOpnd.content.name = NULL;
    return emptyOpnd;
}

static Operand numOperand(int val){
    Operand numOpnd;
    numOpnd.kind = OPND_NUM;
    numOpnd.content.val = val;
    return numOpnd;
}

static Operand varOperand(char *name){
    Operand varOpnd;
    varOpnd.kind = OPND_VAR;
    varOpnd.content.name = name;
    return varOpnd;
}

static Operand funcOperand(char *name){
    Operand funcOpnd;
    funcOpnd.kind = OPND_FUNC;
    funcOpnd.content.name = name;
    return funcOpnd;
}

static Operand scopeOperand(char *name){
    Operand scopeOpnd;
    scopeOpnd.kind = OPND_SCOPE;
    scopeOpnd.content.name = name;
    return scopeOpnd;
}

OpKind opTokenToOpKind(TokenType op){
    switch(op){
        case SOMA:         return OP_ADD;
        case SUB:          return OP_SUB;
        case MUL:          return OP_MUL;
        case DIV:          return OP_DIV;
        case MENOR_IGUAL:  return OP_LEQ; 
        case MENOR:        return OP_LT;
        case MAIOR_IGUAL:  return OP_GEQ;
        case MAIOR:        return OP_GT;
        case IGUAL_IGUAL:  return OP_EQ;
        case DIFERENTE:    return OP_NEQ;
        default:            return OP_ADD; //TODO: Verificar necessidade de fallback
    }
}

static const char* opKindToString(OpKind op) {
    switch (op) {
        case OP_ADD:       return "ADD";
        case OP_SUB:       return "SUB";
        case OP_MUL:       return "MUL";
        case OP_DIV:       return "DIV";
        case OP_ASSIGN:    return "ASSIGN";
        case OP_EQ:        return "EQ";
        case OP_NEQ:       return "NEQ";
        case OP_LT:        return "LT";
        case OP_LEQ:       return "LEQ";
        case OP_GT:        return "GT";
        case OP_GEQ:       return "GEQ";
        case OP_GOTO:      return "GOTO";
        case OP_IFFALSE:   return "IFFALSE";
        case OP_FUNC:      return "FUNC";
        case OP_LABEL:     return "LABEL";
        case OP_PARAM:     return "PARAM";
        case OP_CALL:      return "CALL";
        case OP_ALLOCVAR:  return "ALLOCVAR";
        case OP_ALLOCARR:  return "ALLOCARR";
        case OP_LOAD:      return "LOAD";
        case OP_STORE:     return "STORE";
        case OP_RETURN:    return "RETURN";
        case OP_HALT:      return "HALT";
        default:        return "UNKNOWN";
    }
}

void emitQuad(OpKind op, Operand result, Operand arg1, Operand arg2) {
    Quad* newQ = (Quad*)malloc(sizeof(Quad));
    newQ->op = op;
    newQ->result = result;
    newQ->arg1 = arg1;
    newQ->arg2 = arg2;
    newQ->next = NULL;

    if (headQuad == NULL) {
        headQuad = newQ;
        currentQuad = newQ;
    } else {
        currentQuad->next = newQ;
        currentQuad = newQ;
    }
}

static Operand genExp(TreeNode *t) {
    if(t != NULL){
        switch(t->kind.exp){
            case ConstK:{
                // (LOAD, $t_a, const, -)
                Operand resultTemp = newTemp();
                Operand argNum = numOperand(t->attr.val);
                emitQuad(OP_LOAD, resultTemp, argNum, EMPTY_OPND);
                return resultTemp;
            }
            case VarK:{
                //(LOAD, $t_a, var, -)
                Operand resultTemp = newTemp();
                Operand argVar = varOperand(t->attr.name);
                emitQuad(OP_LOAD, resultTemp, argVar, EMPTY_OPND);
                return resultTemp;
            }
            case ArrK:{
                Operand argArr = varOperand(t->attr.name);
                Operand argIdx = genExp(t->child[0]); //tratamento de constantes, operações matemáticas ou uso de variáveis
                Operand resultTemp = newTemp();
                //(LOAD, $t_a, var, index)
                emitQuad(OP_LOAD, resultTemp, argArr, argIdx);
                return resultTemp;
            }
            case VarDeclK:{
                //(ALLOCVAR, var, scope, -)
                Operand resultVar = varOperand(t->attr.name);
                Operand argScope = scopeOperand(t->scope);
                emitQuad(OP_ALLOCVAR, resultVar, argScope, EMPTY_OPND);
                return emptyOperand();
            }
            case ArrDeclK:{
                //(ALLOCARR, var, arr_size, scope)
                Operand resultArr = varOperand(t->attr.name);
                Operand argNum = numOperand(t->child[0]->attr.val);
                Operand argScope = scopeOperand(t->scope);
                emitQuad(OP_ALLOCARR, resultArr, argNum, argScope);
                return emptyOperand();
            }
            case OpK:{
                Operand arg1 = genExp(t->child[0]);
                Operand arg2 = genExp(t->child[1]);
                Operand resultTemp = newTemp();
                //(OP, $t_a, $t_b, $t_c)
                emitQuad(opTokenToOpKind(t->attr.op), resultTemp, arg1, arg2);
                return resultTemp;
            }
            case AssignK:{
                Operand argVar = varOperand(t->child[0]->attr.name);
                Operand argVal = genExp(t->child[1]); //tratamento de constantes, operações matemáticas ou uso de variáveis
                Operand resultTemp = newTemp();
                //(ASSIGN, $t_a, $t_b, -)
                emitQuad(OP_ASSIGN, resultTemp, argVal, EMPTY_OPND);

                TreeNode *l_tree = t->child[0];
                if(l_tree->kind.exp == VarK){
                    Operand argVar = varOperand(l_tree->attr.name);
                    //(STORE, var, $t_a, -)
                    emitQuad(OP_STORE, argVar, resultTemp, EMPTY_OPND);
                }
                else if(l_tree->kind.exp == ArrK){
                    Operand argArr = varOperand(l_tree->attr.name);
                    Operand argIdx = genExp(l_tree->child[0]);
                    //(STORE, var, $t_a, index)
                    emitQuad(OP_STORE, argArr, resultTemp, argIdx);
                }
                return resultTemp;
            }
            case CallK:{
                //emissão de quádruplas de params (percorrer t->child[0] e seus irmãos)
                TreeNode *argNode = t->child[0];
                int argCount = 0;
                while(argNode != NULL){
                    Operand argVal = genExp(argNode);
                    emitQuad(OP_PARAM, argVal, EMPTY_OPND, EMPTY_OPND);
                    argCount++;
                    argNode = argNode->sibling;
                }
                Operand argFunc = funcOperand(t->attr.name);
                Operand argNum = numOperand(argCount);
                Operand resultTemp = newTemp();
                //(CALL, $t_a, func, numParams)
                emitQuad(OP_CALL, resultTemp, argFunc, argNum);
                return resultTemp;
            }
            default:
                return emptyOperand();
        }
    }
}

static void genStmt(TreeNode *t) {
    if (t != NULL) {
        switch (t->kind.stmt) {
            case IfK:{
                //tratamento de expressão de condição
                Operand condition = genExp(t->child[0]); //$t_n
                Operand labelFalse = newLabel();
                //(IFFALSE, $t_n, L_m, -)
                emitQuad(OP_IFFALSE, condition, labelFalse, EMPTY_OPND);
                //tratamento de sequência verdadeira
                cGen(t->child[1]);
                //tratamento do else
                if(t->child[2] != NULL){
                    Operand labelEnd = newLabel();
                    //GOTO para o bloco then
                    emitQuad(OP_GOTO, EMPTY_OPND, labelEnd, EMPTY_OPND);
                    //else: jump para labelFalse
                    emitQuad(OP_LABEL, EMPTY_OPND, labelFalse, EMPTY_OPND);
                    cGen(t->child[2]);
                    emitQuad(OP_LABEL, EMPTY_OPND, labelEnd, EMPTY_OPND);
                } else {
                    //else: jump para labelFalse
                    emitQuad(OP_LABEL, EMPTY_OPND, labelFalse, EMPTY_OPND);
                }
                break;
            }

            case WhileK:{
                Operand labelStart = newLabel();
                Operand labelEnd = newLabel();
                emitQuad(OP_LABEL, EMPTY_OPND, labelStart, EMPTY_OPND);
                Operand condition = genExp(t->child[0]);
                emitQuad(OP_IFFALSE, condition, labelEnd, EMPTY_OPND);
                //tratamento do compound do while
                cGen(t->child[1]);
                //loop
                emitQuad(OP_GOTO, EMPTY_OPND, labelStart, EMPTY_OPND);
                //label de fim
                emitQuad(OP_LABEL, EMPTY_OPND, labelEnd, EMPTY_OPND);
                break;
            }
            case CompoundK:{
                //tratamento das declarações de variáveis
                cGen(t->child[0]);
                //tratamento da sequência de instruções
                cGen(t->child[1]);
                break;
            }
            case FunctBodyK:{
                //tratamento das variáveis
                cGen(t->child[0]);
                //tratamento da sequência de instruções
                cGen(t->child[1]);
                break;
            }
            case FunctDeclK:{
                Operand labelFunc = funcOperand(t->attr.name);
                emitQuad(OP_FUNC, EMPTY_OPND, labelFunc, EMPTY_OPND);
                cGen(t->child[0]);
                cGen(t->child[1]);
                break;
            }
            case ReturnK:{
                if(t->child[0] != NULL){
                    Operand argVal = genExp(t->child[0]); //tratamento de constantes, operações matemáticas ou variáveis
                    emitQuad(OP_RETURN, argVal, EMPTY_OPND, EMPTY_OPND);
                }
                else
                    emitQuad(OP_RETURN, EMPTY_OPND, EMPTY_OPND, EMPTY_OPND);
                break;
            }
            
            default:
                break;
        }
    }
}

static void cGen(TreeNode * t) {
    if (t != NULL) {
        switch (t->nodeKind) {
            case StmtK:
                genStmt(t);
                break;
            case ExpK:
                genExp(t);
                break;
            default:
                break;
        }
        cGen(t->sibling);
    }
}

void generateIntermediateCode(TreeNode *AST) {
    headQuad = NULL;
    currentQuad = NULL;
    tempOffset = 0;
    labelOffset = 0;

    cGen(AST);

    //emite instrução de parada ao final do programa
    emitQuad(OP_HALT, EMPTY_OPND, EMPTY_OPND, EMPTY_OPND);
}

static void printOperand(FILE *listing, Operand op) {
    switch (op.kind) {
        case OPND_EMPTY:
            fprintf(listing, "-");
            break;
        case OPND_NUM:
            fprintf(listing, "%d", op.content.val); 
            break;
        case OPND_VAR:
            fprintf(listing, "%s", op.content.name); 
            break;
        case OPND_TEMP:
            fprintf(listing, "%s", op.content.name); 
            break;
        case OPND_LABEL:
            fprintf(listing, "%s", op.content.name); 
            break;
        case OPND_FUNC:
            fprintf(listing, "%s", op.content.name); 
            break;
        case OPND_SCOPE:
            fprintf(listing, "%s", op.content.name); 
            break;
        default:
            fprintf(listing, "?");
            break;
    }
}

void printIntermediateCode(FILE *listing) {
    Quad* curr = headQuad;

    while (curr != NULL) {        
        fprintf(listing, "(");
        fprintf(listing, "%s, ", opKindToString(curr->op));
        
        printOperand(listing, curr->result);
        fprintf(listing, ", ");
        
        printOperand(listing, curr->arg1);
        fprintf(listing, ", ");
        
        printOperand(listing, curr->arg2);
        fprintf(listing, ")\n");

        curr = curr->next;
    }
}