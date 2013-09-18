SRC = /Users/flavioipiranga/git/floatpoint/Floatpoint/src/
OBJ_DIR = /Users/flavioipiranga/git/floatpoint/Floatpoint/
all:executavel
	cd ./src	; $(MAKE) clean
	cd ./src	; $(MAKE)
	
executavel: main.o $(SRC)floatpoint.o
	gcc -g -o executavel main.o $(SRC)floatpoint.o

main.o: main.c $(SRC)floatpoint.h
	gcc -g -o main.o -c main.c
	
clean: 
	rm -rf $(OBJ_DIR)*.o executavel
