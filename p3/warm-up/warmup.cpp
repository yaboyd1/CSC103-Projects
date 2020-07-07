#include <vector>
using std::vector;
#include <iostream>
using std::cout;
using std::endl;
#include <stdio.h>

/* NOTE: the vector 'world' above corresponds to the contents
	 * of ../res/tests/0.  TODO: apply the rules to the vector,
	 * write the result to standard output, and compare with the
	 * contents of ../tests/1. */

void printBoard(const vector<vector<bool> > V);
int countAlive(int i, int j, const vector<vector<bool> > V);
void updateBoard();
void gen(int input);

vector<vector<bool> > world = {
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

int n = world.size();
int m = world[0].size();

int main(int argc, char** argv)
{

	//Use second argument as gen parameter
	if (argc == 2) {
		gen(atoi(argv[1]));
	} else {
		//If not given any, just print the first gen
		gen(1);
	}

	return 0;
}

void printBoard(const vector<vector<bool> > V) {
	//Prints the board
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

int countAlive(int i, int j, const vector<vector<bool> > V) {
	//Counts the number of alive neighbors
	int alive = 0;
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
	//Update the world
	vector<vector<bool> > newWorld = world;
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

void gen(int input) {
	//Prints the nth generation of initial world
	for (int i = 0; i < input; i++) {
		updateBoard();
	}
	printBoard(world);
}