/*
 * CSc103 Project 2: prime numbers.
 * See readme.html for details.
 * Please list all references you made use of in order to complete the
 * assignment: your classmates, websites, etc.  Aside from the lecture notes
 * and the book, please list everything.  And remember- citing a source does
 * NOT mean it is okay to COPY THAT SOURCE.  What you submit here **MUST BE
 * YOUR OWN WORK**.
 * References:
 * readme.html
 */

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
 unsigned long input;

 while (cin >> input) {

  //Initializeing as prime
  bool isPrime = true;

  //If even and not 2, not prime
  //If 0 or 1, not prime
  if ((input % 2 == 0 && input != 2) || input < 2) {
   isPrime = false;
  }

  //Checking all odd numbers up to the square root
  for (int i = 3; i < sqrt(input) + 1; i+=2) {
   if (input % i == 0)
    isPrime = false;
  }

  cout << isPrime << endl;

 }

 return 0;
}
