/*
 * main.c
 *
 *  Created on: 04/09/2013
 *      Author: flavioipiranga
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/floatpoint.h"
#include <gmp.h>
/*
 *
 */

#define STAMNUM  43
#define DTAMNUM  313
#define SPTAM  33
#define DPTAM  65
#define SPREC  1
#define DPREC  2


int main(int argc, char** argv) {
	//char *in;
	char* in1, *in2;
	char *binfp;
	double num=0, r;
	int prec;
	int op;
	normbin nb;

	if(!(nb.exp = malloc(sizeof(char)*1)))
		{
			fprintf(stderr, "Memoria insuficiente");
			exit(EXIT_FAILURE);
		}

	if(!(nb.bin = malloc(sizeof(char)*1)))
		{
			fprintf(stderr, "Memoria insuficiente");
			exit(EXIT_FAILURE);
		}

	if(!(in1 = malloc(sizeof(char)*1)))
	{
		fprintf(stderr, "Memoria insuficiente");
		exit(EXIT_FAILURE);
	}

	if(!(in2 = malloc(sizeof(char)*1)))
	{
		fprintf(stderr, "Memoria insuficiente");
		exit(EXIT_FAILURE);
	}

	do{
		printf("Bem-vindo ao software FP.\n\n");

		printf("Menu de opcoes:\n\n");
		printf("(1) Converter nœmero para bin‡rio.\n");
		printf("(2) Converter bin‡rio para nœmero.\n");
		printf("(3) Converter Precis‹o simples para Precis‹o dupla.\n");
		printf("(4) Converter Precis‹o dupla para Precis‹o simples.\n");
		printf("(5) Adicao.\n");
		printf("(6) Subtracao.\n");
		printf("(7) Multiplicacao.\n");
		printf("(8) Divisao.\n");
		printf("(9) Raiz quadrada.\n");
		printf("(10) Comparar dois numeros em ponto flutuante.\n");
		printf("(0) Sair.\n\n");

		printf("Digite sua opcao:");
		scanf("%d", &op);

		switch(op){

		case 1:
			printf("Escolha Precis‹o:\n");
			printf("1) Precis‹o simples\n");
			printf("2) Precis‹o dupla\n");
			scanf("%d", &prec);

			if(prec == 1){
				in1 = realloc(in1, sizeof(char)*100);
				nb.exp =malloc(sizeof(char)*9) ;
				nb.bin =malloc(sizeof(char)*24);
				nb.sinal = 0;
				nb.exp = "\0";
				nb.bin = "\0";
			}
			else {
				in1 = realloc(in1, sizeof(char)*DTAMNUM);
				nb.exp =malloc(sizeof(char)*12);
				nb.bin =malloc(sizeof(char)*53);
				nb.sinal = 0;
				nb.exp = "\0";
				nb.bin = "\0";
			}

			printf("Digite o nœmero real que deseja converter para bin‡rio:\n");
			scanf("%s", in1);

			if(!(NumToFp(&nb, in1, prec))){
				//printf("\n");
			}

			//if((strcmp(nb.bin, "00000000000000000000000") == 0 || strcmp(nb.bin, "0000000000000000000000000000000000000000000000000000") == 0))

			printf("Sinal: %d Expoente: %s Significante: %s\n", nb.sinal, nb.exp, nb.bin);
			printf("%d%s%s\n", nb.sinal, nb.exp, nb.bin);
			break;

		case 2:
			printf("Escolha Precis‹o:\n");
			printf("1) Precis‹o simples\n");
			printf("2) Precis‹o dupla\n");
			scanf("%d", &prec);

			if(prec == 1){
				in1 = realloc(in1, sizeof(char)*SPTAM);
			}
			else in1 = realloc(in1, sizeof(char)*DPTAM);

			printf("Digite o nœmero bin‡rio que deseja converter para real:\n");
			scanf("%s", in1);

			r = FpToNum(in1);
			printf("nœmero eh igual %.16lf\n", r);
			break;

		case 3:
			in1 = realloc(in1, sizeof(char)*SPTAM);
			nb.exp =malloc(sizeof(char)*12);
			nb.bin =malloc(sizeof(char)*53);
			nb.sinal = 0;
			nb.exp = "\0";
			nb.bin = "\0";

			printf("Digite o binario que deseja mudar precisao:\n");
			scanf("%s", in1);

			SimpleFpToDoubleFp(&nb, in1);
			printf("%d%s%s\n", nb.sinal, nb.exp, nb.bin);
			break;

		case 5:
			printf("Escolha Precis‹o:\n");
			printf("1) Precis‹o simples\n");
			printf("2) Precis‹o dupla\n");
			scanf("%d", &prec);

			if(prec == 1){
				in1 = realloc(in1, sizeof(char)*STAMNUM);
				in2 = realloc(in2, sizeof(char)*STAMNUM);
			}
			else {
				in1 = realloc(in1, sizeof(char)*DTAMNUM);
				in2 = realloc(in2, sizeof(char)*DTAMNUM);
			}

			printf("Digite o primeiro nœmero:\n");
			scanf("%s", in1);
			printf("Digite o segundo nœmero:\n");
			scanf("%s", in2);

			printf("Resultado: %.16lf", Add(in1, in2, prec));
			break;

		case 6:

			printf("Escolha Precis‹o:\n");
			printf("1) Precis‹o simples\n");
			printf("2) Precis‹o dupla\n");
			scanf("%d", &prec);

			if(prec == 1){
				in1 = realloc(in1, sizeof(char)*STAMNUM);
				in2 = realloc(in2, sizeof(char)*STAMNUM);
			}
			else {
				in1 = realloc(in1, sizeof(char)*DTAMNUM);
				in2 = realloc(in2, sizeof(char)*DTAMNUM);
			}

			printf("Digite o primeiro nœmero:\n");
			scanf("%s", in1);
			printf("Digite o segundo nœmero:\n");
			scanf("%s", in2);

			r = Sub(in1, in2, prec);
			printf("nœmero eh igual %.16lf\n", r);
			break;
		case 7:

			printf("Escolha Precis‹o:\n");
			printf("1) Precis‹o simples\n");
			printf("2) Precis‹o dupla\n");
			scanf("%d", &prec);

			if(prec == 1){
				in1 = realloc(in1, sizeof(char)*STAMNUM);
				in2 = realloc(in2, sizeof(char)*STAMNUM);
			}
			else {
				in1 = realloc(in1, sizeof(char)*DTAMNUM);
				in2 = realloc(in2, sizeof(char)*DTAMNUM);
			}

			printf("Digite o primeiro nœmero:\n");
			scanf("%s", in1);
			printf("Digite o segundo nœmero:\n");
			scanf("%s", in2);

			Multiplication(in1, in2, prec);
			break;

		case 10:
			printf("Escolha Precis‹o:\n");
			printf("1) Precis‹o simples\n");
			printf("2) Precis‹o dupla\n");
			scanf("%d", &prec);

			if(prec == 1){
				in1 = realloc(in1, sizeof(char)*STAMNUM);
				in2 = realloc(in2, sizeof(char)*STAMNUM);
			}
			else {
				in1 = realloc(in1, sizeof(char)*DTAMNUM);
				in2 = realloc(in2, sizeof(char)*DTAMNUM);
			}

			printf("Digite o primeiro nœmero:\n");
			scanf("%s", in1);
			printf("Digite o segundo nœmero:\n");
			scanf("%s", in2);

			if(FpCmp(in1, in2, prec) == 1){
				printf("Primeiro numero maior que o segundo.");
			}else if(FpCmp(in1, in2, prec) == -1){
				printf("Primeiro numero menor que o segundo.");

			}else printf("Primeiro numero igual o segundo.");

		}
		free(nb.bin);
		free(nb.exp);
	}while(op!=0);

	return (EXIT_SUCCESS);
}
//21321312321312321321312
//12345678901234567000000
//0.000000000000000000000000000000000000012
//12000000000000000000000000000000000000012
