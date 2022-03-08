CC = clang
CFLAGS = -Wall -Wextra -Wpedantic -Werror

all:	banhammer

debug:	CFLAGS += -g

debug:	banhammer

banhammer:	banhammer.o bv.o bf.o node.o ll.o ht.o speck.o parser.o
	$(CC) -o banhammer $^

%.o:	%.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f banhammer *.o

format:
	clang-format -i -style=file *.c *.h


