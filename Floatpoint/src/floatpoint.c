/*
 * floatpoint.c
 *
 *  Created on: 05/09/2013
 *      Author: flavioipiranga
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BIT0  "0"
#define BIT1  "1"
#define SVIES  127
#define DVIES  1023
#define SPREC  1
#define DPREC  2

typedef struct Normbin{
	char *exp;
	char *bin;
}normbin;

//Apenas inverte uma string
char* InvString(char* string){
	int tam =0, j, i;
	char* aux;

	// obtendo o tamanho da string
	while(string[tam] != '\0')
		tam++;

	// alocando espaco
	aux = (char*)malloc(tam * sizeof(char));
	for(i = tam - 1, j = 0; i >= 0; i--, j++)
		aux[j] = string[i];
	aux[j] = '\0';

	return aux;

}

//Recebe a string contendo o numero real e transforma para tipo double
double StringToDouble(char* in){
	double num;

	sscanf(in, "%lf", &num);

	return num;
}

char* IntToBin(double real){

	char* bin = malloc(sizeof(char)*33);

	int deci, i;
	deci = real;

	if(deci == 0)
		strcat(bin, BIT0);

	for(i = 0; i<32; i++){
		if(deci == 0)
			break;

		if(deci%2)
			strcat(bin, BIT1);

		else strcat(bin, BIT0);

		deci = deci/2;

	}

	strcpy(bin, InvString(bin));

	return bin;
}


char* FloatToBin (double real) {


	int i, aux=0;
	double deci, frac;

	deci = real;
	frac = real - frac;
	char* bin = malloc(sizeof(char)*33);

	//tamanho eh de 32 bits pois no MIPS os registradores possuem 32 bits
	for(i = 0; i<32; i++){

		frac = 2*frac;
		aux = frac;
		frac = frac - aux;

		if(aux == 1)
			strcat(bin, BIT1);

		else strcat(bin, BIT0);

	}

	return bin;
}

char* ExpToBinSimple (int exp, int prec){
	int i, max;
	char* bin = malloc(sizeof(char)*33);

	if(prec == SPREC)
		max = 8;

	if(prec == DPREC)
		max = 11;


	for(i = 0; i<max; i++){

		if(exp%2)
			bin[i] = '1';
		else bin[i] = '0';

		exp = exp/2;
	}

	strcpy(bin, InvString(bin));


	return bin;
}

normbin Normalize(char* bin, int prec){

	normbin nbin;
	char *p, *bexp, auxs, *aux;
	int pos = 0, exp=0, i, j;

	if(bin[0] == '0'){
		while(bin[0] == '0'){

			p =  strchr(bin, '.');
			pos = p-bin;

			if(bin[pos - 1] == '1')
				break;

			auxs = bin[pos + 1];
			bin[pos + 1] = '.';
			bin[pos] = auxs;

			exp--;

		}
	}
	else {
		while(bin[1] != '.'){

			p =  strchr(bin, '.');
			pos = p-bin;
			auxs = bin[pos - 1];
			bin[pos - 1] = '.';
			bin[pos] = auxs;

			exp++;

		}
	}

	if(prec == SPREC){

		exp = exp+SVIES;

		if(!(nbin.exp = malloc(sizeof(char)*9)))
		{
			fprintf(stderr, "Memoria insuficiente");
			exit(EXIT_FAILURE);
		}
		nbin.exp = ExpToBinSimple(exp, prec);

		if(!(nbin.bin = malloc(sizeof(char)*23)))
		{
			fprintf(stderr, "Memoria insuficiente");
			exit(EXIT_FAILURE);
		}


		strncpy(nbin.bin, &bin[2], sizeof(char)*23);
	}

	if(prec == DPREC){
		exp = exp+DVIES;

		nbin.exp = malloc(sizeof(char)*12);
		nbin.exp = ExpToBinSimple(exp, prec);
		nbin.bin = malloc(sizeof(char)*52);

		strncpy(nbin.bin, &bin[2], sizeof(char)*52);

	}

	return nbin;
}

char* RealToFloatPoint(double num, int prec){
	char *binint, *binfra;
	char *bin;
	char *bsig, *binfp;
	normbin nbin;

	if(prec == 1)
		binfp = malloc(sizeof(char)*33);

	if(prec == 2)
		binfp = malloc(sizeof(char)*65);

	if(num < 0){
		num = num * -1;
		bsig = "1";
	}

	else bsig = "0";

	binint = malloc(sizeof(char)*33);
	binfra = malloc(sizeof(char)*33);

	bin = malloc(sizeof(char)*66);

	binint = IntToBin(num);
	strcat(bin,binint);
	free(binint);

	strcat(bin,".");

	binfra = FloatToBin(num);
	strcat(bin,binfra);
	free(binfra);

	if(prec == SPREC){
		nbin.bin = malloc(sizeof(char)*24);
		nbin.exp = malloc(sizeof(char)*9);

		nbin = Normalize(bin, prec);

	}

	if(prec == DPREC){
		nbin.bin = malloc(sizeof(char)*53);
		nbin.exp = malloc(sizeof(char)*12);

		nbin = Normalize(bin, prec);
	}
	free(bin);

	strcat(binfp, bsig);
	strcat(binfp, nbin.exp);
	strcat(binfp, nbin.bin);

	return binfp;

}


