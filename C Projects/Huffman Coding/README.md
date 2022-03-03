# Huffman Coding Program
The purpose of this code is to implement a program that compresses a file. Compression is extremely important in anything to do with computing and sending information in today's age. This is done by assigning codes to characters and writing that instead of the orginal message along with information on how to decompress it. Then, this is decompressed with information that tells us the cipher.

## Build

        $ Typing "make", or "make all" will build it all.
	$ Typing "make" with encode, decode, or entropy will make those specific programs
        $ Typing "format" will format it.
        $ Typing "clean" will remove the binaries

## Running
	$ ./entropy < [input (reads from stdin)] will measure the amount of entropy in the input
	$ ./error -h will print all options available.

        $ ./encode along with any of these options will run the encode program.
	$ ./encode -h will print information on all options available.
        $ ./encode -i will set the infile to read from.
        $ ./encode -o will set the outfile to write to.
	$ ./encode -v will print compression statistics.

	$ ./decode along with any of these options will run the decode program.
        $ ./decode -h will print all options available.
        $ ./decode -v will print compression statistics.
        $ ./decode -i will set the infile to read from.
        $ ./decode -o will set the outfile to write to.

## Notes
I was able to get to the point of making the encoding work. However, the decoding part of the program is still not working. It is something I have to work on in the future.

