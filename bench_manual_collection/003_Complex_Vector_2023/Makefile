CC = g++
CFLAGS = -Wall -O3 -march=native -mavx2 -std=c++11 -I.
LDFLAGS = -lm
TARGET = benchmark
SOURCES = main.cpp implementation.cpp
HEADERS = common.h tsc_x86.h utils.h

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET) *.o

run: $(TARGET)
	./$(TARGET)
