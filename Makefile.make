CC=g++
CFLAGS=-Wall

OBJ = main.o

all: race

race: $(OBJ)
	$(CC) $(CFLAGS) -o race $(OBJ)

main.o: main.cpp

clean:
	rm -f race *.o
