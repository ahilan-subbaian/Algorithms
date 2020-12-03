/*******************************************************************************
* Name        : anagramfinder.cpp
* Author      : Ahilan Subbaian
* Version     : 1.0
* Date        : 4/27/20
* Description : anagram time.
* Pledge      :I pledge my honor that I have abided by the Stevens Honor System.
******************************************************************************/

//
//  finalproject.cpp
//
//
//  Created by Ahilan Subbaian on 5/4/20.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <unordered_map>
#include <unordered_set>
#include <array>

std::vector<std::string> data;
std::vector<std::vector<std::string*>> anagrams;
std::vector<int> stringLength;

std::unordered_map<int, std::vector<std::string*>> wordOne;
std::unordered_map<int, std::vector<std::string*>> words;
std::unordered_map<std::string, std::vector<std::string*>> sortedStrings;

void populateWordOne(){
    int len;
    for(size_t i = 0; i < data.size(); i++){
        len = data.at(i).size();
        if(wordOne.find(len) == wordOne.end()){
//            wordOne.emplace(len, vector<int>{i});
            wordOne.emplace(len, std::vector<std::string*>{&data.at(i)});
            stringLength.push_back(len);
        }
        else{
//            wordOne[len].push_back(i);
            wordOne[len].push_back(&data.at(i));
        }
    }
    std::sort(stringLength.begin(), stringLength.end(), std::greater<int>());
}

bool cmpStrPtrs(std::string *a, std::string *b) {
    return *a < *b;
}

int myhash(char* x){
    if((*x) > 64){
        if((*x) > 96){
            if((*x) < 123)
                return (*x) - 97;
            else
                return - 1;
        }//remove special characters
        else if((*x) < 91){
            return (*x) - 65;
        }
        else{
            return -1;
        }
    }
    else if((*x) == 45)
        return 26;
    else if((*x) == 39){
        return 27;
    }
    return -1;
}

template<typename T, size_t N>
struct std::hash<std::array<T, N> >
{
    typedef std::array<T, N> argument_type;
    typedef size_t result_type;

    result_type operator()(const argument_type& a) const
    {
        std::hash<T> hasher;
        result_type h = 0;
        for (result_type i = 0; i < N; ++i)
        {
            h = h * 55 + hasher(a[i]);
        }
        return h;
    }
};

bool stringToMap(int length){
    std::unordered_map<std::array<int, 28>, std::vector<std::string*>> count2;
    std::unordered_set<std::array<int, 28>> count3;
    int x;
    int len;
    for(size_t i = 0; i < wordOne[length].size(); i++){
//        basic_string count = "0000000000000000000000000000";  //figure out heap or stack
        std::array<int, 28> count = std::array<int, 28>();
        for(size_t j  = 0; j < wordOne[length].at(i)->size(); j++){
            x = myhash(&wordOne[length].at(i)->at(j));
//            *(count + x) = *(count + x) + 1; //this way
            if(x == -1){
                continue;
            }
            count.at(x)++;
        }
        if(count2.find(count) == count2.end()){
            count2.emplace(count, std::vector<std::string*>{wordOne[length].at(i)});
        }
        else{
            count3.emplace(count);
            count2[count].push_back(wordOne[length].at(i)); //put the string at the proper location
        }
    }
    
    for(std::unordered_set<std::array<int, 28>>::iterator itr = count3.begin(); itr != count3.end(); ++itr){
        len = anagrams.size();
        anagrams.push_back(count2.at(*itr));
        std::sort(anagrams.at(len).begin(), anagrams.at(len).end(), cmpStrPtrs);
    }
    count2.clear();
    return anagrams.size() > 0;
}

void print_answer(){
    populateWordOne();
    bool check = false;
    size_t i;
    for(i = 0; i < stringLength.size(); i++){
        check = stringToMap(stringLength.at(i));
        if(check){
            break;
        }
    }
    if(!check){
        std::cout << "No anagrams found." << std::endl;
        return;
    }
    std::sort(anagrams.begin(), anagrams.end(), [](const std::vector<std::string*>& i, const std::vector<std::string*>& j) {return (*(i.at(0))) < (*(j.at(0))); });
    std::cout << "Max anagram length: " << stringLength.at(i) << std::endl;
    for(i = 0; i < anagrams.size(); i++){
        for(size_t j = 0; j < anagrams.at(i).size(); j++){
            std::cout << (*anagrams.at(i).at(j)) << std::endl;
        }
        if(i != anagrams.size() - 1)
            std::cout << std::endl;
    }
//    copy(anagrams.begin(), anagrams.end(), std::ostream_iterator<char>(std::cout, " "))
//    anagrams.clear();
//    data.clear();
//    stringLength.clear();
//    wordOne.clear();
//    sortedStrings.clear();
}

bool load_values_from_file(const std::string &filename) {
    std::ifstream input_file(filename.c_str());
    if(!input_file){
        std::cerr << "Error: File '" << filename << "' not found." << std::endl;
        return false;
    }
    input_file.exceptions(std::ifstream::badbit);
    std::string line;
    try {
        while(getline(input_file, line)) {
            data.push_back(line); //each line becomes string
        }
        input_file.close();
    } catch (const std::ifstream::failure &f) {
        std::cerr << "Error: An I/O error occurred reading '" << filename << "'.";
        return false;
    }
    return true;
}

int main(int argc, char * const argv[]) {
    if(argc != 2){
        std::cout << "Usage: ./anagramfinder <dictionary file>" << std::endl;
        return 0;
    }
    std::string filename(argv[1]);
    if (!load_values_from_file(filename)){
        return 1;
    }
    print_answer();
}
