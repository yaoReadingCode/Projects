#include<iostream>
#include<string>
#include<stdexcept>
#include<stdio.h>
#include<stdlib.h>
#include<tgmath.h>
#include"List.h"


using namespace std;

int main () {
	// List will be 1, 2, 3, 4, 5, 6
        List a = List();
        List b = a;
	a.moveFront();
	b.moveBack();
	for (int i = 1; i < 4; i++) {
		a.insertBefore(i);
	}
	for (int i = 6; i > 3; i--) {
		b.insertAfter(i);
	}
	List c = a.concat(b);
	// c = 1,2,3,4,5,6
	std::cout << c << std::endl;
	c.setAfter(7);
	c.moveNext();
	c.setBefore(1);
	c.movePrev();
	std::cout << c << std::endl;
	c.moveBack();
	c.eraseBefore();
	c.movePrev();
	c.eraseAfter();
	std::cout << c << std::endl;
	std::cout << "1 in list c should be at position 0. 1 is at " << c.findPrev(1) << std::endl;
	std::cout << "4 in lsit c should be at position 4. 4 is at " << c.findNext(4) << std::endl;
	c.insertAfter(5);
	c.insertAfter(5);
	c.cleanup();
	List d = c;
	if (!(c == d)) {
		std::cout << "it didnt work out" << std::endl;
	}
	else {
		std::cout << "it worked" << std::endl;
	}
	a = c;
	std::cout << a << endl;
	std::cout << "Everything was tested. All functions were either called or called through another function. Good day, sir" << std::endl;
        return (0);
}


