CC = g++ -std=c++11
CFLAGS = -c -Wall

all: a.out

a.out: Main.o Distances.o KNN.o PreProcess.o
	$(CC) main.o Distances.o KNN.o PreProcess.o -o a.out

main.o: Main.cpp
	$(CC) $(CFLAGS) main.cpp

Distances.o: Distances.cpp Distances.h
	$(CC) $(CFLAGS) Distances.cpp

KNN.o: KNN.cpp KNN.h
	$(CC) $(CFLAGS) KNN.cpp

PreProcess.o: PreProcess.cpp PreProcess.h
	$(CC) $(CFLAGS) PreProcess.cpp

clean:
	rm -rf *o a.out