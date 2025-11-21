CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = ex1
SRC = main.c ppm.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) *.o *.ppm
