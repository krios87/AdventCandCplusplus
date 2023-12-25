//============================================================================
// Name        : 2020_day2.cpp
// Author      : Kristofer
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <cctype>

using namespace std;


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

#define PART2

int main() {
	ifstream inFile;

	inFile.open("../../../Advent/2020_day2.txt");

	string str;

	int CountCorrect= 0;
	vector<int> numbers;
	if(inFile.fail())
		cout << endl << "File not found!" << endl;
	else{  //the file has first row a name
		while(!inFile.eof()){ //until end of file
			getline(inFile,str,'-');
			int minsize = stoi(str);
			getline(inFile,str,' ');
			int maxsize = stoi(str);
			getline(inFile,str,' ');
			char searchCH = str[0];
			getline(inFile,str);

#ifndef PART2
			int countchar = 0;
			for(auto &x : str){
				countchar += x==searchCH;
			}

			CountCorrect += (countchar>=minsize) && (countchar <= maxsize);





#else
		CountCorrect += ((str.at(minsize-1) == searchCH) && (str.at(maxsize-1) != searchCH))
				|| ((str.at(maxsize-1) == searchCH) && (str.at(minsize-1) != searchCH)) ;  //exactly the character at pos minsize or maxsize

		}
#endif
		inFile.close();
	}

	cout << "correct: " << CountCorrect << endl;

	return 0;
}
