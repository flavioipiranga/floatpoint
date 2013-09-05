all:executavel
    
executavel: main.o floatpoint.o
	gcc -o executavel main.o floatpoint.o

main.o: main.c floatpoint.h
	gcc -o main.o -c main.c

floatpoint.o: floatpoint.c
	gcc -o floatpoint.o -c floatpoint.c
