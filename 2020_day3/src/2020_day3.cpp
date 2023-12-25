//============================================================================
// Name        : 2020_day3.cpp
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
#include <map>
#include <algorithm>

#include <regex>

using namespace std;

//#define DEBUGGING

template <typename T>
T myfunc(T &value, T &value2){

	return value + value + value2;
}

string eyecolours[] = {"amb", "blu", "brn" , "gry" ,"grn" ,"hzl" ,"oth"};

bool IsValidpassport(map<string,string>& passport){

	int byr = stoi(passport["byr"]);
	if(byr < 1920 || byr > 2002){
#ifdef DEBUGGING
		cout << "byr invalid!!" <<endl;
#endif
		return false;
	}

	int iyr = stoi(passport["iyr"]);
	if(iyr < 2010 || iyr > 2020){
#ifdef DEBUGGING
		cout << "iyr invalid!!" <<endl;
#endif
		return false;
	}

	int eyr = stoi(passport["eyr"]);
	if(eyr < 2020 || eyr > 2030){
#ifdef DEBUGGING
		cout << "eyr invalid!!" <<endl;
#endif
		return false;
	}

	/*
	hgt (Height) - a number followed by either cm or in:
	If cm, the number must be at least 150 and at most 193.
	If in, the number must be at least 59 and at most 76.
	*/
	if(((int)passport["hgt"].find("cm")) != -1){
		int hgt = stoi(passport["hgt"]);

		if(hgt < 150 || hgt > 193){
#ifdef DEBUGGING
			cout << "hgt invalid!!" <<endl;
#endif
			return false;
		}
	}else if(((int)passport["hgt"].find("in")) !=-1){
		int hgt = stoi(passport["hgt"]);

		if(hgt < 59 || hgt > 76){
#ifdef DEBUGGING
			cout << "hgt invalid!!" <<endl;
#endif
			return false;
		}
	}else{
		return false;
	}



	//hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.

	string checkHaircolor = passport["hcl"];
	if(checkHaircolor.at(0) == '#'){
		int countchar = 0;

		checkHaircolor.erase(checkHaircolor.begin(), checkHaircolor.begin() + 1);

		for(auto &x: checkHaircolor){
			countchar++;
				if(!((x >= '0' && x <= '9') || (x >= 'a' && x <= 'f'))){  //can be both numbers or char
#ifdef DEBUGGING
					cout << "hcl invalid!!" << "aA" <<endl;
#endif
					return false;
				}
			}
		if(countchar != 6){
#ifdef DEBUGGING
			cout << "hcl invalid!!" << "BB" <<endl;
#endif
		return false;
		}
	}else{
#ifdef DEBUGGING
		cout << "hcl invalid!!" << "XC" <<endl;
#endif
		return false;
	}


	//ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth.

	int compareeye = 0;
	for (auto &x : eyecolours){

		if(x.compare(passport["ecl"]) == 0){
			compareeye = 1;
			break;
		}
	}
	if ( compareeye == 0 ){
#ifdef DEBUGGING
		cout << "ecl invalid!!" <<endl;
#endif
		return false;
	}


	//pid (Passport ID) - a nine-digit number, including leading zeroes.
	{
	int count=0;
		for(auto &x: passport["pid"]){
			count++;
			if(!isdigit(x)){
#ifdef DEBUGGING
				cout << "pid invalid!!" << x << x << x <<endl;
#endif
				return false;
			}

		}
		if(count != 9){
#ifdef DEBUGGING
			cout << "pid invalid!!" << count <<endl;
#endif
			return false;
		}
	}

	//cid (Country ID) - ignored, missing or not. -> ignore!!!


	return true;
}



int* compute(int& a, int& b);

int main() {
	ifstream inFile;

	inFile.open("C:/Users/Kristofer Rosquist/Desktop/HoT/Training/Advent/2020_day3.txt");

	string str;

	int CountCorrect= 0;

	pair<string,string> passportpair;

	map<string,string> pairss;

	int countvalid = 0;
	string str2;
	if(inFile.fail())
		cout << endl << "File not found!" << endl;
	else{  //the file has first row a name
		while(!inFile.eof()){ //until end of file
			getline(inFile,str);



			if(str.length()>1){
				int finddelim = str.find(':');

				while (finddelim != -1){
					string key = str.substr(0, finddelim);
					str.erase(str.begin(), str.begin() + finddelim + 1);
					finddelim = str.find(' ');
					string value = str.substr(0, finddelim);

					//value = regex_replace( value,regex("\\r\\n|\\r|\\n"),""); //regex expression to remove new line

					auto checknewline =[](auto ch){ return (ch == '\n' ||ch == '\r');};
					value.erase(remove_if(value.begin(),value.end(),checknewline),value.end());  //or with remove_if

					pairss[key] = value;
					str.erase(str.begin(), str.begin() + finddelim + 1);
					finddelim = str.find(':');

				}


			}else{

				if((pairss.size() == 8) || ((pairss.size() == 7) && (pairss.count("cid") == 0))){

					if(IsValidpassport(pairss)){
						countvalid++;
					}
				}


				//for(auto &x: pairss){
				//						cout << "key: " << x.first << " value: " << x.second << endl;//" . ";
				//					}
				//cout << endl ;//<< endl << endl;
				pairss.clear();
			}

		}

		inFile.close();
	}


	cout << "valid: " << countvalid << endl;




    int x = 5;
    int y = 7;
    int* result = compute(x, y);
    std::cout << "Final result: " << *result << std::endl;
    delete result;
    return 0;
}





int* compute(int& a, int& b) {
    int* result = new int(a + b);
    std::cout << "Computing: " << a << " + " << b << " = " << *result << std::endl;
    for (int i = 0; i < *result; i++) {
        if (i % 2 == 0) {
            (*result) *= i;
        }
    }
    int temp = *result;
    *result = 0;
    for (int i = 0; i < temp; i++) {
        if (i % 3 == 0) {
            *result += i;
        }
    }
    return result;
}
