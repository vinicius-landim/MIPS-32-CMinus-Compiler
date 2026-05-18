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

static Operand newTemp(){
    Operand tempOpnd;
    tempOpnd.kind = OPND_TEMP;
    char *tempName = (char*)malloc(10*sizeof(char));
    tempOffset++;
    sprintf(tempName, "$t%d", tempOffset);
    tempOpnd.content.str_val = tempName;
    return tempOpnd;
}

static Operand newLabel(){
    Operand labelOpnd;
    labelOpnd.kind = OPND_LABEL;
    char *labelName = (char*)malloc(10*sizeof(char));
    labelOffset++;
    sprintf(labelName, "L%d", labelOffset);
    labelOpnd.content.str_val = labelName;
    return labelOpnd;
}

static Operand emptyOperand(){
    Operand emptyOpnd;
    emptyOpnd.kind = OPND_EMPTY;
    emptyOpnd.content.str_val = NULL;
    return emptyOpnd;
}

static Operand numOperand(int val){
    Operand numOpnd;
    numOpnd.kind = OPND_NUM;
    numOpnd.content.val = val;
    return numOpnd;
}

static Operand varOperand(char *var_name){
    Operand varOpnd;
    varOpnd.kind = OPND_VAR;
    varOpnd.content.str_val = copyString(var_name);
    return varOpnd;
}

static Operand funcOperand(char *func_name){
    Operand funcOpnd;
    funcOpnd.kind = OPND_FUNC;
    funcOpnd.content.str_val = copyString(func_name);
    return funcOpnd;
}

static Operand scopeOperand(char *scope){
    Operand scopeOpnd;
    scopeOpnd.kind = OPND_SCOPE;
    scopeOpnd.content.str_val = copyString(scope);
    return scopeOpnd;
}

static Operand typeOperand(ExpType type){
    Operand typeOpnd;
    typeOpnd.kind = OPND_TYPE;
    if(type == Integer)
        typeOpnd.content.str_val = "int";
    else if(type == Void)
        typeOpnd.content.str_val = "void";
    return typeOpnd;
}

OpKind opTokenToOpKind(TokenType op){
    switch(op){
        case SOMA:         return OP_ADD;
        case SUB:          return OP_SUB;
        case MUL:          return OP_MUL;
        case DIV:          return OP_DIV;
        default:
            fprintf(stderr, "Erro GCI: Operador inválido encontrado");
            exit(1);
    }
}

static const char* opKindToString(OpKind op){
    switch(op){
        case OP_ADD:        return "ADD";
        case OP_SUB:        return "SUB";
        case OP_MUL:        return "MUL";
        case OP_DIV:        return "DIV";
        case OP_ASSIGN:     return "ASSIGN";
        case OP_JUMP:       return "JUMP";
        case OP_BEQ:        return "BEQ";
        case OP_BNE:        return "BNE";
        case OP_BGE:        return "BGE";
        case OP_BLE:        return "BLE";
        case OP_BGT:        return "BGT";
        case OP_BLT:        return "BLT";
        case OP_FUNC:       return "FUNC";
        case OP_ENDFUNC:    return "ENDFUNC";
        case OP_LABEL:      return "LABEL";
        case OP_PARAM:      return "PARAM";
        case OP_CALL:       return "CALL";
        case OP_ARG:        return "ARG";
        case OP_ALLOCVAR:   return "ALLOCVAR";
        case OP_ALLOCARR:   return "ALLOCARR";
        case OP_LOADVAR:    return "LOADVAR";
        case OP_LOADARR:    return "LOADARR";
        case OP_LOADIMM:    return "LOADIMM";
        case OP_STOREVAR:   return "STOREVAR";
        case OP_STOREARR:   return "STOREARR";
        case OP_RETURN:     return "RETURN";
        case OP_HALT:       return "HALT";
        default:            return "UNKNOWN";
    }
}

void emitQuad(OpKind op, Operand result, Operand arg1, Operand arg2){
    Quad* newQ = (Quad*)malloc(sizeof(Quad));
    newQ->op = op;
    newQ->result = result;
    newQ->arg1 = arg1;
    newQ->arg2 = arg2;
    newQ->next = NULL;

    if(headQuad == NULL){
        headQuad = newQ;
        currentQuad = newQ;
    } else {
        currentQuad->next = newQ;
        currentQuad = newQ;
    }
}

