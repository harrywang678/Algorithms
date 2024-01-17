/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Harry Wang
 * Date        : 9/18/2023
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve { // PrimesSieve Class
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit):
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document.

    const int max_prime_width = num_digits(max_prime_), // max_prime_width is the number of digits the max prime
        primes_per_row = (80 /(max_prime_width + 1));  // how many prime numbers (max) should be on one line 

    cout << endl;
    cout << "Number of primes found: " << num_primes_ << endl; 
    cout << "Primes up to " << limit_ << ":" << endl;
    
    if (max_prime_width > 2){ 
        cout << right << setw(max_prime_width);
    }

    int spaces = -1; // spaces determines if its multi-line or single line, if spaces > 80, then we will do multi lines, else then just use single lines. Start with -1 because the space at the end is not included.

    for (int i = 2; i <= limit_; i++){ // iterate through the array and every time there is a prime number, count the digit of that number plus one space,
        if (is_prime_[i] == true){
            spaces += num_digits(i) + 1;
        }
    }

    if (spaces <= 80) { // if all the primes can fit onto one line, then just print out the number with one space. 
        for (int  i = 2; i <= limit_; i++){
            if (is_prime_[i] == true){
                if(i == max_prime_){ // the last prime would just print out and not have space. 
                    cout << i;
                }
                else{
                    cout << i << " ";
                }
            }
        }
    }
    else {
        int primes = 2; 
        for (int i = 2; i <= limit_; i++){
            if (is_prime_[i] == true){
                if (primes <= primes_per_row){ // if primes is less than the primes_per_row just continue printing on the same line.
                    cout << i << right << setw(max_prime_width + 1);
                    primes++;
                }

                else{ // if primes is more than primes per row then endl.
                    primes = 2; 
                    cout << i << right << setw(max_prime_width);
                    cout << endl; 
                    
                }

            }
        }
    }
}

void PrimesSieve::sieve() {
    // TODO: write sieve algorithm
    // All instance variables must be initialized by the end of this method.
    for (int i = 0; i <= limit_; i++){ // Initialize the whole array with true..
        is_prime_[i] = true;
    }
    
    for (int j = 2; j <= sqrt(limit_); j++){  // Will make every non-prime numbers into false and remain all prime numbers with true.
        if (is_prime_[0] == true){
            for (int k = j*j; k <= limit_;k += j){
                is_prime_[k] = false;
            }
        }
    }
    num_primes_ = 0; 
    for (int i = 2; i <= limit_; i++){ // Iterate through the array and every time there is a true, num_primes_ will increase by 1.
        if (is_prime_[i] == true){
            num_primes_ += 1;
        }
    }

    for (int i = limit_; i >= 0; i--){ // Iterate through the array from the end and the first true it finds is the max_prime_.
        if (is_prime_[i] == true){
            max_prime_ = i;
            break;
        }
    }
}
int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
    int x = 1; 
    while (num >= 10){ 
        num = num/10;
        x += 1;
    }
    return x;
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


    // TODO: write code that uses your class to produce the desired output.
    
    
    PrimesSieve* x = new PrimesSieve(limit);

    x->display_primes();
    
    delete x;

    

    return 0;
}
