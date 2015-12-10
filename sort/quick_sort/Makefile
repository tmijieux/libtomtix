TARGET=quick_sort1 quick_sort2 quick_sort_threaded
CFLAGS=-std=c99 -Wall -pthread
LDFLAGS=

all: $(TARGET)

%: %.o
	$(CC) $@.o -o $@ $(LDFLAGS)

clean:
	$(RM) *.o *~

mrproper: clean
	$(RM) $(TARGET)
