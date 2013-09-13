SRC = /Users/flavioipiranga/git/floatpoint/Floatpoint/src/

all:executavel
	cd ./src	; $(MAKE)
	
executavel: main.o $(SRC)floatpoint.o
	gcc -o executavel main.o $(SRC)floatpoint.o

main.o: main.c $(SRC)floatpoint.h
	gcc -o main.o -c main.c
