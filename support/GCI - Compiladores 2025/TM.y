%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

extern int yylex();
extern int yyparse();
extern FILE* yyin;

void yyerror(const char* s);

/* --- ESTRUTURAS DA ÁRVORE --- */

typedef enum { TYPE_OP, TYPE_VAL } NodeType;

typedef struct AST {
    NodeType type;
    union {
        char operator;
        float value;
    } data;
    struct AST *left;
    struct AST *right;
} AST;

/* --- PROTÓTIPOS DA ÁRVORE --- */
AST* createOpNode(char op, AST* left, AST* right);
AST* createValNode(float val);
float evalAST(AST* node);
void freeAST(AST* node);

/* Protótipos para a impressão bonita */
void printTree(AST* root);
int getHeight(AST* root);
void fillBuffer(AST* node, int level, int left, int right);

/* Variáveis globais para o "Canvas" de impressão */
#define MAX_LINES 20
#define MAX_WIDTH 80
char canvas[MAX_LINES][MAX_WIDTH];

/* ------------------ Quádruplas (TAC) ------------------ */

typedef struct {
    char *op;
    char *arg1;
    char *arg2;
    char *res;
} Quad;

Quad *quads = NULL;
int quad_count = 0;
int quad_capacity = 0;

char *strdup_safe(const char *s){
    if(!s) return NULL;
    char *r = malloc(strlen(s)+1);
    strcpy(r,s);
    return r;
}

void emit(const char *op, const char *a1, const char *a2, const char *res){
    if(quad_count + 1 > quad_capacity){
        quad_capacity = quad_capacity ? quad_capacity * 2 : 256;
        quads = realloc(quads, quad_capacity * sizeof(Quad));
    }
    quads[quad_count].op   = op ? strdup_safe(op) : NULL;
    quads[quad_count].arg1 = a1  ? strdup_safe(a1) : NULL;
    quads[quad_count].arg2 = a2  ? strdup_safe(a2) : NULL;
    quads[quad_count].res  = res ? strdup_safe(res) : NULL;
    quad_count++;
}

void clear_quads(){
    for(int i=0;i<quad_count;i++){
        if(quads[i].op) free(quads[i].op);
        if(quads[i].arg1) free(quads[i].arg1);
        if(quads[i].arg2) free(quads[i].arg2);
        if(quads[i].res) free(quads[i].res);
    }
    free(quads);
    quads = NULL;
    quad_count = 0;
    quad_capacity = 0;
}

int tmp_count = 0;
char *newtemp(){
    char buf[32];
    snprintf(buf,sizeof(buf),"$t%d", tmp_count++);
    return strdup_safe(buf);
}

/* Gera quádruplas a partir da AST; retorna "place" (string) que contém o resultado */
char *generate_quads(AST *node){
    if(!node) return NULL;

    if(node->type == TYPE_VAL){
        /* cria um temporário para a constante e emite LDI (load immediate): ( LDI, constante, -, temp ) */
        char buf[64];
        if(node->data.value == (int)node->data.value)
            snprintf(buf, sizeof(buf), "%d", (int)node->data.value);
        else
            snprintf(buf, sizeof(buf), "%.6g", node->data.value);
        char *t = newtemp();
        emit("LDI", buf, "-", t);
        return t;
    } else {
        /* operador binário: gerar para filhos, depois emitir operação */
        char *left_place = generate_quads(node->left);
        char *right_place = generate_quads(node->right);
        char opstr[4] = { node->data.operator, 0, 0, 0 };
        char *res = newtemp();
        emit(opstr, left_place, right_place, res);
        return res;
    }
}

void print_quads(FILE *out){
    for(int i=0;i<quad_count;i++){
        Quad *q = &quads[i];
        fprintf(out, "%3d: (%s, %s, %s, %s)\n",
                i,
                q->op ? q->op : "-",
                q->arg1 ? q->arg1 : "-",
                q->arg2 ? q->arg2 : "-",
                q->res  ? q->res  : "-");
    }
}

