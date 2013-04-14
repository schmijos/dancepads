CC=gcc
CFLAGS=-I. -lpthread -Wall
DEPS = utils.h uds.h
OBJ = server.o utils.o uds.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

server: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
