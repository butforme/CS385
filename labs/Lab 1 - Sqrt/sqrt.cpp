/*******************************************************************************
 * Name    : sqrt.cpp
 * Author  : Peter Rauscher
 * Version : 1.0
 * Date    : 09/03/2020
 * Description : Uses newtons method to find sqrt of a double.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <exception>
#include <ios>
#include <iostream>
#include <limits>
#include <iomanip>

using namespace std;

double sqrt(double, double = 1.0e-7);

double sqrt(double num, double epsilon) {
  if (num < 0) {
    return numeric_limits<double>::quiet_NaN();
  } else if (num == 0 || num == 1) {
    return num;
  }
  double last_guess = num;
  double next_guess = (last_guess + (num / last_guess)) / 2;
  while (abs(last_guess - next_guess) > epsilon) {
    last_guess = next_guess;
    next_guess = (last_guess + (num / last_guess)) / 2;
    //cout << next_guess << endl; //shows every computation, for testing only.
  }
  return next_guess;
}

int main(int argc, char *argv[]) {
    
    double eps = 1.0e-7;
    double val;
    
    if(argc < 2 || argc > 3) {
        cerr << "Usage: " << argv[0] << " <value> [epsilon]" << endl;
        return 1;
    }

    try {
        val = stod(argv[1]);
    } catch (exception& e) {
        cerr << "Error: Value argument must be a double." << endl;
        return 1;
    }
    
    if(argc == 3) {
        try {
            eps = stod(argv[2]);
        } catch (exception& e) {
            cerr << "Error: Epsilon argument must be a positive double." << endl;
            return 1;
        }
        if(eps <= 0) {
            cerr << "Error: Epsilon argument must be a positive double." << endl;
            return 1;
        }
    }
    cout << setprecision(8) << fixed << sqrt(val, eps) << endl;
    return 0;
}
