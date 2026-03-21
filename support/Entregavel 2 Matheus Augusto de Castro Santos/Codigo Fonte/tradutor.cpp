#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <iterator>
#include <vector>
#include <stack>
#include <sstream>
#include <locale>
#include <filesystem>
#include "tradutorBinario.h"


using namespace std;

enum instrucoes:int {ADD, SUB, MULT, DIV, AND, OR, NOR,
					 SLT, SGT,SLET, SGET, SET, SDT, SGTI,
					 SLETI, SGETI, SETI, SDTI, SLL, SRL,
					 MOD,JR,ADDI,MULTI,DIVI,ANDI,BLTZ, 
					 BGTZ,BEQZ,BEQ, BNE, LW, SW, ORI, SLTI,
					  MODI, JUMP,JAL,NOP,HALT,INPUT,OUTPUT,LUI};

enum registradores:int {$zero, $t0, $t1, $t2, $t3, $t4, 
						$t5, $t6, $t7, $t8, $t9, $t10, $t11, 
						$t12, $t13, $t14, $t15, $t16, $t17, 
						$t18, $t19, $t20, $t21, $t22, $t23, 
						$t24, $t25, $aux, $rf, $fp, $sp,$ra};

string reg_string[] = { "$zero", "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", "t8", "t9", "t10", "t11", "t12", "t13", "t14", "t15", "$t16", "$t17", "$t18", "$t19", "$t20",
					       "$t21", "$t22", "$t23", "$t24", "$t25", "$aux", "$rf", "$fp", "$sp", "$ra"};

string reg_string_imprimir[] = { "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15", "r16", "r17", "r18", "r19", "r20",
								 					       "r21", "r22", "r23", "r24", "r25", "r26", "r27", "r28", "r29", "r30","r31"};

string inst_string[] = {"add", "sub", "mult", "div", "and", "or", "nor", "slt", "sgt","slet", "sget", "set", "sdt", "sgti","sleti", "sgeti", "seti", "sdti","sll", "srl","mod","jr","addi","multi","divi","andi","bltz", "bgtz","beqz",
				 			 "beq", "bne", "lw", "sw", "ori", "slti", "modi", "jump","jal","nop","halt","input","output","lui"};

int numLinha = 0;

class nodeVariavel
{
	public:
	int memLoc;
	string nome;
	int tipo;
	int tamanho;
	nodeVariavel *prox;
};

class nodeEscopo
{
	public:
	int posAtualMem;
	string nome;
	nodeVariavel *var;
	nodeEscopo *prox;
};

class nodeLabel
{
	public:
	int numLinha;
	string nome;
	nodeLabel *prox;
};

class nodeInstrucao
{
	public:
	instrucoes inst;
	registradores rs;
	registradores rt;
	registradores rd;
	string imediato;
	string endereco;
	int tipo; 
	nodeInstrucao *prox;
};

class listaInstrucao
{
	public:

	nodeInstrucao *primeira;
	nodeInstrucao *ultima;
};



struct quadrupla
{
	string op,end1,end2,end3;
};

//lista com as posições das variaveis na memoria
nodeEscopo *varLoc = NULL;

//lista com as posições das labels
nodeLabel *labelLoc = NULL;

//pilha com os parametros
stack<string> parametros;

//arquivo de entrada
ifstream codInt;

//arquivo de saida
ofstream assemblyFile;

//lista de instruções
listaInstrucao lst;

//posição a partir da qual se iniciam as declarações de variveis dentro de um frame
int frameIni = 2;

void insereFormatoR(instrucoes inst, registradores rs, registradores rt, registradores rd)
{
	/*string instrucao = inst_string[inst]+' '+reg_string[rs]+' '+reg_string[rt]+' '+reg_string[rd];
	if(assemblyFile.is_open())
	{
		assemblyFile<<instrucao<<endl;
		numLinha++;
	}*/
	if(lst.primeira == NULL)
	{
		nodeInstrucao *nova = new nodeInstrucao();
		nova->inst = inst;
		nova->rt = rt;
		nova->rs = rs;
		nova->rd = rd;
		nova->prox = NULL;
		nova->tipo = 1;

		lst.primeira = nova;
		lst.ultima = nova;
	}
	else
	{
		nodeInstrucao *nova = new nodeInstrucao();
		nova->inst = inst;
		nova->rt = rt;
		nova->rs = rs;
		nova->rd = rd;
		nova->prox = NULL;
		nova->tipo = 1;

		lst.ultima->prox = nova;
		lst.ultima = nova;
	}

	numLinha++;
}