static Operand genExp(TreeNode *t){
    if(t != NULL){
        switch(t->kind.exp){
            case ConstK:{
                // (LOAD, $t_a, const, -)
                Operand resultTemp = newTemp();
                Operand argNum = numOperand(t->attr.val);
                emitQuad(OP_LOADIMM, resultTemp, argNum, EMPTY_OPND);
                return resultTemp;
            }
            case VarK:{
                //(LOAD, $t_a, var, -)
                Operand resultTemp = newTemp();
                Operand argVar = varOperand(t->attr.name);
                emitQuad(OP_LOADVAR, resultTemp, argVar, EMPTY_OPND);
                return resultTemp;
            }
            case ArrK:{
                Operand argArr = varOperand(t->attr.name);
                Operand argIdx = genExp(t->child[0]); //tratamento de constantes, operações matemáticas ou uso de variáveis
                Operand resultTemp = newTemp();
                //(LOAD, $t_a, var, index)
                emitQuad(OP_LOADARR, resultTemp, argArr, argIdx);
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
                Operand argNum = numOperand(t->child[0]->attr.val); //C- não permite declaração de array usando [variável]
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
                Operand argVal = genExp(t->child[1]); //tratamento de constantes, operações matemáticas, uso de variáveis ou calls
                TreeNode *l_tree = t->child[0];
                if(l_tree->kind.exp == VarK){
                    Operand argVar = varOperand(l_tree->attr.name);
                    //(STORE, var, $t_a, -)
                    emitQuad(OP_STOREVAR, argVar, argVal, EMPTY_OPND);
                }
                else if(l_tree->kind.exp == ArrK){
                    Operand argArr = varOperand(l_tree->attr.name);
                    Operand argIdx = genExp(l_tree->child[0]);
                    //(STORE, var, $t_a, index)
                    emitQuad(OP_STOREARR, argArr, argVal, argIdx);
                }
                return argVal;
            }
            case ParamK:{
                Operand argType = typeOperand(t->type);
                Operand argName = varOperand(t->attr.name);
                Operand argScope = varOperand(t->scope);
                //(ARG, type, param, scope)
                emitQuad(OP_ARG, argType, argName, argScope);
                break;
            }
            case ParamArrK: {
                Operand argType = typeOperand(t->type);
                char arrName[50];
                sprintf(arrName, "%s[]", t->attr.name);
                Operand argName = varOperand(arrName);
                Operand argScope = varOperand(t->scope);
                emitQuad(OP_ARG, argType, argName, argScope);
                break;
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

static void genStmt(TreeNode *t){
    if(t != NULL){
        switch(t->kind.stmt){
            case IfK:{
                //tratamento de expressão de condição
                TreeNode *condition = t->child[0];
                Operand labelFalse = newLabel();
                if(condition->kind.exp == OpK){
                    //tratar ambos os lados da operação
                    Operand arg1 = genExp(condition->child[0]);
                    Operand arg2 = genExp(condition->child[1]);
                    OpKind branchOp;
                    //inverter operador para branch falso
                    switch(condition->attr.op){
                        case MAIOR: 
                            branchOp = OP_BLE;
                            break;
                        case MENOR:
                            branchOp = OP_BGE;
                            break;
                        case IGUAL_IGUAL:
                            branchOp = OP_BNE;
                            break;
                        case DIFERENTE:
                            branchOp = OP_BEQ;
                            break;
                        case MAIOR_IGUAL:
                            branchOp = OP_BLT;
                            break; 
                        case MENOR_IGUAL:
                            branchOp = OP_BGT;
                            break;
                        default: break;
                    }
                    //(BRANCH, $t_n, $t_m, L_k)
                    emitQuad(branchOp, arg1, arg2, labelFalse);
                }
                //comparação implicita com zero
                else{
                    Operand arg = genExp(condition);
                    Operand zero = numOperand(0);
                    //(BRANCH, $t_n, 0, L_k): branch falso
                    emitQuad(OP_BEQ, arg, zero, labelFalse);
                }
                //tratamento do compound do if
                cGen(t->child[1]);
                //tratamento do else
                if(t->child[2] != NULL){
                    Operand labelEnd = newLabel();
                    //JUMP para bloco then não invadir o bloco else
                    emitQuad(OP_JUMP, labelEnd, EMPTY_OPND, EMPTY_OPND);
                    //else: label para jump falso
                    emitQuad(OP_LABEL, labelFalse, EMPTY_OPND, EMPTY_OPND);
                    cGen(t->child[2]);
                    emitQuad(OP_LABEL, labelEnd, EMPTY_OPND, EMPTY_OPND);
                } else {
                    //labelFalse para jump de condição falsa (encerramento do bloco de comparação)
                    emitQuad(OP_LABEL, labelFalse, EMPTY_OPND, EMPTY_OPND);
                }
                break;
            }

            case WhileK:{
                Operand labelStart = newLabel();
                Operand labelEnd = newLabel();
                emitQuad(OP_LABEL, labelStart, EMPTY_OPND, EMPTY_OPND);
                TreeNode *condition = t->child[0];
                if(condition->kind.exp == OpK){
                    Operand arg1 = genExp(condition->child[0]);
                    Operand arg2 = genExp(condition->child[1]);
                    OpKind branchOp;
                    switch(condition->attr.op){
                        case MAIOR: 
                            branchOp = OP_BLE;
                            break;
                        case MENOR:
                            branchOp = OP_BGE;
                            break;
                        case IGUAL_IGUAL:
                            branchOp = OP_BNE;
                            break;
                        case DIFERENTE:
                            branchOp = OP_BEQ;
                            break;
                        case MAIOR_IGUAL:
                            branchOp = OP_BLT;
                            break; 
                        case MENOR_IGUAL:
                            branchOp = OP_BGT;
                            break;
                        default: break;
                    }
                    //(BRANCH, $t_n, $t_m, L_k)
                    emitQuad(branchOp, arg1, arg2, labelEnd);
                }
                //comparação implicita com zero
                else{
                    Operand arg = genExp(condition);
                    Operand zero = numOperand(0);
                    //(BRANCH, $t_n, 0, L_k): branch falso
                    emitQuad(OP_BEQ, arg, zero, labelEnd);
                }
                //tratamento do compound do while
                cGen(t->child[1]);
                //loop
                emitQuad(OP_JUMP, labelStart, EMPTY_OPND, EMPTY_OPND);
                //label de fim
                emitQuad(OP_LABEL, labelEnd, EMPTY_OPND, EMPTY_OPND);
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
                Operand argType = typeOperand(t->type);
                Operand argFunc = funcOperand(t->attr.name);
                emitQuad(OP_FUNC, argType, argFunc, EMPTY_OPND);
                cGen(t->child[0]);
                cGen(t->child[1]);
                //(ENDFUNC, gcd, -, -)
                emitQuad(OP_ENDFUNC, argFunc, EMPTY_OPND, EMPTY_OPND);
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

static void cGen(TreeNode *t){
    if(t != NULL){
        switch(t->nodeKind){
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

void generateIntermediateCode(TreeNode *AST){
    headQuad = NULL;
    currentQuad = NULL;
    tempOffset = 0;
    labelOffset = 0;

    cGen(AST);

    //emite instrução de parada ao final do programa
    emitQuad(OP_HALT, EMPTY_OPND, EMPTY_OPND, EMPTY_OPND);
}

static void printOperand(FILE *listing, Operand op){
    switch(op.kind){
        case OPND_EMPTY:
            fprintf(listing, "-");
            break;
        case OPND_NUM:
            fprintf(listing, "%d", op.content.val); 
            break;
        case OPND_VAR:
            fprintf(listing, "%s", op.content.str_val); 
            break;
        case OPND_TEMP:
            fprintf(listing, "%s", op.content.str_val); 
            break;
        case OPND_LABEL:
            fprintf(listing, "%s", op.content.str_val); 
            break;
        case OPND_FUNC:
            fprintf(listing, "%s", op.content.str_val); 
            break;
        case OPND_SCOPE:
            fprintf(listing, "%s", op.content.str_val); 
            break;
        case OPND_TYPE:
            fprintf(listing, "%s", op.content.str_val); 
            break;
        default:
            fprintf(listing, "?");
            break;
    }
}

void printIntermediateCode(FILE *listing){
    Quad* curr = headQuad;

    while (curr != NULL){        
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