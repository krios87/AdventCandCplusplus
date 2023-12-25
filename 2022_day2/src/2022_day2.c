/*
 ============================================================================
 Name        : 2022_day2.c
 Author      : Kristofer
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//https://adventofcode.com/2022/day/2
int main(void) {

	FILE *myfile;
	myfile = fopen("C:/Users/kristoferrosquist/Desktop/Training/Christmas_Calendar/2022/day2_input.txt", "r");
	char *row;
	int size = 1000;
	row = malloc(size*sizeof(char));


	char *pMyResponse;
	char MyResponse,ElfResponse,RoundResult;
	int mypoints = 0;
	int mypointsPart2 = 0;
	while(fgets(row, size, myfile)){ //get file row (until \n or EOF) and add 0 to string

		pMyResponse = strchr(row,' ');
		ElfResponse = *row;

		//first part
		MyResponse = *(pMyResponse+1)-('X'-'A');  //x,y,z -> a,b,c
		//1 point A rock, 2 point B paper, 3 point scissor
		char LosingChar = (char)('A' + ((MyResponse-'A')+ 2 ) % 3); //+2 from myResponse is elfs losing choice
		//3 points if equal, 6 points for winning
		mypoints += MyResponse - 'A'+1 + (ElfResponse == MyResponse?3:ElfResponse == LosingChar?6:0);


		//second part
		RoundResult = *(pMyResponse+1);
		int Shift;
		switch(RoundResult){
		case 'X':
			Shift = 2; //loose so use the two next (if rock (A) use scissor (C) etc)
			break;
		case 'Y':
			Shift = 0; //take same as opponent
			mypointsPart2 +=3;
			break;
		case 'Z':
			Shift = 1; //win use next (if stone (A) use paper (B))
			mypointsPart2 +=6;
			break;
		}

		MyResponse = (char)('A' + ((ElfResponse-'A')+Shift)%3); //convert to A, rock, B paper or C scissor.

		mypointsPart2 += MyResponse - 'A' + 1; //1 point A rock, 2 point B paper, 3 point scissor

	}

	printf("points %d \n",mypoints);
	printf("points2 %d",mypointsPart2);
	return EXIT_SUCCESS;
}
