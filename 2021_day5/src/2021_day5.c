/*
 ============================================================================
 Name        : 2021_day5.c
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

int BigMatrix[1000][1000];
int size = 1000;

//https://adventofcode.com/2021/day/5
int main(void) {
	FILE *myfile;
		myfile = fopen("C:/Users/kristoferrosquist/Desktop/ESS/FBIS/Useful things/ChristmasCalendar/2021/day5_input.txt", "r");
		char *buff;
		buff = malloc(555*sizeof(char));
		int i,j,k,l;

		while(l<555){
			*(buff+l) =0;
			l++;
		}

		for(i=0;i<size;i++)
			for(j=0;j<size;j++)
				BigMatrix[i][j]=0;

		printf("hej");

		char *reststring;

		int FirstX[1000];
		int FirstY[1000];
		int SecondX[1000];
		int SecondY[1000];
		int Whichcoord = 0; //0 firstX, 1 FirstY, 2 SecondX
		char stringel;
		j=0;
		int length = 0;
		int NbrOfEntries = 0;
		int lastValue = 0;
		int numberlength= 0;
		char Onevalue[3] = {'\0','\0','\0'};
		while(fgets(buff, 555, myfile)) { //get file row (until \n)

			//if(j==0){
				l=0;
			//	printf("Size: %lu \n", strlen(buff)); //sizeof(buff) will always be 8 since it is size of pointer!
				length = strlen(buff); //get length and do for loop or do while loop

				while(*(buff+l)!=0){
					stringel = *(buff+l);
					if(isdigit(stringel)){
						numberlength++;
						//printf("length %d %c \n", numberlength, stringel);
						lastValue = 1;
					} else{
						if(lastValue){

							strncpy(Onevalue,(buff+l-numberlength),numberlength);
							switch(Whichcoord){

							case 0:
								FirstX[j]= atoi(Onevalue);
								NbrOfEntries++;
								break;

							case 1:
								FirstY[j]= atoi(Onevalue);
								break;
							case 2:
								SecondX[j]= atoi(Onevalue);
								break;
							case 3:
								SecondY[j]= atoi(Onevalue);
								break;
							default:
								break;
							}
							lastValue=0;
							Onevalue[0] =Onevalue[1]=Onevalue[2] = '\0'; //reset to 0
							Whichcoord++;

							if(Whichcoord==4){
								Whichcoord = 0;
							}


							numberlength=0;
						}
					}
					l++;
				}
		//	}
			j++;
		}

		int lenX,lenY;
		int doX,doY;
		doX=doY=0;
		lenX=lenY=0;
		int linelength= 0;
		int linelengthabs = 0;
		int linesign = 1;

		int xsign,ysign;
		xsign = ysign;

		for(i=0;i<NbrOfEntries;i++){

			//if(i==0){

				lenX = SecondX[i]-FirstX[i];
				lenY = SecondY[i]-FirstY[i];

				if(lenX==0){
					linelength = lenY;
					doY=1;
				} else if(lenY==0){
					linelength = lenX;
					doX=1;
				}
				xsign = (lenX > 0) ? 1 : ((lenX < 0) ? -1 : 1);
				ysign = (lenY > 0) ? 1 : ((lenY < 0) ? -1 : 1);

				linelengthabs = abs(linelength)+1;
				linesign = (linelength > 0) ? 1 : ((linelength < 0) ? -1 : 1);

				if(doX || doY){
					for(j=0;j<linelengthabs;j++){
						if(doX){
							BigMatrix[FirstX[i]+linelength-linesign*j][FirstY[i]]++;

						}else if(doY){
							BigMatrix[FirstX[i]][FirstY[i]+linelength-linesign*j]++;
						}

					}
				} else {
					for(j=0;j<=abs(lenX);j++){
						for(k=0;k<=abs(lenY);k++){
							if(j==k){
								if(i==5){
								//	printf("X %d, Y %d \n",FirstX[i]+lenX-xsign*j,FirstY[i]+lenY-ysign*k );
								}
								BigMatrix[FirstX[i]+lenX-xsign*j][FirstY[i]+lenY-ysign*k]++;
							}
						}
					}

				}
				doX=doY=0;

			//}

		}

		for(i=0;i<20;i++){

		//	printf("%d ", BigMatrix[i][4]);
		}
		int count;
		count = 0;
		for(i=0;i<size;i++)
			for(j=0;j<size;j++)
				if(BigMatrix[i][j]>1)
					count++;


		printf("count:  %d\n ", count);

	return EXIT_SUCCESS;
}
