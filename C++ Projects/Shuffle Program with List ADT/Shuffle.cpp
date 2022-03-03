#include<iostream>
#include<string>
#include<stdexcept>
#include<stdio.h>
#include<stdlib.h>
#include<tgmath.h>
#include"List.h"

using namespace std;

void shuffle(List& D) {
	//cout << D << endl;
	int m = floor((D.length()/2));
	if (D.length() < 2) {
		return;
	}
	int x = m;
	D.moveFront();
	for (int i = 0; i < m; i++) {
		ListElement y = D.moveNext();
		D.eraseBefore();
		for (int j = 0; j < x; j++) {
			D.moveNext();
		}
		D.insertBefore(y);
		x = x+1;
		D.moveFront();
	}
}

int main(int argc, char* argv[]){
	int in = 0;
	if (argc != 2) {
		cout << "Usage: " << argv[0] << "<Max cards in Deck>" << endl;
		exit(1);
	}
	in = atoi(argv[1]);
	if (in <= 0) {
		cout << "Invalid card number" << endl;
		exit(1);
	}
	cout << "deck size	shuffle count" << endl;
	cout << "------------------------------" << endl;
	List a = List();
	for (int i = 1; i != in+1; i++) {
		int n = 1;
		for (int j = 0; j < i; j++) {
			a.insertBefore(j);
			//cout << a << endl;
		}
		List b = a;
		shuffle(a);
		while (!(b.equals(a))) {
			//cout << "hello" << endl;
			shuffle(a);
			n++;
		}
		cout << " " << std::to_string(i) << "   		" << std::to_string(n) << endl;
		a.clear();
		b.clear();
	}
	return(0);
}
