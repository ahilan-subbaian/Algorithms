/*******************************************************************************
 * Name       : unique.cpp
 * Author      :  Ahilan Subbaian
 * Date         :  2/17/2020
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>
#include <string>

using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
    int j = (int) s.length();
    for(int i = 0; i < j; i++)
        if((s[i] < 97) | (s[i] > 122)){
            return false;
        }
    return true;
}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.
    // You may use only a single int for storage and work with bitwise
    // and bitshifting operators.
    // No credit will be given for other solutions.
    int bit = 0;
    int j = (int) s.length();
    for(int i = 0; i < j; i++){
        int temp = 1;
        temp = temp << (s[i] - 'a');
        if((temp & bit) != 0){
            return false;
        }
        else{
            bit = temp | bit;
        }
    }
    return true;
}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.
    if(argc != 2)
    {
        cerr << "Usage: ./unique <string>" << endl;
    }
    else if(!is_all_lowercase(argv[1])){
        cerr << "Error: String must contain only lowercase letters." << endl;
    }
    else if(!all_unique_letters(argv[1])){
        cout << "Duplicate letters found." << endl;
    }
    else{
        cout << "All letters are unique." << endl;
    }
}
