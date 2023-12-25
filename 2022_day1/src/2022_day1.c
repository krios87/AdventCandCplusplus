/*
 ============================================================================
 Name        : 2022_day1.c
 Author      : Kristofer
 Version     :
 Copyright   : Your copyright notice
 Description : day1
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//https://adventofcode.com/2022/day/1

void insertionSort(int arr[], int n)
{
    int i, key, j;
    for(i = 1; i < n; i++){
        key = arr[i];
        j = i - 1;
        while(j >= 0 && arr[j] > key){
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int main(void) {
	FILE *myfile;
	myfile = fopen("../../../Advent/2022_day1.txt", "r");
	char *row;
	int size = 1000;
	row = malloc(size*sizeof(char));
	int nbrOfElfs;
	int maxElfs = 5000;
	int Elfs[maxElfs];
	char foodvalue[100];

	//initialize
	memset(Elfs, 0,maxElfs*sizeof(int));
	int ElfIndex = 0;
	nbrOfElfs = 1;

	while(fgets(row, size, myfile)){ //get file row (until \n) and add 0 to string

		strcpy(foodvalue,row);
		if(isdigit((int )*foodvalue)){
			Elfs[ElfIndex] += atoi(foodvalue);
		}else{
			ElfIndex++;
			nbrOfElfs++;
		}
	}
	int maxval[3];
	//sorting the whole array
	insertionSort(Elfs,nbrOfElfs);
	maxval[0]=Elfs[nbrOfElfs-1];
	maxval[1]=Elfs[nbrOfElfs-2];
	maxval[2]=Elfs[nbrOfElfs-3];
	printf("maxval1: %d, maxval2 %d, maxval3 %d total %d",maxval[0],maxval[1],maxval[2],maxval[0]+maxval[1]+maxval[2] );

	return EXIT_SUCCESS;
}
