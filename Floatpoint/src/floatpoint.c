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
double StringToDouble(char* in, double num){

	char **endptr;

	num = strtod(in, endptr);

	return num;

}

char* IntToBin(double real, char* bin){
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


char* FloatToBin (double real, char* bin) {

	int i, aux=0;
	double deci, frac;

	deci = real;
	frac = real - frac;

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

char* ExpToBinSimple (int exp, char* bini, int prec){
	int i, max;

	if(prec == SPREC)
		max = 8;

	if(prec == DPREC)
		max = 11;


	for(i = 0; i<max; i++){

		if(exp%2)
			bini[i] = '1';
		else bini[i] = '0';

		exp = exp/2;
	}

	strcpy(bini, InvString(bini));


	return bini;
}

normbin Normalize(char* bin, normbin nbin, int prec){

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

		bexp = malloc(sizeof(char)*9);
		bexp = ExpToBinSimple(exp,bexp,prec);
		strncpy(nbin.bin, &bin[2], sizeof(char)*23);
		nbin.exp = bexp;
	}

	if(prec == DPREC){
		exp = exp+DVIES;

		bexp = malloc(sizeof(char)*12);
		bexp = ExpToBinSimple(exp,bexp,prec);

		strncpy(nbin.bin, &bin[2], sizeof(char)*52);
		nbin.exp = bexp;

	}

	return nbin;
}

char* RealToFloatPoint(double num, char* binfp,int prec){
	char *binint, *binfra, *binexp;
	char *bin;
	char *bsig;
	normbin nbin;

	if(num < 0){
		num = num * -1;
		bsig = "1";
	}

	else bsig = "0";

	binint = malloc(sizeof(char)*33);
	binfra = malloc(sizeof(char)*33);

	bin = malloc(sizeof(char)*66);

	binint = IntToBin(num, binint);
	strcat(bin,binint);
	free(binint);

	strcat(bin,".");

	binfra = FloatToBin(num,binfra);
	strcat(bin,binfra);
	free(binfra);

	if(prec == SPREC){
		nbin.bin = malloc(sizeof(char)*24);
		nbin.exp = malloc(sizeof(char)*9);

		nbin = Normalize(bin, nbin, prec);

	}

	if(prec == DPREC){
		nbin.bin = malloc(sizeof(char)*53);
		nbin.exp = malloc(sizeof(char)*12);

		nbin = Normalize(bin, nbin, prec);
	}

	strcat(binfp, bsig);
	strcat(binfp, nbin.exp);
	strcat(binfp, nbin.bin);

	return binfp;

}


