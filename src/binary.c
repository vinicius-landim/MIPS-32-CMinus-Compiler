#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "assembly.h"

//tipo R
#define OPCODE_R_TYPE 0b000000
#define FUNCT_ADD     0b000000
#define FUNCT_SUB     0b000001
#define FUNCT_MUL     0b000010
#define FUNCT_DIV     0b000011
#define FUNCT_JR      0b001000

//tipo I
#define OPCODE_ADDI   0b000001
#define OPCODE_LW     0b000101
#define OPCODE_SW     0b000110
#define OPCODE_BEQ    0b001000
#define OPCODE_BNE    0b001001
#define OPCODE_BLT    0b001010
#define OPCODE_BGT    0b001011
#define OPCODE_BLE    0b001100
#define OPCODE_BGE    0b001101
#define OPCODE_IN     0b001110
#define OPCODE_OUT    0b001111
#define OPCODE_HALT   0b010011

//tipo J
#define OPCODE_J      0b010000
#define OPCODE_JAL    0b010001

typedef struct LabelNode {
    char *name;
    int address; //endereço ROM 
    struct LabelNode *next;
} LabelNode;

static LabelNode *labelTable = NULL;

static void insertLabel(char *name, int address) {
    LabelNode *newNode = (LabelNode*)malloc(sizeof(LabelNode));
    newNode->name = strdup(name);
    newNode->address = address;
    newNode->next = labelTable;
    labelTable = newNode;
}

static int getLabelAddress(char *name) {
    LabelNode *curr = labelTable;
    while (curr != NULL) {
        if (strcmp(curr->name, name) == 0) 
            return curr->address;
        curr = curr->next;
    }
    return -1;
}

static void printBinaryString(FILE *out, uint32_t instruction) {
    for (int i = 31; i >= 0; i--) {
        int bit = (instruction >> i) & 1;
        fprintf(out, "%d", bit);
    }
    fprintf(out, "\n");
}

static void mapLabels(AsmInstr *head) {
    AsmInstr *curr = head;
    int rom_address = 0;

    while (curr != NULL) {
        if (curr->format == FORMAT_LABEL) {
            insertLabel(curr->type.label.label_name, rom_address);
        } else {
            rom_address++; 
        }
        curr = curr->next;
    }
}

static void generateMachineCode(AsmInstr *head, FILE *out) {
    AsmInstr *curr = head;
    int rom_address = 0;

    while (curr != NULL) {
        if (curr->format == FORMAT_LABEL) {
            curr = curr->next;
            continue; //labels não geram binário
        }

        uint32_t machine_code = 0;
        uint32_t opcode = 0, rs = 0, rt = 0, rd = 0, shamt = 0, funct = 0, imm = 0, address = 0;

        switch (curr->format) {
            case FORMAT_R: {
                // MIPS Tipo R: [opcode:6] [rs:5] [rt:5] [rd:5] [shamt:5] [funct:6]
                opcode = OPCODE_R_TYPE;
                rs = curr->type.r.rs;
                rt = curr->type.r.rt;
                rd = curr->type.r.rd;
                shamt = curr->type.r.shamt;

                switch (curr->op) {
                    case ASM_ADD:{
                        funct = FUNCT_ADD;
                        break;
                    }
                    case ASM_SUB:{
                        funct = FUNCT_SUB;
                        break;
                    }
                    case ASM_MUL:{
                        funct = FUNCT_MUL;
                        break;
                    }
                    case ASM_DIV:{
                        funct = FUNCT_DIV;
                        break;
                    }
                    case ASM_JR:{
                        funct = FUNCT_JR;
                        break;
                    }
                    default: break;
                }
                machine_code = (opcode << 26) | (rs << 21) | (rt << 16) | (rd << 11) | (shamt << 6) | funct;
                break;
            }
            
            case FORMAT_I: {
                // MIPS Tipo I: [opcode:6] [rs:5] [rt:5] [immediate:16]
                rs = curr->type.i.rs;
                rt = curr->type.i.rt;

                switch (curr->op) {
                    case ASM_ADDI:{
                        opcode = OPCODE_ADDI;
                        imm = curr->type.i.imm & 0xFFFF;
                        break;
                    }
                    case ASM_LW:{
                        opcode = OPCODE_LW;
                        imm = curr->type.i.imm & 0xFFFF;
                        break;
                    }
                    case ASM_SW:{
                        opcode = OPCODE_SW;
                        imm = curr->type.i.imm & 0xFFFF;
                        break;
                    }
                    case ASM_IN:{
                        opcode = OPCODE_IN;   
                        imm = 0; // IN não usa imediato
                        break;
                    }   
                    case ASM_OUT:{
                        opcode = OPCODE_OUT;  
                        imm = 0; // OUT não usa imediato
                        break;
                    }  
                    case ASM_HALT:{
                        opcode = OPCODE_HALT;  
                        imm = 0; // HALT agora mora aqui e não usa imediato
                        break;
                    }
                    case ASM_BEQ:
                    case ASM_BNE:
                    case ASM_BLT:
                    case ASM_BGT:
                    case ASM_BLE:
                    case ASM_BGE:
                        if (curr->op == ASM_BEQ) opcode = OPCODE_BEQ;
                        else if (curr->op == ASM_BNE) opcode = OPCODE_BNE;
                        else if (curr->op == ASM_BLT) opcode = OPCODE_BLT;
                        else if (curr->op == ASM_BGT) opcode = OPCODE_BGT;
                        else if (curr->op == ASM_BLE) opcode = OPCODE_BLE;
                        else if (curr->op == ASM_BGE) opcode = OPCODE_BGE;
                        
                        //cálculo offset
                        int target_address = getLabelAddress(curr->type.i.label_name);
                        int offset = target_address - rom_address - 1; 
                        imm = offset & 0xFFFF; 
                        break;

                    default: break;
                }

                machine_code = (opcode << 26) | (rs << 21) | (rt << 16) | imm;
                break;
            }
            
            case FORMAT_J: {
                // MIPS Tipo J: [opcode:6] [address:26]
                switch (curr->op) {
                    case ASM_J:{
                        opcode = OPCODE_J;
                        break;
                    }
                    case ASM_JAL:{
                        opcode = OPCODE_JAL;
                        break;
                    }
                    default: break;
                }
                
                address = getLabelAddress(curr->type.j.target_name);
                machine_code = (opcode << 26) | (address & 0x3FFFFFF); 
                break;
            }

            default: break;
        }
        
        printBinaryString(out, machine_code);
        rom_address++;
        curr = curr->next;
    }
}

void generateBinary(AsmInstr *head, FILE *out) {
    mapLabels(head);
    generateMachineCode(head, out);
}