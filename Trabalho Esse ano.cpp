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


int main(){
	//definindo os registradores que serao usados
	int PC=0,IR=0,MAR=0,MBR=0,AX=0,BX=0,CX=0,DX=0,SF=0,CF=0;
	//variaveis auxiliares para serem utilizadas para obter informacoes
	int tamPalavra = 0, cont =0, dividInstr = 0;
	char sair[1], opcode[3], reg1[2], reg2[2], virgula[1], registradores[5];
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
	printf("Registradores: \n PC: %i -- IR = %i -- MAR = %i -- MBR = %i -- AX = %i -- BX = %i -- CX= %i, DX = %i -- SF = %i -- CF = %i\n", PC,IR,MAR,MBR,AX,BX,CX,DX,SF,CF);
	system("pause");
	//inicio da contagem dos 30 comandos que podem ser escritos
	for(int i=0; i<30; i++){
		//usuario digita a instrucao que deseja
		printf("Digite a instrucao: ");
		scanf("%s %s", &opcode, &registradores);
		//identificacao da instrucao
		if((strncmp(palavra, "MOV", 3)) == 0){
			tamPalavra = strlen(registradores);
			while(cont < tamPalavra){
				if(registradores[cont] == virgula[0]){
					strncpy(reg1,registradores, dividInstr);
					dividInstr = cont;
					cont = tamPalavra;
				}
				cont++;
					printf("Reg1: %s\n", reg1);
			printf("DividInstr: %i\n", dividInstr);
			printf("TamPalavra: %i\n", tamPalavra);
		}
			
		}else if((strncmp(palavra, "SUB", 3)) == 0){
			
		}else if((strncmp(palavra, "ADD", 3)) == 0){
			
		}else if((strncmp(palavra, "MUL", 3)) == 0){
			
		}else if((strncmp(palavra, "DIV", 3)) == 0){
			
		}else if((strncmp(palavra, "CMP", 3)) == 0){
			
		}else if((strncmp(palavra, "J", 1)) == 0){
			
		}
		printf("Deseja sair s/n?");
		scanf("%s", sair);
		if(strcmp(sair, "s") == 0){
			i=30;
		}
	}
}
