/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Peter Rauscher
 * Date        : 9/11/2020
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;
    int max_prime_width;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

//Constructor implementation
PrimesSieve::PrimesSieve(int limit) : is_prime_(new bool[1 + limit]), limit_(limit) {
        fill_n(is_prime_, limit+1, true);
        sieve();
        num_primes_ = count_num_primes();
}

void PrimesSieve::display_primes() const {
    const int max_prime_width = num_digits(max_prime_),
        primes_per_row = 80 / (max_prime_width + 1);

    cout << endl;
    cout << "Number of primes found: " << num_primes_ << endl;
    cout << "Primes up to " << limit_ << ":" << endl;

    if(num_primes_ <= primes_per_row) {
        //1 row of primes
        for(int i = 2; i <= limit_; i++) {
            if(is_prime_[i]) {
                cout << i;
                if(i != max_prime_) {
                    cout << " ";
                }
            }
        }
    } else {
        //more than 1 row
        int counter = 1;
        for(int i = 2 ; i <= limit_; i++) {
            if(is_prime_[i]) {
                if(counter == primes_per_row) {
                    cout << setw(max_prime_width) << i << endl;
                    counter = 1;
                } else {
                    cout << setw(max_prime_width) << i;
                    if (i != max_prime_) {
                        cout << " ";
                    }
                    counter++;
                }
            }
        }
    }
}

int PrimesSieve::count_num_primes() const {
    int total = 0;
    for(int i = 2; i <= limit_ ; i++) {
        if(is_prime_[i]){
            total++;
        }
    }
    return total;
}

void PrimesSieve::sieve() {
    for(int i = 2; i <= limit_; i++) {
        if(is_prime_[i]) {
            for (int j = pow(i, 2); j<=limit_; j = j + i) {
                is_prime_[j] = false;
            }
        }
    }
    for(int i = limit_; i >= 2; i--) {
        if(is_prime_[i]) {
            max_prime_ = i;
            return;
        }
    }
}

int PrimesSieve::num_digits(int num) {
    int digits = 0;
    int i = num;
    while (i != 0) {
        i = i / 10;
        digits++;
    }
    return digits;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    PrimesSieve sieve(limit);
    sieve.display_primes();
    return 0;
}
