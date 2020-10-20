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
#include <string>

using namespace std;

//Globals
int cap[3]; //convert the arguments to ints
//cap[0] = capacity of A and so on
int goal[3];
//goal[0] = goal for A and so on
bool hasSolution = false;
const int A = 0;
const int B = 1;
const int C = 2;

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
	State initial = State(a, b, c, "");
	initial.directions = "Initial state. " + initial.to_string() + "\n";
	q.push(initial); //add new State(a, b, c) to queue
	int rows = cap[0]+1;
	int cols = cap[1]+1;
	bool** visited = new bool*[rows]; //create matrix with capA rows
	for(int i = 0; i < rows; i++) { //create rows with capB columns
    	visited[i] = new bool[cols];
	}
	for(int i=0; i < rows; i++) //fill visited matrix with false
	{
    	for(int j=0; j < cols; j++)
    	{
        	visited[i][j] = false;
    	}
	}
	while(!q.empty()){ //while (queue is not empty)
		State curr = q.front(); //current <- front of queue
		q.pop(); //pop from the queue
		if(curr.a == goal[A] && curr.b == goal[B] && curr.c == goal[C]) { //if current equals goal_state
			return curr.directions; //return backtracked solution
		}
		if(visited[curr.a][curr.b]) { //if current has already been seen
			continue;
		}
		visited[curr.a][curr.b] = true; //mark current as having been visited
		//WIP try the 6 ways to pour water, pushing new States to the queue
		// 1) Pour from C to A
		if(curr.c != 0 && curr.a < cap[A]) {
			State afterPour = State(0, 0, 0, "");
			//B is same (within bounds)
			afterPour.b = curr.b < 0 ? 0 : curr.b;
			afterPour.b = afterPour.b > cap[B] ? cap[B] : afterPour.b;
			//set A
			afterPour.a = curr.a + curr.c;
			afterPour.a = afterPour.a > cap[A] ? cap[A] : afterPour.a;
			//set C
			afterPour.c = curr.c - (afterPour.a - curr.a);
			afterPour.c = afterPour.c < 0 ? 0 : afterPour.c;
			afterPour.c = afterPour.c > cap[C] ? cap[C] : afterPour.c;

			stringstream ss;
			int gallonsPoured = afterPour.a-curr.a;
			ss<<gallonsPoured;
			string gallonOrGallons = gallonsPoured > 1 ? " gallons" : " gallon";
			if(!visited[afterPour.a][afterPour.b]) {
				afterPour.directions = curr.directions + "Pour " + ss.str() + gallonOrGallons + " from C to A. " + afterPour.to_string() + "\n";
				q.push(afterPour);
			}
		}
		// 2) Pour from B to A
		if(curr.b != 0 && curr.a < cap[A]) {
			State afterPour = State(0, 0, 0, "");
			//C is same (within bounds)
			afterPour.c = curr.c < 0 ? 0 : curr.c;
			afterPour.c = afterPour.c > cap[C] ? cap[C] : afterPour.c;
			//set A
			afterPour.a = curr.a + curr.b;
			afterPour.a = afterPour.a > cap[A] ? cap[A] : afterPour.a;
			//set B
			afterPour.b = curr.b - (afterPour.a - curr.a);
			afterPour.b = afterPour.b < 0 ? 0 : afterPour.b;
			afterPour.b = afterPour.b > cap[B] ? cap[B] : afterPour.b;

			stringstream ss;
			int gallonsPoured = curr.b-afterPour.b;
			ss<<gallonsPoured;
			string gallonOrGallons = gallonsPoured > 1 ? " gallons" : " gallon";
			if(!visited[afterPour.a][afterPour.b]) {
				afterPour.directions = curr.directions + "Pour " + ss.str() + gallonOrGallons + " from B to A. " + afterPour.to_string() + "\n";
				q.push(afterPour);
			}
		}
		// 3) Pour from C to B
		if(curr.c != 0 && curr.b < cap[B]) {
			State afterPour = State(0, 0, 0, "");
			//A is same (within bounds)
			afterPour.a = curr.a < 0 ? 0 : curr.a;
			afterPour.a = afterPour.a > cap[A] ? cap[A] : afterPour.a;
			//set B
			afterPour.b = curr.b + curr.c;
			afterPour.b = afterPour.b > cap[B] ? cap[B] : afterPour.b;
			//set C
			afterPour.c = curr.c - (afterPour.b - curr.b);
			afterPour.c = afterPour.c < 0 ? 0 : afterPour.c;
			afterPour.c = afterPour.c > cap[C] ? cap[C] : afterPour.c;

			stringstream ss;
			int gallonsPoured = afterPour.b-curr.b;
			ss<<gallonsPoured;
			string gallonOrGallons = gallonsPoured > 1 ? " gallons" : " gallon";
			if(!visited[afterPour.a][afterPour.b]) {
				afterPour.directions = curr.directions +  "Pour " + ss.str() + gallonOrGallons + " from C to B. " + afterPour.to_string() + "\n";
				q.push(afterPour);
			}
		}
		// 4) Pour from A to B
		if(curr.a != 0 && curr.b < cap[B]) {
			State afterPour = State(0, 0, 0, "");
			//C is same (within bounds)
			afterPour.c = curr.c < 0 ? 0 : curr.c;
			afterPour.c = afterPour.c > cap[C] ? cap[C] : afterPour.c;
			//set B
			afterPour.b = curr.a + curr.b;
			afterPour.b = afterPour.b > cap[B] ? cap[B] : afterPour.b;
			//set A
			afterPour.a = curr.a - (afterPour.b - curr.b);
			afterPour.a = afterPour.a < 0 ? 0 : afterPour.a;
			afterPour.a = afterPour.a > cap[A] ? cap[A] : afterPour.a;

			stringstream ss;
			int gallonsPoured = afterPour.b-curr.b;
			ss<<gallonsPoured;
			string gallonOrGallons = gallonsPoured > 1 ? " gallons" : " gallon";
			if(!visited[afterPour.a][afterPour.b]) {
				afterPour.directions = curr.directions +  "Pour " + ss.str() + gallonOrGallons + " from A to B. " + afterPour.to_string() + "\n";
				q.push(afterPour);
			}
		}
		// 5) Pour from B to C
		if(curr.b != 0 && curr.a+curr.b < cap[C]) {
			State afterPour = State(0, 0, 0, "");
			//A is same (within bounds)
			afterPour.a = curr.a < 0 ? 0 : curr.a;
			afterPour.a = afterPour.a > cap[A] ? cap[A] : afterPour.a;
			//set C
			afterPour.c = curr.c + curr.b;
			afterPour.c = afterPour.c > cap[C] ? cap[C] : afterPour.c;
			//set B
			afterPour.b = curr.c - afterPour.c;
			afterPour.b = afterPour.b > cap[B] ? cap[B] : afterPour.b;
			afterPour.b = afterPour.b < 0 ? 0 : afterPour.b;

			stringstream ss;
			int gallonsPoured = curr.b-afterPour.b;
			ss<<gallonsPoured;
			string gallonOrGallons = gallonsPoured > 1 ? " gallons" : " gallon";
			if(!visited[afterPour.a][afterPour.b]) {
				afterPour.directions = curr.directions +  "Pour " + ss.str() + gallonOrGallons + " from B to C. " + afterPour.to_string() + "\n";
				q.push(afterPour);
			}
		}
		// 6) Pour from A to C
		if(curr.a != 0 && curr.a+curr.b < cap[C]) {
			State afterPour = State(0, 0, 0, "");
			//B is same (within bounds)
			afterPour.b = curr.b < 0 ? 0 : curr.b;
			afterPour.b = afterPour.b > cap[B] ? cap[B] : afterPour.b;
			//set C
			afterPour.c = curr.c + curr.a;
			afterPour.c = afterPour.c > cap[C] ? cap[C] : afterPour.c;
			//set A
			afterPour.a = curr.a - (afterPour.c - curr.c);
			afterPour.a = afterPour.a < 0 ? 0 : afterPour.a;
			afterPour.a = afterPour.a > cap[A] ? cap[A] : afterPour.a;

			stringstream ss;
			int gallonsPoured = curr.a-afterPour.a;
			ss<<gallonsPoured;
			string gallonOrGallons = gallonsPoured > 1 ? " gallons" : " gallon";
			if(!visited[afterPour.a][afterPour.b]) {
				afterPour.directions = curr.directions +  "Pour " + ss.str() + gallonOrGallons + " from A to C. " + afterPour.to_string() + "\n";
				q.push(afterPour);
			}
		}
	}
	//frees up memory from each row
	for(int i=0; i < rows; i++){
		delete visited[i];
	}
	//frees up memory from visited matrix
	delete [] visited;

	return "No solution."; //return "no solution"
}

int main(int argc, char * const argv[]) {

	if(argc != 7) {
		cout << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
		return 0;
	}

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
		return 0;
	}
	
	// for(int i = 0; i < 6; i++){
	// 	stringstream capI(argv[i]);
	// 	stringstream goalI(argv[i+3]);
	// 	capI >> cap[i];
	// 	goalI >> goal[i];
	// }

	cout << bfs(0, 0, cap[C]);

    return 1;
}