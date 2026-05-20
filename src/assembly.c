#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include "symtab.h"
#include "cgen.h"
#include "assembly.h"

AsmInstr *headAsm = NULL;
AsmInstr *currentAsm = NULL;

int mapRegister(char* reg_name) {
    if (reg_name == NULL) return 0;
    
    //registradores reservados
    if (strcmp(reg_name, "$0") == 0) return 0; //$zero
    if (strcmp(reg_name, "$29") == 0) return 29; //$sp
    if (strcmp(reg_name, "$30") == 0) return 30; //$fp
    if (strcmp(reg_name, "$31") == 0) return 31; //$ra
    
    if (reg_name[0] == '$' && reg_name[1] == 't') {
        int virtual_reg = atoi(&reg_name[2]); 
        return ((virtual_reg - 1) % 28) + 1; 
    }
    
    return 0; //fallback
}

static AsmInstr* createNode(AsmOp op, AsmFormat format) {
    AsmInstr *newA = (AsmInstr*)malloc(sizeof(AsmInstr));
    newA->op = op;
    newA->format = format;
    newA->next = NULL;
    
    if (headAsm == NULL) {
        headAsm = newA;
        currentAsm = newA;
    } else {
        currentAsm->next = newA;
        currentAsm = newA;
    }
    return newA;
}

void emitAsmR(AsmOp op, int rs, int rt, int rd, int shamt) {
    AsmInstr* instr = createNode(op, FORMAT_R);
    instr->type.r.rs = rs;
    instr->type.r.rt = rt;
    instr->type.r.rd = rd;
    instr->type.r.shamt = shamt;
}

void emitAsmI(AsmOp op, int rs, int rt, int imm) {
    AsmInstr* instr = createNode(op, FORMAT_I);
    instr->type.i.rs = rs;
    instr->type.i.rt = rt;
    instr->type.i.imm = imm;
}

void emitAsmJ(AsmOp op, char *target) {
    AsmInstr* instr = createNode(op, FORMAT_J);
    instr->type.j.target_name = strdup(target);
}

void emitAsmLabel(char *label) {
    AsmInstr* instr = createNode(ASM_LABEL, FORMAT_LABEL);
    instr->type.label.label_name = strdup(label);
}

void generateAssembly(Quad *headGCI){
    Quad *curr = headGCI;
    headAsm = NULL;
    currentAsm = NULL;

    int sp = 29;
    int fp = 30;
    int ra = 31;
    int zero = 0;

    while(curr != NULL){
        switch(curr->op){
            case OP_FUNC:{
                //TODO
                break;
            }
            case OP_ALLOCVAR: {
                // addi $sp, $sp, -1 
                emitAsmI(ASM_ADDI, sp, sp, -1);
                break;
            }
            case OP_ALLOCARR: {
                int size = curr->arg1.content.val; //tamanho array  
                
                // addi $sp, $sp, -size (Desce a pilha 'size' palavras de uma vez)
                emitAsmI(ASM_ADDI, 29, 29, -size);
                break;
            }
            case OP_STOREVAR: {
                Symbol s = st_lookup(curr->result.content.str_val);
                int rs_value = mapRegister(curr->arg1.content.str_val);
                
                if (strcmp(s->scope, "global") == 0) {
                    // sw rt, offset(rs) -> sw rs_value, memloc($0)
                    emitAsmI(ASM_SW, 0, rs_value, s->memloc); 
                } else {
                    int offset = -(s->memloc + 1);
                    // sw rt, offset(rs) -> sw rs_value, offset($30)
                    emitAsmI(ASM_SW, 30, rs_value, offset); 
                }
                break;
            }
            case OP_STOREARR:{
                //TODO
                break;
            }
            case OP_LOADVAR:{
                //TODO
                // lw $rt, offset($fp) -> lw rt, offset(rs)
                break;
            }
            case OP_LOADARR:{
                //TODO
                break;
            }
            case OP_LOADIMM:{
                int rt = mapRegister(curr->result.content.str_val);
                int value = curr->arg1.content.val;
                // addi $rt, $0, value
                emitAsm(ASM_ADDI, rt, zero, 0, value, NULL);
                break;
            }
            case OP_ADD: {
                int rd = mapRegister(curr->result.content.str_val);
                int rs = mapRegister(curr->arg1.content.str_val);
                int rt = mapRegister(curr->arg2.content.str_val);
                // add rd, rs, rt (shamt = 0)
                emitAsmR(ASM_ADD, rs, rt, rd, 0); 
                break;
            }
            case OP_JUMP: {
                // j target
                emitAsmJ(ASM_J, curr->result.content.str_val);
                break;
            }

            case OP_LABEL: {
                // L1:
                emitAsmLabel(curr->result.content.str_val);
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