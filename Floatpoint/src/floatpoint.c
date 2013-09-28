/*
 * floatpoint.c
 *
 *  Created on: 05/09/2013
 *      Author: flavioipiranga
 */

/*! \mainpage My Personal Index Page
 *
 * \section intro_sec Introduction
 *
 * This is the introduction.
 *
 * \section install_sec Installation
 *
 * \subsection step1 Step 1: Opening the box
 *
 * etc...
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <gmp.h>

#define BIT0  "0"
#define BIT1  "1"
#define SVIES  127
#define DVIES  1023
#define SSIGN  23
#define DSIGN  52
#define SPREC  1
#define DPREC  2

typedef struct Normbin{
	char *exp;
	char *bin;
	int sinal;
}normbin;
/**
 *
 * @param string
 * @return
 */
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
float StringToDouble(char* in){
	double num;

	sscanf(in, "%lf", &num);

	return num;
}
/**
 *
 * @param real Nœmero representado pelo conjunto dos nœmeros reais
 * @return 	Nœmero transformado para bin‡rio
 */
char* IntToBin(long int real, int prec){
	int sign;

	if(prec == SPREC)
		sign = SSIGN;
	else sign = DSIGN;

	char* bin = malloc(sizeof(char)*(sign+2));

	int i;

	long int deci;
	deci = real;

	if(deci == 0)
		strcat(bin, BIT0);

	for(i = 0; i<sign+2; i++){
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



char* ExpToBin (int exp, int prec){
	int i, max;
	char *bin;

	if(prec == SPREC){
		max = 8;

	}
	if(prec == DPREC){
		max = 11;

	}

	bin =malloc(sizeof(char)*max);
	printf("expoente %d\n", exp);

	for(i = 0; i<max; i++){

		if(exp%2)
			strcat(bin,"1");
		else strcat(bin,"0");

		exp = exp/2;
	}

	strcpy(bin, InvString(bin));

	return bin;
}

normbin Normalize(char* bin, int prec, int sinal, int expoente){

	normbin nbin;
	char *p, *bexp, auxs, *aux;
	int pos = 0, exp = expoente, i, j;

	realloc(bin, sizeof(char)*1);

	strcat(bin, ".");
	printf("lala bin %s\n", bin);

	nbin.sinal = sinal;

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
		nbin.exp = ExpToBin(exp, prec);

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
		nbin.exp = ExpToBin(exp, prec);
		nbin.bin = malloc(sizeof(char)*52);

		strncpy(nbin.bin, &bin[2], sizeof(char)*52);

	}

	return nbin;
}

void BigNumToBin(char* num, int prec){

	mpz_t q,r, dividendo, divisor, suplimit, inflimit, sign;

	mpz_init(q);
	mpz_init(suplimit);
	mpz_init(inflimit);

	mpz_init(sign);

	mpz_init(r);
	mpz_init(dividendo);
	mpz_init(divisor);

	int tam;

	if(prec == SPREC){

		tam = 23;

	}

	else{
		tam =52;

	}
	char *in = malloc(sizeof(char)*tam);
	char *frac = malloc(sizeof(char)*tam);

	int pos, i=0;
	char *p = malloc(sizeof(char)*2);

	normbin nb;
	int sinal, exp=0;

	if(num[0] == '-'){
		sinal = 1;
		num[0] = '0';
	}
	else sinal = 0;

	printf("STRING NUM %s\n", num);


	if(strchr(num, '.') != NULL){
		p =  strchr(num, '.');
		pos = p-num;

		strncpy(in, &num[0], sizeof(char)*(pos));
		strncpy(frac, &num[pos+1], sizeof(char) * (strlen(num) - pos));

		if((strlen(in)+strlen(frac)) > tam){
			printf("numero grande\n");
		}
		else{
			num = in;
			strcat(num, frac);
			mpz_set_str(sign, num, 10);
			mpz_ui_pow_ui(divisor, 10, strlen(frac));

		}

	}
	else{
		mpz_set_str(sign, num, 10);
		mpz_ui_pow_ui(divisor, 10, 0);
	}

	mpz_ui_pow_ui(inflimit, 2, tam);
	mpz_ui_pow_ui(suplimit, 2, tam+1);
	mpz_sub_ui(suplimit, suplimit, 1);


	mpz_tdiv_q(q, sign, divisor);
	gmp_printf ("numero%Zd %Zd\n", sign, divisor);

	while(mpz_cmp(q, inflimit)<0){
		mpz_mul_ui(sign, sign, 2);
		mpz_tdiv_q(q, sign, divisor);
		exp--;
	}

	while(mpz_cmp(q, suplimit)>0){
		mpz_tdiv_q_ui(sign, sign, 2);
		mpz_tdiv_q(q, sign, divisor);
		exp++;
	}


	mpz_tdiv_q(sign, sign, divisor);
	gmp_printf("%Zd %Zd\n", sign, divisor);

	//printf("%ld tam %lu", mpz_get_si(sign), sizeof(int)*1);

	printf("Resultado %s\n", IntToBin(mpz_get_si(sign), prec));

	printf("sinal aqui %d\n", nb.sinal);
	nb = Normalize(IntToBin(mpz_get_si(sign), prec), prec, sinal, exp);

	printf("SINAL:%d EXPOENTE:%s SIGNIFICANTE:%s\n", nb.sinal, nb.exp, nb.bin);


	/* free used memory */
	mpz_clear(dividendo);
	mpz_clear(divisor);
	mpz_clear(q);
	mpz_clear(r);
}

char *BinToNum(char* bin){
	int tamexp, tamsign, i, sinal;

	int exp = 0, e, vies;
	double sign, num;
	if(bin[0] == '0')
		sinal = 0;
	else sinal = 1;

	if(strlen(bin) == 32){
		tamexp = 8;
		vies =SVIES;
	}
	else if(strlen(bin) == 64){
		tamexp = 11;
		vies = DVIES;
	}
	printf("%d\n", exp);


	for(i=1, e=7; i<tamexp+1; i++, e--){
		if(bin[i] == '1'){
			exp = exp + pow(2, e);
			printf("%d\n", exp);

		}
	}

	for(i=9, e=1; i<strlen(bin); i++, e++){
			if(bin[i] == '1'){
				sign = sign + 1/pow(2, e);
			}

		}

	printf("expoente: %d significante: %.16lf", exp, sign);

	num = pow(-1, sinal)*pow(2, exp-127)*(1+sign);

	printf("numero final %.16lf", num);

	return bin;

}
