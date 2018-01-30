CC=gcc
CFLAGS=-I.
DEPS = foo.h bar.h
OBJ = foo.o bar.o main.o


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

staticvars: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)



