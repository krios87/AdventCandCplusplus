/*
 ============================================================================
 Name        : 2022_day25.c
 Author      : Kristofer
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//https://adventofcode.com/2022/day/25

int calcval(char character){

	switch(character){

	case '2':
		return 2;
		break;

	case '1':
		return 1;
		break;

	case '0':
		return 0;
		break;

	case '-':
		return -1;
		break;

	case '=':
		return -2;
		break;
	}
}

volatile int indexSnafu = 0;

void convertToSNAFU(long ival, char* array){

	if(ival == 0){
		return;
	}

	switch(ival % 5){
        case 0: case 1: case 2:
        	char strval[8];
        	memset(strval,0,sizeof(strval));
        	sprintf(strval,"%ld",ival % 5);
        	array[indexSnafu++] = *strval;
        	convertToSNAFU((ival / 5),array);
        	break;
        case 3:
        	array[indexSnafu++] = '=';
            convertToSNAFU( 1 + ival / 5,array);
            break;
        case 4:
        	array[indexSnafu++] = '-';
        	convertToSNAFU( 1 + ival / 5,array);
            break;
	}

}


int main(void) {


	FILE *myfile;
	myfile = fopen("C:/Users/kristoferrosquist/Desktop/Training/Christmas_Calendar/2022/day25_input.txt", "r");
	char *row;
	int size = 5000;
	row = malloc(size*sizeof(char));
	long length = 0;
	int i = 0;
	long sum = 0;
	long value;
	while(fgets(row, size, myfile)){ //get file row (until \n or EOF) and add 0 to string
		length = strlen(row)-3; //last index (end -1 - LR CR)
		int charindex = length;
			value = 0;
			while(charindex >= 0){
				value += pow(5,(length-charindex))*calcval(*(row+charindex));
				//printf("%c \n",*(row + length));

				charindex--;

			}

			sum += value;

		i++;
	}

	printf("sum %lu \n", sum);

	//int testval = 4890;


	char resultArray[800];
	memset(resultArray,0,sizeof(resultArray));


	convertToSNAFU(sum,resultArray);

	//revert:
	char newArray[800];
	memset(newArray,0,sizeof(newArray));

	for(int i = indexSnafu-1;i>-1;i--){
		newArray[indexSnafu-i-1] = resultArray[i];
	}
	printf("%s \n",newArray);

	return EXIT_SUCCESS;
}


