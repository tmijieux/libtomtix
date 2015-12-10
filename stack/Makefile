TARGET=stack
SRC=$(wildcard *.c)
OBJ=$(patsubst %.c, %.o, $(SRC))
CFLAGS=-Wall -std=c99
LDFLAGS=

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

clean:
	$(RM) *.o *~

mrproper: clean
	$(RM) $(TARGET)
