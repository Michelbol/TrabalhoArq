#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
typedef char TIPOINFO[7];
typedef int TIPOCHAVE;

//fazer uma lista dinanica representando minha RAM
typedef struct estrutura{
	TIPOCHAVE posicao;
    TIPOCHAVE palavra;
    struct estrutura *prox;
} NO;
typedef struct {
    NO *inicio, *fim;
} RAM;
//inicializa a lista
void inicializar (RAM *ra){
    ra->inicio = NULL;
    ra->fim = NULL;
    printf("\nRAM Inicializada");
}
//mostra a RAM na tela
void mostraLista(RAM ra){
    NO* p = ra.inicio;
    printf("\nInicio ->[\n");
    while (p){
    	printf("Posicao: %i\n", p->posicao);
        printf("Palavra: %i",p->palavra);
            p=p->prox;
        if(p)
            printf(",\n");
    }
    printf("]<- Fim\n");
}

void inserir(TIPOCHAVE dado, TIPOCHAVE posicao, RAM *ra){
    NO *novo;
	novo = (NO*)malloc(sizeof(NO));
    novo->palavra = dado;
    novo->posicao = posicao;
	novo->prox = NULL;
	if(!ra->inicio)	{
		ra->inicio = novo;
	}else{
		ra->fim->prox = novo;
	}
	ra->fim = novo;
}

int remover(RAM *ra){
	NO *alvo;
	alvo = ra->inicio;
    if(!alvo){
    	printf("\nElemento nao encontrado");
    	 return 0;
	}
	if(ra->inicio == ra->fim){
		ra->fim = NULL;
	}
	ra->inicio = alvo->prox;
	alvo->prox = NULL;
	printf("\nDesempilhado: %I", alvo->palavra);
	free(alvo);
	
    return 1;
}

//NO* buscaSeq(TIPOCHAVE ch, RAM ra, NO* *ant){
//    NO* p = ra.inicio;
//    *ant = NULL;
//    while(p->chave < ch){
//		*ant = p;
//        p = p->prox;
//        if(p->prox == NULL){
//        	break;
//		}
//    }
//	if((p->prox == NULL) && (p->chave == ch)) {
//		return p;
//	}
//	return NULL;
//}


