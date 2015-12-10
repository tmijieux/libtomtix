TARGET=tree_node.o
CFLAGS=-std=c99 -Wall
LDFLAGS=
SRC=$(wildcard *.c)
OBJ=$(patsubst %.c, %.o, $(SRC))

all: $(TARGET)

clean:
	$(RM) *.o *~

mrproper: clean
	$(RM) $(TARGET)
