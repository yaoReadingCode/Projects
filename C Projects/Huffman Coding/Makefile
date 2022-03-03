CC = clang
CFLAGS = -Wall -Wextra -Wpedantic -Werror

all:	encode decode entropy

debug:	CFLAGS += -g

debug:	encode decode entropy

encode:	encode.o stack.o code.o io.o node.o huffman.o pq.o
	$(CC) -o encode $^

%.o:	%.c
	$(CC) $(CFLAGS) -c $<

decode:	decode.o stack.o code.o io.o node.o huffman.o pq.o
	$(CC) -o decode $^

%.o:	%.c
	$(CC) $(CFLAGS) -c $<

entropy:	entropy.o
	$(CC) -o entropy -lm $^

%.o:	%.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f encode decode entropy *.o

format:
	clang-format -i -style=file *.c *.h


