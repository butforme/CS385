/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Peter Rauscher and Joseph Sofia III
 * Date        : 10/19/2020
 * Description : Assignment 4
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <queue>

using namespace std;

// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    string directions;
    State *parent;

    State(int _a, int _b, int _c, string _directions) :
        a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} { }

    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

string bfs(int a, int b, int c) {
	queue<State> q;
	State goal = State(a, b, c, "Initial state.");
	q.push(goal);
	while(!q.empty()){
		State curr = q.front();
		
	}
	return "No solution.";
}

int main(int argc, char * const argv[]) {

	if(argc != 7) {
		cout << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
		return 0;
	}

	int cap[3]; //convert the arguments to ints
	//cap[0] = capacity of A and so on
	int goal[3];
	//goal[0] = goal for A and so on

	for (int i=1; i < 4; i++){
		istringstream iss;
		iss.str(argv[i]);
		if ( !(iss >> cap[i-1]) or cap[i-1] <= 0 ) {
			cout << "Error: Invalid capacity '" << argv[i] << "' for jug " << char(65 + i-1) << ".";

			return 0;
		}
	}
	for (int i=1; i<4; i++) {
		istringstream iss;
		iss.str(argv[i+3]);
		if ( !(iss >> goal[i-1]) or goal[i-1] < 0 ) {
			cout << "Error: Invalid goal '" << argv[i+3] << "' for jug " << char(65 + i-1) << ".";
			return 0;
		}
	}
	for (int i=1; i<4; i++){
		if (goal[i-1] > cap[i-1]) {
			cout << "Error: Goal cannot exceed capacity of jug " << char(65 + i-1) << ".";
			return 0;
		}
	}
	if ((goal[0] + goal[1] + goal[2]) != cap[2]){
		cout << "Error: Total gallons in goal state must be equal to the capacity of jug C.";
	}

    return 1;
}