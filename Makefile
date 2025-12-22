CC = gcc
CFLAGS = -O3 -march=native -flto -funroll-loops

OBJS_1 = ./src/sort.c
OBJS_2 = ./src/program.c

TARGET_1 = ./src/output
TARGET_2 = ./src/program.dll

sort: $(TARGET_1)
program: $(TARGET_2)

.PHONY: clean_1 clean_2

$(TARGET_1): $(OBJS_1)
	$(CC) $(CFLAGS) $(OBJS_1) -o $(TARGET_1)

$(TARGET_2): $(OBJS_2)
	$(CC) $(CFLAGS) $(OBJS_2) -shared -o $(TARGET_2)

clean_1:
	rm -f $(TARGET_1)

clean_2:
	rm -f $(TARGET_2)
