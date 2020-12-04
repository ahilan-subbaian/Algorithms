/*******************************************************************************
 * Name    : sqrt.cpp
 * Author  : Ahilan Subbaian
 * Version : 1.0
 * Date    : January 31, 2020
 * Description : take the square root using newton method
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/


#include <iostream>
#include <sstream>
#include <iomanip> 
#include <limits>
#include <typeinfo>

using namespace std;

double sqrt2(double a, double b, double c) { 
	if(a < 0) { 
		return numeric_limits<double>::quiet_NaN(); 
	 } 
	if(a == 0) { 
		return 0; 
	 } 
	if(a == 1) { 
		return 1; 
	 } 
	double d = (b + a / b) / 2;
	if(abs(d - b) <= c) { 
		return d; 
	 } 
	return sqrt2(a, d, c); 
 } 

double sqrt(double a, double c) { 
	return sqrt2(a, a, c); 
 } 

int main(int argc, char* argv[]) { 
	istringstream iss;
	if(!(argc > 1)){
		cerr << "Usage: ./sqrt <value> [epsilon]" << endl;
		return 0;
	}
	if(argc > 3){
		cout << "Usage: ./sqrt <value> [epsilon]" << endl;
		return 0;
	}

	double m;
	iss.str(argv[1]);
	if(!(iss >> m)){
		cerr << "Error: Value argument must be a double." << endl;
		return 0;
	}
	iss.clear();
	double result = std::stod(argv[1]);
	if(argc == 2) { 
		std::cout << std::fixed;
		std::cout << std::setprecision(8) << sqrt(result, 1.0 / 10000000) << endl; 
		return 0; 
	 } 
	iss.str(argv[2]);
	if(!(iss >> m)){
		cerr << "Error: Epsilon argument must be a positive double." << endl;
		return 0;
	}

	double result2 = std::stod(argv[2]);
	if(result2 <= 0){
		cout << "Error: Epsilon argument must be a positive double." << endl;
		return 0;
	}
	if(argc == 3) { 
		std::cout << std::fixed;
		std::cout << std::setprecision(8) << sqrt(result, result2) << endl; 
		return 0; 
	 } 
	return 0; 
 }