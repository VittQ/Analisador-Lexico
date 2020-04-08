
//---------------------------------------------> Analisador Léxico Completo <-------------------------------------------//


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>



//automato
void e0();
void e1();
void e2();
void e3();
void e4();
void e5();
void e6();
void aceita();
void rejeita();


//sigmas
void sigma1();
void sigma2();
void sigma3();
void sigma4();
void sigma5();
void sigma6();
void sigma7();
void sigma8();
void sigma9();
void sigma10();


//vetores
char texto[100];
char tempS[100];
char tabVar[100][100];
char reser[8][100];


//variaveis
int tempN = 0;
char tempC;
int s = 0;   //tamanho do tempS
int x = 0;   //percorrer entrada


//flags
int qtdVar = 0;  //quantidade de variaveis na tabela
int fpp = 0;     //primeiro item da tabela
int w = -1;      // localização da variavel





int main(void){
	
	printf("----------- Tabela de Palavras Reservadas -------------\n\n");
	arm("IF",2,0);
	arm("THEN",4,1);
	arm("ELSE",4,2);
	arm("GOTO",4,3);
	arm("LET",3,4);
	arm("END",3,5);
	arm("PRINT",5,6);
	arm("READ",4,7);
	arm("OF",2,8);
	
	printf("\n\n");
	
	printf("Entrada: \n");
	gets(texto);
	printf("\n");
	
	e0();
	
	getch();
	return 0;
}


void aceita(){
	printf("\n");
	printf("--------------------------------------------------\n");
	printf("		   Texto aceito.");
	getch();
	exit(0);
}


void rejeita(){
	printf("\n");
	printf("--------------------------------------------------\n");
	printf("		   Texto rejeitado.");
	getch();
	exit(0);	
}


// -----------------------------------> Armazenar as palavras reservadas <---------------------------------
void arm(char v[], int l, int lug){
	int i = 0;
	for(i=0; i<l; i++){
		reser[lug][i] = v[i];	
	}	
	
	printa(reser,l,lug);
}


void printa(char vetor[8][100], int l, int lug){
	int i = 0;
	printf("		P(%d) .......... ", lug);
	for(i=0; i<l; i++){
		printf("%c", vetor[lug][i]);
	}
	printf("\n");
}


//zerar tempS
void inicializa(){
	
	int i = 0;
	for(i = 0; i<100; i++){
		tempS[i] = '\0';
	}	
}

// ----------------------------------------------> Sigmas <-----------------------------------------------
void sigma1(){
	
	inicializa();
	
	tempS[0] = texto[x];
	s = 1;
}

void sigma2(){
	
	tempS[s] = texto[x];
	s++; 
}

void sigma3(){   
	
	
	//flags
	int var = 0; // flag para caso exista na tabela de variaveis
	int ex = 0;	 // flag para saber a linha da variavel 
	int re = 0;  // se é uma palavra reservada
	
	//variaveis
	int i, j = 0;
	
	
	tempS[s] = '\0';
	
	
	// verificar se é palavra reservada            
	for(i=0; i<9; i++){
		for(j=0; j<s; j++){
			
			if(tempS[j] == reser[i][j]){
				
				if(reser[i][j+1] == '\0' && tempS[j+1] == '\0'){   //  if(reser[i][j+1] == '\0' /*|| tempS[j+1] == '\0'*/)
					w = i;
					re = 1;
				}	
			}
			
			else{
				re = 0;
				break;
			}
		}
		
		if(re == 1){
			break;
		}
	}
	
	if(re == 1){
		printf("P(%d)", w);
	}
	
	else{
		//primeiro item da tabela
		if(fpp == 0){
			for(i=0; i<s; i++){
				tabVar[qtdVar][i] = tempS[i];
			}
			
			printf("V(%d)", qtdVar);
			qtdVar = 1;
			fpp = 1;
		}
		
		else{
			// ver se existe na tabela     
			for(i=0; i<qtdVar; i++){
				for(j=0; j<s; j++){
					
					if(tempS[j] == tabVar[i][j]){
						if(tempS[j+1] == '\0' && tabVar[i][j+1] == '\0'){
							var = 1;
							ex = i;	
						}	
					}
					
					else{
						var = 0;
						break;
					}
				}
				
				if(var == 1){
					break;
				}
			}
			
			// se não existir adiciona na tabela, se existir printa a posição da variavel
			if(var == 0){
				for(j=0; j<100; j++){
					tabVar[qtdVar][j] = tempS[j];
				}
				
				printf("V(%d)", qtdVar);
				qtdVar++;
			}
			
			else{
				printf("V(%d)", ex);
			}
		}
	}
	
	inicializa();
}


void sigma4(){
	
	int a = texto[x] - '0';
	tempN = a;
}


void sigma5(){
	int b = texto[x] - '0';
	tempN = tempN * 10;
	tempN = tempN + b;
}


void sigma6(){
	printf("N(%d)", tempN);
}


void sigma7(){
	printf(":");
}


void sigma8(){
	printf(":=");
}


void sigma9(){
	tempC = texto[x];
}


void sigma10(){
	printf("%c", tempC);
}




// ----------------------------------------------> Estados <-----------------------------------------------
void e0(){
	
	//if para letra
	if(isalpha(texto[x])){
		sigma1();
		x++;
		e1();
	}	
	
	
	//if para numero
	else if(isdigit(texto[x])){
		sigma4();
		x++;
		e2();
	}
	
	
	//if para espaço
	else if(texto[x] == ' '){
		x++;
		e0();
	}
	
	
	//if para ":"
	else if(texto[x] == ':'){
		x++;
		e3();
	}
	
	
	//if para "%"
	else if(texto[x] == '%'){
		x++;
		e6();
	}
	
	
	//if para outros
	else if(texto[x] == '.' || texto[x] == '#' ||texto[x] == '&' || texto[x] == '$' || texto[x] == '!' || texto[x] == '@' || texto[x] == '(' || 
			texto[x] == ')' || texto[x] == ';' || texto[x] == '>' || texto[x] == '<' || texto[x] == '=' || texto[x] == ',' || texto[x] == '+' || 
			texto[x] == '-' || texto[x] == '*' || texto[x] == '/' || texto[x] == '¨' || texto[x] == '\\' || texto[x] == ':' ){
		sigma9(); 
		x++;
		e5();
	}
	
	
	//if para final do texto
	else if(texto[x] == '\0'){
		printf("\n\n-------------> Tabela de Variaveis <-------------\n");
		
		int i = 0;
		for(i = 0; i<qtdVar; i++){
			printf("\n%d ......... %s\n", i, tabVar[i]);
		}
		
		printf("\n");
		aceita();
		system("PAUSE");
	}
	
	
	else{
		rejeita();
	}
}


void e1(){
	
	//if para letra
	if(isalpha(texto[x])){
		sigma2();
		x++;
		e1();
	}
		
		
	//if para numero
	else if(isdigit(texto[x])){
		sigma2();
		x++;
		e1();
	}
		
	
	else{
		sigma3();
		e0();
	}
}


void e2(){
		
	//if para numero
	if(isdigit(texto[x])){
		sigma5();
		x++;
		e2();
	}
		
		
	else{
		sigma6();
		e0();
	}
				
}


void e3(){
	
	//if para "="
	if(texto[x] == '='){
		x++;
		e4();
	}
	
	
	else{
		sigma7();
		e0();
	}
}


void e4(){
	sigma8();
	e0();
}


void e5(){
	sigma10();
	e0();
}


void e6(){
	//rodar até o final da entrada
	if(texto[x] == '\0'){
		e0();
	}
	
	else{
		x++;
		e6();
	}
}


