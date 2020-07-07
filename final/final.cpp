/* Name: Dewan Tahmid */

#include <iostream>
#include <vector>
#include <string>
#include <limits.h>
#include <cmath>
#include <set>
using namespace std;

struct node {
 int data;
 node* next;
 //node(int d = 0, node* n=NULL) : data(d), next(n) {}
};

struct point {
 double x;
 double y;
};

/* ~~~~~~~~~~~ Answer to #1 ~~~~~~~~~~~ */

void minMaxAvg() {
 int min = INT_MAX;
 int max = INT_MIN;
 int sum = 0;
 int count = 0;
 int input;

 while (cin >> input) {
  if (input > max) {
   max = input;
  }
  if (input < min) {
   min = input;
  }
  sum += input;
  count++;
 }

 cout << "Min: " << min << endl;
 cout << "Max: " << max << endl;
 cout << "Avg: " << (double)sum/count << endl;
}

/* ~~~~~~~~~~~ Answer to #2 ~~~~~~~~~~~ */

void printTriangle(size_t input) {
 for (size_t i = 0; i < input; i++) {
  for (size_t j = 0; j < input; j++) {
   //I just discovered the ? operator midway into coding this and I gotta use it everywhere now
   i == input - 1 || j == 0 || i == j ? cout << "* " : cout << "  ";
   /*
   if (i == input - 1 || j == 0 || i == j) {
    cout << "* ";
   } else {
    cout << "  ";
   }
   */
  }
  cout << endl;
 }
}

/* ~~~~~~~~~~~ Answer to #3 ~~~~~~~~~~~ */

bool hasIntNthRoot(int k, int n) {
 for (int x = -abs(k); x <= abs(k); x++) {
  if (pow(x, n) == k) {
   return true;
  }
 }
 return false;
}

/* ~~~~~~~~~~~ Answer to #4 ~~~~~~~~~~~ */

void printSet(set<int> S) {
 for(set<int>::iterator i = S.begin(); i != S.end(); i++) {
  cout << *i << endl;
 }
}

bool isPerm(const vector<int>& V) {

 //Converting vector into an ordered set
 set<int> S;
 for (size_t i = 0; i < V.size(); i++) {
  S.insert(V[i]);
 }
 //printSet(S);

 //Ensures no repeating values
 if (S.size() != V.size()) return false;

 //Checks if vector indices are in set
 for (size_t i = 0; i < V.size(); i++) {
  if (S.find(i) == S.end()) {
   return false;
  }
 }

 return true;
}

/* ~~~~~~~~~~~ Answer to #5 ~~~~~~~~~~~ */

void printList(node* L) {
 for (node* i = L; i->next != NULL; i = i->next) {
  cout << i->data << " ";
 }
 cout << endl;
}

void insertNext(int x, node*& last) {
 last->next = new node();
 last->data = x;
 last = last->next;
}

void even_odd(node* L, node* E, node* O) {
 for (node* i = L; i->next != NULL; i = i->next) {
  //The ? is sooo cool omg
  i->data % 2 ? insertNext(i->data, O) : insertNext(i->data, E);
  /*
  if (i->data % 2) {
   insertNext(i->data, O);
  } else {
   insertNext(i->data, E);
  }
  */
 }
}

/* ~~~~~~~~~~~ Answer to #6 ~~~~~~~~~~~ */

/*
vector<vector<point> > classify(vector<point> S, vector<point> V) {
 double distance = (S[0].x * S[0].x) + (S[0].y * S[0].y);
 for (size_t i = 0; i < V.size(); i++) {
  for (size_t j = i; j < V.size(); j++) {

  }
 }
 return;
}
*/


/* ~~~~~~~~~~~ Answer to #7 ~~~~~~~~~~~ */

void printBinary(string input) {
 //Lmao, this just prints a string backwards
 for (int i = input.length(); i >= 0; i--) {
  cout << input[i];
 }
}

string convertToBinary(size_t input) {
 string binary = "";
 while (input > 0) {
  //for some reason binary += input % 2 doesn't work
  //I guess you can't type cast integers into strings
  //Damn, this is the first time I used the ? operator, I gotta go back and use it everywhere else now
  binary += input % 2 ? "1" : "0";
  input /= 2;
 }
 return binary;
}


size_t hamming(size_t x, size_t y) {
 size_t count = 0;

 string binX = convertToBinary(x), binY = convertToBinary(y);
 //cout << binX << endl << binY << endl;

 /*
  Algorithm in mind:
  Count which bits differ until min length reached
  Count the amount of zeroes until max length reached
 */

 string max = binX.length() > binY.length() ? binX : binY;
 string min = binX.length() < binY.length() ? binX : binY;
 //cout << max << endl << min << endl;
 //cout << max.length() << endl << min.length() << endl;

 for (size_t i = 0; i < max.length(); i++) {
  if (i < min.length()) {
   if (min[i] != max[i]) {
    count++;
   }
  } else {
   if (max[i] == 'O') {
    count++;
   }
  }
 }

 return count;
}


/* ~~~~~~~~~~~ Answer to #8 ~~~~~~~~~~~ */

int main() {
 /*
 //minMaxAvg();
 printTriangle(7);

 int num1 = -27, num2 = 3;
 cout << num1 << " does " << (hasIntNthRoot(num1, num2) ? "" : "not ") << "have an integer value of root " << num2 << endl;

 //Test List with both Evens and Odds
 node* L = new node();
 node* last = L;
 insertNext(82, last);
 insertNext(42, last);
 insertNext(33, last);
 insertNext(14, last);
 insertNext(79, last);
 insertNext(72, last);
 insertNext(81, last);
 cout << "L: ";
 printList(L);

 node* E = new node();
 node* O = new node();
 even_odd(L, E, O);
 cout << "E: ";
 printList(E); //82, 42, 14, 72
 cout << "O: ";
 printList(O); //33, 79, 81

 size_t ham1 = 7, ham2 = 1;
 cout << "The hamming distance between " << ham1 << " and " << ham2 <<" is " << hamming(7, 1) << endl; //1

 vector<int> V1 = {2,1,0,2}; //Not a Permutation
 vector<int> V2 = {3,1,0,2}; //Permutation
 cout << (isPerm(V1) ? "Permuation!" : "Not a Permutation :(") << endl;
 cout << (isPerm(V2) ? "Permuation!" : "Not a Permutation :(") << endl;
 */

 return 0;
}