void insereFormatoI(instrucoes inst, registradores rs, registradores rt, string imediato)
{
	//cout << "Imprime I" << endl;
	/*string instrucao = inst_string[inst]+' '+reg_string[rs]+' '+reg_string[rt]+' '+imediato;
	if(assemblyFile.is_open())
	{
		assemblyFile<<instrucao<<endl;
		numLinha++;
	}*/
	if(lst.primeira == NULL)
	{
		nodeInstrucao *nova = new nodeInstrucao();
		nova->inst = inst;
		nova->rt = rt;
		nova->rs = rs;
		nova->imediato = imediato;
		nova->prox = NULL;
		nova->tipo = 2;

		lst.primeira = nova;
		lst.ultima = nova;
	}
	else
	{
		nodeInstrucao *nova = new nodeInstrucao();
		nova->inst = inst;
		nova->rt = rt;
		nova->rs = rs;
		nova->imediato = imediato;
		nova->prox = NULL;
		nova->tipo = 2;

		lst.ultima->prox = nova;
		lst.ultima = nova;
	}

	numLinha++;
}

void insereFormatoJ(instrucoes inst, string endereco)
{
	//cout << "Imprime J" << endl;
	/*string instrucao = inst_string[inst]+' '+endereco;
	if(assemblyFile.is_open())
	{
		assemblyFile<<instrucao<<endl;
		numLinha++;
	}*/

	if(lst.primeira == NULL)
	{
		nodeInstrucao *nova = new nodeInstrucao();
		nova->inst = inst;
		nova->endereco = endereco;
		nova->prox = NULL;
		nova->tipo = 3;

		lst.primeira = nova;
		lst.ultima = nova;
	}
	else
	{
		nodeInstrucao *nova = new nodeInstrucao();
		nova->inst = inst;
		nova->endereco = endereco;
		nova->prox = NULL;
		nova->tipo = 3;


		lst.ultima->prox = nova;
		lst.ultima = nova;
	}

	numLinha++;
}

void insereInstrucaoIO(instrucoes inst, registradores rs)
{
	if(lst.primeira == NULL)
	{
		nodeInstrucao *nova = new nodeInstrucao();
		nova->inst = inst;
		nova->rs = rs;
		nova->prox = NULL;
		nova->tipo = 4;

		lst.primeira = nova;
		lst.ultima = nova;
	}
	else
	{
		nodeInstrucao *nova = new nodeInstrucao();
		nova->inst = inst;
		nova->rs = rs;
		nova->prox = NULL;
		nova->tipo = 4;

		lst.ultima->prox = nova;
		lst.ultima = nova;
	}

	numLinha++;
}

void insereVetor(string escopo, string nome, int tamanho){
	nodeVariavel *nova = new nodeVariavel();

	if(varLoc == NULL)
	{
		nodeEscopo *novo = new nodeEscopo();
		if(escopo == "global" || escopo == "main")
			novo->posAtualMem = 0;
		else
			novo->posAtualMem = frameIni;
		novo->nome = escopo;
		novo->prox = NULL;

		nova->memLoc = novo->posAtualMem;
		nova->nome = nome;
		nova->tipo = 1;
		nova->tamanho = tamanho;
		nova->prox = NULL;

		novo->var = nova;
		novo->posAtualMem = novo->posAtualMem+tamanho+1;

		varLoc = novo;
	}
	else
	{
		nodeEscopo *p;
		nodeEscopo *pAnterior;
		bool verificaEscopo = false;
		for(p=varLoc;p != NULL; p = p->prox)
		{
			if(p->nome == escopo)
			{
				verificaEscopo = true;
				break;
			}
			pAnterior = p;
		}

		if(verificaEscopo == true)//escopo já está na lista
		{
			nodeVariavel *q;
			nodeVariavel *qAnterior;
			bool verificaVar = false;
			for(q=p->var;q != NULL; q = q->prox)
			{
				if(q->nome == nome)
				{
					verificaVar = true;
					break;
				}
				qAnterior = q;
			}

			if(verificaVar == false)//vetor não declarados
			{
				nova->memLoc = p->posAtualMem;
				nova->nome = nome;
				nova->tipo = 1;
				nova->tamanho = -1;
				nova->prox = NULL;
				p->posAtualMem = p->posAtualMem+tamanho+1;
				qAnterior->prox = nova;
			}
		}
		else//escopo não está na lista
		{
			nodeEscopo *novo = new nodeEscopo();
			if(escopo == "global" || escopo == "main")
				novo->posAtualMem = 0;
			else
				novo->posAtualMem = frameIni;

			novo->nome = escopo;
			novo->prox = NULL;

			nova->memLoc = novo->posAtualMem;
			nova->nome = nome;
			nova->tipo = 1;
			nova->tamanho = -1;
			nova->prox = NULL;

			novo->var = nova;
			novo->posAtualMem = novo->posAtualMem + tamanho + 1;

			pAnterior->prox = novo;
		}
	}

	if(escopo == "global" && tamanho>0)
	{
		insereFormatoI(ADDI,$zero,$aux,to_string(nova->memLoc+1));
		insereFormatoI(SW,$zero,$aux,to_string(nova->memLoc));
	}
	else
	{
		if(tamanho>0)
		{
			insereFormatoI(ADDI,$fp,$aux,to_string(nova->memLoc+1));
			insereFormatoI(SW,$fp,$aux,to_string(nova->memLoc));
		}
		insereFormatoI(ADDI,$sp,$sp,to_string(tamanho+1));
	}

}

