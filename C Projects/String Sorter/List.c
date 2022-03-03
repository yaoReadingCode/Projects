#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj	{
	int data;
	Node next;
	Node prev;
} NodeObj;

// private ListObj type
typedef struct ListObj	{
	Node front;
	Node back;
	int length;
	Node cursor;
	int index;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(int data){
	// allocates memory for node
	Node N = malloc(sizeof(NodeObj));
	N->data = data;
	N->next = NULL;
	N->prev = NULL;
	return(N);
}

// Frees memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN){
	if( pN!=NULL && *pN!=NULL ){
		free(*pN);
		*pN = NULL;
	}
}

// newList()
// Returns reference to new empty List object.
List newList(void){
	List L = malloc(sizeof(ListObj));
	L->front = L->back = L->cursor = NULL;
	L->length = 0;
	L->index = -1;
	return(L);
}

void freeList(List* pL) {
	if(pL!=NULL && *pL!=NULL) {
		while( !isEmpty(*pL) ) {
			deleteFront(*pL);
		}
		free(*pL);
		*pL = NULL;
	}
}

// Access functions -----------------------------------------------------------

// Returns the number of elements in L.
int length(List L){
	return L->length;
}

// Returns index of cursor element if defined, -1 otherwise.
int index(List L){
	if (L->cursor!=NULL) {
		return L->index;
	}
	return -1;
}

// Returns front element of L. Pre: length()>0
int front(List L) {
	if (length(L) == 0) {
		return -1;
	}
	return L->front->data;
}

// Returns back element of L. Pre: length()>0
int back(List L) {
	if (length(L) == 0) {
		return -1;
	}
	return L->back->data;
}

// Returns cursor element of L. Pre: length()>0, index()>=0
int get(List L) {
	if (length(L)==0 && L->index==-1) {
		printf("hello");
		return -1;
	}
	return L->cursor->data;
}

// Returns true iff Lists A and B are in same state, and returns false otherwise.
bool equals(List A, List B) {
	if( A==NULL || B==NULL ){
		printf("List Error: calling equals() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	bool equal = (A->length == B->length);
	Node N = NULL;
	Node M = NULL;
	N = A->front;
	M = B->front;
	while (equal && N!=NULL) {
		equal = (N->data == M->data);
		N = N->next;
		M = M->next;
	}
	return equal;
}

// Manipulation procedures ----------------------------------------------------

// Resets L to its original empty state.
void clear(List L) {
	while(!isEmpty(L)) {
		deleteFront(L);
	}
}

// Overwrites the cursor element’s data with x. Pre: length()>0, index()>=0
void set(List L, int x) {
	if (!isEmpty(L) && L->index!=-1) {
		L->cursor->data = x;
	}
}

// If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveFront(List L) {
	if (!isEmpty(L)) {
		L->cursor = L->front;
		L->index = 0;
	}
	if( L==NULL ){
		printf("List Error: calling getFront() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if( isEmpty(L) ){
		printf("List Error: calling getFront() on an empty List\n");
		exit(EXIT_FAILURE);
	}
}

// If L is non-empty, sets cursor under the back element, otherwise does nothing
void moveBack(List L) {
	if (!isEmpty(L)) {
		L->cursor = L->back;
		L->index = (L->length);
	}
	if( L==NULL ){
		printf("List Error: calling getFront() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if( isEmpty(L) ){
		printf("List Error: calling getFront() on an empty List\n");
		exit(EXIT_FAILURE);
	}
}

// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined do nothing
void movePrev(List L) {
	if (L->cursor!=NULL && L->index!=0) {
	       L->cursor = L->cursor->prev;
	       L->index--;
	} 
	else if (L->cursor!=NULL && L->index==0) {
		L->cursor = NULL;
		L->index = -1;
	}
}

// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L) {
	if (L->cursor!=NULL && L->index!=(L->length)) {
               L->cursor = L->cursor->next;
               L->index++;
        } 
	else if (L->cursor!=NULL && L->index==(L->length)) {
		L->cursor = NULL;
                L->index = -1;
	}
}

// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, int x) {
	Node N = newNode(x);
	if (isEmpty(L)) {
		L->front = L->back = N;
		L->length += 1;
		return;
	}
	L->front->prev = N;
	N->next = L->front;
	N->prev = NULL;
	L->front = N;
	L->length += 1;
}

// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, int x) {
	Node N = newNode(x);
	if (isEmpty(L)) {
                L->front = L->back = N;
                L->length += 1;
		return;
        }
	L->back->next = N;
	N->prev = L->back;
	N->next = NULL;
	L->back = N;
	L->length += 1;
}

// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int x) {
	if (!isEmpty(L) && L->index!=-1) {
		Node N = newNode(x);
		N->next = L->cursor;
		N->prev = L->cursor->prev;
		L->cursor->prev->next = N;
		L->cursor->prev = N;
		L->length += 1;
	}
}

// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int x) {
	if (!isEmpty(L) && L->index!=-1) {
		Node N = newNode(x);
		N->next = L->cursor->next;
		N->prev = L->cursor;
		L->cursor->next->prev = N;
		L->cursor->next = N;
		L->length += 1;
	}
}

// Delete the front element. Pre: length()>0
void deleteFront(List L) {
	if (!isEmpty(L) || L->length!=1) {
		L->front = L->front->next;
		freeNode(&L->front->prev);
		L->front->prev = NULL;
		L->length -= 1;
	}
	if (L->length == 1) {
		freeNode(&L->front);
		L->front = L->back = NULL;
		L->length -= 1;
	}

}


// Delete the back element. Pre: length()>0
void deleteBack(List L) {
	if (!isEmpty(L) || L->length!=1) {
                L->back = L->back->prev;
                freeNode(&L->back->next);
                L->back->next = NULL;
                L->length -= 1;
        }
        if (L->length == 1) {
                freeNode(&L->front);
                L->front = L->back = NULL;
		L->length -= 1;
        }
}

// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L) {
	if (isEmpty(L)) {
		printf("List Error: calling delete on an empty List\n");
		exit(EXIT_FAILURE);
	}
	if (L->index == -1) {
		printf("List Error: calling delete with no cursor\n");
                exit(EXIT_FAILURE);
	}
	L->cursor->next->prev = L->cursor->prev;
	L->cursor->prev->next = L->cursor->next;
	freeNode(&L->cursor);
	L->length -= 1;
}

// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
void printList(FILE* out, List L) {
	Node N = NULL;
	if( L==NULL ){
		printf("List Error: calling printList() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	for(N = L->front; N != NULL; N = N->next){
		fprintf(out, "%d ", N->data);
	}
	fprintf(out, "\n");
}

// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L) {
	List R = newList();
	//L->cursor = L->front;
	//Node N = newNode(L->front->data);
	//R->front = R->back = N;
	moveFront(L);
	for (int i = 0; i < length(L); i++) {
		append(R, L->cursor->data);
		moveNext(L);
		R->cursor = NULL;
	}
	moveFront(L);
	for (int x = 0; x != L->index; x++) {
		moveNext(L);
	}
	return R;
}

bool isEmpty(List L) {
	if (L == NULL) {
		printf("Queue Error: calling isEmpty() on NULL Queue reference\n");
		exit(EXIT_FAILURE);
	}
	return (L->length == 0);
}
