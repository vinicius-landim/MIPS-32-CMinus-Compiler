#include "globals.h"
#include "util.h"
static int indentno = 0;
#define INDENT indentno+=2
#define UNINDENT indentno-=2

FILE* listing;

/*Função new StmtNode cria um novo nó de declaraçõ para a construção da arvore sintática*/

TreeNode *newStmtNode(StmtKind kind)
{
	TreeNode *t = (TreeNode*) malloc(sizeof(TreeNode));
	int i;
	if(t!=NULL)
	{
		//printf("Entrou1\n" );
		for(i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
		t->sibling = NULL;
		t->nodeKind = StmtK;
		t->kind.stmt = kind;
		t->lineno = lineno;
	}
	return t;
}

/*Função newExpNode cria um novo nó de expressao para a construção da arvore sintática*/
TreeNode *newExpNode(ExpKind kind)
{
	TreeNode *t = (TreeNode*) malloc(sizeof(TreeNode));
	int i;
	if(t!=NULL)
	{	
		for(i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
		t->sibling = NULL;
		t->nodeKind = ExpK;
		t->kind.exp = kind;
		t->lineno = lineno;
		t->type = Void;
		//printf("Entrou exp node %d aqui \n",t->nodeKind);
	}
	return t;
}
char *copyString(char *s)
{
	int n;
	char *t;
	if(s==NULL) return NULL;
	n = strlen(s)+1;
	t = malloc(n);
	if(t!=NULL){
		strcpy(t,s);
	}
	return t;
}

char *printToken(TokenType token, const char* tokenString)
{
	char *tokenS;
	tokenS = malloc(100);
	switch(token)
	{
		case IF:
		case ELSE:
		case INT:
		case VOID:
		case WHILE:
		case RETURN:
			strcpy(tokenS,tokenString);
			break;
		case NUM:
			strcpy(tokenS,"NUM");
			break;
		case SOMA:
			strcpy(tokenS,"+");
			break;
		case SUB:
			strcpy(tokenS,"-");
			break;
		case DIV:
			strcpy(tokenS,"/");
			break;
		case MUL:
			strcpy(tokenS,"*");
			break;
		case APR:
			strcpy(tokenS,"(");
			break;
		case FPR:
			strcpy(tokenS,")");
			break;
		case ID:
			strcpy(tokenS,tokenString);
			break;
		case ACOL:
			strcpy(tokenS,"[");
			break;
		case FCOL:
			strcpy(tokenS,"]");
			break;
		case ACH:
			strcpy(tokenS,"{");
			break;
		case FCH:
			strcpy(tokenS,"}");
			break;
		case ATRIB:
			strcpy(tokenS,"=");
			break;
		case IGL:
			strcpy(tokenS,"==");
			break;
		case DIF:
			strcpy(tokenS,"!=");
			break;
		case MAIGL:
			strcpy(tokenS,">=");
			break;
		case MEIGL:
			strcpy(tokenS,"<=");
			break;
		case MAI:
			strcpy(tokenS,">");
			break;
		case MEN:
			strcpy(tokenS,"<");
			break;
		case VIRG:
			strcpy(tokenS,",");
			break;
		case PV:
			strcpy(tokenS,";");
			break;
	}
	return tokenS;
}

static void printSpaces(void)
{ int i;
  for (i=0;i<indentno;i++)
    fprintf(listing," ");
}

char *getType(int x)
{
	char *tipo;
	if(x)
	{
		tipo = (char*) malloc(4*sizeof(char));
		strcpy(tipo,"int");
	}
	else if(x==0)
	{
		tipo = (char*) malloc(5*sizeof(char));
		strcpy(tipo,"void");
	}
	return tipo;
}

void printTree(TreeNode *t)
{ 
	int i;
    INDENT;
  while (t != NULL) {
    printSpaces();
    if (t->nodeKind==StmtK)
    { 
	    switch (t->kind.stmt) {
	        case IfK:
	          fprintf(listing,"If\n");
	          break;
	        case WhileK:
	          fprintf(listing,"while\n");
	          break;
	        case AssignK:
	          fprintf(listing,"Assign\n");
	          break;
	        case ReturnK:
	          fprintf(listing,"Return\n");
	          break;
	        case CallK:
	          fprintf(listing,"Call: %s Linha: %d\n",t->attr.name,t->lineno);
	          break;
			case FuncaoK:
		      fprintf(listing,"Funcão - %s - %s - Linha: %d Escopo: %s\n",getType(t->type),t->attr.name,t->lineno,t->escopo);
		      break;
   	   		case VarK:
          	  fprintf(listing,"Var %s Linha: %d Escopo: %s\n",t->attr.name,t->lineno,t->escopo);
              break;
			case VetK:
          	  fprintf(listing,"Vetor %s Linha: %d Escopo: %s\n",t->attr.name,t->lineno,t->escopo);
			  break;
	        default:
	          fprintf(listing,"Unknown ExpNode kind\n");
	          break;
	      }
    }
    else if (t->nodeKind==ExpK)
    { 

    	switch (t->kind.exp) {
        case OpK:
          fprintf(listing,"Op: %s\n",printToken(t->attr.op,"\0"));
          break;
        case ConstK:
          fprintf(listing,"Const: %d\n",t->attr.val);
          break;
        case IdK:
          fprintf(listing,"Id: %s Line:%d\n",t->attr.name,t->lineno);
          break;
        case TypeK:
          fprintf(listing,"Tipo: %s\n",getType(t->type));
          break;
        case VetIdK:
          	fprintf(listing,"VetID: %s Line: %d Escopo: %s\n",t->attr.name,t->lineno,t->escopo);
          	break;
		case VarIdK:
			fprintf(listing,"VarID: %s Line: %d Escopo: %s\n",t->attr.name, t->lineno,t->escopo);
			break;
        default:
          fprintf(listing,"Unknown ExpNode kind\n");
          break;
      }
    }
    else fprintf(listing,"Unknown node kind\n");
    for (i=0;i<MAXCHILDREN;i++)
   	{
   		if(t->child[i]!=NULL)
   		{
         	printTree(t->child[i]);
   		}
   	}
	
    t = t->sibling;

  }
UNINDENT;
}

void printTreeR( TreeNode * t )
{
	listing = fopen("saidas/arvore.txt","w");
	if(listing!=NULL)
	{
		printTree(t);
	}
	
}
