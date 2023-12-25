/*
 ============================================================================
 Name        : 2021_day1.c
 Author      : Kristofer
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
int AddToMovingAverageArray(int array[], int value);

int main(void) {
	//https://adventofcode.com/2021/day/1
	FILE *myfile;
		myfile = fopen("../../../Advent/2021_day1.txt", "r");
		char buff[255];
		int i,j;
		int valarray[2000];
		int prevSum = 0;
		int newSum = 0;
		int countlarger = 0;
		int window = 3;
		int sum[window];
		for(i=0;i<window;i++){
			sum[i] = 0;
		}
		j=0;


		while(fgets(buff, 255, myfile)) { //get file row (until \n)

				valarray[j] = atoi(buff);
			j++;
		}

		//initialize array:
		sum[0] = valarray[0];
		sum[1] = valarray[1];
		sum[2] = valarray[2];
		prevSum = sum[0]+sum[1]+sum[2];

		for(i=3;i<2000;i++){
			newSum= AddToMovingAverageArray(sum, valarray[i]);
			printf("newsum %d \n", newSum);
			if ( newSum > prevSum){
				countlarger++;
			}
			prevSum = newSum;

		}

		printf("Larger: %d", countlarger);

	return EXIT_SUCCESS;
}

int AddToMovingAverageArray(int array[], int value){
	array[0] = array[1];
	array[1] = array[2];
	array[2] = value;
	return array[0]+array[1]+array[2];
}
