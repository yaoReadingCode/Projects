//-----------------------------------------------------------------------------
// List.cpp
// Implementation file for List ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include<limits>
#include"List.h"

// Private Constructor --------------------------------------------------------

// Node constructor
List::Node::Node(ListElement x){
   data = x;
   next = nullptr;
   prev = nullptr;
}

// Class Constructors & Destructors -------------------------------------------

// Creates a new List in the empty state.
List::List() {
	frontDummy = new Node(std::numeric_limits<int>::min());
	backDummy =  new Node(std::numeric_limits<int>::max());
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	num_elements = 0;
	pos_cursor = 0;
}

// Copy Constructor.
List::List(const List& L) {
	// make this an empty List
	frontDummy = new Node(std::numeric_limits<int>::min());
	backDummy = new Node(std::numeric_limits<int>::max());
	//frontDummy->next = backDummy;
	//backDummy->prev = frontDummy;
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	num_elements = 0;
	beforeCursor->next = backDummy;
	afterCursor->prev = frontDummy;
	Node* n = L.frontDummy->next;
	while( n->next != nullptr) {
		this->insertBefore(n->data);
		n = n->next;
	}
	pos_cursor = 0;
	//for (int i = 0; i != L.position(); i++) {
	//	this->moveNext();
	//}
}

// Destructor
List::~List() {
	clear();
	Node* f = frontDummy;
	delete f;
	Node* d = backDummy;
	delete d;
}

// Access functions --------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const {
	return(this->num_elements);
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const {
	if( num_elements == 0 ){
		throw std::length_error("List: front(): empty List");
	}
	return(this->frontDummy->next->data);
}

