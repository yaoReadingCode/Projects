# Bloom Filter and Hash Table Program
The purpose of this code is to implement a program that filters out specific words from text that is inputed. This is done through bloom filters and hash tables. Bloom filters all for no false negatives and only false positives which we will then check the hash table to see if a banned word is actually on the list. Collisions are fixed through linked lists.

## Build

        $ Typing "make", or "make all" will build it all.
	$ Typing "make" with encode, decode, or entropy will make those specific programs
        $ Typing "format" will format it.
        $ Typing "clean" will remove the binaries

## Running
        $ ./banhammer along with any of these options will run the banhammer program.
	$ ./banhammer -h will print information on all options available.
        $ ./banhammer -m Print program statistics.
        $ ./banhammer -t Specify hash table size (default: 10000).
	$ ./banhammer -f Specify Bloom filter size (default: 2^20).
	$ ./banhammer -s Print program statistics.