/* ------------------ TM generation ------------------ */

/* Utilitários para coletar símbolos não-numéricos */
char **sym_list = NULL;
int sym_count = 0;
int sym_cap = 0;

int is_number(const char *s){
    if(!s) return 0;
    int i=0; if(s[0]=='-'||s[0]=='+') i=1;
    int has_digit=0, has_dot=0;
    for(; s[i]; i++){
        if(isdigit((unsigned char)s[i])) has_digit=1;
        else if(s[i]=='.' && !has_dot) has_dot=1;
        else return 0;
    }
    return has_digit;
}

char *labelize(const char *name){
    if(!name) return NULL;
    /* replace characters not allowed with '_' and convert leading '$' to 't_' */
    char buf[128];
    int j=0;
    for(int i=0; name[i] && j < (int)sizeof(buf)-1; i++){
        char c = name[i];
        if(c=='$'){ buf[j++]='t'; buf[j++]='_'; continue; }
        if(isalnum((unsigned char)c) || c=='_') buf[j++]=c;
        else buf[j++]='_';
    }
    buf[j]=0;
    return strdup_safe(buf);
}

void add_symbol_if_needed(const char *s){
    if(!s) return;
    if(strcmp(s,"-")==0) return;
    if(is_number(s)) return;
    /* also skip labels like L0? keep them too as they are labels in text, not data */
    /* we will collect any non-number as a data symbol */
    for(int i=0;i<sym_count;i++) if(strcmp(sym_list[i], s)==0) return;
    if(sym_count + 1 > sym_cap){
        sym_cap = sym_cap ? sym_cap*2 : 128;
        sym_list = realloc(sym_list, sym_cap * sizeof(char*));
    }
    sym_list[sym_count++] = strdup_safe(s);
}

/* imprime seção de dados com rótulos para cada símbolo */
void print_data_section(FILE *out){
    fprintf(out, "; --- DATA SECTION (automatically generated) ---\n");
    for(int i=0;i<sym_count;i++){
        char *lab = labelize(sym_list[i]);
        fprintf(out, "%s:  .word 0\n", lab);
        free(lab);
    }
    fprintf(out, "\n");
}

/* imprime instrução TM com comentário */
void print_inst(FILE *out, const char *inst, const char *comment){
    if(comment)
        fprintf(out, "%-20s ; %s\n", inst, comment);
    else
        fprintf(out, "%s\n", inst);
}

