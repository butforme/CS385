 /*******************************************************************************
 * Name        : unique.cpp
 * Author      : Peter Rauscher
 * Date        : 9/25/20
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    for(unsigned int i = 0; i < s.size(); i++) {
        if(islower(s[i])) {
            continue;
        } else {
            return false;
        }
    }
    return true;
}

bool all_unique_letters(const string &s) {
    unsigned int vector = 0;
    for(unsigned int i = 0; i < s.length(); i++) {
        int index = s[i] - 'a';
        unsigned int setter = 1 << index;
        if ((vector & setter) == 0) {
            vector = vector | setter;
            continue;
        } else {
            return false;
        }
    }
    return true;
}

int main(int argc, char * const argv[]) {
    if(argc != 2) {
        cout << "Usage: ./unique <string>" << endl;
        return 0;
    }
    string s = argv[1];
    if(!is_all_lowercase(s)) {
        cout << "Error: String must contain only lowercase letters." << endl;
        return 0;
    } else {
        if(all_unique_letters(s)){
            cout << "All letters are unique." << endl;
        } else {
            cout << "Duplicate letters found." << endl;
        }
    }
}
