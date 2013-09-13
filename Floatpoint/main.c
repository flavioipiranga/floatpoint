/*
 * main.c
 *
 *  Created on: 04/09/2013
 *      Author: flavioipiranga
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./src/floatpoint.h"
/*
 *
 */
int main(int argc, char** argv) {
	char *in, *binfp;
	double num=0;
	in = malloc(sizeof(char)*33);
	int prec;

	printf("digite o numero real que deseja converter para binario\n");
	scanf("%s", in);

	printf("Digite o numero da precisao que deseja utilizar:\n");
	printf("1) Precisao simples\n");
	printf("2) Precisao dupla\n");
	scanf("%d", &prec);

	num = StringToDouble(in,num);

	if(prec == 1)
		binfp = malloc(sizeof(char)*33);

	if(prec == 2)
		binfp = malloc(sizeof(char)*65);

	binfp = RealToFloatPoint(num, binfp, prec);
	printf("O numero %f no padrao IEEE 754: %s", num, binfp);
	return (EXIT_SUCCESS);
}


