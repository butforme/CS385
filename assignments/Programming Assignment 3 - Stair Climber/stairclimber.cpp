/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Peter Rauscher
 * Date        : 10/2/2020
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

int digits(int x) {
    int y = 1;
    while(x >= 10) {
        x /= 10;
        y++;
    }
    return y;
}

int totalstairs = 0;

vector< vector<int> > get_ways(int num_stairs) {
    vector<vector<int>> waysVect;
    if(!num_stairs) {
        waysVect.push_back(vector<int>());
    } else {
        for(int i = 1; i <= 3; i++){
            if (num_stairs >= i) {
                vector<vector<int>> toPush = get_ways(num_stairs - i);
                for(unsigned int k = 0; k < toPush.size(); k++) {
                    toPush.at(k).push_back(i);
                }
                waysVect.insert(waysVect.end(), toPush.begin(), toPush.end());
            }
        }
    }
    
    return waysVect;
}

void display_ways(const vector< vector<int> > &ways) {
    if(ways.size() == 1) {
		    cout << "1 way to climb 1 stair." <<  endl;
		    cout << "1. [1]" <<  endl;
    } else {
        cout << ways.size() << " ways to climb " << totalstairs << " stairs." << endl;
        for (unsigned int i = 0; i < ways.size(); i++) {
            cout << setw(digits(ways.size())) << i+1 << ". [";
            for (unsigned int k = ways[i].size() - 1; k > 0; k--) {
                cout << ways[i][k] << ", ";
            }
            cout << ways[i][0] << "]" << endl;
	}
    }
    return;
}

int main(int argc, char * const argv[]) {
    int i;
    istringstream ss;
    if(argc != 2) {
        cerr << "Usage: ./stairclimber <number of stairs>" <<  endl;
        return -1;
    } else {
        ss.str(argv[1]);
    }
    
    ss >> i;
    if(i < 0 || !ss) {
        cerr << "Error: Number of stairs must be a positive integer." <<  endl;
        return -1;
    } else {
        totalstairs = i;
        display_ways(get_ways(totalstairs));
    }

    return 0;
}
