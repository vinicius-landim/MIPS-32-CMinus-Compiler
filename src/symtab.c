#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//LOUDEN (2004, p.517-9)
#define SIZE 211
#define SHIFT 4

static int hash(char *key){
    int temp = 0;
    int i = 0;
    while(key[i] != '\0'){
        temp = ((temp<<SHIFT) + key[i]) % SIZE;
        i++;
    }
    return temp;
}