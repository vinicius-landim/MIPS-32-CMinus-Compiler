#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include "symtab.h"
#include "cgen.h"
#include "assembly.h"
#include "util.h"

#define RAM_SIZE 4096
#define MAX_PENDING_PARAMS 8
AsmInstr *headAsm = NULL;
AsmInstr *currentAsm = NULL;

static int pendingParams[MAX_PENDING_PARAMS];
static int pendingParamCount = 0;

static void insertParamList(int reg) {
    if (pendingParamCount >= MAX_PENDING_PARAMS) {
        fprintf(stderr, "Erro: quantidade maxima de parametros excedida (%d).\n", MAX_PENDING_PARAMS);
        exit(1);
    }
    pendingParams[pendingParamCount++] = reg;
}

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
    instr->type.i.label_name = NULL;
}

void emitAsmIBranch(AsmOp op, int rs, int rt, char *target) {
    AsmInstr* instr = createNode(op, FORMAT_I);
    instr->type.i.rs = rs;
    instr->type.i.rt = rt;
    instr->type.i.imm = 0;
    instr->type.i.label_name = copyString(target);
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
    pendingParamCount = 0;

    // registradores especiais MIPS
    int zero = 0;
    int temp = 28;
    int sp = 29;
    int fp = 30;
    int ra = 31;

    emitAsmI(ASM_ADDI, zero, sp, RAM_SIZE);
    emitAsmI(ASM_ADDI, zero, fp, RAM_SIZE);
    emitAsmJ(ASM_J, "main");
    while(curr != NULL){
        switch(curr->op){
            case OP_PARAM: {
                int rt = getPhysicalReg(curr->result.content.reg_id);
                insertParamList(rt);
                break;
            }
            case OP_FUNC: {
                Symbol s = curr->arg1.content.s_node;
                emitAsmLabel(s->name);

                //armazenar $ra (após jal) no primeiro slot do frame
                emitAsmI(ASM_SW, fp, ra, -1);
                break;
            }
            case OP_ENDFUNC: {
                //restaura $ra
                emitAsmI(ASM_LW, fp, ra, -1);
                
                //ajusta sp para a posição: $sp original estava exata 1 posição acima do ofp
                emitAsmI(ASM_ADDI, fp, sp, 1);
                
                //restaura $ofp
                emitAsmI(ASM_LW, fp, fp, 0);
                
                //jr para retorno
                emitAsmR(ASM_JR, ra, zero, zero, 0);
                break;
            }
            case OP_RETURN: {
                //registrador de retorno //TODO DEFINIR
                if (curr->result.kind != OPND_EMPTY) {
                    int rt = getPhysicalReg(curr->result.content.reg_id);
                    emitAsmR(ASM_ADD, rt, zero, temp, 0); 
                }

                //sequência de ENDFUNC
                emitAsmI(ASM_LW, fp, ra, -1);
                emitAsmI(ASM_ADDI, fp, sp, 1);
                emitAsmI(ASM_LW, fp, fp, 0);
                emitAsmR(ASM_JR, ra, zero, zero, 0);
                break;
            }
            case OP_CALL: {
                Symbol s = curr->arg1.content.s_node;
                int numParams = curr->arg2.content.imm;
                //$ofp armazenado 
                emitAsmI(ASM_ADDI, sp, sp, -1);
                emitAsmI(ASM_SW, sp, fp, 0);
                
                //$fp deslocado para a base
                emitAsmR(ASM_ADD, sp, zero, fp, 0);
                //reservar espaço do $ra
                emitAsmI(ASM_ADDI, sp, sp, -1);
                
                //empilhar os parâmetros sequencialmente
                int startIdx = pendingParamCount - numParams;
                for (int i = startIdx; i < pendingParamCount; i++) {
                    emitAsmI(ASM_ADDI, sp, sp, -1);
                    emitAsmI(ASM_SW, sp, pendingParams[i], 0);
                }
                pendingParamCount -= numParams;

                // jal funct
                emitAsmJ(ASM_JAL, s->name);

                //salvar valor retornado em um registrador
                int rt_return = getPhysicalReg(curr->result.content.reg_id);
                emitAsmR(ASM_ADD, temp, zero, rt_return, 0);

                break;
            }
            case OP_ALLOCVAR: {
                // Symbol s = curr->result.content.s_node;
                // if(strcmp(s->scope, "global") == 0){
                //     //memloc da tabela define a posição a partir de $zero 
                // } else {
                //     // addi $sp, $sp, -1 
                //     emitAsmI(ASM_ADDI, sp, sp, -1); //TODO: necessário?
                // }
                break;
            }
            case OP_ALLOCARR: {
                // Symbol s = curr->result.content.s_node;
                // int size = curr->arg1.content.imm; 
                // if(strcmp(s->scope, "global") == 0){
                //     //memloc da tabela define a posição a partir de $zero 
                // } else {
                //     //addi $sp, $sp, -size
                //     emitAsmI(ASM_ADDI, sp, sp, -size); //TODO: necessário?
                // }
                break;
            }
            case OP_STOREVAR: {
                Symbol s = curr->result.content.s_node;
                int rt = getPhysicalReg(curr->arg1.content.reg_id);
                
                if (strcmp(s->scope, "global") == 0) {
                    emitAsmI(ASM_SW, zero, rt, s->memloc); //inserção na base da memória
                } else {
                    int frameloc = -(s->memloc + 2);
                    emitAsmI(ASM_SW, fp, rt, frameloc);
                }
                break;
            }
            case OP_STOREARR: {
                Symbol s = curr->result.content.s_node;
                int rs_value = getPhysicalReg(curr->arg1.content.reg_id);
                int rs_index = getPhysicalReg(curr->arg2.content.reg_id);
                
                if (strcmp(s->scope, "global") == 0) {
                    emitAsmR(ASM_ADD, zero, rs_index, temp, 0); // temp = index
                    emitAsmI(ASM_SW, temp, rs_value, s->memloc); // mem[index + memloc] = value
                } else {
                    int frameloc = -(s->memloc+2);
                    //carrega o ponteiro da array para o $temp
                    emitAsmI(ASM_LW, fp, temp, frameloc);
                    //temp = temp + index
                    emitAsmR(ASM_ADD, temp, rs_index, temp, 0);
                    //guarda o valor no endereço exato
                    emitAsmI(ASM_SW, temp, rs_value, 0); // sw value, 0(temp)
                }
                break;
            }
            case OP_LOADVAR: {
                Symbol s = curr->arg1.content.s_node;
                int rt_dest = getPhysicalReg(curr->result.content.reg_id);
                
                if (strcmp(s->scope, "global") == 0) {
                    emitAsmI(ASM_LW, zero, rt_dest, s->memloc); //$gp = $zero
                } else {
                    //duas primeiras posições destinadas para o $ofp e $ra
                    int frameloc = -(s->memloc+2);
                    emitAsmI(ASM_LW, fp, rt_dest, frameloc);
                }
                break;
            }
            case OP_LOADARR: {
                Symbol s = curr->arg1.content.s_node;
                int rt_dest = getPhysicalReg(curr->result.content.reg_id);
                int rs_index = getPhysicalReg(curr->arg2.content.reg_id);
                
                if (strcmp(s->scope, "global") == 0) {
                    emitAsmR(ASM_ADD, zero, rs_index, temp, 0); // temp = index
                    emitAsmI(ASM_LW, temp, rt_dest, s->memloc); // dest = mem[index + memloc]
                } else {
                    int frameloc = -(s->memloc+2);
                    //carrega o ponteiro do frame para o $temp
                    emitAsmI(ASM_LW, fp, temp, frameloc);
                    //temp = temp + index
                    emitAsmR(ASM_ADD, temp, rs_index, temp, 0);
                    //lê o valor no endereço exato!
                    emitAsmI(ASM_LW, temp, rt_dest, 0); // lw dest, 0(temp)
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
                // j target
                emitAsmJ(ASM_J, curr->result.content.label_name);
                break;
            }
            case OP_LABEL: {
                emitAsmLabel(curr->result.content.label_name);
                break;
            } 
            case OP_BEQ: {
                int rs = getPhysicalReg(curr->result.content.reg_id);
                int rt = getPhysicalReg(curr->arg1.content.reg_id);
                emitAsmIBranch(ASM_BEQ, rs, rt, curr->arg2.content.label_name);
                break;
            }
            case OP_BNE: {
                int rs = getPhysicalReg(curr->result.content.reg_id);
                int rt = getPhysicalReg(curr->arg1.content.reg_id);
                emitAsmIBranch(ASM_BNE, rs, rt, curr->arg2.content.label_name);
                break;
            }
            case OP_BGT: {
                int rs = getPhysicalReg(curr->result.content.reg_id);
                int rt = getPhysicalReg(curr->arg1.content.reg_id);
                emitAsmIBranch(ASM_BGT, rs, rt, curr->arg2.content.label_name);
                break;
            }
            case OP_BLT: {
                int rs = getPhysicalReg(curr->result.content.reg_id);
                int rt = getPhysicalReg(curr->arg1.content.reg_id);
                emitAsmIBranch(ASM_BLT, rs, rt, curr->arg2.content.label_name);
                break;
            }
            case OP_BGE: {
                int rs = getPhysicalReg(curr->result.content.reg_id);
                int rt = getPhysicalReg(curr->arg1.content.reg_id);
                emitAsmIBranch(ASM_BGE, rs, rt, curr->arg2.content.label_name);
                break;
            }
            case OP_BLE: {
                int rs = getPhysicalReg(curr->result.content.reg_id);
                int rt = getPhysicalReg(curr->arg1.content.reg_id);
                emitAsmIBranch(ASM_BLE, rs, rt, curr->arg2.content.label_name);
                break;
            }
            case OP_IN: {
                int rt_dest = getPhysicalReg(curr->result.content.reg_id);
                emitAsmI(ASM_IN, zero, rt_dest, 0);
                break;
            }
            case OP_OUT: {
                int rs_src = getPhysicalReg(curr->arg1.content.reg_id);
                emitAsmI(ASM_OUT, rs_src, zero, 0);
                break;
            }
            case OP_HALT: {
                emitAsmR(ASM_HALT, zero, zero, zero, 0); //TODO: minha ISA tem HALT como tipo J
                break;
            }
            default: break;
        }
        curr = curr->next;
    }
}

static const char* asmOpToString(AsmOp op){
    switch(op){
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

static const char* printReg(int reg_id){
    static const char* reg_names[32] = {
        "$zero",
        "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$t8", "$t9", "$t10", "$t11", "$t12", "$t13", "$t14", "$t15", "$t16", "$t17", "$t18", "$t19", "$t20", "$t21", "$t22", "$t23", "$t24", "$t25", "$t26", "$t27", "$t28",
        "$sp", // $sp = $29
        "$fp", // $fp = #30
        "$ra"  // $ra = $31
    };

    if(reg_id >= 0 && reg_id <= 31){
        return reg_names[reg_id];
    }
    
    return "$?"; //fallback
}

void printAssembly(FILE *listing){
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
                    if (curr->op == ASM_IN) {
                        fprintf(listing, "%s %s\n", opName, printReg(curr->type.i.rt));
                    } 
                    else if (curr->op == ASM_OUT) {
                        fprintf(listing, "%s %s\n", opName, printReg(curr->type.i.rs));
                    }
                    else if (curr->op == ASM_LW || curr->op == ASM_SW) {
                        // memória: op rt, offset(rs) (Ex: lw $1, -2($30))
                        fprintf(listing, "%s %s, %d(%s)\n", opName, printReg(curr->type.i.rt), curr->type.i.imm, printReg(curr->type.i.rs));
                    }
                    else if (curr->op == ASM_BEQ || curr->op == ASM_BNE || curr->op == ASM_BLT || curr->op == ASM_BGT || curr->op == ASM_BLE || curr->op == ASM_BGE) {
                        // branch: op rs, rt, offset (Ex: beq $1, $2, 15)
                        fprintf(listing, "%s %s, %s, %s\n", opName, printReg(curr->type.i.rs), printReg(curr->type.i.rt), curr->type.i.label_name);                    
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