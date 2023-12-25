//============================================================================
// Name        : 2020_day1.cpp
// Author      : Kristofer
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#include <fstream>

using namespace std;

template <typename T>
vector<pair<T,size_t>> find_most_frequent(vector<T> const & range){

	map<T,size_t> counts;
	for(auto &e : range){
		counts[e]++; //e value key is incremented by one, not existing it is added.
	}

	auto maxelement = max_element(begin(counts),end(counts),
			[](auto const & el, auto const & e2){
		return el.second < e2.second;
	});

	vector<pair<T,size_t>> result;

	copy_if(begin(counts),end(counts), back_inserter(result),
			[maxelement](auto const &kvp) {
		return kvp.second == maxelement->second;
	});

	return result;

}

unsigned long getmult(vector<int>& array){
	for(auto &x: array){
		for(auto &y : array){
			for(auto &z : array){
				if(y != x && x != z){
					if((x+y+z)==2020){
						return x*y*z;
					}
				}
			}
		}
	}
	return 0;
}
int main() {

	auto range = vector<int>{1,1,3,5,5,8,13,3,5,8,8,5};
	auto result = find_most_frequent(range);

	for(auto const & e : result){
		cout << e.first << " : " << e.second << endl;
	}


	ifstream inFile;

	inFile.open("C:/Users/Kristofer Rosquist/Desktop/HoT/Training/Advent/2020_day1.txt");

	string str;

	vector<int> numbers;
	if(inFile.fail())
		cout << endl << "File not found!" << endl;
	else{  //the file has first row a name
		while(!inFile.eof()){ //until end of file
			getline(inFile,str);
			numbers.push_back(stoi(str));
		}
		inFile.close();
	}


	cout << "mult: " << getmult(numbers);

	return 0;
}
