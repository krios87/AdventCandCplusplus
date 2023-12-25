/*
 ============================================================================
 Name        : 2021_day3-1.c
 Author      : Kristofer
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int smallerprogram(void);
int getMaskMostCommonOnes(int array[], int arraysize, int NumberOfBits, int SearchOnes);
int SearchMostCommonbit(int Bitnumber, int arraysize, int array[], int SearchMost);
int solvepart2(int array[], int arraysize,int bits, int CheckMost);


int main(void) {
//https://adventofcode.com/2021/day/3
	FILE *myfile;
	myfile = fopen("../../../Advent/2021_day3.txt", "r");
	char buff[255];
	char strings[2] = {'1','\0'};
	int i, ones, zeros, gamma,j, ray,binary, maskbit,mostLeastOnes;
	int valarray[1000];

	j=0;
	while(fgets(buff, 255, myfile)) { //get file row (until \n)
		valarray[j] = 0;
		for(i=0;i<12;i++){
			strings[0] = buff[i];
			binary = atoi(strings);
			valarray[j] |= binary<<(11-i);
		}
		j++;
	}

	fclose(myfile);
	int newMask;

	newMask = 0;

	//solve part 1:
	for(j=12; j> -1; j--)
	{

		mostLeastOnes = SearchMostCommonbit(j,sizeof(valarray)/sizeof(valarray[0]), valarray,1);
		if(mostLeastOnes){
			newMask |= 1<<j;
		}
	}

	gamma = newMask;
	ray = gamma ^ 0b111111111111;


	printf("gamma  %d\n",gamma);
	printf("ray  %d\n",ray);
	printf("result: %d\n ",gamma*ray);



	//part 2:
	int Oxygen,CO2;
	Oxygen = solvepart2(valarray, sizeof(valarray)/sizeof(valarray[0]),11,1);
	CO2 = solvepart2(valarray, sizeof(valarray)/sizeof(valarray[0]),11,0);

	printf("oxygen %d CO2 %d  multipli %d",Oxygen,CO2, Oxygen*CO2);


	smallerprogram();
	return EXIT_SUCCESS;
}

int solvepart2(int array[], int arraysize,int bits, int CheckMost){
	int smallerarray[arraysize],newSmallerArray[arraysize],emptyarray[arraysize];
	int j, mask,i;
	for(j=0;j<arraysize;j++){
		emptyarray[j]=0;
	}

	memcpy(smallerarray,emptyarray,sizeof(smallerarray));

	//initialize array
	memcpy(newSmallerArray,array,sizeof(smallerarray));




	int newIndex = 0;
	int mostLeastOnes = 0;
	int size = arraysize;
	int returnVAL;


	for(j=bits; j> -1; j--)
	{
		//initialize the search:
		newIndex = 0;
		//initialize arrays
		memcpy(smallerarray,newSmallerArray,sizeof(smallerarray));
		memcpy(newSmallerArray,emptyarray,sizeof(newSmallerArray)); //set empty

		mostLeastOnes = SearchMostCommonbit(j,size, smallerarray,CheckMost);

		mask = 1 << j;
		for(i = 0; i < size; i++)
		{
			if(mostLeastOnes){
				if((smallerarray[i] & mask)){
						newSmallerArray[newIndex] = smallerarray[i];
						newIndex++;
				}
			}
			else {
				if((~smallerarray[i]) & mask){
					newSmallerArray[newIndex] = smallerarray[i];
					newIndex++;
				}
			}
		}
		size = newIndex;


		if(size < 2){
			returnVAL = newSmallerArray[newIndex-1];
			break;
		}
	}
	return returnVAL;
}
int SearchMostCommonbit(int Bitnumber, int arraysize, int array[], int SearchMost){
	int mask;
	int ones, zeros,i,j;
	int MostOnes;
	ones = zeros = 0;
	mask = 1 << Bitnumber;
	for(i = 0; i < arraysize; i++)
		{
			if(array[i] & mask){
				ones++;
			}
			else{
				zeros++;
			}
		}

	if(SearchMost){
		if(ones >= zeros){
			MostOnes = 1;
		}
		else {
			MostOnes = 0;
		}
	}else if(SearchMost == 0){

		if(ones < zeros){
			MostOnes = 1;
		}
		else{
			MostOnes = 0;
		}
	}

	return MostOnes;

}

int smallerprogram(){
	int DiagArray[] = {0b00100,0b11110,0b10110,0b10111,0b10101,0b01111,0b00111,0b11100,0b10000,0b11001,0b00010,0b01010};

		int length = sizeof(DiagArray)/sizeof(DiagArray[0]);
		int i, ones, zeros, gamma,j, ray;
		int mask = 0b00000;
		gamma =0;
		for(j=0; j< 5; j++)
		{
			ones = zeros = 0;
			mask = 1 << j;
			for(i = 0; i < length; i++)
			{
				if(DiagArray[i] & mask){
					ones++;
				}
				else{
					zeros++;
				}
			}
			if(ones > zeros){
				gamma |= mask;
			}
		}
		ray = gamma ^ 0b11111;

		//part2 small:
		int Oxygen, CO2;
		Oxygen = solvepart2(DiagArray, sizeof(DiagArray)/sizeof(DiagArray[0]),4,1);
		CO2 = solvepart2(DiagArray, sizeof(DiagArray)/sizeof(DiagArray[0]),4,0);



	  return 0;

}
