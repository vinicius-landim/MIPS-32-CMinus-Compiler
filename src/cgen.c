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
    tempOffset++;
    tempOpnd.content.reg_id = tempOffset;
    return tempOpnd;
}

static Operand newLabel(){
    Operand labelOpnd;
    labelOpnd.kind = OPND_LABEL;
    char *labelName = (char*)malloc(10*sizeof(char));
    labelOffset++;
    sprintf(labelName, "L%d", labelOffset);
    labelOpnd.content.label_name = labelName;
    return labelOpnd;
}

static Operand emptyOperand(){
    Operand emptyOpnd;
    emptyOpnd.kind = OPND_EMPTY;
    emptyOpnd.content.s_node = NULL;
    return emptyOpnd;
}

static Operand symbOperand(Symbol symb){
    Operand symbOpnd;
    symbOpnd.kind = OPND_SYMB;
    symbOpnd.content.s_node = symb;
    return symbOpnd;
}

static Operand numOperand(int val){
    Operand numOpnd;
    numOpnd.kind = OPND_NUM;
    numOpnd.content.imm = val;
    return numOpnd;
}

static Operand scopeOperand(char *scope) {
    Operand scopeOpnd;
    scopeOpnd.kind = OPND_SCOPE;
    scopeOpnd.content.scope_name = scope;
    return scopeOpnd;
}

static Operand typeOperand(ExpType type){
    Operand typeOpnd;
    typeOpnd.kind = OPND_TYPE;
    if(type == Integer)
        typeOpnd.content.type_name = "int";
    else if(type == Void)
        typeOpnd.content.type_name = "void";
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
        case OP_ARG_ARR:    return "ARGARR";
        case OP_ALLOCVAR:   return "ALLOCVAR";
        case OP_ALLOCARR:   return "ALLOCARR";
        case OP_LOADVAR:    return "LOADVAR";
        case OP_LOADARR:    return "LOADARR";
        case OP_LOADIMM:    return "LOADIMM";
        case OP_STOREVAR:   return "STOREVAR";
        case OP_STOREARR:   return "STOREARR";
        case OP_RETURN:     return "RETURN";
        case OP_IN:         return "INPUT";
        case OP_OUT:        return "OUTPUT";
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
                Operand argVar = symbOperand(t->symb);
                emitQuad(OP_LOADVAR, resultTemp, argVar, EMPTY_OPND);
                return resultTemp;
            }
            case ArrK:{
                Operand argArr = symbOperand(t->symb);
                Operand argIdx = genExp(t->child[0]); //tratamento de constantes, operações matemáticas ou uso de variáveis
                Operand resultTemp = newTemp();
                //(LOAD, $t_a, var, index)
                emitQuad(OP_LOADARR, resultTemp, argArr, argIdx);
                return resultTemp;
            }
            case VarDeclK:{
                //(ALLOCVAR, var, scope, -)
                Operand resultVar = symbOperand(t->symb);
                Operand argScope = scopeOperand(t->scope);
                emitQuad(OP_ALLOCVAR, resultVar, argScope, EMPTY_OPND);
                return emptyOperand();
            }
            case ArrDeclK:{
                //(ALLOCARR, var, arr_size, scope)
                Operand resultArr = symbOperand(t->symb);
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
                    Operand argVar = symbOperand(l_tree->symb);
                    //(STORE, var, $t_a, -)
                    emitQuad(OP_STOREVAR, argVar, argVal, EMPTY_OPND);
                }
                else if(l_tree->kind.exp == ArrK){
                    Operand argArr = symbOperand(l_tree->symb);
                    Operand argIdx = genExp(l_tree->child[0]);
                    //(STORE, var, $t_a, index)
                    emitQuad(OP_STOREARR, argArr, argVal, argIdx);
                }
                return argVal;
            }
            case ParamK:{
                Operand argType = typeOperand(t->type);
                Operand argVar = symbOperand(t->symb);
                Operand argScope = scopeOperand(t->scope);
                //(ARG, type, param, scope)
                emitQuad(OP_ARG, argType, argVar, argScope);
                break;
            }
            case ParamArrK: {
                Operand argType = typeOperand(t->type);
                Operand argArr = symbOperand(t->symb);
                Operand argScope = scopeOperand(t->scope);
                emitQuad(OP_ARG_ARR, argType, argArr, argScope);
                break;
            }
            case CallK:{
                char *funcName = t->symb->name;
                if (strcmp(funcName, "input") == 0) {
                    Operand resultTemp = newTemp();
                    // (IN, $t_a, -, -)
                    emitQuad(OP_IN, resultTemp, EMPTY_OPND, EMPTY_OPND);
                    return resultTemp;
                } 
                else if (strcmp(funcName, "output") == 0) {
                    Operand argVal = genExp(t->child[0]);
                    // (OUT, -, arg, -)
                    emitQuad(OP_OUT, EMPTY_OPND, argVal, EMPTY_OPND);
                    return emptyOperand();
                }
                //emissão de quádruplas de params (percorrer t->child[0] e seus irmãos)
                TreeNode *argNode = t->child[0];
                int argCount = 0;
                while(argNode != NULL){
                    Operand argVal = genExp(argNode);
                    emitQuad(OP_PARAM, argVal, EMPTY_OPND, EMPTY_OPND);
                    argCount++;
                    argNode = argNode->sibling;
                }
                Operand argFunc = symbOperand(t->symb);
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
                Operand argFunc = symbOperand(t->symb);
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
    //emitQuad(OP_HALT, EMPTY_OPND, EMPTY_OPND, EMPTY_OPND); //TODO: VERIFICAR NECESSIDADE DE HALT FINAL
}

static void printOperand(FILE *listing, Operand op){
    switch(op.kind){
        case OPND_EMPTY:
            fprintf(listing, "-");
            break;
            
        case OPND_NUM:
            fprintf(listing, "%d", op.content.imm); 
            break;
            
        case OPND_TEMP:
            fprintf(listing, "$t%d", op.content.reg_id); 
            break;
            
        case OPND_LABEL:
            fprintf(listing, "%s", op.content.label_name); 
            break;
            
        case OPND_TYPE:
            fprintf(listing, "%s", op.content.type_name); 
            break;
            
        case OPND_SCOPE:
            fprintf(listing, "%s", op.content.scope_name); 
            break;
            
        case OPND_SYMB:
            if (op.content.s_node != NULL) {
                fprintf(listing, "%s", op.content.s_node->name);
            } else {
                fprintf(listing, "?NULL_SYM?");
            }
            break;
            
        default:
            fprintf(listing, "?");
            break;
    }
}
void printIntermediateCode(FILE *listing){
    Quad *curr = headQuad;

    while(curr != NULL){        
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