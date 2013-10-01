#include <gmp.h>

typedef struct Normbin{
	char *exp;
	char *bin;
	int sinal;
}normbin;

char* InvString(char* string);
char* IntToBin(long int real, int prec);
int NumToFp(normbin *nb, char* num1, int prec);
float StringToDouble(char* in);
char* ExpToBin (int exp, int prec);
int Normalize(normbin *nb, char* bin, int prec, int sinal, int expoente);
double FpToNum(char* bin);
int FpCmp(char* in1, char* in2, int prec);
double Add(char* num1, char* num2, int prec);
double Sub(char* in1, char* in2, int prec);
double Multiplication(char* in1, char* in2, int prec);


