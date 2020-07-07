/*
 * CSc103 Project 4: Sorting with lists
 * See readme.html for details.
 * Please list all references you made use of in order to complete the
 * assignment: your classmates, websites, etc.  Aside from the lecture notes
 * and the book, please list everything.  And remember- citing a source does
 * NOT mean it is okay to COPY THAT SOURCE.  What you submit here **MUST BE
 * YOUR OWN WORK**.
 * References:
 * Ash, Azwad, Kyle, Matt
 * Finally, please indicate approximately how many hours you spent on this:
 * #hours: 5
 */

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <getopt.h> // to parse long arguments.
#include <string>
using std::string;

/* doubly linked list node: */
struct node {
	string data;
	node* prev;
	node* next;
	node(string s="", node* p=NULL, node* n=NULL) : data(s),prev(p),next(n) {}
};

node* first = NULL;
node* last = NULL;

void printListForward(node* L = first);
void printListReverse(node* L = last);
void printList(bool reverse = false);
void insertNext(string line, node*& L = last);
void insertPrev(string line, node*& L = first);
void insertBetween(string line, node*& before, node*& after);
bool isUnique(string line, node*& L = first);

//Deleted function
//void insertBefore(string line, node*& n);

int main(int argc, char *argv[]) {
	/* define long options */
	static int unique=0, reverse=0;
	static struct option long_opts[] = {
		{"unique",   no_argument,       &unique,   'u'},
		{"reverse",  no_argument,       &reverse,  'r'},
		{0,0,0,0} // this denotes the end of our options.
	};
	/* process options */
	char c; /* holds an option */
	int opt_index = 0;
	while ((c = getopt_long(argc, argv, "ur", long_opts, &opt_index)) != -1) {
		switch (c) {
			case 'u':
				unique = 1;
				break;
			case 'r':
				reverse = 1;
				break;
			case '?': /* this will catch unknown options. */
				return 1;
		}
	}
	/* NOTE: at this point, variables 'reverse' and 'unique' have been set
	 * according to the command line.  */
	/* TODO: finish writing this.  Maybe use while(getline(cin,line)) or
	 * similar to read all the lines from stdin. */

	string line;

	if (getline(cin, line)) {
		first = new node(line);
		last = first;
	}

	while (getline(cin, line)) {

		//I had no idea how to use echo for this so I did this to test
		//if (line == "END") break;

		if(line > last->data)
			insertNext(line);
		else if (line < first->data)
			insertPrev(line);
		else if(!isUnique(line, first) && (bool)unique) {
		}
		else {
			node* i;
			for (i = first; line >= i->data; i=i->next)
				if (i == last) break;

			if (i == first)
				insertPrev(line);
			else
				insertBetween(line, i->prev, i);
		}

		/* More things I used to test
		cout << "LIST: ";
		printList();
		cout << "| ";
		*/

	}

	printList((bool)reverse);

	return 0;
}

//Prints the linked list given start
void printListForward(node* L) {
	for (node* i = L; i != NULL; i = i->next) {
		cout << i->data << endl;
	}
}

//Prints linked list backwards given end
void printListReverse(node* L) {
	for (node* i = L; i != NULL; i = i->prev) {
		cout << i->data << endl;
	}
}

//Chooses to print in reverse or not
void printList(bool reverse) {
	if (reverse) printListReverse();
	else printListForward();
}

//Inserts an element to the last index of the linked list (pushback)
void insertNext(string line, node*& L) {
	L->next = new node(line, L);
	L = L->next;
}

//Inserts an element to the 1st index of the linked list (pushfront)
void insertPrev(string line, node*& L) {
	L->prev = new node(line, NULL, L);
	L = L->prev;
}

//Inserts an element in between two nodes
void insertBetween(string line, node*& before, node*& after) {
	node* temp = new node(line, before, after);
	before->next = temp;
	after->prev = temp;
}

//Checks if string is unique in a list
bool isUnique(string line, node*& L) {
	for (node* i = L; i != NULL; i = i->next) {
		if (line == i->data) return false;
	}
	return true;
}

/* I wrote this first but I kind of liked insertBetween better
//Inserts an elements before another element
void insertBefore(string line, node*& n) {
	node* temp = new node(line, n->prev, n);
	n->prev->next = temp;
	n->prev = temp;
}
*/