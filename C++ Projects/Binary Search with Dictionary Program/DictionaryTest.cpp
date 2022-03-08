//-----------------------------------------------------------------------------
//  BigIntegerClient.cpp
//  A test client for the BigInteger ADT
//-----------------------------------------------------------------------------
#include "Dictionary.h"
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

int main() {
	Dictionary A = Dictionary();
	A.setValue("f", 1);
	A.setValue("b", 2);
	A.setValue("e", 3);
	A.setValue("h", 4);
	A.setValue("a", 5);
	A.setValue("i", 6);
	cout << A.pre_string() << endl;
	Dictionary B = Dictionary(A);
	cout << B << endl;
	cout << B.pre_string() << endl;
	Dictionary C;
       	C = B;
	B.setValue("g", 6);
	cout << C << endl;
	if (A == B) {
		cout << "A = B" << endl;
	}
	else {
		cout << "A does not equal B" << endl;
	}
	cout << "A size if 6 and my size function says it is " << A.size() << endl;
	int i;
	if (A.contains("b")) {
		i = A.getValue("b");
	}
	cout << "A contains b at " << to_string(i) << endl;
	A.begin();
	if (A.hasCurrent()) {
		cout << "A has current at " << A.currentKey() << " with " << A.currentVal() << endl;
	}
	A.clear();
	cout << "A has been cleared so it has a size of " << A.size() << endl;
	cout << "This program has now tested all functions from the Dictionary ADT, either explicity or through a function that uses other functions. Good Day" << endl;
	return EXIT_SUCCESS;;
}

