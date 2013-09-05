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

//Real para binario


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

char* InttoBin(char* in){
	char bin[32];
	int deci;

	int i;

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


char* FloattoBin (char* in) {





	return in;
	}

char* RealtoFloatPoint(char* in){

	char **endptr;
	double num;
	puts(in);
	num = strtod(in, endptr);

	printf("Teste:%lf", num);

	return in;

	}