void insereVariavel(string escopo, string nome)
{
	if(varLoc == NULL)
	{
		nodeEscopo *novo = new nodeEscopo();
		if(escopo == "global" || escopo == "main")
			novo->posAtualMem = 0;
		else
			novo->posAtualMem = frameIni;
		novo->nome = escopo;
		novo->prox = NULL;

		nodeVariavel *nova = new nodeVariavel();
		nova->memLoc = novo->posAtualMem;
		nova->nome = nome;
		nova->tipo = 0;
		nova->tamanho = -1;
		nova->prox = NULL;

		novo->var = nova;
		novo->posAtualMem = novo->posAtualMem + 1;

		varLoc = novo;
	}
	else
	{
		nodeEscopo *p;
		nodeEscopo *pAnterior;
		bool verificaEscopo = false;
		for(p=varLoc;p != NULL; p = p->prox)
		{
			if(p->nome == escopo)
			{
				verificaEscopo = true;
				break;
			}
			pAnterior = p;
		}

		if(verificaEscopo == true)//escopo já está na lista
		{
			nodeVariavel *q;
			nodeVariavel *qAnterior;
			bool verificaVar = false;
			for(q=p->var;q != NULL; q = q->prox)
			{
				if(q->nome == nome)
				{
					verificaVar = true;
					break;
				}
				qAnterior = q;
			}

			if(verificaVar == false)//variavel não declarada
			{
				nodeVariavel *nova = new nodeVariavel();
				nova->memLoc = p->posAtualMem;
				nova->nome = nome;
				nova->tipo = 0;
				nova->tamanho = -1;
				nova->prox = NULL;
				p->posAtualMem = p->posAtualMem+1;
				qAnterior->prox = nova;
			}
		}
		else//escopo não está na lista
		{
			nodeEscopo *novo = new nodeEscopo();
			if(escopo == "global" || escopo == "main")
				novo->posAtualMem = 0;
			else
				novo->posAtualMem = frameIni;
			novo->nome = escopo;
			novo->prox = NULL;

			nodeVariavel *nova = new nodeVariavel();
			nova->memLoc = novo->posAtualMem;
			nova->nome = nome;
			nova->tipo = 0;
			nova->tamanho = -1;
			nova->prox = NULL;

			novo->var = nova;
			novo->posAtualMem = novo->posAtualMem + 1;

			pAnterior->prox = novo;
		}
	}
}

void imprimeVariaveis()
{
	nodeEscopo *p = varLoc;
	nodeVariavel *q;
	do
	{
		cout << "Escopo:" << p->nome << endl;
		q=p->var;
		do
		{
			cout<<"  "<<q->nome<< " pos: "<< q->memLoc<<endl;
			q=q->prox;
		}while(q!= NULL);
		p =p->prox;
	}while(p != NULL);

}

int pegaEndereco(string escopo, string nome)
{
	nodeEscopo *p;
	for(p=varLoc;p!=NULL;p = p->prox)
	{
		if(p->nome == escopo)
			break;
	}
	nodeVariavel *q;
	for(q=p->var;q!=NULL;q = q->prox)
	{
		if(q->nome == nome)
			break;
	}
	//cout << q->memLoc << endl;
	return q->memLoc;
}

void imprimeLabels()
{
	nodeLabel *p = labelLoc;
	do
	{
		//cout << "Label:" << p->nome << endl;
		p =p->prox;
	}while(p != NULL);

}

