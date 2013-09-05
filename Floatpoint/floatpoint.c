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

char* ExpToBinSimple (int exp, char* bini){
    int i;

    for(i = 0; i<8; i++){

        if(exp%2)
            strcat(bini, BIT1);
        else strcat(bini, BIT0);

        exp = exp/2;
    }

    strcpy(bini, InvString(bini));

    return bini;
}

char* RealToFloatPoint(double num, char* bin){
	char *binint, *binfra;
	char *binfp;
	char p, auxs;
	int pos = 0, exp = 0, i, j;

	binint = malloc(sizeof(char)*32);
	binfra = malloc(sizeof(char)*33);

	binfp = malloc(sizeof(char)*67);


	binint = IntToBin(num, binint);
	binfra = FloatToBin(num,binfra);

	strcat(binfp,binint);
	strcat(binfp,".");
	strcat(binfp,binfra);


	   if(binfp[0] == '0'){
	       while(binfp[0] == '0'){

	            p =  strchr(binfp, '.');
	            pos = p-binfp;

	            if(binfp[pos - 1]== '1')
	                break;

	            auxs = binfp[pos + 1];
	            binfp[pos + 1] = '.';
	            binfp[pos] = auxs;

	            exp--;

	       }
	   }
	   else {
	       while(binfp[1] != '.'){

	            p =  strchr(binfp, '.');
	            pos = p-binfp;
	            auxs = binfp[pos - 1];
	            binfp[pos - 1] = '.';
	            binfp[pos] = auxs;

	            exp++;

	       }
	   }

	   p =  strchr(binfp, '.');
	   pos = p-binfp;

	   for(i=0, j=pos+1; i < 23; i++, j++){

	       binfra[i] = binfp[j];

	   }

	   exp = exp+SVIES;

	   strcpy(binexp, ExpToBinSimple(exp));

	   for(i=0, j=0; i<32; i++){
		   if(i=0)
			   floatbin[0] = bsig;
		   else if (i>0 && i<9)
			   floatbin[i] = binexp[j];
		   else floatbin[i] = binfra[j];

	   }

	return bin;

}
