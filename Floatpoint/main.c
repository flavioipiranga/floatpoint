/*
 * main.c
 *
 *  Created on: 04/09/2013
 *      Author: flavioipiranga
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "floatpoint.h"
/*
 *
 */
int main(int argc, char** argv) {
	char *in, *binfp;
	double num=0;
	in = malloc(sizeof(char)*33);

	printf("digite o numero binario que deseja converter\n");
	scanf("%s", in);
	num = StringToDouble(in,num);

	binfp = malloc(sizeof(char)*33);
	binfp = RealToFloatPoint(num, binfp);
	printf("O numero %f no padrao IEEE 754: %s %ld", num, binfp, strlen(binfp));
	return (EXIT_SUCCESS);
}


