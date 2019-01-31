CC = gcc
CFLAGS = -Wall - g

all: run
 
run: bankingServer.c bankingClient.c sl.o
	$(CC) $(CCFLAGS) -pthread -o bankingServer bankingServer.c sl.o
	$(CC) $(CCFLAGS) -pthread -o bankingClient bankingClient.c

sl.o: sl.c sl.h
	$(CC) -c sl.c
clean:
	rm -rf *.o
	rm -rf bankingServer
	rm -rf bankingClient