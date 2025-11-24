CC = gcc
CFLAGS = -Wall -Wextra -pthread
TARGET = lock

all: $(TARGET)

$(TARGET): lock.c
	$(CC) $(CFLAGS) -o $(TARGET) lock.c

clean:
	rm -f $(TARGET)
