CC=gcc
TARGET=f

HEADERS=f.h q.h
SOURCES=f.c q.c
OBJECTS=f.o q.o

LDFLAGS=-lrt

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

%.o : %.c %.h
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

clean:
	-rm f *.o

run: $(TARGET)
	./$(TARGET)


.PHONY: all clean run