ListElement List::back() const {
	if( num_elements == 0 ){
                throw std::length_error("List: back(): empty List");
        }
	return(this->backDummy->prev->data);
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const {
	if( pos_cursor < 0 || pos_cursor > num_elements ){
                throw std::out_of_range("List: position(): cursor position value is out of range");
        }
	return(this->pos_cursor);
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const {
	if( pos_cursor >= num_elements ){
                throw std::range_error("List: peekNext: cursor at back");
        }
	return(this->afterCursor->data);
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const {
	if( pos_cursor <= 0 ){ // check this
                throw std::range_error("List: peekPrev(): cursor at front"); // check this
        }
	return(this->beforeCursor->data);
}

// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear() {
	moveFront();
	while(num_elements != 0) {
		this->eraseAfter();
	}
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront() {
	pos_cursor = 0;
	beforeCursor = this->frontDummy;
	afterCursor = (this->frontDummy->next);
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack() {
	pos_cursor = this->num_elements;
	beforeCursor = this->backDummy->prev;
	afterCursor = this->backDummy;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over.
// pre: position()<length()
ListElement List::moveNext() {
	if(pos_cursor >= num_elements) { 
		throw std::range_error("List: moveNext(): cursor at back");
	}
	pos_cursor++;
	afterCursor = this->afterCursor->next;
	beforeCursor = this->beforeCursor->next;
	return (this->beforeCursor->data);
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over.
// pre: position()>0
ListElement List::movePrev() {
	if(pos_cursor <= 0) {
                throw std::range_error("List: movePrev(): cursor at front");
        }
        pos_cursor--;
        afterCursor = afterCursor->prev;
        beforeCursor = beforeCursor->prev;
        return (afterCursor->data);
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x) { // isnt insert after and insert before the same thing?
	Node* n = new Node(x);
	n->next = this->afterCursor;
	n->prev = this->beforeCursor;
	this->afterCursor->prev = n;
	this->afterCursor = n;
	this->beforeCursor->next = n;
	this->num_elements++;
}

// insertBefore()
// Inserts x after cursor.
void List::insertBefore(ListElement x) {
        Node* n = new Node(x);
        n->next = afterCursor;
        n->prev = beforeCursor;
        this->afterCursor->prev = n;
        this->beforeCursor->next = n;
	this->beforeCursor = n;
	this->num_elements++;
	this->pos_cursor++;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x) {
	if(pos_cursor >= num_elements) {
                throw std::range_error("List: setAfter(): cursor at back");
        }
	this->afterCursor->data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x) {
	if(pos_cursor <= 0) {
                throw std::range_error("List: setBefore(): cursor at front");
        }
	this->beforeCursor->data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter() {
	if(pos_cursor >= num_elements) {
                throw std::range_error("List: eraseAfter(): cursor at back");
        }
	Node* n = afterCursor;
	this->afterCursor->next->prev = this->beforeCursor;
	this->beforeCursor->next = this->afterCursor->next;
	this->afterCursor = this->afterCursor->next;
	this->num_elements--;
	delete n;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore() {
	if(pos_cursor <= 0) {
                throw std::range_error("List: setBefore(): cursor at front");
        }
	Node* n = this->beforeCursor;
        this->beforeCursor->prev->next = this->afterCursor;
        this->afterCursor->prev = this->beforeCursor->prev;
        this->beforeCursor = this->beforeCursor->prev;
        this->num_elements--;
	this->pos_cursor--;
        delete n;
}

// Other Functions ---------------------------------------------------------


// findNext()
// Starting from the current cursor position, performs a linear search (in
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then
// returns the final cursor position. If x is not found, places the cursor
// at position length(), and returns -1.
int List::findNext(ListElement x) {
	ListElement a;
	bool f = false;
	//this->moveFront();
	//int p = this->pos_cursor;
	//int c = this->num_elements - p;
	for(int i = this->pos_cursor; i != num_elements; i++) {
		a = this->moveNext();
		if (x == a) {
			f = true;
			//c = this->pos_cursor - p;
			break;
		}
	}
	//for (int j = 0; j < c; j++) {
	//	this->movePrev();
	//}
	if (f == false) {
		return -1;
	}
	else {
		return pos_cursor;
	}
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor
// at position 0, and returns -1.
int List::findPrev(ListElement x) {
	ListElement a;
	bool f = false;
	//int p = this->pos_cursor;
	//int c = -(0 - p);
	//moveBack();
	for(int i = this->pos_cursor; i != 0; i--) {
		a = this->movePrev();
		if (x == a) {
			f = true;
			//c = -(this->pos_cursor - p);
			break;
		}
	}
	//for (int j = 0; j < c; j++) {
        //        this->moveNext();
        //}
	if (f == false) {
		return -1;
	}
	else {
		return pos_cursor;
	}
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup() {
	int pc = this->pos_cursor;
	Node*n = this->afterCursor;
	Node*p = this->beforeCursor;
	this->moveFront();
	this->moveNext();
	int c = 1;
	for (Node* x = this->frontDummy->next; x != this->backDummy; x = x->next) {
		//std::cout << "A = " << (*this) << std::endl;
		//std::cout << "x value is " << std::to_string(x->data) << std::endl;
		c += 1;
		while( this->pos_cursor != this->backDummy->data ) {
			if (x->data == this->afterCursor->data) {
				if(this->pos_cursor == pc) {
					p->next = p->next->next;
				}
				else if (this->pos_cursor +1 == pc) {
					n ->prev = n->prev->prev;
					pc -= 1;
				}
				else if(this->pos_cursor < pc) {
					pc -= 1;
				}
				this->eraseAfter();
			}
			else {
				if( this->pos_cursor == this->num_elements) {
					break;
				}
				else {
					this->moveNext();
				}
			}
		}
		this->moveFront();
		for (int i = 0; i < c; i+=1) {
			if (this->pos_cursor == this->num_elements) {
				break;
			}
			else {
				this->moveNext();
			}
		}
	}
	this->pos_cursor = pc;
	this->afterCursor = n;
	this->beforeCursor = p;
}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const {
	List A = List(*this);
	Node* n = L.frontDummy->next;
	A.moveBack();
	while(n != L.backDummy) {
		A.insertAfter(n->data);
		n = n->next;
		A.moveNext();
	}
	A.moveFront();
	return A;
	// List* B = this->concat(List* L); ???
}

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const {
	std::string s = "(";
	Node* n;
	if ( this->num_elements == 0) {
		return (s += ")");
	}
	for( n = this->frontDummy->next; n != this->backDummy->prev; n = n->next) {
		s += std::to_string(n->data)+", ";
		//std::cout << "the next one is " << std::to_string(n->next->data);
	}
	//n = n->next;
	s += std::to_string(n->data);
	s += ")";
	return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const {
	bool eq = false;
	Node* n = this->frontDummy->next;
	Node* m = R.frontDummy->next;
	eq = ( this->num_elements == R.num_elements );
	while(eq && n!= this->backDummy) {
		eq = (n->data == m->data);
		n = n->next;
		m = m->next;
	}
	return eq;
}

// Overriden Operators --------------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ) {
	return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ) {
	return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ) {
	if ((L.length() == 0) &&  (this->num_elements == 0)) {
		return *this;
	}
	//std::cout << "hello" << std::endl;
	if (this != &L){
		List temp = L;
		std::swap(beforeCursor, temp.beforeCursor);
		std::swap(afterCursor, temp.afterCursor);
		std::swap(frontDummy, temp.frontDummy);
		std::swap(backDummy, temp.backDummy);
		//std::swap(this->num_elements, temp.num_elements);
		std::swap(this->pos_cursor, temp.pos_cursor);
		temp.num_elements = num_elements;
		num_elements = L.num_elements;
		//pos_cursor = L.pos_cursor;
	}
	return *this;
}


