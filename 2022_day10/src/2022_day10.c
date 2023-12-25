/*
 ============================================================================
 Name        : 2022_day10.c
 Author      : Kristofer
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//https://adventofcode.com/2022/day/10
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define ROWLENGTH 40

void marksprite(int* Sprite,int value){

	Sprite[0] = MAX(value-1,0);
	Sprite[1] = MIN(MAX(value,0),(ROWLENGTH-1));
	Sprite[2] = MIN(value+1,(ROWLENGTH-1));
}

int main(void) {


		FILE *myfile;
		char *row;
		int size = 200;
		char* string;
		row = malloc(size*sizeof(char));
		int rowIndex,drawIndex,Loop, SpriteIndeces[3],signalstrengths[100];
		int value =1;
		int cycles = 0;
		int signalstrengthIndex = 0;
		int NbrOfPixels = 40*6;
		char pixels[NbrOfPixels];

		char* pAddx = NULL;
		char* pNoop = NULL;

		memset(signalstrengths,0,sizeof(signalstrengths));
		memset(pixels,0,sizeof(pixels));
		memset(SpriteIndeces,0,sizeof(SpriteIndeces));




		myfile = fopen("../../../Advent/2022_day10.txt", "r");
		//get map size and allocate memory
		while(fgets(row, size, myfile)){ //get file row (until \n or EOF) and add 0 to string

			pAddx = strstr(row,"addx ");
			pNoop = strstr(row,"noop");

			if(pAddx || pNoop){
				cycles++; //1 cycle started
				Loop = pAddx?2:1; //2 cycles for addx, 1 for noop

				while(Loop>0){
					//first cycle
					//part1
					if((cycles == 20) || ((cycles > 20) && ((cycles-20)%40 ==0))){
						signalstrengths[signalstrengthIndex] = value*cycles;
						signalstrengthIndex++;
					}
					//part2
					marksprite(SpriteIndeces,value);
					drawIndex = (cycles-1);
					rowIndex = drawIndex%ROWLENGTH;

					pixels[drawIndex] = (SpriteIndeces[0] == rowIndex || SpriteIndeces[1] == rowIndex || SpriteIndeces[2] == (rowIndex)) ? '#' : '.';

					if(pAddx){
						if(Loop ==2){
							cycles++;//Second cycle for addx
						}else if(Loop==1){ //end of second cycle add value
							string = strstr(row,"addx ")+strlen("addx ");
							value += atoi(string);
						}
					}
					Loop--;
				}
			}
		}

		//first part
		int sum=0;
		for(int i=0;i<signalstrengthIndex;i++){
			sum+=signalstrengths[i];
		}
		printf("sum: %d \n",sum);

		//draw second part
		for(int i=0;i<NbrOfPixels;i++){
			printf("%c",pixels[i]);
			if((i%ROWLENGTH)==(ROWLENGTH-1)){
				printf("\n");
			}
		}


	return EXIT_SUCCESS;
}
