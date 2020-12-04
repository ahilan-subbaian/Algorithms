/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Ahilan Subbaian
 * Date        : 2 / 5 / 2020
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/
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
    
    void max_prime(int max){
        max_prime_ = max;
    }
    
    void add_num_primes(){
        num_primes_++;
    }
    
    void max_prime(){
        for(int i = limit_; i > 1 && max_prime_ == 0; i--){
            if(is_prime_[i]){
                max_prime_ = i;
            }
        }
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) : is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
    num_primes_ = count_num_primes();
    max_prime();
}

void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document.
    const int max_prime_width = num_digits(max_prime_), primes_per_row = 80 / (max_prime_width + 1);
    int counter = 0;
    for(int i = 0; i < num_primes_; i = i){
        cout << endl;
        while(!is_prime_[counter]){
            counter = counter + 1;
        }
        if(limit_ > 104){
            std::cout << std::setw(max_prime_width);
        }
        std::cout << counter;
        i++;
        counter++;
        for(int j = 1; j < primes_per_row && i < num_primes_; j++){
            while(!is_prime_[counter]){
                counter = counter + 1;
            }
            if(limit_ > 104){
                std::cout << std::setw(max_prime_width + 1);
            }
            else {
                std::cout << std::setw(num_digits(counter) + 1);
            }
            std::cout << counter;
            i++;
            counter++;
        }
    }
}

int PrimesSieve::count_num_primes() const {
    // TODO: write code to count the number of primes found
    int numprimes = 0;
    for(int i = limit_; i > 1; i--){
        if(is_prime_[i]){
            numprimes = numprimes + 1;
        }
    }
    return numprimes;
}

void PrimesSieve::sieve() {
    // TODO: write sieve algorithm
    for(int i = 0; i < 2; i++){
        is_prime_[i] = false;
    }
    for(int i = 2; i <= limit_; i++){
        is_prime_[i] = true;
    }
    for(int i = 2; i <= sqrt(limit_); i++){
        for(int j = i * i; j <= limit_; j = j + i){
            is_prime_[j] = false;
        }
    }
}

int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
    int digits = 0;
    while (num > 0) {
        digits++;
        num = num / 10;
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
    
    // TODO: write code that uses your class to produce the desired output.
    cout << endl;
    PrimesSieve one = PrimesSieve(limit);
    cout << "Number of primes found: " << one.num_primes() << endl;
    cout << "Primes up to " << limit << ":";
    one.display_primes();
    return 0;
}
