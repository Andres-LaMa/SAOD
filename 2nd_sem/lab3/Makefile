TARGET = lab
CC = gcc
CFLAGS = -Wall
DEBAGfFLAGS = -g3 -O0
SRC = lab3.c graph.c heap.c algoritm.c

$(TARGET)1 : $(SRC)
	$(CC) $(CFLAGS) $(DEBAGfFLAGS) $(SRC) -o $(TARGET) -lm

run : 
	./$(TARGET)
rung : 
	gdb ./$(TARGET)

clean :
	rm $(TARGET)