int main(){
	//definindo os registradores que serao usados
	//atencao AX = 1, BX = 2, CX = 3, DX = 4
	int PC=0,IR=0,MAR=0,MBR=0,AX=5,BX=0,CX=0,DX=0,SF=0,CF=0, ZF = 0;
	//variaveis auxiliares para serem utilizadas para obter informacoes
	int tamPalavra = 0, cont =0, cont2 = 0, dividInstr = 0, instrucao1Registrador = FALSE, instrucao2Registrador = FALSE, posicao1Memoria, posicao2Memoria;
	char registradores[5], sair[1], opcode[3], virgula[2], reg1[2], reg2[2];
	TIPOINFO palavra;
	strcpy(virgula, ",");
	//=========================Memoria Ram==============================================================================================================
	RAM ram;
	inicializar(&ram);
	inserir(5, 1, &ram);
	inserir(4, 2, &ram);
	inserir(6, 3, &ram);
	mostraLista(ram);
	//==================================================================================================================================================
	//printando os registradores
	printf("Registradores: \n PC: %i -- IR = %i -- MAR = %i -- MBR = %i -- AX = %i -- BX = %i -- CX= %i, DX = %i -- SF = %i -- CF = %i -- ZF = %i\n",
	PC,IR,MAR,MBR,AX,BX,CX,DX,SF,CF,ZF);
	system("pause");
	//inicio da contagem dos 30 comandos que podem ser escritos
	for(int i=0; i<30; i++){
		//usuario digita a instrucao que deseja
		printf("Digite a instrucao: ");
		scanf("%s %s", &opcode, &registradores);
		//identificacao da instrucao
		if((strncmp(opcode, "MOV", 3)) == 0){
			tamPalavra = strlen(registradores);
			while(cont < tamPalavra){
				if(registradores[cont] == virgula[0]){
					dividInstr = cont;
					strncpy(reg1, registradores, dividInstr);
					while(cont2 < dividInstr){
						reg2[cont2] = registradores[dividInstr+cont2+1];
						cont2++;	
					}					
					cont = tamPalavra;
				}
				cont++;
			}
			if(((strcmp(reg2, "AX")) == 0) || ((strcmp(reg2, "BX")) == 0) || ((strcmp(reg2, "CX")) == 0) || ((strcmp(reg2, "DX")) == 0)){
				if((strcmp(reg2, "AX")) == 0){
					instrucao2Registrador = 1;
				}else if((strcmp(reg2, "BX")) == 0){
					instrucao2Registrador = 2;
				}else if((strcmp(reg2, "CX")) == 0){
					instrucao2Registrador = 3;
				}else if((strcmp(reg2, "DX")) == 0){
					instrucao2Registrador = 4;
				}
			}else{
				posicao2Memoria = atoi(reg2);
				printf("posicao1Memoria: %i", posicao1Memoria);
				printf("REG1: %s", reg1);
			}
			if(((strcmp(reg1, "AX")) == 0) || ((strcmp(reg1, "BX")) == 0) || ((strcmp(reg1, "CX")) == 0) || ((strcmp(reg1, "DX")) == 0)){
				if((strcmp(reg1, "AX")) == 0){
					instrucao1Registrador = 1;
				}else if((strcmp(reg1, "BX")) == 0){
					instrucao1Registrador = 2;
				}else if((strcmp(reg1, "CX")) == 0){
					instrucao1Registrador = 3;
				}else if((strcmp(reg1, "DX")) == 0){
					instrucao1Registrador = 4;
				}
			}else{
				posicao1Memoria = atoi(reg1);
				printf("posicao1Memoria: %i", posicao1Memoria);
				printf("REG1: %s", reg1);
				printf("Busca na lista!\n");
			}
			
			if(instrucao1Registrador > 0 && instrucao2Registrador > 0){
				if(instrucao1Registrador == 1 &&  instrucao2Registrador == 2){
					AX = BX;
				}else if(instrucao1Registrador == 1 &&  instrucao2Registrador == 3){
					AX = CX;
				}else if(instrucao1Registrador == 1 &&  instrucao2Registrador == 4){
					AX = DX;
				}else if(instrucao1Registrador == 2 &&  instrucao2Registrador == 1){
					BX = AX;
					printf("ola\n");
				}else if(instrucao1Registrador == 2 &&  instrucao2Registrador == 3){
					BX = CX;
				}else if(instrucao1Registrador == 2 &&  instrucao2Registrador == 4){
					BX = DX;
				}else if(instrucao1Registrador == 3 &&  instrucao2Registrador == 1){
					CX = AX;
				}else if(instrucao1Registrador == 3 &&  instrucao2Registrador == 2){
					CX = BX;
				}else if(instrucao1Registrador == 3 &&  instrucao2Registrador == 4){
					CX = DX;
				}else if(instrucao1Registrador == 4 &&  instrucao2Registrador == 1){
					DX = AX;
				}else if(instrucao1Registrador == 4 &&  instrucao2Registrador == 2){
					DX = BX;
				}else if(instrucao1Registrador == 4 &&  instrucao2Registrador == 3){
					DX = CX;
				}
			}
			printf("Registradores: \n PC: %i -- IR = %i -- MAR = %i -- MBR = %i -- AX = %i -- BX = %i -- CX= %i, DX = %i -- SF = %i -- CF = %i -- ZF = %i\n",
			PC,IR,MAR,MBR,AX,BX,CX,DX,SF,CF,ZF);
//			printf("reg1: %i", reg1);
//			printf("reg2: %i", reg2);
			
		}else if((strncmp(opcode, "SUB", 3)) == 0){
			
		}else if((strncmp(opcode, "ADD", 3)) == 0){
			
		}else if((strncmp(opcode, "MUL", 3)) == 0){
			
		}else if((strncmp(opcode, "DIV", 3)) == 0){
			
		}else if((strncmp(opcode, "CMP", 3)) == 0){
			
		}else if((strncmp(opcode, "J", 1)) == 0){
			
		}else{
			printf("eh um dado!");
		}
		printf("Deseja sair s/n?");
		scanf("%s", sair);
		if(strcmp(sair, "s") == 0){
			i=30;
		}
	}
}