void insereLabel(string nome)
{
	if(labelLoc == NULL)
	{
		nodeLabel *nova = new nodeLabel();
		nova->numLinha = numLinha;
		nova->nome = nome;
		nova->prox = NULL;
		labelLoc = nova;
	}
	else
	{
		nodeLabel *p;
		nodeLabel *pAnterior;

		for(p=labelLoc; p != NULL; p = p->prox)
		{
			pAnterior = p;
		}

		nodeLabel *nova = new nodeLabel();
		nova->numLinha = numLinha;
		nova->nome = nome;
		nova->prox = NULL;

		pAnterior->prox = nova;

	}
}

void pegaLinhaIntermediario(quadrupla *quad)
{
	string line;
	if(!codInt.eof())
	{
		getline(codInt,line);
		vector<string> result;
   		stringstream s_stream(line); //create string stream from the string
   		while(s_stream.good()) {
	      	string substr;
	     	getline(s_stream, substr, ','); //get first string delimited by comma
	      	result.push_back(substr);
   		}

	    if(result.size()==4)
	    {
	    	quad->op = result[0];
		    quad->end1 = result[1];
		    quad->end2 = result[2];
		    quad->end3 = result[3];
	    }
	    else//pega uma linha em branco no fim do arquivo -> evita executar a ultima operação duas vezes
	    {
	    	quad->op = "";
	    }
	}
}

registradores pegaRegistradorNumero(string r)
{
	for(int i=0;i<32;i++)
	{
		if(r==reg_string[i])
			return (registradores) i;
	}

	return (registradores)0;
}

bool ehNumero(string s)
{
	bool result = true;
	for(int i = 0; i<s.size();i++)
	{
		if(!isdigit(s[i]))
		{
			result = false;
			break;
		}
	}

	return result;
}
int labelLinha(string label)
{
	nodeLabel *p;
	int  n =  0;
	for(p=labelLoc;p!=NULL;p = p->prox)
	{
		if(p->nome == label)
		{
			n = p->numLinha;
		}
	}
	return n;
}

void imprimeInstrucoes()
{
	nodeInstrucao *p;
	int n = 0;
	for(p=lst.primeira;p!=NULL;p = p->prox)
	{
		if(p->tipo == 1)
		{
			string instrucao = inst_string[p->inst]+' '+reg_string_imprimir[p->rs]+' '+reg_string_imprimir[p->rt]+' '+reg_string_imprimir[p->rd];
			if(assemblyFile.is_open())
			{
				assemblyFile<<instrucao<<endl;
			}
		}
		else if(p->tipo == 2)
		{
			string instrucao;

			if(p->inst == BEQZ)
			{
				instrucao = inst_string[p->inst]+' '+reg_string_imprimir[p->rs]+' '+reg_string_imprimir[p->rt]+' '+to_string(labelLinha(p->imediato)-n-1);
			}
			else
			{
				instrucao = inst_string[p->inst]+' '+reg_string_imprimir[p->rs]+' '+reg_string_imprimir[p->rt]+' '+p->imediato;
			}
			if(assemblyFile.is_open())
			{
				assemblyFile<<instrucao<<endl;
			}
		}
		else if(p->tipo == 3)
		{
			
			string instrucao = inst_string[p->inst]+' '+to_string(labelLinha(p->endereco));
			if(assemblyFile.is_open())
			{
				assemblyFile<<instrucao<<endl;
			}
		}
		else if(p->tipo == 4)
		{
			string instrucao = inst_string[p->inst]+' '+reg_string_imprimir[p->rs];
			if(assemblyFile.is_open())
			{
				assemblyFile<<instrucao<<endl;
			}
		}
		n++;
		
	}
	
}

