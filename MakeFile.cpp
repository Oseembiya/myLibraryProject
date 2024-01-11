CC = g++
CFLAGS = -std=c++11

SRC = main.cpp
OBJS = main.o

all: mylibrary clean

mylibrary: $(OBJS)
	$(CC) $(CFLAGS) -o mylibrary $(OBJS)

main.o: myCodeFile.cpp
	$(CC) $(CFLAGS) -c myCodeFile.cpp

clean:
	rm -f $(OBJS)
