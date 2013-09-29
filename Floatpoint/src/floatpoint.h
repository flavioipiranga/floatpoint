#include <gmp.h>

typedef struct Normbin{
	char *exp;
	char *bin;
	int sinal;
}normbin;

char* InvString(char* string);
char* IntToBin(long int real, int prec);
char* FloatToBin(double real);
normbin BigNumToBin(char* num1, int prec);
float StringToDouble(char* in);
char* ExpToBin (int exp, int prec);
normbin Normalize(char* bin, int prec, int sinal, int expoente);
double BinToNum(char* bin);
void Add(char* num1, char* num2, int prec);

