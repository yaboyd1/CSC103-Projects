/*
 * CSc103 Project 1: (hello_world++)
 * See readme.html for details.
 * Please list all references you made use of in order to complete the
 * assignment: your classmates, websites, etc.  Aside from the lecture notes
 * and the book, please list everything.  And remember- citing a source does
 * NOT mean it is okay to COPY THAT SOURCE.  What you submit here **MUST BE
 * YOUR OWN WORK**.
 * References:
 * Used the temnplate from readme.html
 * The website showed me how to save/compile my code.
 * https://www-cs.ccny.cuny.edu/~wes/CSC103/commandline.html
 * Ash showed me namepace.
 * Zafrul helped fix my bugs regarding the getline function.
 */

#include<iostream>
#include<string>
using namespace std;

/*
Dewan Tahmid
ID: 23927007
CSC 103 Project 1
Goal: Modify helloworld.cpp into a more personal greeting.
*/

int main()
{
    // Declaring two strings to hold a  name and a relative
    string name, relative;

    // Assigning name to whatever the user wants
    cout << "Enter your name:\n";
    getline(cin,name);

    // Assigning relative to whatever the user wants
    cout << "Enter a relative:\n";
    getline(cin,relative);

    // Printing out "The Princess Bride" line thing
    cout << "Hello. My name is " << name << ". You killed my " << relative << ". Prepare to die.\n";

    // If "echo'd", should return 0 which means good
    return 0;
}
