CC = clang
CFLAGS = -Wall -Wextra -Wpedantic -Werror

all: tsp

debug:	CFLAGS += -g

debug:	tsp

tsp: tsp.o graph.o path.o stack.o
	$(CC) -o tsp $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f tsp *.o

format:
	clang-format -i -style=file *.c *.h


