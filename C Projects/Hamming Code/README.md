# Hamming Coding
The purpose of this code is to implement a program that checks if there are errors within a communicated data. This is done by adding extra bits at the end the data bits. The extra data checks if there are any problems. We are implementing matrices to encode and decode data which will result in an error code that tells us if there is something wrong with the message.

## Build

        $ Typing "make" will build it.
        $ Typing "format" will format it.
        $ Typing "clean" will remove the binaries

## Running
	$ ./error along with any of these options will run the program.
	$ ./error -h will print all options available.
	$ ./error -s will specifies random seed.
	$ ./error -e will specifies error rate.
	
	$ ./encode along with any of these options will run the encode program.
	$ ./encode -h will print all options available.
	$ ./encode -i will set the infile to read from.
	$ ./encode -o will set the outfile to write to.
	
	$ ./decode along with any of these options will run the decode program.
	$ ./decode -h will print all options available.
	$ ./decode -v will set verbose which means that it will print out statistics.
	$ ./decode -i will set the infile to read from.
	$ ./decode -o will set the outfile to write to.

## scan-build make errors
When scan-build make is run, it says that a parameter is set but not used but that is simply because I haven't used the function. It "works" regardless though.

## Notes
I have gotten the encoding program to work. However, I have not gotten my decoding to work yet. It is something I will work on in the future.

