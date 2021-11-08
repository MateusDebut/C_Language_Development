#Nome do projeto
PROJ_NOME=main

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
		  -g 	\
		  -W 	\
		  -Wall	\
		  -ansi	\
		  -pedantic\
		  -Werror \

#compilation and linking
all: $(PROJ_NOME)

$(PROJ_NOME): $(OBJ)
	$(CC) -o $@ $^ -g -lm

valgrind:
	valgrind --leak-check=full -s ./$(PROJ_NOME)

%.o: %.c %.h
	$(cc) -o $@ $< $(CC_FLAGS)

main.o: main.c $(H_SOURCE)
	$(CC) -o $@ $< $(CC_FLAGS)

run:
	./$(PROJ_NOME)

clean: 
	rm -rf *.o $(PROJ_NOME) *~