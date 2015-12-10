TARGET=breadth_first_search depth_first_search
CFLAGS=-std=c99 -Wall -g -O0
LDFLAGS=-ltomtix
SRC=$(wildcard *.c)
OBJ=$(patsubst %.c, %.o, $(SRC))

all: $(TARGET)

breadth_first_search: tree.o token.o expr2tree.o breadth_first_search.o tree_node.o
	$(CC) $^ -o $@ $(LDFLAGS)

depth_first_search: depth_first_search.o tree.o expr2tree.o token.o tree_node.o
	$(CC) $^ -o $@ $(LDFLAGS)

clean:
	$(RM) *.o *~

mrproper: clean
	$(RM) $(TARGET)
