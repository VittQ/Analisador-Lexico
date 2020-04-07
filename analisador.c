//---------------------------------------------> Analisador Léxico de Variáveis e Números <-------------------------------------------//

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

//automato
void e0();
void e1();
void e2();
void aceita();
void rejeita();


//sigmas
void sigma1();
void sigma2();
void sigma3();
void sigma4();
void sigma5();
void sigma6();

//vetores
char texto[100];
char tempS[100];
char tabVar[100][100];

//variaveis
int tempN = 0;
int s = 0; //tamanho do tempS
int x = 0; //percorrer texto

//flags
int qtdVar = 0; //quantidade de variaveis na tabela
int fpp = 0; //primeiro item da tabela



int main(void){
	
	printf("Entrada: \n");
	gets(texto);
	printf("\n");
	
	e0();
	
	getch();
	return 0;
}


// ----------------------------------------------> Sigmas <-----------------------------------------------
void sigma1(){
	//inicializar tempS
	int i = 0;
	for(i = 0; i<s; i++){
		tempS[i] = '\0';
	}
	
	tempS[0] = texto[x];
	s = 1;
}

void sigma2(){
	tempS[s] = texto[x];
	s++; 
}

void sigma3(){   
	
	//flags
	int var = 0; // flag para se existir na tabela de variaveis
	int ex = 0;	 // flag para saber a linha da variavel 
	
	//variaveis
	int i, j = 0;
	
	tempS[s] = '\0';
	
	//primeiro item da tabela
	if(fpp == 0){
		for(i=0; i<s; i++){
			tabVar[qtdVar][i] = tempS[i];
		}
		printf("V(%d) ", qtdVar);
		qtdVar = 1;
		fpp = 1;
	}
	
	else{
		// ver se existe na tabela
		for(i=0; i<qtdVar; i++){
			for(j=0; j<s; j++){
				if(tempS[j] == tabVar[i][j]){
					var = 1;
					ex = i;
				}
			}
		}
		
		// se não existir adiciona na tabela, se existir printa a posição da variavel
		if(var == 0){
			for(j=0; j<100; j++){
				tabVar[qtdVar][j] = tempS[j];
			}
			printf("V(%d) ", qtdVar);
			qtdVar++;
		}
		else{
			printf("V(%d) ", ex);
		}
	}
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
	printf("N(%d) ", tempN);
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
	
	//if para final do texto
	else if(texto[x] == '\0'){
		printf("\n\n -------------> Tabela de Variaveis <-------------");
		int i = 0;
		for(i = 0; i<qtdVar; i++){
			printf("\n%d ......... %s\n", i, tabVar[i]);
		}
			
		getch();
		system("PAUSE");
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
		
	//if para espaço ou final
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
