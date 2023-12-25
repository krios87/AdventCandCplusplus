/*
 ============================================================================
 Name        : 2021_day2.c
 Author      : Kristofer
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int main(void) {
	//https://adventofcode.com/2021/day/2
	FILE *myfile;
	myfile = fopen("C:/Users/kristoferrosquist/Desktop/ESS/FBIS/Useful things/ChristmasCalendar/2021/day2_input.txt", "r");
	char buff[255];
	//char strings[2] = {'1','\0'};
	int i,j;
	int valarray[1000];
	char direction[10];
	char empty[10];
	for(j=0;j<10;j++){
		empty[j] = 0;
	}
	char *rest;
	j=0;
	const char searchspace = ' ';
	int position = 0;
	int depth = 0;
	int aim = 0;
	while(fgets(buff, 255, myfile)) { //get file row (until \n)
		rest = strchr(buff, searchspace);
		valarray[j] = atoi(rest);
		strncpy(direction,empty,sizeof(empty));
		strncpy(direction,buff,(strlen(buff)-strlen(rest)));
	if(strcmp(direction,"forward")==0){
		position+= valarray[j];
		depth += aim * valarray[j];
	} else if(strcmp(direction,"up")==0){
		aim-= valarray[j];
	} else if(strcmp(direction,"down")==0){
		aim+= valarray[j];
	}
		j++;

	}

	printf("position: %d, depth: %d, mult: %d \n",position, depth,position*depth);
	return EXIT_SUCCESS;
}
