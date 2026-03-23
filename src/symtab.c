#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

//LOUDEN (2004, p.517-9)
#define SIZE 211
#define SHIFT 4

//Lista com número da linha de todas as ocorrências de uma variável
typedef struct LineListNode{
    int lineNo;
    struct LineListNode *next;
} *LineList;

//Lista de variáveis em uma bucket
typedef struct BucketListNode{
    char *name;
    LineList lines;
    int memloc;
    struct BucketListNode *next;
} *BucketList;

//Tabela hash
static BucketList hashTable[SIZE];

static int hash(char *key){
    int temp = 0;
    int i = 0;
    while(key[i] != '\0'){
        temp = ((temp<<SHIFT) + key[i]) % SIZE;
        ++i;
    }
    return temp;
}
//Inserção na tabela de símbolos
void st_insert (char *name, int lineNo, int loc){
    int h = hash(name);
    BucketList b_node = hashTable[h]; //Endereço para um novo nó na bucket
    while ((b_node != NULL) && (strcmp(name, b_node->name) != 0))
        b_node = b_node->next;
    if(b_node == NULL) {
        // Primeiro nó na posição da tabela
        b_node->name = name;
        b_node->lines = (LineList)malloc(sizeof(struct LineListNode));
        b_node->lines->lineNo=lineNo;
        b_node->memloc = loc;
        b_node->lines->next = NULL;
        b_node->next = hashTable[h];
        hashTable[h] = b_node;
    } else {
        // Nó da variável já inserido na posição. Assim, insere-se apenas a nova ocorrência na LineList
        LineList line_node = b_node->lines;
        while(line_node->next != NULL)
            line_node = line_node->next;
        line_node->next = (LineList)malloc(sizeof(struct LineListNode));
        line_node->next->lineNo = lineNo;
        line_node->next->next = NULL;
    }
}

int st_lookup(char *name){
    int h = hash(name);
    BucketList b_node = hashTable[h];
    while((b_node != NULL) && (strcmp(name, b_node->name) != 0))
        b_node = b_node->next;
    if(b_node == NULL)
        return -1;
    else 
        return 1;
}