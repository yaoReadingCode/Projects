# Breadth First Search Program
The purpose of this program is to find the shortest paths between pairs of vertices using the Breadth First Algorithm.

## Files
	List.h-  	This file is a header file for the List ADT. It is what is included in the main Graph.c and FindPath program.
	List.c-  	This file is the List ADT that is the source file. It provides the functions for FindPath.c to use the List operations.
	Graph.h- 	This is the header file for the Graph ADT. It is included in the FindPath Program.
	Graph.c- 	This is the source file for the Graph ADT. It provides the functions for FindPath.c.
	GraphTest.c-	This tests the functionality of the Graph.c file. It makes sure everything works as is.
	FindPath.c-	This file is the main program. It uses the all ADT operations to find the shortest path between two vertices.
	Makefile-	This file is a script that runs the command to compile the code.
	README- 	This file descripes the program and lists all files submitted.

## Build
        $ Typing make will make FindPath
        $ Typing GraphClient makes GraphClient
        $ Typing make clean removes all binaries
        $ Typing "format" will format it.