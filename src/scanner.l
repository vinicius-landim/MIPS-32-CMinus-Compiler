%option noyywrap
%option yylineno

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include "util.h"
#include "parser.tab.h"

extern int lineNo;
%}

/* Definições*/
DIGITO  [0-9]
LETRA   [a-zA-Z]
ID      {LETRA}+
NUM     {DIGITO}+
ESPACO  [ \t\r]+

/* Estado para Comentários Multilinha*/
%x COMENTARIO

%%

 /* Palavras-Reservadas*/
"if"            { return IF; }
"else"          { return ELSE; }
"int"           { return INT; }
"return"        { return RETURN; }
"void"          { return VOID; }
"while"         { return WHILE; }

 /*Operadores e Símbolos*/
"+"             { return SOMA; }
"-"             { return SUB; }
"*"             { return MUL; }
"/"             { return DIV; }
"<="            { return MENOR_IGUAL; }
"<"             { return MENOR; }
">="            { return MAIOR_IGUAL; }
">"             { return MAIOR; }
"=="            { return IGUAL_IGUAL; }
"!="            { return DIFERENTE; }
"="             { return ATRIBUICAO; }
";"             { return PONTO_VIRGULA; }
","             { return VIRGULA; }
"("             { return ABRE_PARENTESE; }
")"             { return FECHA_PARENTESE; }
"["             { return ABRE_COLCHETE; }
"]"             { return FECHA_COLCHETE; }
"{"             { return ABRE_CHAVE; }
"}"             { return FECHA_CHAVE; }

 /*Identificadores e Números*/
{ID} {
      yylval.name = copyString(yytext); 
      return ID; 
}
{NUM} { 
        yylval.val = atoi(yytext); 
        return NUM; 
}

 /*Gerenciamento de Espaços e Linhas*/
\n        { lineNo++; }
{ESPACO}  { /* ignora */ }

 /*Tratamento de Comentários*/
"/*"             { BEGIN(COMENTARIO); }
<COMENTARIO>"*/" { BEGIN(INITIAL); }
<COMENTARIO>\n   { lineNo++; }
<COMENTARIO>.    { /* ignora conteúdo */ }

 /*Erros Léxicos*/
. { 
    fprintf(stderr, "ERRO LEXICO: Caractere '%s' inválido - LINHA:%d\n", yytext, lineNo); 
}

%%