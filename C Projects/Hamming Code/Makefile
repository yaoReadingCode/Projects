CC = clang
CFLAGS = -Wall -Wextra -Wpedantic -Werror

all:	encode decode error entropy

debug:	CFLAGS += -g

debug:	encode decode error entropy

encode:	encode.o bv.o bm.o hamming.o
	$(CC) -o encode $^

%.o:	%.c
	$(CC) $(CFLAGS) -c $<

decode:	decode.o bv.o bm.o hamming.o
	$(CC) -o decode $^

%.o:	%.c
	$(CC) $(CFLAGS) -c $<

error:	error.o
	$(CC) -o error $^

%.o:	%.c
	$(CC) $(CFLAGS) -c $<

entropy:	entropy.o
	$(CC) -o entropy -lm $^

%.o:	%.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f encode decode error entropy *.o

format:
	clang-format -i -style=file *.c *.h


