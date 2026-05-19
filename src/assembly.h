typedef enum {
    ASM_ADD, ASM_SUB, ASM_MUL, ASM_DIV,
    ASM_ADDI, ASM_LW, ASM_SW,
    ASM_BEQ, ASM_BNE, ASM_BLT, ASM_BGT, ASM_BLE, ASM_BGE,
    ASM_J, ASM_JAL, ASM_JR, ASM_HALT,
    ASM_IN, ASM_OUT
} AsmOp;

typedef struct AsmInstruction {
    AsmOp op;
    int rd;
    int rs;
    int rt;
    int imm;
    char *label_name;
    struct AsmInstruction *next;
} AsmInstr;

extern AsmInstr *headAsm;
extern AsmInstr *currentAsm;