CC = gcc

OBJS = ./src/sort.c

TARGET = ./src/output

.PHONY: clean

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

clean:
	rm -f $(TARGET)
