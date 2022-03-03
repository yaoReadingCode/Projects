## Depth First Seach Program
The purpose of this program is to implement an algorithm to iterate through vertices using the Depth First Search Algorithm.

## Files
        List.h-         This file is a header file for the List ADT. It is what is included in the main Graph.c and FindPath program.
        List.c-         This file is the List ADT that is the source file. It provides the functions for FindPath.c to use the List operations.
        Graph.h-        This is the header file for the Graph ADT. It is included in the FindComponents Program.
        Graph.c-        This is the source file for the Graph ADT. It provides the functions for FindComponents.c.
        GraphTest.c-    This tests the functionality of the Graph.c file. It makes sure everything works as is.
        FindComponents.c-     This file is the main program. It uses the all ADT operations to find the strongly connected componenets of the digraph.
        Makefile-       This file is a script that runs the command to compile the code.
        README-         This file descripes the program and lists all files submitted.

## Build
        $ Typing make will make FindComponents
        $ Typing make GraphClient makes GraphClient
	$ Typing make GraphTest makes GraphTest
        $ Typing make clean removes all binaries
        $ Typing "format" will format it.
