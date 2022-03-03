CC = clang
CFLAGS = -Wall -Wextra -Wpedantic -Werror

all: sorting

debug:	CFLAGS += -g

debug:	sorting

sorting: sorting.o bubble.o shell.o quick.o stack.o queue.o stat.o set.o
	$(CC) -o sorting $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f sorting *.o

format:
	clang-format -i -style=file *.c *.h


