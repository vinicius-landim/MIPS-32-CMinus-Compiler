#ifndef _CGEN_H_
#define _CGEN_H_

#include "globals.h"
#include "parser.tab.h"
#include "symtab.h"

//Operações intermediárias
typedef enum {
    OPND_EMPTY,
    OPND_NUM,
    OPND_TEMP,
    OPND_SCOPE,
    OPND_LABEL,
    OPND_TYPE,
    OPND_SYMB
} OpndKind;

typedef enum {
    OP_ADD, OP_SUB, OP_MUL, OP_DIV, 
    OP_ASSIGN, 
    OP_JUMP,
    OP_BEQ, OP_BNE, OP_BLT, OP_BGT, OP_BLE, OP_BGE,
    OP_LABEL,
    OP_FUNC, OP_ENDFUNC, 
    OP_ARG, OP_ARG_ARR, OP_PARAM,
    OP_CALL,
    OP_ALLOCVAR, OP_ALLOCARR,
    OP_LOADVAR, OP_LOADARR, OP_LOADIMM,
    OP_STOREVAR, OP_STOREARR,
    OP_RETURN,
    OP_IN, OP_OUT,
    OP_HALT
} OpKind;

typedef struct {
    OpndKind kind;
    union {
        int imm; //valor de registrador e imediato
        int reg_id;
        char *label_name;
        char *type_name;
        char *scope_name;
        Symbol s_node;
    } content;
} Operand;

typedef struct QuadList {
    OpKind op;
    Operand result;
    Operand arg1;
    Operand arg2;
    struct QuadList* next;
} Quad;

extern Quad* headQuad;
extern Quad* currentQuad;

void printIntermediateCode(FILE *listing);
void generateIntermediateCode();

#endif