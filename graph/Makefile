TARGET=libgraph_list.so libgraph_matrix.so graph.o
CFLAGS=-std=c99 -Wall -g -O0
LDFLAGS=-ltomtix
SRC=$(wildcard *.c)
OBJ=$(patsubst %.c, %.o, $(SRC))

all: $(TARGET)

libgraph_list.so: graph_list.c
	$(CC) $(CFLAGS) -fPIC -shared $< -o $@ -llist

libgraph_matrix.so: graph_matrix.c
	$(CC) $(CFLAGS) -fPIC -shared $< -o $@

clean:
	$(RM) *.o *~

mrproper: clean
	$(RM) $(TARGET)
