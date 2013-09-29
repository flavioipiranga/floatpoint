/*
 * main.c
 *
 *  Created on: 04/09/2013
 *      Author: flavioipiranga
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/floatpoint.h"
#include <gmp.h>
/*
 *
 */


int main(int argc, char** argv) {
	//char *in;
	char* in1, *in2;
	char *binfp;
	double num=0, r;
	int prec;
	int op;
	normbin nb;

	/*if(!(in1 = malloc(sizeof(char)*312)))
	{
		fprintf(stderr, "Memoria insuficiente");
		exit(EXIT_FAILURE);
	}

	if(!(in2 = malloc(sizeof(char)*312)))
	{
		fprintf(stderr, "Memoria insuficiente");
		exit(EXIT_FAILURE);
	}*/

	do{
		printf("Bem-vindo ao software FP.\n\n\n");

		printf("Menu de opcoes:\n");
		printf("(1) Converter numero para binario.\n");
		printf("(2) Converter binario para numero.\n");
		printf("(3) Converter precisao simples para precisao dupla.\n");
		printf("(4) Converter precisao dupla para precisao simples.\n");
		printf("(5) Adicao.\n");
		printf("(6) Subtracao.\n");
		printf("(7) Multiplicacao.\n");
		printf("(8) Divisao.\n");
		printf("(9) Raiz quadrada.\n");
		printf("(0) Sair.\n");

		printf("Digite sua opcao:");
		scanf("%d", &op);

		switch(op){

		case 1:
			printf("Escolha precisao:\n");
			printf("1) Precisao simples\n");
			printf("2) Precisao dupla\n");
			scanf("%d", &prec);

			if(prec == 1){
				in1 = realloc(in1, sizeof(char)*43);
			}
			else in1 = realloc(in1, sizeof(char)*313);

			printf("Digite o numero real que deseja converter para binario:\n");
			scanf("%s", in1);

			nb = BigNumToBin(in1, prec);
			printf("Sinal: %d Expoente: %s Significante: %s\n", nb.sinal, nb.exp, nb.bin);
			printf("%d%s%s\n", nb.sinal, nb.exp, nb.bin);
			break;

		case 2:
			printf("Escolha precisao:\n");
			printf("1) Precisao simples\n");
			printf("2) Precisao dupla\n");
			scanf("%d", &prec);

			if(prec == 1){
				in1 = realloc(in1, sizeof(char)*33);
			}
			else in1 = realloc(in1, sizeof(char)*65);

			printf("Digite o numero binario que deseja converter para real:\n");
			scanf("%s", in1);

			r = BinToNum(in1);
			printf("Numero eh igual %.16lf\n", r);
			break;
		}

	}while(op!=0);




	//BigNumToBin(in, prec);



	//BinToNum("00111111111111111111111111111111");

	//Add(in1, in1, 1);
	return (EXIT_SUCCESS);
}
//21321312321312321321312
//12345678901234567000000
//0.000000000000000000000000000000000000012
