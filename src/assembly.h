typedef enum {
    ASM_ADD, ASM_SUB, ASM_MUL, ASM_DIV,
    ASM_ADDI, ASM_LW, ASM_SW,
    ASM_BEQ, ASM_BNE, ASM_BLT, ASM_BGT, ASM_BLE, ASM_BGE,
    ASM_LABEL, ASM_J, ASM_JAL, ASM_JR, ASM_HALT,
    ASM_IN, ASM_OUT
} AsmOp;

typedef enum {FORMAT_R, FORMAT_I, FORMAT_J, FORMAT_LABEL} AsmFormat;

typedef struct AsmInstruction {
    AsmOp op;
    AsmFormat format; 
    
    union{
        struct{ 
            int rs;
            int rt;
            int rd;
            int shamt;
        } r;
        struct{
            int rs;
            int rt;
            int imm;
            char *label_name;
        } i;
        struct {
            char *target_name;
        } j;
        struct {
            char *label_name;
        } label;
    } type;

    struct AsmInstruction *next;
} AsmInstr;

void generateAssembly(Quad *headGCI);
void printAssembly(FILE *listing);

extern AsmInstr *headAsm;
extern AsmInstr *currentAsm;