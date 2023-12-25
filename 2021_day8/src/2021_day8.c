/*
 ============================================================================
 Name        : 2021_day8.c
 Author      : Kristofer
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

//https://adventofcode.com/2021/day/8 


struct CodeNumber{
	int code;
	int value;
};
int main(void) {
	clock_t start, stop;
	    start = clock();


	FILE *myfile;
		myfile = fopen("../../../Advent/2021_day8.txt", "r");
		char *buff;
		int size = 10000;
		buff = malloc(size*sizeof(char));
		int i,j,k,l;
		int sum;

		char *rest,*rest1,*rest2,*rest3,*rest4;
		int count1,count4,count7,count8, counttotal;
		counttotal = 0;
		count1=0;
		int length;
		char letter;
		int codeLetter[10];
		int codeLength[10];
		int value;
		int number[10];

		j=0;
		sum=0;
		while(fgets(buff, size, myfile)) { //get file row (until \n)

			for(i=0;i<10;i++){
				codeLetter[i]=codeLength[i]=0;
				number[i]=100000;
			}
				rest = buff;
				for(i=0;i<10;i++){
					length= 0;
					while(isalpha(*rest)){
						codeLetter[i] += 1 << (*rest-97);
						rest++;
						codeLength[i]+=1;
					} //count letters

					switch(codeLength[i]){

					case 7:
						number[8]=codeLetter[i];

						break;

					case 2:
						number[1]=codeLetter[i];

						break;

					case 3:
						number[7]=codeLetter[i];
						break;

					case 4:
						number[4]=codeLetter[i];
						break;
					}


					while(!isalpha(*rest)){
						rest++;
					} //find start of next word

				}

				for(i=0;i<10;i++){

					if(codeLength[i]==6){ //0 or 6 or 9
						if((codeLetter[i] & number[7])==number[7]){ //9 or 0
							if((codeLetter[i] & number[4])==number[4]){
								number[9]=codeLetter[i];
							}else{
								number[0]=codeLetter[i];
							}
						} else{
							number[6]=codeLetter[i];
						}

					} else if(codeLength[i]==5){//2, 3, 5

						if((codeLetter[i] & number[1])==number[1]){ //3
							number[3]=codeLetter[i];
						}

					}
				}

				for(i=0;i<10;i++){

					if(codeLength[i]==5){

						if(((codeLetter[i] & number[6]) ==codeLetter[i])){
							number[5]=codeLetter[i];
						} else if((codeLetter[i]!=number[5]) && (codeLetter[i]!=number[3])){
							number[2]=codeLetter[i];
						}
					}
				}

				rest = strchr(buff, '|');
				value = 0;
				for(k=0;k<4;k++){
					while(!isalpha(*rest)){
						rest++;
					} //find start of next word

					int code=0;
					while(isalpha(*rest)){
						code += 1 << (*rest-97);
						rest++;
					} //count letters

					for(i=0;i<10;i++){//search for code
						if(code==number[i]){
							value += (int)(i*pow(10.0,(float)(3-k)));

						}
					}
				}
				sum +=value;

			j++;
		}

		printf("total: %d \n",sum);

		   stop = clock();

		double mytime = (double)(stop - start)/ CLOCKS_PER_SEC;

		printf("time: %6.6f",mytime);
	return EXIT_SUCCESS;
}
