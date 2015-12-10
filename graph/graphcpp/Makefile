CC=g++
TARGET=graph
CFLAGS=-Wall
LDFLAGS=
SRC=main.cpp graph_list.cpp
OBJ=$(patsubst %.cpp, %.o, $(SRC))

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

clean:
	$(RM) *.o *~

mrproper: clean
	$(RM) $(TARGET)
