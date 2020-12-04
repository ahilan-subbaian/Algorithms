/*******************************************************************************
 * Name        : maxsumdescent.cpp
 * Author      : Ahilan Subbaian
 * Version     : 1.0
 * Date        : 4/27/20
 * Description : Dynamic programming solution to max sum descent problem.
 * Pledge      :I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

const char DELIMITER = ' ';

int **values, // This is your 2D array of values, read from the file.
    **sums;   // This is your 2D array of partial sums, used in DP.

int num_rows; // num_rows tells you how many rows the 2D array has.
              // The first row has 1 column, the second row has 2 columns, and
              // so on...

/**
 * Displays the 2D array of values read from the file in the format of a table.
 */
void display_table() {
    for(int i = 0; i < num_rows; i++){
        for(int j = 0; j < i; j++){
            std::cout << std::setw(2);
            std::cout << values[i][j] << " ";
        }
        std::cout << std::setw(2);
        std::cout << values[i][i] << endl;
    }
    /*
    for(int i = 0; i < num_rows; i++){
        for(int j = 0; j < i; j++){
            std::cout << std::setw(2);
            std::cout << sums[i][j] << " ";
        }
        std::cout << std::setw(2);
        std::cout << sums[i][i] << endl;
    }
     */
}

/**
 * Returns the maximum sum possible in the triangle of values.
 * By starting at the top of the triangle and moving to adjacent numbers on the
 * row below, this function uses dynamic programming to build up another table
 * of partial sums.
 */
int compute_max_sum() {
    // TODO

    // Populate the 2D array of partial sums. It should still work even if
    // num_rows is 0 (i.e. the file was blank).
    if(num_rows == 0)
        return 0;
    sums = new int*[num_rows];
    for(int i = 0; i < num_rows; i++){
        sums[i] = new int[num_rows];
        for(int j = 0; j < num_rows; j++){
            sums[i][j] = 0;
        }
    }
    sums[0][0] = values[0][0];
    for(int i = 1; i < num_rows; i++){
        sums[i][0] = sums[i - 1][0] + values[i][0];
        for(int j = 1; j < i; j++){
            sums[i][j] = max(sums[i - 1][j - 1], sums[i - 1][j]) + values[i][j];
        }
        sums[i][i] = sums[i - 1][i - 1] + values[i][i];
    }
    // Loop over the last row to find the max sum.
    int maxes = 0;
    for(int i = 0; i < num_rows; i++){
        maxes = max(maxes, sums[num_rows - 1][i]);
    }
    // Return the max sum.
    return maxes;
}

/**
 * Returns a vector of ints with the values from the top to the bottom of the
 * triangle that comprise the maximum sum.
 */
vector<int> backtrack_solution() {
    vector<int> solution;
    // TODO
    if(num_rows == 0)
        return solution;
    int maxes = 0;
    int j = 0;
    for(int i = 0; i < num_rows; i++){
        if(sums[num_rows - 1][i] > maxes){
            j = i;
            maxes = sums[num_rows - 1][i];
        }
    }
    int i = num_rows - 1;
    solution.push_back(values[i][j]);
    while(i > 0){
        if(j == 0){
            solution.push_back(values[i - 1][j]);
        }
        else if(j == i){
            solution.push_back(values[i - 1][j - 1]);
            j--;
        }
        else{
            if(sums[i - 1][j - 1] > sums[i - 1][j]){
                solution.push_back(values[i - 1][j - 1]);
                j--;
            }
            else{
                solution.push_back(values[i - 1][j]);
            }
        }
        i--;
    }
    vector<int> one;
    for(int i = (int) solution.size() - 1; i >= 0; i--){
        one.push_back(solution.at(i));
    }
    return one;
}

/**
 * Reads the contents of the file into the global 2D array 'values'. If
 * successful, the function also allocates memory for the 2D array 'sums'.
 */
bool load_values_from_file(const string &filename) {
    ifstream input_file(filename.c_str());
    if (!input_file) {
        cerr << "Error: Cannot open file '" << filename << "'." << endl;
        return false;
    }
    input_file.exceptions(ifstream::badbit);
    string line;
    vector<string> data;
    try {
        while(getline(input_file, line)) {
            data.push_back(line);
        }
        input_file.close();
    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << filename << "'.";
        return false;
    }
    
    // TODO
    num_rows = data.size();
    values = new int*[num_rows];

    for(int i = 0; i < num_rows; i++){
        values[i] = new int[num_rows];
        for(int j = 0; j < num_rows; j++){
            values[i][j] = 0;
        }
    }
    string num;
    int n;
    int j;
    for(int i = 0; i < num_rows; i++){
        num = data.at(i);
        stringstream stream(num);
        j = 0;
        while(stream >> n){
            values[i][j] = n;
            j++;
        }
    }

    return true;
}

/**
 * Frees up the memory allocated for the 2D array of values and the 2D array of
 * partial sums.
 */
void cleanup() {
    // TODO
    for(int i = 0; i < num_rows; i++){
        delete values[i];
        delete sums[i];
    }
    delete values;
    delete sums;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    string filename(argv[1]);
    if (!load_values_from_file(filename)) {
        return 1;
    }
    // TODO
    display_table();
    cout << "Max sum: " << compute_max_sum() << endl;
    vector<int> one = backtrack_solution();
    cout << "Values: [";
    for(int i = 0; i < (int) one.size() - 1; i++){
        cout << one.at(i) << ", ";
    }
    if(one.size() > 0)
        cout << one.at(one.size() - 1);
    cout << "]" << endl;
    one.clear();
    cleanup();
    return 0;
}
