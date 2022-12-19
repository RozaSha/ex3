OBJS	= Distances.o KNN.o PreProcess.o main.o
SOURCE	= Distances.cpp KNN.cpp PreProcess.cpp main.cpp
HEADER	= Distances.h KNN.h PreProcess.h
OUT	= a.out
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 =

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

Distances.o: Distances.cpp
	$(CC) $(FLAGS) Distances.cpp

KNN.o: KNN.cpp
	$(CC) $(FLAGS) KNN.cpp

PreProcess.o: PreProcess.cpp
	$(CC) $(FLAGS) PreProcess.cpp

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp


clean:
	rm -f $(OBJS) $(OUT)