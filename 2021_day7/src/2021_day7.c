/*
 ============================================================================
 Name        : 2021_day7.c
 Author      : Kristofer
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {

	FILE *myfile;
		myfile = fopen("../../../Advent/2021_day7.txt", "r");
	int num,i,j;
	int list[10000];
	i=0;
	while (fscanf(myfile, "%d,", &num) == 1)
	{
	    list[i] = num;
	 i++;
	}
	int sizelist = i;


	unsigned long int max = 2000;
	unsigned long mindist=1000000000;
	unsigned long testpartsum;
	unsigned long crabcost,k;

	int linepos;

	for(i=0;i<max;i++){
		testpartsum=0;
		for(j=0;j<sizelist;j++){
			crabcost=0;
			k=list[j]; //position crab
			while(abs(k-i)>0){ //distance to line > 0
				crabcost += abs(k-i);
				if(k>i){
					k--;
				}else{
					k++;
				}
			}
			testpartsum+=crabcost;
		}
		if(testpartsum<mindist){
			mindist=testpartsum;
			linepos = i;
		}
	}
	printf("testpart %lu, pos: %d",mindist,linepos);

	return EXIT_SUCCESS;
}
