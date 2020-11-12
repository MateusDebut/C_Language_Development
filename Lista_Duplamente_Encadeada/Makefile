#Nome do projeto
PROJ_NOME=list

#.c files
C_SOURCE = $(wildcard *.c)

#.h files
H_SOURCE = $(wildcard *.h)

#Object files
OBJ = $(C_SOURCE: .c=.o)

#Compiler
CC=gcc

#Flags for compiler
CC_FLAGS =-c 	\
		  -W 	\
		  -Wall	\
		  -ansi	\
		  -pedantic

#compilation and linking
all: $(PROJ_NOME)

$(PROJ_NOME): $(OBJ)
	$(CC) -o $@ $^

%.o: %.c %.h
	$(cc) -o $@ $< $(CC_FLAGS)

main.o: main.c $(H_SOURCE)
	$(CC) -o $@ $< $(CC_FLAGS)

run:
	./$(PROJ_NOME)

clean: 
	rm -rf *.o $(PROJ_NOME) *~