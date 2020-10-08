objects = main.c fila.c util.c

all: $(objects)
	gcc -Wall -Werror -o main $(objects) -g

fila.c: fila.h
util.c: util.h fila.h
main.c: fila.h util.c


run: $(objects)
	./main

clean:
	rm *.o main