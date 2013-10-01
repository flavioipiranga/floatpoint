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

	char* bin = malloc(sizeof(char)*(sign+1+1));

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

	int i, j, num=0;
	for(i = strlen(bin)-1, j=0; i>=0; i--, j++){
		if(bin[i] == '1')
			num = num + pow(2, j);
	}

	return num;

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

	bin =malloc(sizeof(char)*(max+1));

	for(i = 0; i<max; i++){

		if(exp%2)
			strcat(bin,"1");
		else strcat(bin,"0");

		exp = exp/2;
	}

	strcpy(bin, InvString(bin));
	return bin;
}
int Normalize(normbin *nbin, char* bin, int prec, int sinal, int expoente){

	char *p, *bexp, auxs, *aux;
	int pos = 0, exp = expoente, i, j, qntd = 0;


	if(strchr(bin, '.') == NULL){
		bin = realloc(bin, sizeof(char)*(strlen(bin)+1+1));
		strcat(bin, ".");
	}

	if(bin[0] == '0' && (bin[1] == '0' || bin[1] == '1') && bin[2] == '.' && strchr(bin, '1')!=NULL){
		for(i = 0; i<=strlen(bin)+1; i++){
			bin[i] = bin[i+1];
		}

	}
	nbin->sinal = sinal;
	/*
	 * tratar excecao do numero zero, pois nao tem como normalizar
	 */

	if(bin[0] == '0' && bin[1] == '.' && strchr(bin, '1')!=NULL){
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
	else if(strchr(bin, '1')!=NULL){
		while(bin[1] != '.'){

			p =  strchr(bin, '.');
			pos = p-bin;
			auxs = bin[pos - 1];
			bin[pos - 1] = '.';
			bin[pos] = auxs;

			exp++;

		}
	}else if(strchr(bin, '1') == NULL){
		printf("impossivel normalizar");
	}

	if(prec == SPREC){

		for(i=2; i<strlen(bin); i++){
			if(bin[i] == '0' || bin[i] == '1')
				qntd++;
		}

		while(qntd <= SSIGN){
			strcat(bin, "0");
			qntd++;
		}


		exp = exp+SVIES;
		if(exp > 254){
			exp = 255;
		}
		if(exp < 1){
			exp = 0;
		}
		if(!(nbin->exp = malloc(sizeof(char)*9)))
		{
			fprintf(stderr, "Memoria insuficiente");
			exit(EXIT_FAILURE);
		}
		nbin->exp = ExpToBin(exp, prec);

		if(!(nbin->bin = malloc(sizeof(char)*23)))
		{
			fprintf(stderr, "Memoria insuficiente");
			exit(EXIT_FAILURE);
		}


		p =  strchr(bin, '.');
		pos = p-bin;
		strncpy(nbin->bin, &bin[pos+1], sizeof(char)*23);
	}

	if(prec == DPREC){
		for(i=2; i<strlen(bin); i++){
			if(bin[i] == '0' || bin[i] == '1')
				qntd++;
		}

		while(qntd <= DSIGN){
			strcat(bin, "0");
			qntd++;
		}
		exp = exp+DVIES;
		if(exp > 2046){
			exp = 2047;
		}
		if(exp < 1){
			exp = 0;
		}

		nbin->exp = malloc(sizeof(char)*12);
		nbin->exp = ExpToBin(exp, prec);
		nbin->bin = malloc(sizeof(char)*52);

		p =  strchr(bin, '.');
		pos = p-bin;
		strncpy(nbin->bin, &bin[pos+1], sizeof(char)*52);
	}
	return 1;
}
int NumToFp(normbin *nb, char* num, int prec){
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

	Normalize(nb, IntToBin(mpz_get_si(sign), prec), prec, sinal, exp);

	/* free used memory */
	mpz_clear(dividendo);
	mpz_clear(divisor);
	mpz_clear(q);
	mpz_clear(r);

	if(strchr(nb->exp, '1') == NULL && strchr(nb->bin, '1') == NULL ){
		printf("Underflow!\n");
		return 0;
	}else if(strchr(nb->exp, '0') == NULL){
		printf("Overflow!\n");
		return 0;
	}
	else if(strchr(nb->exp, '1') == NULL && strchr(nb->bin, '1') != NULL ){
		printf("Denormalized number");
		return 0;
	}else if(strchr(nb->exp, '1') == NULL && strchr(nb->bin, '1') == NULL){
		if(nb->sinal == 1){
			printf("negative zero");
			return 0;
		}else {
			printf("positive zero");
			return 0;
		}
	}

	return 1;
}
double FpToNum(char* bin){
	int tamexp, tamsign, i, sinal;

	int  vies;
	int e;
	double sign, num;

	/*
	 * fazer pra caso double
	 */
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


	for(i=1, e=tamexp-1; i<tamexp+1; i++, e--){
		if(bin[i] == '1'){
			exp = exp + pow(2, e);
		}
	}

	for(i=tamexp+1, e=1; i<strlen(bin); i++, e++){
		if(bin[i] == '1'){
			sign = sign + 1/pow(2, e);

		}

	}
	num = pow(-1, sinal)*pow(2, exp-vies)*(1+sign);
	return num;
}

int SimpleFpToDoubleFp(normbin *nb, char *in){

	char *num = malloc(sizeof(char)*100);
	sprintf(num, "%lf",FpToNum(in));
	NumToFp(nb, num, 2);

	return 1;
}

int FpCmp(char* in1, char* in2, int prec){
	normbin nb1, nb2;
	int tamsign, i;

	if(prec == 1){
		tamsign = SSIGN;
		nb1.exp =malloc(sizeof(char)*9) ;
		nb1.bin =malloc(sizeof(char)*24);
		nb1.sinal = 0;
		nb1.exp = "\0";
		nb1.bin = "\0";
		nb2.exp =malloc(sizeof(char)*9) ;
		nb2.bin =malloc(sizeof(char)*24);
		nb2.sinal = 0;
		nb2.exp = "\0";
		nb2.bin = "\0";
	}
	else {
		tamsign = DSIGN;
		nb1.exp =malloc(sizeof(char)*12);
		nb1.bin =malloc(sizeof(char)*53);
		nb1.sinal = 0;
		nb1.exp = "\0";
		nb1.bin = "\0";
		nb2.exp =malloc(sizeof(char)*12);
		nb2.bin =malloc(sizeof(char)*53);
		nb2.sinal = 0;
		nb2.exp = "\0";
		nb2.bin = "\0";
	}

	NumToFp(&nb1, in1, prec);
	NumToFp(&nb2, in2, prec);

	char *frac1 = malloc(sizeof(char)*(tamsign+2+1));
	char *frac2 = malloc(sizeof(char)*(tamsign+2+1));

	strcat(frac1, "1.");
	strcat(frac2, "1.");
	strcat(frac1, nb1.bin);
	strcat(frac2, nb2.bin);

	/*
	 * Logica inversa, pois na matematica 0<1, no caso do jogo de sinais 0>1
	 */
	if(nb1.sinal != nb2.sinal){
		if(nb1.sinal < nb2.sinal){
			return 1;
		}else return -1;
	}else{
		/*
		 * Igualando expoentes
		 */
		if(strcmp(nb1.exp, nb2.exp) < 0){
			int exp1, exp2;
			exp1 = BinToInt(nb1.exp);
			exp2 = BinToInt(nb2.exp);

			while(exp1 < exp2 ){

				for(i = tamsign+1; i>=0; i-- ){
					if(i == 2){
						frac1[i] = frac1[0];
					}else if(i==1)
						frac1[i] = '.';

					else if(i ==0){
						frac1[i] = '0';
					}else frac1[i] = frac1[i-1];
				}
				exp1++;
			}

			nb1.exp = ExpToBin(exp1, prec);
		}

		else if(strcmp(nb1.exp, nb2.exp) > 0){
			int exp1, exp2;
			exp1 = BinToInt(nb1.exp);
			exp2 = BinToInt(nb2.exp);

			while(exp1 > exp2 ){

				for(i = tamsign+1; i>=0; i-- ){
					if(i == 2){
						frac2[i] = frac2[0];
					}else if(i==1)
						frac2[i] = '.';

					else if(i ==0){
						frac2[i] = '0';
					}else frac2[i] = frac2[i-1];
				}
				exp2++;
			}

			nb2.exp = ExpToBin(exp2, prec);
		}

		if(nb1.sinal == 0){
			return strcmp(frac1, frac2);
		}


		else{
			if(strcmp(frac1, frac2) > 0 )
				return -1;
			else if(strcmp(frac1, frac2) < 0){
				return 1;
			}else return 0;
		}
	}


}
double Add(char* in1, char* in2, int prec){

	char *num1, *num2, *aux;
	char auxs;
	char carry = '0';
	int tam, pos, j, i, sinal, tamexp, tamsign, vies;
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

	if(!(NumToFp(&nb1, in1, prec))){
		printf("trata excecao");
	}

	if(!(NumToFp(&nb2, in2, prec))){
		printf("trata excecao");
	}


	sinal = nb1.sinal;

	char *frac1 = malloc(sizeof(char)*(tamsign+2+1));
	char *frac2 = malloc(sizeof(char)*(tamsign+2+1));

	strcat(frac1, "1.");
	strcat(frac2, "1.");
	strcat(frac1, nb1.bin);
	strcat(frac2, nb2.bin);


	if(strcmp(nb1.exp, nb2.exp) < 0){
		int exp1, exp2;
		exp1 = BinToInt(nb1.exp);
		exp2 = BinToInt(nb2.exp);

		while(exp1 < exp2 ){

			for(i = tamsign+1; i>=0; i-- ){
				if(i == 2){
					frac1[i] = frac1[0];
				}else if(i==1)
					frac1[i] = '.';

				else if(i ==0){
					frac1[i] = '0';
				}else frac1[i] = frac1[i-1];
			}
			exp1++;
		}

		nb1.exp = ExpToBin(exp1, prec);
	}

	else if(strcmp(nb1.exp, nb2.exp) > 0){
		int exp1, exp2;
		exp1 = BinToInt(nb1.exp);
		exp2 = BinToInt(nb2.exp);

		while(exp1 > exp2 ){

			for(i = tamsign+1; i>=0; i-- ){
				if(i == 2){
					frac2[i] = frac2[0];
				}else if(i==1)
					frac2[i] = '.';

				else if(i ==0){
					frac2[i] = '0';
				}else frac2[i] = frac2[i-1];
			}
			exp2++;
		}

		nb2.exp = ExpToBin(exp2, prec);
	}



	char *result = malloc(sizeof(char)*(tamsign+3));
	result[tamsign+3] = '\0';

	for(i = tamsign+1, j = tamsign+2; i>=0 ; i--, j--){
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
			if(carry == '1')
				result[i] = carry;
			else{
				strncpy(result, &result[1], sizeof(char)*(tamsign+1));

			}

		}

	}

	Normalize(&fp, result, prec, sinal, BinToInt(nb1.exp)-vies);

	if(fp.sinal)
		strcat(aux, "1");
	else strcat(aux,"0");

	strcat(aux, fp.exp);
	strcat(aux, fp.bin);

	return FpToNum(aux);

}
double Multiplication(char* in1, char* in2, int prec){
	char *num1, *num2, *aux;
	char auxs;
	char carry = '0';
	int tam, pos, j, i, sinal, tamexp, tamsign, vies;
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

	if(!(NumToFp(&nb1, in1, prec))){
		printf("trata excecao");
	}

	if(!(NumToFp(&nb2, in2, prec))){
		printf("trata excecao");
	}

	sinal = nb1.sinal;

	char *frac1 = malloc(sizeof(char)*(tamsign+3+1));
	char *frac2 = malloc(sizeof(char)*(tamsign+3+1));

	strcat(frac1, "1.");
	strcat(frac2, "1.");
	strcat(frac1, nb1.bin);
	strcat(frac2, nb2.bin);

	printf("frac1 %s exp %s frac2 %s exp %s\n", frac1, nb1.exp, frac2, nb2.exp);


	if(strcmp(nb1.exp, nb2.exp) < 0){
		int exp1, exp2;
		exp1 = BinToInt(nb1.exp);
		exp2 = BinToInt(nb2.exp);

		while(exp1 < exp2 ){

			for(i = tamsign+1; i>=0; i-- ){
				if(i == 2){
					frac1[i] = frac1[0];
				}else if(i==1)
					frac1[i] = '.';

				else if(i ==0){
					frac1[i] = '0';
				}else frac1[i] = frac1[i-1];
			}
			exp1++;
		}

		nb1.exp = ExpToBin(exp1, prec);
	}

	else if(strcmp(nb1.exp, nb2.exp) > 0){
		int exp1, exp2;
		exp1 = BinToInt(nb1.exp);
		exp2 = BinToInt(nb2.exp);

		while(exp1 > exp2 ){

			for(i = tamsign+1; i>=0; i-- ){
				if(i == 2){
					frac2[i] = frac2[0];
				}else if(i==1)
					frac2[i] = '.';

				else if(i ==0){
					frac2[i] = '0';
				}else frac2[i] = frac2[i-1];
			}
			exp2++;
		}

		nb2.exp = ExpToBin(exp2, prec);
	}

	printf("frac1 %s exp %s frac2 %s exp %s\n", frac1, nb1.exp, frac2, nb2.exp);


	char *result = malloc(sizeof(char)*(tamsign+3));
	result[tamsign+3] = '\0';

	for(i = tamsign+1, j = tamsign+2; i>=0 ; i--, j--){
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
			if(carry == '1')
				result[i] = carry;
			else{
				strncpy(result, &result[1], sizeof(char)*(tamsign+1));

			}

		}
	}

	return 1.0;
}
double Sub(char* in1, char* in2, int prec){

	char *num1, *num2, *aux;
	char auxs;
	char carry = '0';
	int tam, pos, j, i, sinal, tamexp, tamsign, vies;
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
	/*
	 * Caso de 3-5, fazer tratamento
	 * if(FpCmp(in1, in2) == -1){
				bsinal = nb2.;
				fracaux = frac2;
				frac2 = frac1;
				frac1 = fracaux;
			}
	 */
	num1 = malloc(sizeof(char)*tam);
	num2 = malloc(sizeof(char)*tam);

	if(!(NumToFp(&nb1, in1, prec))){
		printf("trata excecao");
	}

	if(!(NumToFp(&nb2, in2, prec))){
		printf("trata excecao");
	}

	sinal = nb1.sinal;

	char *frac1 = malloc(sizeof(char)*(tamsign+3+1));
	char *frac2 = malloc(sizeof(char)*(tamsign+3+1));

	strcat(frac1, "1.");
	strcat(frac2, "1.");
	strcat(frac1, nb1.bin);
	strcat(frac2, nb2.bin);


	if(strcmp(nb1.exp, nb2.exp) < 0){
		int exp1, exp2;
		exp1 = BinToInt(nb1.exp);
		exp2 = BinToInt(nb2.exp);

		while(exp1 < exp2 ){

			for(i = tamsign+1; i>=0; i-- ){
				if(i == 2){
					frac1[i] = frac1[0];
				}else if(i==1)
					frac1[i] = '.';

				else if(i ==0){
					frac1[i] = '0';
				}else frac1[i] = frac1[i-1];
			}
			exp1++;
		}

		nb1.exp = ExpToBin(exp1, prec);
	}

	else if(strcmp(nb1.exp, nb2.exp) > 0){
		int exp1, exp2;
		exp1 = BinToInt(nb1.exp);
		exp2 = BinToInt(nb2.exp);

		while(exp1 > exp2 ){

			for(i = tamsign+1; i>=0; i-- ){
				if(i == 2){
					frac2[i] = frac2[0];
				}else if(i==1)
					frac2[i] = '.';

				else if(i ==0){
					frac2[i] = '0';
				}else frac2[i] = frac2[i-1];
			}
			exp2++;
		}

		nb2.exp = ExpToBin(exp2, prec);
	}

	frac1 = realloc(frac1, sizeof(char)*(tamsign+3+1+1));
	frac2 = realloc(frac2, sizeof(char)*(tamsign+3+1+1));

	/*
	 *Insere bit de sinal
	 */
	for(i = strlen(frac1); i>=0; i--){
		if(i == 0)
			frac1[i] = '0';
		else frac1[i] = frac1[i-1];

	}

	for(i = strlen(frac2); i>=0; i--){
		if(i == 0)
			frac2[i] = '0';
		else frac2[i] = frac2[i-1];

	}


	/*
	 * Invertendo string
	 */
	for(i = 0; i < strlen(frac2); i++){
		if(frac2[i] == '0'){
			frac2[i] = '1';

		}else if(frac2[i] == '1')
			frac2[i] = '0';

	}


	char *comp = malloc(sizeof(char)*(tamsign+3+1));
	comp[tamsign+4] = '\0';

	/*
	 * soma com 1
	 */
	for(i = tamsign+2, j = tamsign+2; i>=0 ; i--, j--){
		if(i == tamsign+2){
			if(frac2[i] == '0'){
				comp[j] = '1';
				carry = '0';
			}else {
				comp[j] = '0';
				carry = '1';
			}
		}else if(frac2[i] == '0' && i != 2){
			if(carry == '0'){
				comp[j] = '0';
				carry = '0';
			}else {
				comp[j] = '1';
				carry = '0';
			}
		}else if(frac2[i] == '1' && i != 2){
			if(carry == '0'){
				comp[j] = '1';
				carry = '0';
			}else {
				comp[j] = '0';
				carry = '1';
			}
		}

		if(frac2[i] == '.' ){
			comp[j] = '.';
		}

	}

	frac2 = comp;
	char *result = malloc(sizeof(char)*(tamsign+4));
	result[tamsign+3] = '\0';
	for(i = tamsign+2, j = tamsign+2; i>=0 ; i--, j--){
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

	}
	Normalize(&fp, result, prec, sinal, BinToInt(nb1.exp)-vies);

	if(fp.sinal)
		strcat(aux, "1");
	else strcat(aux,"0");

	strcat(aux, fp.exp);
	strcat(aux, fp.bin);


	return FpToNum(aux);
}
