/*
 ============================================================================
 Name        : 2022_day4-1.c
 Author      : Kristofer
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//https://adventofcode.com/2022/day/4

//part 1 function
int checkOverlapFull(int** Elfs){

	return (((Elfs[0][0] <= Elfs[1][0]) && (Elfs[0][1] >= Elfs[1][1])) || ((Elfs[1][0] <= Elfs[0][0]) && (Elfs[1][1] >= Elfs[0][1])));
}

//part2 function
int checkOverlap(int** Elfs){

	return ((Elfs[0][1]>=Elfs[1][0] && Elfs[0][0] <= Elfs[1][0]) || (Elfs[1][1]>=Elfs[0][0] && Elfs[1][0] <= Elfs[0][0]));

}
int main(void) {
	FILE *myfile;
	myfile = fopen("C:/Users/kristoferrosquist/Desktop/Training/Christmas_Calendar/2022/day4_input.txt", "r");
	char *row;
	int size = 500;
	row = malloc(size*sizeof(char));
	int i;

	char *string;
	//elf1 has areas elf[0][0] + elf[0][1], initialize matrix:
	int** Elfs = (int **)malloc(2*sizeof(int));
	for(i=0;i<2;i++)
		Elfs[i]=(int *)malloc(2*sizeof(int));

	int count = 0;
	while(fgets(row, size, myfile)){ //get file row (until \n or EOF) and add 0 to string
		i=0;
		string = strtok(row, ",-"); //separate by , or -
		while(string != NULL){
			Elfs[i/2][i%2] = atoi(string);
			string = strtok(NULL, ",-"); //continue to separate rest of string (row)
			i++;
		}
		count += checkOverlap(Elfs);
	}

	printf("count %d",count);
	return EXIT_SUCCESS;
}
