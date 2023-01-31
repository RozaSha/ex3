CC=g++ -std=c++11
CFLAGS=-c -Wall

all: Server Client

Server: Server.o Distances.o KNN.o PreProcess.o
	$(CC) Server.o Distances.o KNN.o PreProcess.o -o Server.out

Client: Client.o Distances.o KNN.o PreProcess.o
	$(CC) Client.o Distances.o KNN.o PreProcess.o -o Client.out

Server.o: Server.cpp
	$(CC) $(CFLAGS) Server.cpp

Client.o: Client.cpp
	$(CC) $(CFLAGS) Client.cpp

Distances.o: Distances.cpp
	$(CC) $(CFLAGS) Distances.cpp

KNN.o: KNN.cpp
	$(CC) $(CFLAGS) KNN.cpp

PreProcess.o: PreProcess.cpp
	$(CC) $(CFLAGS) PreProcess.cpp

clean:
	rm -rf *.o Server Client
