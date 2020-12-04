/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Ahilan Subbaian
 * Version     : 1.0
 * Date        : 3/29/20
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    // TODO
    long count = 0;
    for(int i = 0; i < length - 1; i++){
        for(int j = i + 1; j < length; j++){
            if(array[i] > array[j])
                count += 1;
        }
    }
    return count;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    // TODO
    // Hint: Use mergesort!
    long count;
    //int *scratch = (int *) malloc(length * sizeof(int));
    int *scratch=new int[length];
    for (int i = 0; i < length; i++) {
        scratch[i] = 0;
    }
    count= mergesort(array, scratch, 0, length - 1);
    delete[] scratch;
    return count;
}

static long mergesort(int array[], int scratch[], int low, int high) {
    // TODO
    int mid, L, H = 0;
    long count=0;
    if (low < high) {
        mid = low + (high - low) / 2;
        count = mergesort(array, scratch, low, mid);
        count += mergesort(array, scratch, mid + 1, high);
        L = low;
        H = mid + 1;
        for (int k = low; k <= high; k++) {
            if (L <= mid && (H > high || array[L] <= array[H])) {
                scratch[k] = array[L];
                L=L+1;
            } else {
                scratch[k] = array[H];
                H=H+1;
                if (L<=mid)
                    count+=mid-L+1;
            }
        }
        for (int k = low; k <= high; k++) {
            array[k] = scratch[k];
        }
    }
    return count;
}

int main(int argc, char *argv[]) {
    // TODO: parse command-line argument
    if ((argc == 2 ) && (strcmp(argv[1], "slow") != 0)){
        cerr << "Error: Unrecognized option '" <<  argv[1] << "'." << endl;
        return 1;
    }
    if ((argc > 2 )){
        cerr << "Usage: " << argv[0] << " [slow]" << endl;
        return 1;
    }
    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    // TODO: produce output
    //checks to see that the inputed sequence is not empty
    if (values.empty()) {
        cerr << "Error: Sequence of integers not received." << endl;
        return 1;
    }
    //checks if the argument count is 2 and then checks to see if the first argument is slow
    if ((argc == 2 ) && (strcmp(argv[1], "slow") == 0)){
            cout << "Number of inversions: " << count_inversions_slow(&values[0], values.size()) << endl;
            return 0;
    //if only one argument inputted, then automatically prints the number of inversions using the fast inversion method
    } else if (argc == 1) {
        cout << "Number of inversions: " << count_inversions_fast(&values[0], values.size()) << endl;
    }
    return 0;
}
