CC=g++ -std=c++11
CFLAGS=-c -Wall

all: server client

server: Server.o Distances.o KNN.o PreProcess.o
	$(CC) Server.o Distances.o KNN.o PreProcess.o -o server.out

client: client.o Distances.o KNN.o PreProcess.o
	$(CC) client.o Distances.o KNN.o PreProcess.o -o client.out

Server.o: Server.cpp
	$(CC) $(CFLAGS) Server.cpp

client.o: client.cpp
	$(CC) $(CFLAGS) client.cpp

Distances.o: Distances.cpp
	$(CC) $(CFLAGS) Distances.cpp

KNN.o: KNN.cpp
	$(CC) $(CFLAGS) KNN.cpp

PreProcess.o: PreProcess.cpp
	$(CC) $(CFLAGS) PreProcess.cpp

clean:
	rm -rf *.o server client