/* gera TM a partir das quádruplas (apenas LDI e ops binários + - * /) */
void generate_tm_from_quads(FILE *out){
    /* coletar símbolos */
    for(int i=0;i<quad_count;i++){
        Quad *q = &quads[i];
        add_symbol_if_needed(q->arg1);
        add_symbol_if_needed(q->arg2);
        add_symbol_if_needed(q->res);
    }

    print_data_section(out);
    fprintf(out, "; --- TEXT SECTION (generated TM) ---\n");
    fprintf(out, "    ; using registers R1,R2,R3 for temporaries\n\n");

    for(int i=0;i<quad_count;i++){
        Quad *q = &quads[i];
        char comment[256];
        snprintf(comment, sizeof(comment), "quad %d: (%s, %s, %s, %s)",
                 i,
                 q->op?q->op:"-",
                 q->arg1?q->arg1:"-",
                 q->arg2?q->arg2:"-",
                 q->res?q->res:"-");
        if(q->op && strcmp(q->op,"LDI")==0){
            /* (LDI, const, -, res) => LDC R1,const ; ST R1, res */
            fprintf(out, "; %s\n", comment);
            fprintf(out, "LDC R1, %s\n", q->arg1);
            char *reslab = labelize(q->res);
            fprintf(out, "ST  R1, %s\n\n", reslab);
            free(reslab);
        } else if(q->op && strlen(q->op)==1 && (q->op[0]=='+'||q->op[0]=='-'||q->op[0]=='*'||q->op[0]=='/')){
            /* binary op */
            fprintf(out, "; %s\n", comment);
            /* load arg1 into R1 */
            if(q->arg1 && is_number(q->arg1)){
                fprintf(out, "LDC R1, %s\n", q->arg1);
            } else {
                char *arg1lab = labelize(q->arg1);
                fprintf(out, "LD  R1, %s\n", arg1lab);
                free(arg1lab);
            }
            /* load arg2 into R2 */
            if(q->arg2 && is_number(q->arg2)){
                fprintf(out, "LDC R2, %s\n", q->arg2);
            } else {
                char *arg2lab = labelize(q->arg2);
                fprintf(out, "LD  R2, %s\n", arg2lab);
                free(arg2lab);
            }
            /* perform op into R3 */
            if(q->op[0]=='+') fprintf(out, "ADD R3, R1, R2\n");
            else if(q->op[0]=='-') fprintf(out, "SUB R3, R1, R2\n");
            else if(q->op[0]=='*') fprintf(out, "MUL R3, R1, R2\n");
            else if(q->op[0]=='/') fprintf(out, "DIV R3, R1, R2\n");
            /* store result */
            char *reslab = labelize(q->res);
            fprintf(out, "ST  R3, %s\n\n", reslab);
            free(reslab);
        } else {
            /* operação desconhecida: só emite comentário */
            fprintf(out, "; %s -- (operation not translated)\n\n", comment);
        }
    }

    /* final */
    fprintf(out, "; --- end of generated TM ---\n");
}

/* cleanup sym_list */
void clear_sym_list(){
    for(int i=0;i<sym_count;i++) free(sym_list[i]);
    free(sym_list);
    sym_list = NULL;
    sym_count = 0;
    sym_cap = 0;
}

/* ----------------------------------------------------- */

%}

%union {
    int   ival;
    float fval;
    struct AST* node;
}

%token<ival> T_INT
%token<fval> T_FLOAT
%token T_MAIS T_MENOS T_LPAR T_RPAR T_MULT T_DIV
%token T_NEWLINE

%left T_MAIS T_MENOS
%left T_MULT T_DIV

%type<node> exp termo fator

%start calculation 

%%

calculation:
    | calculation line
    ;

line: exp T_NEWLINE { 
        printf("\n");
        printTree($1); // Chama a nova função de print
        printf("\nResultado: %.2f\n", evalAST($1));

        /* Geração de quádruplas a partir da AST */
        clear_quads(); /* limpa quádruplas anteriores */
        tmp_count = 0; /* reinicia temporários para esta expressão (opcional) */
        char *final_place = generate_quads($1);
        printf("\nQuádruplas geradas:\n");
        print_quads(stdout);

        /* Geração de TM a partir das quádruplas */
        printf("\n\n--- Código TM gerado ---\n");
        generate_tm_from_quads(stdout);
        clear_sym_list();

        /* opcional: mostrar where result is */
        if(final_place) printf("\nResultado em: %s\n", final_place);

        printf("---------------------\n> ");
        /* liberar recursos */
        if(final_place) free(final_place);
        clear_quads();
        freeAST($1);
    }
    | T_NEWLINE { printf("> "); }
    ;

exp : exp T_MAIS termo    { $$ = createOpNode('+', $1, $3); } 
    | exp T_MENOS termo   { $$ = createOpNode('-', $1, $3); } 
    | termo               { $$ = $1; }      
    ;

termo : termo T_MULT fator    { $$ = createOpNode('*', $1, $3); } 
      | termo T_DIV fator     { $$ = createOpNode('/', $1, $3); } 
      | fator                 { $$ = $1; }      
      ;

fator : T_LPAR exp T_RPAR { $$ = $2; }
      | T_INT             { $$ = createValNode((float)$1); }
      | T_FLOAT           { $$ = createValNode($1); }
      ;

