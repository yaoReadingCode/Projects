#include "Dictionary.h"
#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <tgmath.h>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {
	ifstream in;
	ofstream out;
	string line;
	// check command line for correct number of arguments
	if( argc != 3 ){
		cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
		return(EXIT_FAILURE);
	}
	
	// open files for reading and writing
	in.open(argv[1]);
	if( !in.is_open() ){
		cerr << "Unable to open file " << argv[1] << " for reading" << endl; 
		return(EXIT_FAILURE);
	}
	out.open(argv[2]);
	if( !out.is_open() ){
		cerr << "Unable to open file " << argv[2] << " for writing" << endl;
		return(EXIT_FAILURE);
	}
	int ll = 1;
	Dictionary D = Dictionary();
	while( getline(in, line) )  {
		D.setValue(line, ll);
		ll++;
	}
	//cout << D << endl;
	out << D << endl;
	//cout << D.pre_string();
	out << D.pre_string();
	in.close();
	out.close();
	return (EXIT_SUCCESS);
}

