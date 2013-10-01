EMB_UNIT_DIR = /Users/flavioipiranga/Downloads/embunit
CC = gcc
CFLAGS = -O
INCLUDES = -I.. -I. -I$(EMB_UNIT_DIR)
LIBS = $(EMB_UNIT_DIR)/lib
FP = .
RM = rm
MV = mv
BINARIES = ../bin
TARGET = testeexec

OBJSGCC := All.c
OBJSGCC += ../floatpoint.c
OBJSGCC += embunit.c

all: $(TARGET)

$(TARGET): 

	$(info Running embedded software testing with gcc...)
	$(CC) -o $(TARGET) $(OBJSGCC) $(INCLUDES) -L$(LIBS) -lembUnit -ltextui -lgmp
	#$(MV) $(TARGET) $(BINARIES)
	#$(BINARIES)/$(TARGET) -X > ../target/testResults/TEST-alltests.xml
  
clean:

	$(RM) -rf $(TARGET)
	$(RM) -rf *.o

.PHONY: clean all
