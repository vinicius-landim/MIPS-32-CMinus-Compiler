#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include "symtab.h"
#include "cgen.h"
#include "assembly.h"
#include "util.h"

AsmInstr *headAsm = NULL;
AsmInstr *currentAsm = NULL;

int getPhysicalReg(int virtual_reg) {
    if (virtual_reg <= 0) return 0; // Fallback
    return ((virtual_reg - 1) % 27) + 1; 
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
    AsmInstr *instr = createNode(op, FORMAT_R);
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
    AsmInstr *instr = createNode(op, FORMAT_J);
    instr->type.j.target_name = copyString(target);
}

void emitAsmLabel(char *label) {
    AsmInstr *instr = createNode(ASM_LABEL, FORMAT_LABEL);
    instr->type.label.label_name = copyString(label);
}

void generateAssembly(Quad *headGCI){
    Quad *curr = headGCI;
    headAsm = NULL;
    currentAsm = NULL;

    // registradores especiais MIPS
    int zero = 0;
    int temp = 28;
    int sp = 29;
    int fp = 30;
    int ra = 31;

    while(curr != NULL){
        switch(curr->op){
            case OP_FUNC: {
                Symbol s = curr->arg1.content.s_node;
                emitAsmLabel(s->name);
                //sw $fp, 0($sp): salva o $fp da função anterior na pilha
                emitAsmI(ASM_SW, sp, fp, 0);
                //add $fp, $sp, $0: O $fp atual trava na base do frame
                emitAsmR(ASM_ADD, sp, zero, fp, 0);
                break;
            }
            case OP_ENDFUNC: {
                // add $sp, $fp, $0: libera todas as variáveis locais movendo o $sp de volta ao topo
                emitAsmR(ASM_ADD, fp, zero, sp, 0);
                // lw $fp, 0($sp): restaura o $fp da função que chamou a função atual
                emitAsmI(ASM_LW, sp, fp, 0);
                // jr $ra
                emitAsmR(ASM_JR, ra, zero, zero, 0);
                break;
            }
            case OP_ALLOCVAR: {
                // addi $sp, $sp, -1 
                emitAsmI(ASM_ADDI, sp, sp, -1);
                break;
            }
            case OP_ALLOCARR: {
                int size = curr->arg1.content.imm; 
                // addi $sp, $sp, -size
                emitAsmI(ASM_ADDI, sp, sp, -size);
                break;
            }
            case OP_STOREVAR: {
                Symbol s = curr->result.content.s_node;
                int rs_value = getPhysicalReg(curr->arg1.content.reg_id);
                
                if (strcmp(s->scope, "global") == 0) {
                    emitAsmI(ASM_SW, zero, rs_value, s->memloc); 
                } else {
                    int offset = -(s->memloc + 1);
                    emitAsmI(ASM_SW, fp, rs_value, offset); 
                }
                break;
            }
            case OP_STOREARR: {
                Symbol s = curr->result.content.s_node;
                int rs_value = getPhysicalReg(curr->arg1.content.reg_id);
                int rs_index = getPhysicalReg(curr->arg2.content.reg_id);
                
                if (strcmp(s->scope, "global") == 0) {
                    // global (cresce pra cima): addr = $0 + rs_index
                    // add $28, $0, rs_index
                    emitAsmR(ASM_ADD, zero, rs_index, temp, 0);
                    // sw rs_value, memloc($28)
                    emitAsmI(ASM_SW, temp, rs_value, s->memloc);
                } else {
                    // local (cresce pra baixo): addr = $fp - rs_index
                    int offset = -(s->memloc + 1);
                    // sub $28, $fp, rs_index
                    emitAsmR(ASM_SUB, fp, rs_index, temp, 0);
                    // sw rs_value, offset($28)
                    emitAsmI(ASM_SW, temp, rs_value, offset);
                }
                break;
            }
            case OP_LOADVAR: {
                Symbol s = curr->arg1.content.s_node;
                int rt_dest = getPhysicalReg(curr->result.content.reg_id);
                
                if(strcmp(s->scope, "global") == 0){
                    emitAsmI(ASM_LW, zero, rt_dest, s->memloc); 
                } else {
                    int offset = -(s->memloc+1);
                    emitAsmI(ASM_LW, fp, rt_dest, offset);
                }
                break;
            }
            case OP_LOADARR: {
                Symbol s = curr->arg1.content.s_node;
                int rt_dest = getPhysicalReg(curr->result.content.reg_id);
                int rs_index = getPhysicalReg(curr->arg2.content.reg_id);
                
                if (strcmp(s->scope, "global") == 0) {
                    // add $28, $0, rs_index
                    emitAsmR(ASM_ADD, zero, rs_index, temp, 0);
                    // lw rt_dest, memloc($28)
                    emitAsmI(ASM_LW, temp, rt_dest, s->memloc);
                } else {
                    int offset = -(s->memloc + 1);
                    // sub $28, $fp, rs_index
                    emitAsmR(ASM_SUB, fp, rs_index, temp, 0);
                    // lw rt_dest, offset($28)
                    emitAsmI(ASM_LW, temp, rt_dest, offset);
                }
                break;
            }
            case OP_LOADIMM: {
                int rt_dest = getPhysicalReg(curr->result.content.reg_id);
                int value = curr->arg1.content.imm;
                // addi rt, $0, value
                emitAsmI(ASM_ADDI, zero, rt_dest, value);
                break;
            }
            case OP_ADD: {
                int rd = getPhysicalReg(curr->result.content.reg_id);
                int rs = getPhysicalReg(curr->arg1.content.reg_id);
                int rt = getPhysicalReg(curr->arg2.content.reg_id);
                emitAsmR(ASM_ADD, rs, rt, rd, 0); 
                break;
            }
            case OP_SUB: {
                int rd = getPhysicalReg(curr->result.content.reg_id);
                int rs = getPhysicalReg(curr->arg1.content.reg_id);
                int rt = getPhysicalReg(curr->arg2.content.reg_id);
                emitAsmR(ASM_SUB, rs, rt, rd, 0); 
                break;
            }
            case OP_MUL: {
                int rd = getPhysicalReg(curr->result.content.reg_id);
                int rs = getPhysicalReg(curr->arg1.content.reg_id);
                int rt = getPhysicalReg(curr->arg2.content.reg_id);
                emitAsmR(ASM_MUL, rs, rt, rd, 0); 
                break;
            }
            case OP_DIV: {
                int rd = getPhysicalReg(curr->result.content.reg_id);
                int rs = getPhysicalReg(curr->arg1.content.reg_id);
                int rt = getPhysicalReg(curr->arg2.content.reg_id);
                emitAsmR(ASM_DIV, rs, rt, rd, 0); 
                break;
            }
            case OP_JUMP: {
                // j target (Lê do tipo de variável específico para rótulos)
                emitAsmJ(ASM_J, curr->result.content.label_name);
                break;
            }
            case OP_LABEL: {
                emitAsmLabel(curr->result.content.label_name);
                break;
            }
            case OP_HALT: {
                emitAsmR(ASM_HALT, zero, zero, zero, 0);
                break;
            }
            default: break;
        }
        curr = curr->next;
    }
}

