CC=gcc
CFLAGS=-I.
DEPS = matriz.h
OBJ = trab1.o func.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

trab: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm *.o
