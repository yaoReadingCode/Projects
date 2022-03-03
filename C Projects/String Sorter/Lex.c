#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "List.h"
#include<string.h>

#define BUFFER 255

int main(int argc, char * argv[]) {
	FILE *in, *out;
	char line[BUFFER];
	if (argc != 3) {
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}

	in = fopen(argv[1], "r");
	if (in == NULL) {
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}

	out = fopen(argv[2], "w");
        if (out == NULL) {
                printf("Unable to open file %s for writing\n", argv[2]);
                exit(1);
        }

	int lc = 0;
	for (char c = fgetc(in); c != EOF; c = fgetc(in)) {
		if (c == '\n') { // Increment count if this character is newline
			lc++; 
		}
	}
//	printf("%d\n", lc);
	fseek(in, 0, SEEK_SET);
//	char** strings = malloc(lc * sizeof(char*));
	char* strings[lc];
	int Lcount = 0;
	while( fgets(line, BUFFER, in) != NULL)  {
		strings[Lcount] =  (char*) calloc(1, BUFFER);
		strcpy(strings[Lcount], line);
		Lcount++;
	}
	List L = newList();
	append(L, 0);
	moveFront(L);
	//printList(stdout, L);
	int x = 0;
	for (int i=1; i<lc; i++) {
		int loc = get(L);
		int result = strcmp(strings[i], strings[loc]);
		if (result < 0) {
			while(result <0) {
				movePrev(L);
				if (index(L) == -1) {
					prepend(L, i);
					moveFront(L);
					result = 0;
					x = 1;

				} else {
					loc = get(L);
					result = strcmp(strings[i], strings[loc]);
				}
			}
			if (x == 0) {
				insertAfter(L, i);
			}
			x = 0;
		}
		else if (result > 0) {
//			printList(stdout, L);
			while(result > 0) {
                                 moveNext(L);
                                 if (index(L) == -1) {
                                         append(L, i);
                                         moveBack(L);
                                         result = 0;
					 x = 1;
                                 } else {
                                         loc = get(L);
                                         result = strcmp(strings[i], strings[loc]);
                                 }
                         }
			if (x == 0) {
				insertBefore(L, i);
			}
			x = 0;
                 }
		else {
			insertAfter(L, i);
		}
//		printList(stdout, L);
	}
//	for (int i=0; i<lc; i++) {
//		printf("%s\n", strings[i]);
//	}
//	printList(out, L);
	moveFront(L);
	for (int i=0; i < lc; i++) {
		fprintf(out, "%s", strings[get(L)]);
		moveNext(L);
	}
	freeList(&L);
//	free(*strings);
//	*strings=NULL;
	fclose(in);
	fclose(out);
	return(0);
}
