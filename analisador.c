// Victor Antonio Silva de Queiroga
// 22117054-1

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

//automato
void e0();
void e1();
void e2();


//sigmas
void sigma1();
void sigma2();
void sigma3();
void sigma4();
void sigma5();
void sigma6();


//vetores
char tempS[10];
char texto[30];


//variaveis
int tempN = 0;
int i, x = 0;
int n = 0; // percorrer tempS
int u, e = 0; //testar se esta na lista


//matriz
char tabVar[6][5];


//flags
int fpp = 0;  // primero item da matriz


int main(void){
	
	printf("Entrada: \n");
	gets(texto);
	printf("\n");
	
	e0();
	
	
	printf("\n");

	system("PAUSE");
	return 0;
}


void sigma1(){
	tempS[n] = texto[i];
	n++;	
	e = 0;
}


void sigma2(){
	tempS[n] = texto[i];
	n++;
}


void sigma3(){
	// primeiro item da lista
	if(fpp == 0){
		while(tempS[x] != '\0'){
			tabVar[fpp][x] = tempS[x];
			x++;
		}
		printf("V(%d) ", fpp);
		fpp++;
	}
	
	// caso não seja o primeiro item da lista
	else{
		// vê se já existe na lista
		for(u=0; u<fpp; u++){
			for(x=0; x<5; x++){
				if(tabVar[u][x] == tempS[x]){
					e=1;
				}
				else{
					e=0;
					break;
				}
			}
		}
		
		// se não existir então adiciona na lista
		if(e == 0){
			x=0;
			while(tempS[x] != '\0'){
				tabVar[fpp][x] = tempS[x];
				x++;
			}
			printf("V(%d) ", fpp);
			fpp++;
		}
		
		//caso já exista imprime o valor da variavel
		else{
			printf("V(%d) ", u-1);
		}
	}
	
	n = 0;
	x = 0;
}


void sigma4(){
	int a = texto[i] - '0';
	tempN = a;
}


void sigma5(){
	int b = texto[i] - '0';
	tempN = tempN * 10;
	tempN = tempN + b;
}


void sigma6(){
	printf("N(%d) ", tempN);
}
 
 
void e0(){
	
	if(isalpha(texto[i])){
		sigma1();
		i++;
		e1();
	}
		
	else if(isdigit(texto[i])){
		sigma4();
		i++;
		e2();
	}
		
	else if(texto[i] == ' '){
		i++;
		e0();
	}
	
	else if(texto[i] == '\0'){
		system("PAUSE");
		
	}
}


void e1(){
	
	if(isalpha(texto[i])){
		sigma2();
		i++;
		e1();
	}
		
	else if(isdigit(texto[i])){
		sigma2();
		i++;
		e1();
	}
		
	else if(texto[i] == ' '){
		sigma3();
		i++;
		e0();
	}
	
	else if(texto[i] == '\0'){    
		sigma3();
		e0();
	}		
}


void e2(){
	
	if(isalpha(texto[i])){
		sigma6();
		tempN = 0;
		tempS[0] = '\0';
		e0();
	}
		
	else if(isdigit(texto[i])){
		sigma5();
		i++;
		e2();
	}
		
	else if(texto[i] == ' '){
		sigma6();
		i++;
		e0();
	}
		
	else if(texto[i] == '\0'){
		sigma6();
	}			
}

