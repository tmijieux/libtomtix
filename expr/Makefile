nCFLAGS=-Wall -std=c99
LIBS=
OBJS1=	main.o \
	stack.o
OBJS2=	evaluation.o \
	stack.o

all: transformation_expression evaluation

transformation_expression:$(OBJS1)
	$(CC) $(OBJS1) -o transformation_expression $(LIBS)

debug:
	$(CC) -c -o main.o $(CFLAGS) -DDEBUG main.c
	$(CC) -c -o stack.o $(CFLAGS) -DDEBUG stack.c
	$(CC) $(OBJS1) -o debug $(LIBS)

clean:
	@rm -f *.o *~

evaluation: $(OBJS2)
	$(CC) $(OBJS2) -o evaluation $(LIBS)

