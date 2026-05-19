#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include "symtab.h"
#include "cgen.h"
#include "assembly.h"

AsmInstr* headAsm = NULL;
AsmInstr* currentAsm = NULL;

void emitAsm(AsmOp op, int rd, int rs, int rt, int imm, char* label){
    AsmInstr* newA = (AsmInstr*)malloc(sizeof(AsmInstr));
    newA->op = op;
    newA->rd = rd;
    newA->rs = rs;
    newA->rt = rt;
    newA->imm = imm;
    newA->label_name = (label != NULL) ? strdup(label) : NULL;
    newA->next = NULL;

    if(headAsm == NULL){
        headAsm = newA;
        currentAsm = newA;
    } else {
        currentAsm->next = newA;
        currentAsm = newA;
    }
}

void generateAssembly(Quad* headGCI){
    Quad *curr = headGCI;
    headAsm = NULL;
    currentAsm = NULL;

    while(curr != NULL){
        switch(curr->op){
            case OP_LOADIMM:{
                int reg_dest = getRegisterNum(curr->result.content.str_val);
                int value = curr->arg1.content.val;
                // addi $reg_dest, $0, value
                emitAsm(ASM_ADDI, reg_dest, 0, 0, value, NULL);
                break;
            }
            case OP_FUNC:{
                //TODO
                break;
            }
            case OP_ALLOCVAR:{
                //TODO
                break;
            }
            case OP_STOREVAR:{
                //TODO
                // sw $reg_source, offset($fp) -> sw rt, offset(rs)
                break;
            }
            case OP_LOADVAR:{
                //TODO
                // lw $reg_dest, offset($fp) -> lw rt, offset(rs) [cite: 39, 65]
                break;
            }
            case OP_ADD:{
                //TODO: (também fazer lógica de ADDI)
                // add rd, rs, rt
                break;
            }
            case OP_JUMP:{
                //TODO
                // j target_label
                break;
            }
            case OP_LABEL:{
                //TODO
                break;
            }
            case OP_ENDFUNC:{
                //TODO
                break;
            }
            case OP_HALT:{
                emitAsm(ASM_HALT, 0, 0, 0, 0, NULL);
                break;
            }
            default: break;
        }
        curr = curr->next;
    }
}