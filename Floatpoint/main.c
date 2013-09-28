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
	char* in, *in2;
	char *binfp;
	double num=0;
	int prec;

	if(!(in = malloc(sizeof(char)*53)))
	{
		fprintf(stderr, "Memoria insuficiente");
		exit(EXIT_FAILURE);
	}

	if(!(in2 = malloc(sizeof(char)*33)))
	{
		fprintf(stderr, "Memoria insuficiente");
		exit(EXIT_FAILURE);
	}

	printf("digite o numero real que deseja converter para binario\n");
	scanf("%s", in);

	printf("Digite o numero da precisao que deseja utilizar:\n");
	printf("1) Precisao simples\n");
	printf("2) Precisao dupla\n");
	scanf("%d", &prec);

	BigNumToBin(in, prec);

	BinToNum("00111111111111111111111111111111");
	return (EXIT_SUCCESS);
}
//21321312321312321321312
//12345678901234567000000
