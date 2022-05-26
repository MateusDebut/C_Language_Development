#Nome do projeto
PROJ_NAME=main

#.c files
C_SOURCE = $(wildcard *.c)

#.h files
H_SOURCE = $(wildcard *.h)

#Object files
OBJ = $(C_SOURCE: .c=.o)

#Compiler
CC=gcc

#Flags for compiler
CC_FLAGS =-c	\
				-W	 \
				-Wall\
				-ansi\
				-pedantic\
				-Werror \

#Compilation and Linking
all: $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
		$(CC) -o $@ $^

%.o: %.c %.h
		$(cc) -o $@ $< $(CC_FLAGS)

main.o: main.c $(H_SOURCE)
		$(CC) -o $@ $< $(CC_FLAGS)
run:
		./$(PROJ_NAME)

clean:
		rm -rf *.o $(PROJ_NAME) *~