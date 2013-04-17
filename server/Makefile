CC=gcc
CFLAGS=-I. -lpthread -lwiringPi -Wall
DEPS = utils.h uds.h
OBJ = server.o utils.o uds.o
OBJ2 = wiringpi_test.o
OBJ3 = sample_uds_client.o utils.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: server wiringpi_test sample_uds_client

server: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

wiringpi_test: $(OBJ2)
	gcc -o $@ $^ $(CFLAGS)

sample_uds_client: $(OBJ3)
	gcc -o $@ $^ $(CFLAGS)
