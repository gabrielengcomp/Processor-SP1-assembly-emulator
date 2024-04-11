#include <stdio.h> 
#include <stdlib.h>

#define byte unsigned char

void jmp(int operando, int *pnt);	// 12 desvio incondicional
void accStat(int acc, int *statPnt, int operação);	//Função flags

struct INSTRUCTION{ //Struct para armazenar os comandos lidos no arquivo
	byte opcode;
	byte operand;
};
typedef struct INSTRUCTION inst; 

int main(){
	
	//Declarações de variáveis
	int acc = 0;
	int pc = 0;
	int stat = 1;
	int i = 0;
	inst programa[256] = {0};
	int memoria[256] = {0};
	short instruction;
	int *statPnt;
	int *pcPnt;
	int o = 0, c = 0, z = 0;

	pcPnt = &pc;
	statPnt = &stat;

	FILE  * file = fopen("programa.exe", "rb"); //abertura do arquivo binário

	while(fread(&instruction, 2, 1, file) != 0) //leitura do arquivo binário
	{
		programa[i].opcode = instruction & 0xFF; //armanazena os comandos no vetor struct
		programa[i].operand = instruction >> 8;

		//printf("%.2X %.2X\n", programa[i].opcode, programa[i].operand); //print para confirmação se a leitura está certa
		i++;
	}

	while(1)
	{ 
		//printf("pc: %i ", pc);
		//printf("\nopcode: %X ", programa[pc].opcode);
		//printf("\noperando: %i\n", programa[pc].operand);
		switch (programa[pc].opcode)
		{
			;
			case 0: //LOAD_M
				acc = memoria[programa[pc].operand];
				accStat(acc, statPnt, 2); //verificação de flags
				pc++;
				break;

			case 1: //LOAD_V
				acc = programa[pc].operand;
				accStat(acc, statPnt, 2);
				pc++;
				break;

			case 2: // STORE
				memoria[programa[pc].operand] = acc;
				pc++;
				break;

			case 3: // ADD
				acc = acc + memoria[programa[pc].operand];
				accStat(acc, statPnt, 0);
				pc++;
				break;

			case 4: // SUB 
				acc = acc - memoria[programa[pc].operand];
				accStat(acc, statPnt, 0);
				pc++;
				break;

			case 5: // MUL
				acc = acc * memoria[programa[pc].operand];
				accStat(acc, statPnt, 2);
				pc++;
				break;

			case 6: //DIV
				acc = acc / memoria[programa[pc].operand];
				accStat(acc, statPnt, 2);
				pc++;
				break;

			case 7: // INC
				acc++;
				accStat(acc, statPnt, 0);
				pc++;
				break;

			case 8: // DEC
				acc--;
				accStat(acc, statPnt,0);
				pc++;
				break;

			case 9: // AND
				acc = acc & memoria[programa[pc].operand];
				accStat(acc, statPnt, 0);
				pc++;
				break;

			case 10: // OR
				acc = acc | memoria[programa[pc].operand];
				accStat(acc, statPnt, 0);
				pc++;
				break;

			case 11: // NOT
				acc = ~(acc);
				accStat(acc, statPnt, 0);
				pc++;
				break;

			case 12: // JMP
				jmp(programa[pc].operand, pcPnt);
				break;

			case 13: // JZ
				if(acc == 0)
				{ 
					jmp(programa[pc].operand, pcPnt);
					break;
				}
				pc++;
				break;

			case 14: // JNZ
				if(acc != 0)
				{ 	
					jmp(programa[pc].operand, pcPnt);
					break;
				}
				pc++;
				break;

			case 15: // JG
				if(acc > 0)
				{ 
					jmp(programa[pc].operand, pcPnt);
					break;
				}
				pc++;
				break;

			case 16: // JL
				if(acc < 0)
				{ 
					jmp(programa[pc].operand, pcPnt);
					break;
				}
				pc++;
				break;

			case 17: // JGE
				if(acc >= 0)
				{ 
					jmp(programa[pc].operand, pcPnt);
					break;
				}
				pc++;
				break;

			case 18: // JLE
				if(acc <= 0)
				{ 
					jmp(programa[pc].operand, pcPnt);
					break;
				}
				pc++;
				break;

			case 19: // HLT - sai do switch e para o loop while, fechando a execução do programa 
				printf("\nACC: %i\n", acc); //Retorna o acumulador
				if(stat==1) {z = 1;}
				if(stat==2) {c = 1;}
				if(stat==4) {o = 1;}

				printf("STAT: xxxxx%d%d%d\n", o, c, z);//printa as flags OCZ = xxxxx111
				return 0;
				break;
			
			default:
				printf("OPCODE NAO ENCONTRADO: %X, %i", programa[pc].opcode, pc);
				return 0;
				break;
		}
	}

	return 0;
}

void jmp(int operando, int *pnt)
{
	//move o ponteiro pc counter para o label
	*pnt = operando++/2;
}

void accStat(int acc, int *statPnt, int operação)
{ 
	*statPnt = 0;	

	//verifica o overflow, carry e zero
	if(acc == 0)
		*statPnt = 1;
	if((acc > 255) || (acc < -256))
		*statPnt = operação + 2;
}
