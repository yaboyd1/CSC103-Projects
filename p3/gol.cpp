/*
 * CSc103 Project 3: Game of Life
 * References:
 * readme.html
 * Ash, Azwad, Kyle, Matt, Ahmad
 * Finally, please indicate approximately how many hours you spent on this:
 * #hours: 13
 */

#include <cstdio>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <vector>
using std::vector;
#include <string>
using std::string;
#include <iostream>
using std::cout;
using std::endl;

static const char* usage =
"Usage: %s [OPTIONS]...\n"
"Text-based version of Conway's game of life.\n\n"
"   --seed,-s     FILE     read start state from FILE.\n"
"   --world,-w    FILE     store current world in FILE.\n"
"   --fast-fw,-f  NUM      evolve system for NUM generations and quit.\n"
"   --help,-h              show this message and exit.\n";

size_t max_gen = 0; //If >0, fast forward
string wfilename =  "/tmp/gol-world-current"; //File name
FILE* fworld = 0; //File itself
string initfilename = "/tmp/gol-world-current"; //Initial state from file
vector<vector<bool> > world; //Board
char state[4] = ".O\n"; //Possible states for rewriteStates

void mainLoop(bool rewrite); //Main loop
int countAlive(int i, int j, const vector<vector<bool> > V); //Counts alive neighbors
void updateBoard(); //Updates the board once
void gen(int input, bool rewrite, int time = 0); //Prints or rewrites the board at the nth generation
void rewriteORprint(bool rewrite); //Prints to stdin or rewrites to given file
void initializeFromFile(string fname); //Initiliazes the board from a file
void rewriteStates(FILE* f); //Rewrites board states into a file

/* Functions that aren't used but I would feel bad deleting them:
void printBoard(const vector<vector<bool> > V); //Prints board to stdin
void storeInFile(string fname); //Stores board into a file
*/

int main(int argc, char *argv[]) {
	static struct option long_opts[] = {
		{"seed",    required_argument, 0, 's'},
		{"world",   required_argument, 0, 'w'},
		{"fast-fw", required_argument, 0, 'f'},
		{"help",    no_argument,       0, 'h'},
		{0,0,0,0}
	};
	char c;
	int opt_index = 0;
	while ((c = getopt_long(argc, argv, "hs:w:f:", long_opts, &opt_index)) != -1) {
		switch (c) {
			case 'h':
				printf(usage,argv[0]);
				return 0;
			case 's':
				initfilename = optarg;
				break;
			case 'w':
				wfilename = optarg;
				break;
			case 'f':
				max_gen = atoi(optarg);
				break;
			case '?':
				printf(usage,argv[0]);
				return 1;
		}
	}

	//Not used but good for debugging
	//printf("input file:  %s\n",initfilename.c_str());
	//printf("output file: %s\n",wfilename.c_str());
	//printf("fast forward to generation: %lu\n",max_gen);

	if (!(initfilename == "-")) {
		initializeFromFile(initfilename);
	}

	//Opens a file
	bool rewrite = false;
	if (!(wfilename == "-")) {
		rewrite = true;
		fworld = fopen(wfilename.c_str(), "wb");
		if (!fworld) {
			exit(1);
		}
	}

	//Rewrites file
	mainLoop(rewrite);

	//Closes file
	if (rewrite) {
		fclose(fworld);
	}
	return 0;
}

void mainLoop(bool rewrite) {
	//Plays game of life
	if (max_gen == 0) {
		while(true) {
			gen(1, rewrite, 1);
		}
	} else {
		gen(max_gen, rewrite);
	}
}

int countAlive(int i, int j, const vector<vector<bool> > V) {
	//Counts the number of alive neighbors
	int alive = 0;
	int n = V.size();
	int m = V[0].size();
	for (int a = -1; a <= 1; a++) {
		for (int b = -1; b <= 1; b++) {
			//Count alive in a 3x3, wraps around
			if (V[(i+a+n)%n][(j+b+m)%m] == 1) {
				alive++;
			}
		}
	}
	//Exclude if alive
	if (V[i][j] == 1) {
		alive--;
	}
	return alive;
}

void updateBoard() {
	//Updates the world
	vector<vector<bool> > newWorld = world;
	int n = world.size();
	int m = world[0].size();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			//Count alive neighbors
			int alive = countAlive(i, j, world);
			//Apply game of life rules
			if (world[i][j] == 1 && (alive < 2 || alive > 3)) {
				newWorld[i][j] = 0;
			} else if (world[i][j] == 0 && alive == 3){
				newWorld[i][j] = 1;
			}
		}
	}
	world = newWorld;
}

void gen(int input, bool rewrite, int time) {
	//Prints or rewrites the nth generation of initial board
	for (int i = 0; i < input; i++) {
		updateBoard();
	}
	sleep(time);
	rewriteORprint(rewrite);
}

void rewriteORprint(bool rewrite) {
	//Prints to stdin or rewrites to another file
	if (rewrite) {
		rewriteStates(fworld);
	} else {
		rewriteStates(stdout);
	}
}

void initializeFromFile(string fname) {
	//Initializes board from a file
	FILE* f = fopen(fname.c_str(),"rb");
	if (!f) {
		exit(1);
	}
	//Reinitialiaze world
	world.clear();
	world.push_back(vector<bool>());
	size_t rows = 0;
	//Read character by character and input into world
	char c;
	while (fread(&c,1,1,f)) {
    if (c == '\n') {
        rows++;
        world.push_back(vector<bool>());
    } else if (c == '.') {
        world[rows].push_back(false);
    } else {
        world[rows].push_back(true);
    }
	}
	fclose(f);
	//Remove last row (if empty?) I didn't even bother to check if it was empty but it works so...
	world.pop_back();
}

void rewriteStates(FILE* f) {
	//Rewrites current board into a file
	rewind(f);
	for (size_t i = 0; i < world.size(); i++) {
		for (size_t j = 0; j < world[0].size(); j++) {
			if (world[i][j] == 1) {
				fwrite(&state[1],1,1,f);
			} else if (world[i][j] == 0) {
				fwrite(&state[0],1,1,f);
			}
		}
		fwrite(&state[2],1,1,f);
	}
}

/* Functions used to test:
void printBoard(const vector<vector<bool> > V) {
	//Prints the board to stdin
	for (size_t i = 0; i < V.size(); i++) {
		for (size_t j = 0; j < V[i].size(); j++) {
			if (V[i][j] == 1) {
				cout << "O";
			} else {
				cout << ".";
			}
		}
		cout << "\n";
	}
}

void storeInFile(string fname) {
	//Stores current board into a file
	FILE* f = fopen(fname.c_str(), "wb");
	if (!f) {
		exit(1);
	}
	rewriteStates(f);
	fclose(f);
}
*/