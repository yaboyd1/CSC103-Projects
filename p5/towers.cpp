/*
 * CSc103 Project 5: Towers of Hanoi
 * See readme.html for details.
 * Please list all references you made use of in order to complete the
 * assignment: your classmates, websites, etc.  Aside from the lecture notes
 * and the book, please list everything.  And remember- citing a source does
 * NOT mean it is okay to COPY THAT SOURCE.  What you submit here **MUST BE
 * YOUR OWN WORK**.
 * References:
 *
 * http://www.cplusplus.com/reference/cstdio/printf/
 * https://youtu.be/fffbT41IuB4?t=339
 *
 * Finally, please indicate approximately how many hours you spent on this:
 * #hours: 2
 */

// TODO: write the program.
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <getopt.h> // to parse long arguments.
#include <cstdlib> // for atoi function and exit
#include <stdio.h> // printf!

void hanoi(size_t n, short start, short end, short placeholder);

static const char* usage =
"Usage: %s [OPTIONS]...\n"
"Solution to Tower of Hanoi Puzzle.\n\n"
"   -n \t sets the number of discs\n"
"   -s \t sets the starting peg location\n"
"   -e \t sets the ending peg location\n\n"
"./towers -n 4 -s 1 -e 3\n";

/* Here's a skeleton main function for processing the arguments. */
int main(int argc, char *argv[]) {
	// define long options
	static struct option long_opts[] = {
		{"start",        required_argument, 0, 's'},
		{"end",          required_argument, 0, 'e'},
		{"num-disks",    required_argument, 0, 'n'},
		{0,0,0,0} // this denotes the end of our options.
	};
	// now process the options:
	char c; // to hold the option
	int opt_index = 0;
	short n=4,start=1,end=3; /* to store inputs to the towers function. */
	while ((c = getopt_long(argc, argv, "s:e:n:", long_opts, &opt_index)) != -1) {
		switch (c) {
			case 's': // process option s
				start = atoi(optarg);
				break;
			case 'e': // process option e
				end = atoi(optarg);
				break;
			case 'n': // process option n
				n = atoi(optarg);
				break;
			case '?': // this will catch unknown options.
				// here is where you would yell at the user.
				// although, getopt will already print an error message.
				printf(usage,argv[0]);
				return 1;
		}
	}

	/* TODO: now that you have the options and arguments,
	 * solve the puzzle. */

	// Makes sure that start and end are not stupid inputs
	if (start == end) {
		printf("Starting and Ending pegs cannot be equal.\n");
		exit(1);
	}
	else if (!(start >= 1 && start <= 3)) {
		printf("Invalid starting peg: %i\n", start);
		exit(1);
	}
	else if (!(end >= 1 && end <= 3)) {
		printf("Invalid ending peg: %i\n", end);
		exit(1);
	}

	// Sets the placeholder peg
	short placeholder = 6 - (start + end);

	// Recursion
	hanoi(n, start, end, placeholder);

	return 0;
}

void hanoi(size_t n, short start, short end, short placeholder) {
	//Base Case: Last Disc should move from its starting starting to the intended peg
	if (n == 1) {
		printf("%i\t%i\n", start, end);
		return;
	}
	//Places n-1 tower to placeholder
	hanoi(n-1, start, placeholder, end);
	printf("%i\t%i\n", start, end);
	//Places rest of the towers back to the ending location
	hanoi(n-1, placeholder, end, start);
}

//I wanted to be fancy and use printf instead of cout
//I'm leaving cout here though just in case
//cout << start << '\t' << end << endl;
//cout << "Starting and Ending pegs cannot be equal" << endl;
//cout << "Inavalid starting peg" << endl;
//cout << "Invalid ending peg" << endl;

//I changed this up to something smarter but I'm still leaving this here
//for (short i = 1; i <= 3; i++)
		//if (i!=start && i!=end)
			//placeholder = i;