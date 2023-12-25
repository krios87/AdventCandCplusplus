/*
 ============================================================================
 Name        : 2022_day6.c
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

#define BUFFER_SIZE 14 //4 for first part
//https://adventofcode.com/2022/day/6
typedef struct {
	int writeindex;
	char array[BUFFER_SIZE];
	int size;
}Mybuffer;

void init_buffer(Mybuffer* buffer){
	buffer->writeindex = 0;
	buffer->size = 0;
	memset(buffer->array,0,sizeof(buffer->array));
}

void Write_Buffer(Mybuffer* buffer,char c){

	buffer->array[buffer->writeindex++] = c;

	if(buffer->writeindex == BUFFER_SIZE){
		buffer->writeindex = 0;
	}

	if(buffer->size < BUFFER_SIZE){
		buffer->size++;
	}
}

int HasDuplicate(char* array,int number){
	int Equal = 0;

	if(number==0){
		return Equal;
	}else{
		for(int i=0; i<number;i++){
			Equal |= (array[i] == array[number]);
		}
		return HasDuplicate(array,number-1) || Equal;
	}
}


int main(void) {


	FILE *myfile;
	myfile = fopen("C:/Users/kristoferrosquist/Desktop/Training/Christmas_Calendar/2022/day6_input.txt", "r");
	char *row;
	int size = 5000;
	row = malloc(size*sizeof(char));

	Mybuffer Buffer;
	init_buffer(&Buffer);

	int LetterIndex = 0;
	while(fgets(row, size, myfile)){ //get file row (until \n or EOF) and add 0 to string

		while(*(row+LetterIndex)){

			Write_Buffer(&Buffer,*(row+LetterIndex));

			if((Buffer.size == BUFFER_SIZE) && (!HasDuplicate(Buffer.array,Buffer.size-1))){
				printf("result: %d\n",LetterIndex+1);
				break;
			}
			LetterIndex++;
		}

	}
	myfile = fopen("C:/Users/kristoferrosquist/Desktop/Training/Christmas_Calendar/2022/day7_input.txt", "r");
	char buff[5000];
	fscanf(myfile,"%40s\n",buff);
	printf("%s \n",buff);
	fscanf(myfile,"%40s\n",buff);
		printf("%s \n",buff);
		fscanf(myfile,"%40s\n",buff);
			printf("%s \n",buff);
	//fscanf(myfile,"%40s \n",buff);
//
	//printf("%s",buff);
	return EXIT_SUCCESS;
}
