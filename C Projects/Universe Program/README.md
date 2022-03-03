# Double Pointer ADT Program "Universe"

The purpose of this code is to implement the game of life. This is a game that initializes each cell in a matrix to alive, true, or dead, false. It will run through so many generations before reaching a conclusion. Every round it kills off, keeps alive, or revives a cell depending on its surounding neighbors. This program creates an ADT called universe and is the central point of this assignment. 

## Build

        Typing "make" will build it.
        Typing "format" will format it.
        Typing "clean" will remove the binaries

## Running

        $ ./life along with the specified command line options will run this program.
        $ ./life -t will specify that the universe is a toroidal
        $ ./life -s will silence ncurses
        $ ./life -n generations(must specify) will specify the number of generations to run. Default is 100.
        $ ./life -i along with an input file will specify the input file to read
        $ ./life -o along with an output file will specify the outfile to print the final state to.

