#ifndef _CGEN_H_
#define _CGEN_H_

#include "globals.h"
#include "parser.tab.h"

//Operações intermediárias
typedef enum {
    OPND_EMPTY,
    OPND_NUM,
    OPND_VAR,
    OPND_TEMP,
    OPND_LABEL,
    OPND_FUNC,
    OPND_SCOPE,
    OPND_TYPE
} OpndKind;

typedef enum {
    OP_ADD, OP_SUB, OP_MUL, OP_DIV, 
    OP_ASSIGN, 
    OP_JUMP,
    OP_BEQ, OP_BNE, OP_BLT, OP_BGT, OP_BLE, OP_BGE,
    OP_LABEL,
    OP_FUNC, OP_ENDFUNC, 
    OP_ARG, OP_PARAM,
    OP_CALL,
    OP_ALLOCVAR, OP_ALLOCARR,
    OP_LOADVAR, OP_LOADARR, OP_LOADIMM,
    OP_STOREVAR, OP_STOREARR,
    OP_RETURN,
    OP_HALT
} OpKind;

typedef struct {
    OpndKind kind; //especifica o que val/str_val diz respeito
    union {
        int val;
        char *str_val; //nome variável/função, tipo, escopo, label, registradores
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