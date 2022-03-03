# Depth First Search- Hamiltonion Path
The purpose of this code is to implement a program that will find a hamiltonian path through a graph of vertices. A hamiltonian path is a path that travels through all the vertices only once. This code finds the shortest one out of all the hamiltonian paths. This is also a program that focuses heavily on recursion.

## Build

        $ Typing "make" will build it.
        $ Typing "format" will format it.
        $ Typing "clean" will remove the binaries

## Running

        $ ./tsp along with any of these options will run the program
        $ ./tsp -u will set the matrix type as undirected (this means that the weight between two vertices is the same forwards and back).
        $ ./tsp -v will set verbose which means that it will print out all paths
        $ ./tsp -i will set the infile to read from
	$ ./tsp -o will set the outfile to write to
        $ ./tsp -h will print all options available.

## scan-build make errors
When scan-build make is run, it call error on some of my comparisons in regards to making sure that the vertices inputed are not smaller than 0. It says that uint32 integers cannot be lower than 0. While this is true and I can easily remove it, it feels wrong to me to not write that to check it's not lower than 0. Although I understand why it's not possible for a uint32 number to be lower than 0, I am keeping it in as a design choice due to my primative monkey brain like to keep that comparison in. It still works perfectly fine regardless.


