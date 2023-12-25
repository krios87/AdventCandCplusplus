/*
 ============================================================================
 Name        : 2021_day6.c
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

//https://adventofcode.com/2021/day/6 

uint32_t size = 200000000;
int solution1();

int main(void) {

	//solution1();
	solution2();
	return EXIT_SUCCESS;
}


int solution2(){
	FILE *myfile;
		myfile = fopen("C:/Users/kristoferrosquist/Desktop/ESS/FBIS/Useful things/ChristmasCalendar/2021/day6_input.txt", "r");
		char *buff;
		buff = malloc(1000*sizeof(char));
		int i,j,k,l;
		char *Fish = (char*)malloc(4000 * sizeof(char)); //defining array will not work with such a big value. also char is the smallest possible type

		j=0;
		l=0;
		k=0;
		char value[2] = {'\0','\0'};
		char pval;
		unsigned long long nbrOfFish = 0;
		unsigned long long countfishes[9];
		unsigned long long newFishes[9];
		for(i=0;i<9;i++)
			countfishes[i]=0;
		while(fgets(buff, 1000, myfile)) { //get file row (until \n)
			pval = *buff;
			for(i=0;i<strlen(buff);i++){
				strncpy(value,buff+i,1);

				if(isdigit(*value)){
					Fish[k]=atoi((char*)value);
					//printf("fish: %d \n",Fish[k]);
					//printf("VAL: %d \n",i);

					countfishes[(unsigned long long)Fish[k]] += 1;

					nbrOfFish++;
					k++;
				}

				pval++;
			}
			//printf("VAL: %c",val);
			j++;
		}
	//
		for(i=0;i<9;i++){
			printf("%llu ",countfishes[i]);
		}
		printf("\n");

		unsigned long long nbrOfDays = 256;
		unsigned long long NbrOfFishes = 0;

		for(i=0;i<nbrOfDays;i++){


			newFishes[0] = countfishes[1];
			newFishes[1] = countfishes[2];
			newFishes[2] = countfishes[3];
			newFishes[3] = countfishes[4];
			newFishes[4] = countfishes[5];
			newFishes[5] = countfishes[6];
			newFishes[6] = countfishes[7]+countfishes[0];
			newFishes[7] = countfishes[8];
			newFishes[8] = countfishes[0];

			memcpy(countfishes, newFishes, sizeof countfishes);

//			for(j=0;j<9;j++){
//				printf("%llu, ", countfishes[j]);
//			}
//			printf("i %d\n",i);
		}

		for(i=0;i<9;i++){
			NbrOfFishes += countfishes[i];
			//printf("values: %llu \n", countfishes[i]);
		}

		printf("\n Total: %llu\n",NbrOfFishes);

//			for(j=0;j<nbrOfFish;j++){
//
//				if(Fish[j]==0){
//					newFishes++;
//					Fish[j]=7;
//				}
//
//				Fish[j]--;
//			}

//			while(newFishes){
//				Fish[nbrOfFish] = 8;
//				nbrOfFish++;
//				newFishes--;
//	//
//			}





}

int solution1(){
	FILE *myfile;
		myfile = fopen("C:/Users/kristoferrosquist/Desktop/ESS/FBIS/Useful things/ChristmasCalendar/2021/day6_input.txt", "r");
		char *buff;
		buff = malloc(1000*sizeof(char));
		int i,j,k,l;
		char *Fish = (char*)malloc(40000000000 * sizeof(char)); //defining array will not work with such a big value. also char is the smallest possible type

		j=0;
		l=0;
		k=0;
		char value[2] = {'\0','\0'};
		char pval;
		unsigned long long nbrOfFish = 0;
		while(fgets(buff, 1000, myfile)) { //get file row (until \n)
			pval = *buff;
			for(i=0;i<strlen(buff);i++){
				strncpy(value,buff+i,1);

				if(isdigit(*value)){
					Fish[k]=atoi((char*)value);
					//printf("fish: %d \n",Fish[k]);
					//printf("VAL: %d \n",i);
					k++;
					nbrOfFish++;

				}

				pval++;
			}
			//printf("VAL: %c",val);
			j++;
		}
	//
	//	for(i=0;i<2000;i++){
	//		printf("%lu ",Fish[i]);
	//	}


		unsigned long long nbrOfDays = 80;
		unsigned long long newFishes = 0;

		for(i=0;i<nbrOfDays;i++){


			for(j=0;j<nbrOfFish;j++){

				if(Fish[j]==0){
					newFishes++;
					Fish[j]=7;
				}

				Fish[j]--;
			}

			while(newFishes){
				Fish[nbrOfFish] = 8;
				nbrOfFish++;
				newFishes--;
	//
			}
	//		if(i==(nbrOfDays-1)){
	//		for(k=0;k<nbrOfFish;k++){
	//				printf(" %d, ",Fish[k]);
	//		}
	//		}
		}



			printf("\n Total: %llu\n",nbrOfFish);
}
