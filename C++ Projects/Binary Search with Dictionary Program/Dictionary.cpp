#include "Dictionary.h"
#include <iostream>
#include <math.h>
#include <stdexcept>
#include <string>
#include <string.h>
#include <stdio.h>
#include <limits>

// Private Constructor --------------------------------------------------------

// Node constructor
Dictionary::Node::Node(keyType k, valType v) {
	key = k;
	val = v;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
}

// Helper Functions (Optional) ---------------------------------------------

// Transplant- Helper
// slices node into tree
void Dictionary::Transplant(Node* u, Node* v) {
        if (u->parent == this->nil) {
                this->root = v;
        }
        else if (u == u->parent->left) {
                u->parent->left = v;
        }
        else { // u == u->parent->right
                u->parent->right = v;
        }
        if (v != this->nil) {
                v->parent = u->parent;
        }
}

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const {
	if (R != this->nil) {
		this->inOrderString(s, R->left);
		s += R->key + " : " + std::to_string(R->val) + "\n";
		this->inOrderString(s, R->right);
	}
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const {
	if (R != this->nil) {
                s += R->key + "\n";
		this->preOrderString(s, R->left);
                this->preOrderString(s, R->right);
	}
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N) {
	if (R != N) {
		this->setValue(R->key, R->val);
		this->preOrderCopy(R->left, N);
		this->preOrderCopy(R->right, N);
	}
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R, sets R to nil.
void Dictionary::postOrderDelete(Node* R) {
	if (R != this->nil) {
		this->postOrderDelete(R->left);
		this->postOrderDelete(R->right);
		delete(R);
	}
	this->num_pairs = 0;
	this->current = this->nil;
	this->root = this->nil;
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
	//Dictionary::Node nil = new Dictionary::Node("/000", std::numeric_limits<int>::min());
	if (R == this->nil || k == R->key) {
		return R;
	}
	else if (k < (R->key)) { // k < R->key
		return search(R->left, k);
	}
	else { // k > R->key
		return search(R->right, k);
	}
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R) {
	if (R != this->nil) {
		while (R->left != this->nil) {
			R = R->left;
		}
		return R;
	}
	else {
		return this->nil;
	}
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R) {
	if (R != this->nil) {
		while (R->right != this->nil) {
			R = R->right;
		}
		return R;
	}
	else {
		return this->nil;
	}
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findNext(Node* N) {
	if (N == this->nil || N->right == this->nil) {
		return this->nil;
	}
	while (N->right != this->nil ) {
		N = N->right;
	}
	return N;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N) {
	if (N == this->nil || N->left == this->nil) {
		return this->nil;
	}
	while (N->left != this->nil) {
		N = N->left;
	}
	return N;
}


// Class Constructors & Destructors ----------------------------------------

// Creates new Dictionary in the empty state.
Dictionary::Dictionary() {
	nil = new Node("/000", std::numeric_limits<int>::min());
	root = nil;
	current = nil;
	num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D) {
	this->nil = new Node("/000", std::numeric_limits<int>::min());
	this->num_pairs = 0;
	this->root = this->nil;
	this->current = this->nil;
	this->preOrderCopy(D.root, D.nil);
}

// Destructor
Dictionary::~Dictionary() {
	this->clear();
	delete(this->nil);
}

// Access functions --------------------------------------------------------
// size()
// Returns the size of this Dictionary.
int Dictionary::size() const {
	return this->num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const {
	Node*n = this->search(this->root, k);
	if (n == this->nil) {
		return false;
	}
	else {
		return true;
	}
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const {
	if (this->contains(k)) {
		Node* n = this->search(this->root, k);
		return n->val;
	}
	else {
		throw std::logic_error("Dictionary: getValue(): key  does not exist");
	}
}



// hasCurrent()
// Returns true if the current iterator is defined, and returns false
// otherwise.
bool Dictionary::hasCurrent() const {
	return (this->current != this->nil);
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent()
keyType Dictionary::currentKey() const {
	if (this->hasCurrent()) {
		return this->current->key;
	}
	else {
		throw std::logic_error("Dictionary: currentKey(): current undefined");
	}
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const {
	if (this->hasCurrent()) {
		return this->current->val;
	}
	else {
		throw std::logic_error("Dictionary: currentVal(): current undefined");
	}
}

// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear() {
	this->postOrderDelete(this->root);
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v,
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v) {
	this->num_pairs += 1;
	Node *z = new Node(k, v);
	z->left = this->nil;
	z->right = this->nil;
	Node *y = this->nil;
	Node *x = this->root;
	bool c;
	while (x != this->nil) {
		y = x;
		if (y->key == k) {
			this->num_pairs -= 1;
			y->val = v;
			delete(z);
			return;
		}
		//y->left = z; // extra code
		//std::cout << "root left is " << this->root->left->key << std::endl;
		//std::cout << "x is " << x->key << " k is " << k << std::endl;
		if ((c = (z->key < x->key))) {
			//std::cout << "left" << std::endl;
			x = x->left;
		}
		else {
			//std::cout << "right" << std::endl;
			x = x->right;
		}
	}
	z->parent = y;
	if (y == this->nil) {
		this->root = z;
		//std::cout << this->root->key << " is the root" << std::endl;
	}
	else if (c) { //z->key < y->key) {
		//std::cout << !k.compare(y->key) << std::endl;
		y->left = z;
		//std::cout << y->key << " is the parent of left child z " << z->key << std::endl;
	}
	else { // z->key > y->key
		y->right = z;
		//std::cout << y->key << " is the parent of left child z " << z->key << std::endl;
	}
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k) {
	if (contains(k)) {
		Node* z = this->search(this->root, k);
		if (z->left == this->nil) {
			this->Transplant(z, z->right);
		}
		else if (z->right == this->nil) {
			this->Transplant(z, z->left);
		}
		else {
			Node* y = this->findMin(z->right);
			if (y->parent != z) {
				this->Transplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			this->Transplant(z, y);
			y->left = z->left;
			y->left->parent = y;
		}
		if (this->current == z) {
			this->current = this->nil;
		}
		delete(z);
		this->num_pairs -= 1;
	}
	else {
		throw std::logic_error("Dictionary: remove(): key does not exist");
	}
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing.
void Dictionary::begin() {
	if (this->size() > 0) {
		this->current = this->findMin(this->root);
	}
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing.
void Dictionary::end() {
	if (this->size() > 0) {
		this->current = this->findMax(this->root);
	}
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next() {
	if (this->hasCurrent()) {
		if (this->current == this->findMax(this->root)) {
			this->current = this->nil;
			return;
		}
		if (this->current->right != this->nil) {
			this->current = this->findMin(this->current->right);
			return;
		}
		Node* y = this->current->parent;
		while (y != this->nil && this->current == y->right) {
			this->current = y;
			y = y->parent;
		}
		this->current = y;
		return;
	}
	else {
		throw std::logic_error("Dictionary: next(): current not defined");
	}
}

// prev()
// If the current iterator is not at the first pair, moves current to
// the previous pair (as defined by the order operator < on keys). If
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev() {
	if (this->hasCurrent()) {
		if (this->current == this->findMin(this->root)) {
			this->current = this->nil;
			return;
		}
		if (this->current->left != this->nil) {
			this->current = this->findMax(this->current->left);
			return;
		}
		Node* y = this->current->parent;
		while (y != this->nil && this->current == y->left) {
			this->current = y;
			y = y->parent;
		}
		this->current = y;
		return;
	}
	else {
		throw std::logic_error("Dictionary: prev(): current not defined");
	}
}

// Other Functions --------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const {
	std::string s;
	this->inOrderString(s, this->root);
	return s;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const {
	std::string s;
	this->preOrderString(s, this->root);
	return s;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const {
	std::string s = this->pre_string();
	std::string x = this->to_string();
	std::string r = D.pre_string();
	std::string y = D.to_string();
	if (s == r && x == y) {
		return true;
	}
	else {
		return false;
	}
}

// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ) {
	return stream << D.Dictionary::to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals().
bool operator==( const Dictionary& A, const Dictionary& B ) {
	if (A.equals(B)) {
		return true;
	}
	else {
		return false;
	}
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ) {
	Dictionary temp = Dictionary(D);
	std::swap(nil, temp.nil);
	std::swap(root, temp.root);
	std::swap(current, temp.current);
	num_pairs = temp.num_pairs;
	return (*this);
}

