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
 * @param real N�mero representado pelo conjunto dos n�meros reais
 * @return 	N�mero transformado para bin�rio
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

int BinToInt(char *bin){

	printf("bin %s\n", bin);
	int i, j, num=0;
	for(i = strlen(bin)-1, j=0; i>=0; i--, j++){
		if(bin[i] == '1')
			num = num + pow(2, j);
	}

	return num;

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

	if(strchr(bin, '.') == NULL){
		bin = realloc(bin, sizeof(char)*1);
		strcat(bin, ".");
	}

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

normbin BigNumToBin(char* num, int prec){

	mpz_t q,r, dividendo, divisor, suplimit, inflimit, sign;


	mpz_init(q);
	mpz_init(suplimit);
	mpz_init(inflimit);

	mpz_init(sign);

	mpz_init(r);
	mpz_init(dividendo);
	mpz_init(divisor);

	int tam=0;

	if(prec == SPREC){
		tam = 23;
	}

	else{
		tam =52;
	}

	int sinal=0, exp=0;

	if(num[0] == '-'){
		sinal = 1;
		num[0] = '0';
	}
	char *in = malloc(sizeof(char)*311);
	char *frac = malloc(sizeof(char)*311);

	int pos, i=0;
	char *p = malloc(sizeof(char)*2);
	normbin nb;


	if(strchr(num, '.') != NULL){
		p =  strchr(num, '.');
		pos = p-num;

		strncpy(in, &num[0], sizeof(char)*(pos));
		strncpy(frac, &num[pos+1], sizeof(char) * (strlen(num) - pos));


		num = in;
		strcat(num, frac);
		mpz_set_str(sign, num, 10);
		mpz_ui_pow_ui(divisor, 10, strlen(frac));
	}
	else{
		mpz_set_str(sign, num, 10);
		mpz_ui_pow_ui(divisor, 10, 0);
	}

	mpz_ui_pow_ui(inflimit, 2, tam);
	mpz_ui_pow_ui(suplimit, 2, tam+1);
	mpz_sub_ui(suplimit, suplimit, 1);


	mpz_tdiv_q(q, sign, divisor);

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

	nb = Normalize(IntToBin(mpz_get_si(sign), prec), prec, sinal, exp);

	/* free used memory */
	mpz_clear(dividendo);
	mpz_clear(divisor);
	mpz_clear(q);
	mpz_clear(r);

	return nb;
}

double BinToNum(char* bin){
	int tamexp, tamsign, i, sinal;

	int  vies;
	int e;
	double sign, num;


	double exp =0 ;

	char* out= malloc(sizeof(char)*312);

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


	for(i=1, e=7; i<tamexp+1; i++, e--){
		if(bin[i] == '1'){
			exp = exp + pow(2, e);
		}
	}

	for(i=9, e=1; i<strlen(bin); i++, e++){
		if(bin[i] == '1'){
			sign = sign + 1/pow(2, e);

		}

	}
	num = pow(-1, sinal)*pow(2, exp-127)*(1+sign);
	return num;
}

double Add(char* in1, char* in2, int prec){

	char *num1, *num2, *aux;
	char carry = '0';
	int tam, j, i, sinal, tamexp, tamsign, vies;
	normbin nb1, nb2;
	normbin fp;

	if(prec == SPREC){
		tam = 33;
		tamexp = 8;
		tamsign = 23;
		vies = SVIES;
		aux = malloc(sizeof(char)*33);
	}
	else{
		tam = 65;
		tamexp = 11;
		tamsign = 52;
		vies =DVIES;
		aux = malloc(sizeof(char)*65);

	}

	num1 = malloc(sizeof(char)*tam);
	num2 = malloc(sizeof(char)*tam);

	nb1 = BigNumToBin(in1, prec);
	nb2 = BigNumToBin(in2, prec);

	sinal = nb1.sinal;

	char *frac1 = malloc(sizeof(char)*(tamsign+3));
	char *frac2 = malloc(sizeof(char)*(tamsign+3));

	strcat(frac1, "1.");
	strcat(frac2, "1.");
	strcat(frac1, nb1.bin);
	strcat(frac2, nb2.bin);

	if(strcmp(nb1.exp, nb2.exp) < 0){

		printf("menor");
	}

	else if(strcmp(nb1.exp, nb2.exp) > 0){
		printf("maior");
	}

	char *result = malloc(sizeof(char)*(tamsign+3));
	result[tamsign+2] = '\0';

	for(i = tamsign, j = tamsign+1; i>=0 ; i--, j--){
		if(frac1[i] == '0' && frac2[i] == '0'){
			if(carry == '0'){
				result[j] = '0';
				carry = '0';
			}

			else {
				result[j] = '1';
				carry = '0';
			}
		}
		if((frac1[i] == '1' && frac2[i] == '0') || (frac1[i] == '0' && frac2[i] == '1')){
			if(carry == '0'){
				result[j] = '1';
				carry = '0';
			}
			else {
				result[j] = '0';
				carry = '1';
			}
		}

		if(frac1[i] == '1' && frac2[i] == '1'){
			if(carry == '0'){
				result[j] = '0';
				carry = '1';
			}
			else{
				result[j] = '1';
				carry = '1';
			}
		}

		if(frac1[i] == '.' ){
			result[j] = '.';
		}

		if(i == 0){
			result[0] = carry;
		}
	}

	printf("debug %d \n", BinToInt(nb1.exp)-vies);
	fp = Normalize(result, prec, sinal, BinToInt(nb1.exp)-vies);
	printf("fp.sinal %d, fp.exp %s, fp.sign %s", fp.sinal, fp.exp, fp.bin);

	if(fp.sinal)
		strcat(aux, "1");
	else strcat(aux,"0");

	strcat(aux, fp.exp);
	strcat(aux, fp.bin);

	printf("saida %.16lf", BinToNum(aux));
	return BinToNum(aux);

}
