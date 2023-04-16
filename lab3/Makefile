TARGET = lab
CC = gcc
CFLAGS = -Wall
SRC = lab3.c graph.c heap.c

$(TARGET)1 : $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) -lm
	./$(TARGET)

clean :
	rm $(TARGET)