%%

/* --- IMPLEMENTAÇÃO EM C --- */

AST* createOpNode(char op, AST* left, AST* right) {
    AST* node = (AST*) malloc(sizeof(AST));
    node->type = TYPE_OP;
    node->data.operator = op;
    node->left = left;
    node->right = right;
    return node;
}

AST* createValNode(float val) {
    AST* node = (AST*) malloc(sizeof(AST));
    node->type = TYPE_VAL;
    node->data.value = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

float evalAST(AST* node) {
    if (!node) return 0;
    if (node->type == TYPE_VAL) return node->data.value;
    
    float l = evalAST(node->left);
    float r = evalAST(node->right);
    
    switch (node->data.operator) {
        case '+': return l + r;
        case '-': return l - r;
        case '*': return l * r;
        case '/': return (r != 0) ? l / r : 0;
    }
    return 0;
}

void freeAST(AST* node) {
    if (!node) return;
    freeAST(node->left);
    freeAST(node->right);
    free(node);
}

/* --- LÓGICA DE IMPRESSÃO BONITA (PRETTY PRINT) --- */

int getHeight(AST* root) {
    if (!root) return 0;
    int lh = getHeight(root->left);
    int rh = getHeight(root->right);
    return (lh > rh ? lh : rh) + 1;
}

void fillBuffer(AST* node, int level, int left, int right) {
    if (!node || level >= MAX_LINES) return;

    int width = right - left;
    int mid = left + width / 2;

    char str[16];
    if (node->type == TYPE_OP) {
        sprintf(str, "(%c)", node->data.operator);
    } else {
        if (node->data.value == (int)node->data.value)
            sprintf(str, "%.0f", node->data.value);
        else
            sprintf(str, "%.1f", node->data.value);
    }

    int len = strlen(str);
    int start = mid - len / 2;
    if (start < 0) start = 0;
    if (start + len >= MAX_WIDTH) start = MAX_WIDTH - len - 1;

    strncpy(&canvas[level * 2][start], str, len);

    if (node->left) {
        int childMid = left + (mid - left) / 2;
        int slashPos = (mid + childMid) / 2; 
        if (slashPos >= 0 && slashPos < MAX_WIDTH) 
             canvas[level * 2 + 1][slashPos] = '/';
        fillBuffer(node->left, level + 1, left, mid);
    }

    if (node->right) {
        int childMid = mid + (right - mid) / 2;
        int backSlashPos = (mid + childMid) / 2;
        if (backSlashPos >= 0 && backSlashPos < MAX_WIDTH)
            canvas[level * 2 + 1][backSlashPos] = '\\';
        fillBuffer(node->right, level + 1, mid, right);
    }
}

void printTree(AST* root) {
    for (int i = 0; i < MAX_LINES; i++) {
        for (int j = 0; j < MAX_WIDTH; j++) {
            canvas[i][j] = ' ';
        }
        canvas[i][MAX_WIDTH - 1] = '\0';
    }

    int h = getHeight(root);
    if(h==0) return;
    fillBuffer(root, 0, 0, MAX_WIDTH);

    for (int i = 0; i < h * 2; i++) {
        int j = MAX_WIDTH - 2;
        while (j > 0 && canvas[i][j] == ' ') j--;
        canvas[i][j+1] = '\0';
        printf("%s\n", canvas[i]);
    }
}

int main(int argc, char **argv){
    if(argc > 1) yyin = fopen(argv[1], "r");
    else {
        printf("Digite uma expressão (ex: 2 * (3 + 4)):\n> ");
        yyin = stdin;
    }

    do { yyparse(); } while(!feof(yyin));

    if (yyin != stdin) fclose(yyin);
    return 0;
}

void yyerror(const char* s) {
    fprintf(stderr, "Erro: %s\n", s);
    exit(1);
}
