CC = gcc
CFLAGS = -Wall -O2 `pkg-config --cflags gtk+-2.0`
LDFLAGS =
INCLUDES =
LIBS = `pkg-config --libs gtk+-2.0`

TARGET = console.exe
OBJS = main.o console.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

clean:
	-rm -f $(OBJS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

main.o: console.h
console.o: console.h