int main()
{

	codInt.open("saidas/intermediario.txt");
	quadrupla quad;
	lst.primeira = NULL;
	lst.ultima = NULL;
	
	insereFormatoJ(JUMP,"main");

	while(!codInt.eof())
	{
		pegaLinhaIntermediario(&quad);
		if(quad.op == "add")
		{
			if(ehNumero(quad.end1) && ehNumero(quad.end2))//os dois operadores são numeros
			{
				//coloca o primeiro operando no registrador de destino RT
				insereFormatoI(ADDI,$zero,pegaRegistradorNumero(quad.end3),quad.end1);
				//soma o segundo operando com o primeiro q está no reg de destino
				insereFormatoI(ADDI,pegaRegistradorNumero(quad.end3),pegaRegistradorNumero(quad.end3),quad.end2);
			}
			else if (!ehNumero(quad.end1) && !ehNumero(quad.end2))//ADD
			{
				insereFormatoR(ADD,pegaRegistradorNumero(quad.end1),pegaRegistradorNumero(quad.end2),pegaRegistradorNumero(quad.end3));
			}
			else//ADDI
			{
				if(ehNumero(quad.end1))
				{
					insereFormatoI(ADDI,pegaRegistradorNumero(quad.end2),pegaRegistradorNumero(quad.end3),quad.end1);
				}
				else
				{
					insereFormatoI(ADDI,pegaRegistradorNumero(quad.end1),pegaRegistradorNumero(quad.end3),quad.end2);
				}
			}
		}
		else if(quad.op == "sub")
		{
			if(ehNumero(quad.end1) && ehNumero(quad.end2))//os dois operadores são numeros
			{
				insereFormatoI(ADDI,$zero,pegaRegistradorNumero(quad.end3),quad.end1);//coloca o primeiro operando no registrador de destino RT
				insereFormatoI(ADDI,pegaRegistradorNumero(quad.end3),pegaRegistradorNumero(quad.end3),"-"+quad.end2);//adiciona  o sinal de menos ao segundo operando
			}
			else if (!ehNumero(quad.end1) && !ehNumero(quad.end2))//SUB
			{
				insereFormatoR(SUB,pegaRegistradorNumero(quad.end1),pegaRegistradorNumero(quad.end2),pegaRegistradorNumero(quad.end3));
			}
			else//subtração com imediato
			{
				if(ehNumero(quad.end1))
				{
					insereFormatoI(ADDI,pegaRegistradorNumero(quad.end2),pegaRegistradorNumero(quad.end3),"-"+quad.end1);
				}
				else
				{
					insereFormatoI(ADDI,pegaRegistradorNumero(quad.end1),pegaRegistradorNumero(quad.end3),"-"+quad.end2);
				}
			}
		}
		else if(quad.op == "mult")
		{
			if(ehNumero(quad.end1) && ehNumero(quad.end2))//os dois operadores são numeros
			{
				insereFormatoI(ADDI,$zero,pegaRegistradorNumero(quad.end3),quad.end1);//coloca o primeiro operando no registrador de destino RT
				insereFormatoI(MULTI,pegaRegistradorNumero(quad.end3),pegaRegistradorNumero(quad.end3),quad.end2);
			}
			else if (!ehNumero(quad.end1) && !ehNumero(quad.end2))//os dois operandos são registradores
			{
				insereFormatoR(MULT,pegaRegistradorNumero(quad.end1),pegaRegistradorNumero(quad.end2),pegaRegistradorNumero(quad.end3));
			}
			else//multiplicação com imediato
			{
				if(ehNumero(quad.end1))
				{
					insereFormatoI(MULTI,pegaRegistradorNumero(quad.end2),pegaRegistradorNumero(quad.end3),quad.end1);
				}
				else
				{
					insereFormatoI(MULTI,pegaRegistradorNumero(quad.end1),pegaRegistradorNumero(quad.end3),quad.end2);
				}
			}
		}
		else if(quad.op == "divisao")
		{
			if(ehNumero(quad.end1) && ehNumero(quad.end2))//os dois operadores são numeros
			{
				insereFormatoI(ADDI,$zero,pegaRegistradorNumero(quad.end3),quad.end1);//coloca o primeiro operando no registrador de destino RT
				insereFormatoI(DIVI,pegaRegistradorNumero(quad.end3),pegaRegistradorNumero(quad.end3),quad.end2);
			}
			else if (!ehNumero(quad.end1) && !ehNumero(quad.end2))//os dois operandos são registradores
			{
				insereFormatoR(DIV,pegaRegistradorNumero(quad.end1),pegaRegistradorNumero(quad.end2),pegaRegistradorNumero(quad.end3));
			}
			else//divisão com imediato
			{
				if(ehNumero(quad.end1))
				{
					insereFormatoI(DIVI,pegaRegistradorNumero(quad.end2),pegaRegistradorNumero(quad.end3),quad.end1);
				}
				else
				{
					insereFormatoI(DIVI,pegaRegistradorNumero(quad.end1),pegaRegistradorNumero(quad.end3),quad.end2);
				}
			}
		}
		else if(quad.op == "ifFalso")
		{
			insereFormatoI(BEQZ,pegaRegistradorNumero(quad.end1),$zero,quad.end2);
		}
		else if(quad.op == "call")
		{
			if(quad.end1 == "output")
			{
				if(ehNumero(parametros.top()))
				{
					insereFormatoI(ADDI,$zero,$aux,parametros.top());
					parametros.pop();
					insereInstrucaoIO(OUTPUT,$aux);
				}
				else
				{
					insereInstrucaoIO(OUTPUT,pegaRegistradorNumero(parametros.top()));
					parametros.pop();
				}
			}
			else if(quad.end1 == "input")
			{
				insereInstrucaoIO(INPUT,$rf);
			}
			else
			{
				insereFormatoI(SW,$sp,$fp,"0");//armazena o fp antigo na pilha
				insereFormatoI(ADDI,$sp,$fp,"0");//novo fp
				insereFormatoI(ADDI,$sp,$sp,"1");//sobe a pilha em 1
				int qtdeParam = stoi(quad.end2);
				for(int i = qtdeParam+frameIni-1;i>=frameIni;i--)
				{
					if(ehNumero(parametros.top()))
					{
						insereFormatoI(ADDI,$zero,$aux,parametros.top());
						parametros.pop();
						insereFormatoI(SW,$fp,$aux,to_string(i));
					}
					else
					{
						insereFormatoI(SW,$fp,pegaRegistradorNumero(parametros.top()),to_string(i));
						parametros.pop();
					}
				}
				insereFormatoJ(JAL,quad.end1);
				insereFormatoI(ADDI,$fp,$sp,"0");//copia o fp para sp
				insereFormatoI(LW,$fp,$fp,"0");//restaria fp anterior
			}
		}
		else if(quad.op == "move")
		{
			if(ehNumero(quad.end1))
			{
				insereFormatoI(ADDI,$zero,pegaRegistradorNumero(quad.end2),quad.end1);
			}
			else
			{
				
				insereFormatoI(ADDI,pegaRegistradorNumero(quad.end1),pegaRegistradorNumero(quad.end2),"0");
			}
			
		}
		else if(quad.op == "label_op")
		{
			insereLabel(quad.end1);
		}
		else if(quad.op == "storeVet")
		{

			if(ehNumero(quad.end1))//store de imediato
			{
				insereFormatoI(ADDI,$zero,$aux,quad.end1);
				insereFormatoI(SW,pegaRegistradorNumero(quad.end2),$aux,"0");
			}
			else
			{
				insereFormatoI(SW,pegaRegistradorNumero(quad.end2),pegaRegistradorNumero(quad.end1),"0");
			}
		}
		else if(quad.op == "jump")
		{
			insereFormatoJ(JUMP,quad.end1);
		}
		else if(quad.op == "slt")
		{
			if(ehNumero(quad.end1) && ehNumero(quad.end2))//os dois operadores são numeros
			{
				insereFormatoI(ADDI,$zero,pegaRegistradorNumero(quad.end3),quad.end1);//coloca o primeiro operando no registrador de destino RT
				insereFormatoI(SLTI,pegaRegistradorNumero(quad.end3),pegaRegistradorNumero(quad.end3),quad.end2);//verifico se o operando presente no registrador é menor q o imediato
			}
			else if (!ehNumero(quad.end1) && !ehNumero(quad.end2))//SLT
			{
				insereFormatoR(SLT,pegaRegistradorNumero(quad.end1),pegaRegistradorNumero(quad.end2),pegaRegistradorNumero(quad.end3));
			}
			else//SLTI
			{
				if(ehNumero(quad.end1))
				{
					insereFormatoI(SGTI,pegaRegistradorNumero(quad.end2),pegaRegistradorNumero(quad.end3),quad.end1);
				}
				else
				{
					insereFormatoI(SLTI,pegaRegistradorNumero(quad.end1),pegaRegistradorNumero(quad.end3),quad.end2);
				}
			}
		}
		else if(quad.op == "sgt")
		{
			if(ehNumero(quad.end1) && ehNumero(quad.end2))//os dois operadores são numeros
			{
				insereFormatoI(ADDI,$zero,pegaRegistradorNumero(quad.end3),quad.end1);//coloca o primeiro operando no registrador de destino RT
				insereFormatoI(SGTI,pegaRegistradorNumero(quad.end3),pegaRegistradorNumero(quad.end3),quad.end2);//verifico se o operando presente no registrador é maior q o imediato
			}
			else if (!ehNumero(quad.end1) && !ehNumero(quad.end2))//SLT
			{
				insereFormatoR(SGT,pegaRegistradorNumero(quad.end1),pegaRegistradorNumero(quad.end2),pegaRegistradorNumero(quad.end3));
			}
			else//SGTI
			{
				if(ehNumero(quad.end1))
				{
					insereFormatoI(SLTI,pegaRegistradorNumero(quad.end2),pegaRegistradorNumero(quad.end3),quad.end1);
				}
				else
				{
					insereFormatoI(SGTI,pegaRegistradorNumero(quad.end1),pegaRegistradorNumero(quad.end3),quad.end2);
				}
			}
		}
		else if(quad.op == "slet")
		{
			if(ehNumero(quad.end1) && ehNumero(quad.end2))//os dois operadores são numeros
			{
				insereFormatoI(ADDI,$zero,pegaRegistradorNumero(quad.end3),quad.end1);//coloca o primeiro operando no registrador de destino RT
				insereFormatoI(SLETI,pegaRegistradorNumero(quad.end3),pegaRegistradorNumero(quad.end3),quad.end2);//verifico se o operando presente no registrador é menor/igual q o imediato
			}
			else if (!ehNumero(quad.end1) && !ehNumero(quad.end2))//SLET
			{
				insereFormatoR(SLET,pegaRegistradorNumero(quad.end1),pegaRegistradorNumero(quad.end2),pegaRegistradorNumero(quad.end3));
			}
			else//SLET
			{
				if(ehNumero(quad.end1))
				{
					insereFormatoI(SGETI,pegaRegistradorNumero(quad.end2),pegaRegistradorNumero(quad.end3),quad.end1);
				}
				else
				{
					insereFormatoI(SLETI,pegaRegistradorNumero(quad.end1),pegaRegistradorNumero(quad.end3),quad.end2);
				}
			}
		}
		else if(quad.op == "sdt")
		{
			if(ehNumero(quad.end1) && ehNumero(quad.end2))//os dois operadores são numeros
			{
				insereFormatoI(ADDI,$zero,pegaRegistradorNumero(quad.end3),quad.end1);//coloca o primeiro operando no registrador de destino RT
				insereFormatoI(SDTI,pegaRegistradorNumero(quad.end3),pegaRegistradorNumero(quad.end3),quad.end2);//verifico se o operando presente no registrador é diferente do imediato
			}
			else if (!ehNumero(quad.end1) && !ehNumero(quad.end2))//SLET
			{
				insereFormatoR(SDT,pegaRegistradorNumero(quad.end1),pegaRegistradorNumero(quad.end2),pegaRegistradorNumero(quad.end3));
			}
			else//SDTI
			{
				if(ehNumero(quad.end1))
				{
					insereFormatoI(SDTI,pegaRegistradorNumero(quad.end2),pegaRegistradorNumero(quad.end3),quad.end1);
				}
				else
				{
					insereFormatoI(SDTI,pegaRegistradorNumero(quad.end1),pegaRegistradorNumero(quad.end3),quad.end2);
				}
			}
		}
		else if(quad.op == "set")
		{
			if(ehNumero(quad.end1) && ehNumero(quad.end2))//os dois operadores são numeros
			{
				insereFormatoI(ADDI,$zero,pegaRegistradorNumero(quad.end3),quad.end1);//coloca o primeiro operando no registrador de destino RT
				insereFormatoI(SETI,pegaRegistradorNumero(quad.end3),pegaRegistradorNumero(quad.end3),quad.end2);//verifico se o operando presente no registrador é diferente do imediato
			}
			else if (!ehNumero(quad.end1) && !ehNumero(quad.end2))//SLET
			{
				insereFormatoR(SET,pegaRegistradorNumero(quad.end1),pegaRegistradorNumero(quad.end2),pegaRegistradorNumero(quad.end3));
			}
			else//SDTI
			{
				if(ehNumero(quad.end1))
				{
					insereFormatoI(SETI,pegaRegistradorNumero(quad.end2),pegaRegistradorNumero(quad.end3),quad.end1);
				}
				else
				{
					insereFormatoI(SETI,pegaRegistradorNumero(quad.end1),pegaRegistradorNumero(quad.end3),quad.end2);
				}
			}
		}
		else if(quad.op == "sget")
		{
			if(ehNumero(quad.end1) && ehNumero(quad.end2))//os dois operadores são numeros
			{
				insereFormatoI(ADDI,$zero,pegaRegistradorNumero(quad.end3),quad.end1);//coloca o primeiro operando no registrador de destino RT
				insereFormatoI(SGETI,pegaRegistradorNumero(quad.end3),pegaRegistradorNumero(quad.end3),quad.end2);//verifico se o operando presente no registrador é maior/igual q o imediato
			}
			else if (!ehNumero(quad.end1) && !ehNumero(quad.end2))//SLET
			{
				insereFormatoR(SGET,pegaRegistradorNumero(quad.end1),pegaRegistradorNumero(quad.end2),pegaRegistradorNumero(quad.end3));
			}
			else//SLET
			{
				if(ehNumero(quad.end1))
				{
					insereFormatoI(SLET,pegaRegistradorNumero(quad.end2),pegaRegistradorNumero(quad.end3),quad.end1);
				}
				else
				{
					insereFormatoI(SGET,pegaRegistradorNumero(quad.end1),pegaRegistradorNumero(quad.end3),quad.end2);
				}
			}
		}
		else if(quad.op == "funInicio")
		{
			insereLabel(quad.end1);
			if(quad.end1!="main")
			{
				insereFormatoI(SW,$fp,$ra,"1");
				insereFormatoI(ADDI,$sp,$sp,"1");
			}
		}
		else if(quad.op == "funFim")
		{
			if(quad.end1!="main")
			{
				insereFormatoI(LW,$fp,$ra,"1");
				insereFormatoR(JR,$ra,$zero,$zero);
			}
		}
		else if(quad.op == "loadVar")
		{
			string memLoc = to_string(pegaEndereco(quad.end1,quad.end2));
			if(quad.end1 == "global")
			{
				insereFormatoI(LW,$zero,pegaRegistradorNumero(quad.end3),memLoc);
			}
			else
			{
				insereFormatoI(LW,$fp,pegaRegistradorNumero(quad.end3),memLoc);
			}
		}
		else if(quad.op == "loadVet")
		{
			insereFormatoI(LW,pegaRegistradorNumero(quad.end1),pegaRegistradorNumero(quad.end2),"0");
		}
		else if(quad.op == "storeVar")
		{
			string memLoc = to_string(pegaEndereco(quad.end3,quad.end2));
			if(ehNumero(quad.end1))//store de imediato
			{
				insereFormatoI(ADDI,$zero,$aux,quad.end1);
				if(quad.end3 == "global")//se o escopo for global
				{
					insereFormatoI(SW,$zero,$aux,memLoc);
				}
				else
				{
					insereFormatoI(SW,$fp,$aux,memLoc);
				}
			}
			else
			{
				if(quad.end3 == "global")//se o escopo for global
				{
					insereFormatoI(SW,$zero,pegaRegistradorNumero(quad.end1),memLoc);
				}
				else
				{
					insereFormatoI(SW,$fp,pegaRegistradorNumero(quad.end1),memLoc);
				}
			}
		}
		else if(quad.op == "allocaMemVar")
		{
			insereVariavel(quad.end1,quad.end2);
			if(quad.end1 != "global")
			{
				insereFormatoI(ADDI,$sp,$sp,"1");
			}
		}
		else if(quad.op == "allocaMemVet")
		{
			if(stoi(quad.end3)==-1)//vetor parametro
			{
				insereVetor(quad.end1,quad.end2, 0);
			}
			else
			{
				insereVetor(quad.end1,quad.end2, stoi(quad.end3));
			}

		}
		else if(quad.op == "empilha")
		{
			insereFormatoI(SW,$sp,pegaRegistradorNumero("t"+quad.end1),"0");
			insereFormatoI(ADDI,$sp,$sp,"1");
		}
		else if(quad.op == "desempilha")
		{
			insereFormatoI(ADDI,$sp,$sp,"-1");
			insereFormatoI(LW,$sp,pegaRegistradorNumero("t"+quad.end1),"0");
		}
		else if(quad.op == "param")
		{
			parametros.push(quad.end1);
		}


	}
	//cout << "Imprimindo variaveis: " << endl;
	//imprimeVariaveis();
	if(numLinha>1)
	{
		assemblyFile.open("saidas/assembly.txt");
		imprimeInstrucoes();
		codInt.close();
		assemblyFile.close();
		cout << "Tradução para Assembly concluida..." << endl;
		geraBinario();
	}
	
	/*insereEscopo("global");
	Escopo n = varLoc.front();
	cout << n.nome << endl;
	string line;
	codInt.open("intermediario.txt");*/


}

