/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author       : Ahilan Subbaian
 * Date          : 2/19/2020
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

//two options create dictionary and remove all but the three greatest
//and option to take out the base case and store in dictionary
//or just make the process more efficient

vector<vector<int>> get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
    vector<vector<int>> temp_stairs, simple_stairs;
    vector<int> easy;
    if(num_stairs <= 0){
        temp_stairs.push_back(easy);
        return temp_stairs;
    }
    for(int i = 1; (i < 4) & (i <= num_stairs); i++){
        simple_stairs = get_ways(num_stairs - i);
        for(unsigned int j = 0; j < simple_stairs.size(); j++){
            simple_stairs.at(j).push_back(i);
            temp_stairs.push_back(simple_stairs.at(j));
        }
    }
    return temp_stairs;
}
void print(const vector<int> &ways){
    int a = ways.size();
    for(int i = a - 1; i > 0; i--){
        cout << ways.at(i) << ", ";
    }
    cout << ways.at(0);
}

void display_ways(const vector<vector<int>> &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
    int len = ways.size();
    int digits = 0;
    while(len > 0){
        len = len / 10;
        digits++;
    }
    len = ways.size();
    for(int i = 0; i < len; i++){
        cout << setw(digits) << (i + 1) << ". [";
        print(ways[i]);
        cout << "]";
        if(i != len - 1){
            cout << endl;
        }
    }
}

int main(int argc, char * const argv[]) {
    if(argc != 2){
        cout << "Usage: ./stairclimber <number of stairs>";
        return 0;
    }
    int c;
   // cout << "works" << endl;
    int a = atoi(argv[1]);
    istringstream iss;
    iss.str(argv[1]);
    if(!(iss >> c) | (a <= 0)){
        cerr << "Error: Number of stairs must be a positive integer.";
        return 0;
    }
    vector<vector<int>> ways;
    ways = get_ways(a);
    if(ways.size() == 1){
        cout << ways.size() << " way to climb " << argv[1] << " stair." << endl;
    }
    else{
        cout << ways.size() << " ways to climb " << argv[1] << " stairs." << endl;
    }
    display_ways(ways);
}
