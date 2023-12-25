/*
 ============================================================================
 Name        : 2022_day3.c
 Author      : Kristofer
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//https://adventofcode.com/2022/day/3
int getPrio(char Letter){
	int prio = 0;
	if(isupper((int)Letter)){
		prio = Letter-38;
	}else{
		prio = Letter-96;
	}
	return prio;
}

int main(void) {
	FILE *myfile;
	myfile = fopen("C:/Users/kristoferrosquist/Desktop/Training/Christmas_Calendar/2022/day3_input.txt", "r");
	char *row;
	int size = 1000;
	row = malloc(size*sizeof(char));
	int linelength,i,halflength,prioletter;
	int NbrOFPrio=53;
	char aPriorities[NbrOFPrio];
	char aPriorities2[NbrOFPrio];
	int sum = 0;
	int LineNbr = 0;
	int sum2 = 0;
	int bitNbr;

	while(fgets(row, size, myfile)) { //get file row (until \n)
		linelength= strlen(row)-2;  //need new line for last row to work
		halflength= linelength/2;
		memset(aPriorities, 0,NbrOFPrio*sizeof(char));

		//First compartment
		for(i=0;i<halflength;i++){
			prioletter = getPrio(*(row+i));
			aPriorities[prioletter] = aPriorities[prioletter] | 1;
		}

		//second compartment
		for(i=halflength;i<linelength;i++){
			prioletter = getPrio(*(row+i));
			if(aPriorities[prioletter] == 1){ //already in first compartment
				sum+= prioletter;
				break;
			}
		}

		//Second part:
		bitNbr = 1<<(LineNbr%3);

		if(bitNbr==1){ //first line in new group
			//reset list for new group
			memset(aPriorities2, 0,NbrOFPrio*sizeof(char));
		}
		for(i=0;i<linelength;i++){
			prioletter = getPrio(*(row+i));
			aPriorities2[prioletter] = aPriorities2[prioletter] | bitNbr;  //item found, add bit1 for first row, 2 for second and 3rd for 3rd
		}

		if(bitNbr==4){ //check for 3rd row common character in all 3
			for(i=0;i<NbrOFPrio;i++){
				sum2 += aPriorities2[i] == 7?i:0;
			}
		}

		LineNbr++;

	}

	printf("sum1: %d \n",sum);
	printf("sum2: %d \n",sum2);
	return EXIT_SUCCESS;
}
