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
	char *in, *bin;
	double num=0;
	in = malloc(sizeof(char)*32);
	bin = malloc(sizeof(char)*32);

	printf("digite\n");
	scanf("%s", in);
	num = StringToDouble(in,num);

	printf("binario %s", RealToFloatPoint(num, bin));
	return (EXIT_SUCCESS);
}