static const char* asmOpToString(AsmOp op) {
    switch(op) {
        case ASM_ADD:   return "add";
        case ASM_SUB:   return "sub";
        case ASM_MUL:   return "mul";
        case ASM_DIV:   return "div";
        case ASM_ADDI:  return "addi";
        case ASM_LW:    return "lw";
        case ASM_SW:    return "sw";
        case ASM_BEQ:   return "beq";
        case ASM_BNE:   return "bne";
        case ASM_BLT:   return "blt";
        case ASM_BGT:   return "bgt";
        case ASM_BLE:   return "ble";
        case ASM_BGE:   return "bge";
        case ASM_J:     return "j";
        case ASM_JAL:   return "jal";
        case ASM_JR:    return "jr";
        case ASM_HALT:  return "halt";
        case ASM_IN:    return "in";
        case ASM_OUT:   return "out";
        default:        return "unknown";
    }
}

static const char* printReg(int reg_id) {
    static const char* reg_names[32] = {
        "$zero",
        "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$t8", "$t9", "$t10", "$t11", "$t12", "$t13", "$t14", "$t15", "$t16", "$t17", "$t18", "$t19", "$t20", "$t21", "$t22", "$t23", "$t24", "$t25", "$t26", "$t27", "$t28",
        "$sp", // $sp = $29
        "$fp", // $fp = #30
        "$ra"  // $ra = $31
    };

    if (reg_id >= 0 && reg_id <= 31) {
        return reg_names[reg_id];
    }
    
    return "$?"; //fallback
}

void printAssembly(FILE *listing) {
    AsmInstr *curr = headAsm;

    while(curr != NULL){
        if(curr->format == FORMAT_LABEL) {
            fprintf(listing, "%s:\n", curr->type.label.label_name);
        } 
        else {
            fprintf(listing, "    "); 
            const char* opName = asmOpToString(curr->op);

            switch (curr->format) {
                case FORMAT_R:{
                    if (curr->op == ASM_JR) {
                        fprintf(listing, "%s %s\n", opName, printReg(curr->type.r.rs));
                    } else if (curr->op == ASM_HALT) {
                        fprintf(listing, "halt\n");
                    } else {
                        // op rd, rs, rt
                        fprintf(listing, "%s %s, %s, %s\n", opName, printReg(curr->type.r.rd), printReg(curr->type.r.rs), printReg(curr->type.r.rt));
                    }
                    break;
                }
                case FORMAT_I:{
                    if (curr->op == ASM_LW || curr->op == ASM_SW) {
                        // memória: op rt, offset(rs) (Ex: lw $1, -2($30))
                        fprintf(listing, "%s %s, %d(%s)\n", opName, printReg(curr->type.i.rt), curr->type.i.imm, printReg(curr->type.i.rs));
                    }
                    else if (curr->op == ASM_BEQ || curr->op == ASM_BNE || curr->op == ASM_BLT || curr->op == ASM_BGT || curr->op == ASM_BLE || curr->op == ASM_BGE) {
                        // branch: op rs, rt, offset (Ex: beq $1, $2, 15)
                        fprintf(listing, "%s %s, %s, %d\n", opName, printReg(curr->type.i.rs), printReg(curr->type.i.rt), curr->type.i.imm);                    
                    } else {
                        // imediato: op rt, rs, imm (Ex: addi $1, $0, 5)
                        fprintf(listing, "%s %s, %s, %d\n", opName, printReg(curr->type.i.rt), printReg(curr->type.i.rs), curr->type.i.imm);
                    }
                    break;
                }
                case FORMAT_J:{
                    // tipo J: op target (Ex: j L1 / jal main)
                    fprintf(listing, "%s %s\n", opName, curr->type.j.target_name);
                    break;
                }
                default: break;
            }
        }
        curr = curr->next;
    }
}