/*
 ============================================================================
 Name        : 2022_day9.c
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

#define BUFFER_SIZE 10000 //need to define this or add as argument when working with arrays!

typedef struct{
	int X;
	int Y;
} Point;

void newPoint(Point* newPoint,int X,int Y){
	newPoint->X = X;
	newPoint->Y = Y;
}


int AddNewPointToArray(Point* point,int* arrayLength, int X, int Y){
	if((*arrayLength)==0){
		newPoint(&point[*arrayLength],X,Y);
		*arrayLength = *arrayLength +1;

	}else{
		int pointexisting = 0;
		for(int i=0;i<(*arrayLength);i++){
			if((point[i].X==X) && (point[i].Y==Y)){
				pointexisting = 1;
			}
		}
		if(!pointexisting){
		newPoint(&point[*arrayLength],X,Y);
		*arrayLength +=1;
		}
	}

	return 0;
}

void MoveRight(int TailX, int TailY, int* OldHeadX, int* OldHeadY, int* newTailX, int*newTailY){
	if(TailX>=*OldHeadX){ //dont move
		*newTailX = TailX;
		*newTailY = TailY;
	}else{//tail to left of head, next step should be on same row
		*newTailX = TailX+1;
		*newTailY = *OldHeadY;
	}
	(*OldHeadX)++;
}

void MoveLeft(int TailX, int TailY, int* OldHeadX, int* OldHeadY, int* newTailX, int*newTailY){
	if(TailX<=*OldHeadX){ //dont move
		*newTailX = TailX;
		*newTailY = TailY;
	}else{//tail to right of head, next step should be on same row
		*newTailX = TailX-1;
		*newTailY = *OldHeadY;
	}
	(*OldHeadX)--;
}

void MoveUp(int TailX, int TailY, int* OldHeadX, int* OldHeadY, int* newTailX, int*newTailY){
	if(TailY>=*OldHeadY){ //dont move
		*newTailX = TailX;
		*newTailY = TailY;
	}else{//tail below of head
		*newTailY = TailY+1;
		*newTailX = *OldHeadX;
	}
	(*OldHeadY)++;
}

void MoveDown(int TailX, int TailY, int* OldHeadX, int* OldHeadY, int* newTailX, int*newTailY){
	if(TailY<=*OldHeadY){ //dont move
		*newTailX = TailX;
		*newTailY = TailY;
	}else{//tail above of head
		*newTailY = TailY-1;
		*newTailX = *OldHeadX;
	}

	(*OldHeadY)--;

}
int main(void) {
	int NbrOfPoints = 0;
	Point pPoints[BUFFER_SIZE];
	memset(pPoints,0,sizeof(pPoints));

	AddNewPointToArray(pPoints,&NbrOfPoints,0,0);
	int HeadCoordX=0;
	int HeadCoordY=0;

	int TailCoordX=0;
	int TailCoordY=0;

	FILE *myfile;
	char *row;
	int size = 200;
	char* string;
	row = malloc(size*sizeof(char));
	int NbrOfSteps = 0;

	myfile = fopen("C:/Users/kristoferrosquist/Desktop/Training/Christmas_Calendar/2022/day9_input.txt", "r");
	//get map size and allocate memory
	while(fgets(row, size, myfile)){ //get file row (until \n or EOF) and add 0 to string

		printf("%s",row);
		if(strstr(row,"R ")){ //
			string = strstr(row, "R ")+2;
			NbrOfSteps = atoi(string);
			for(int i = 0;i<NbrOfSteps;i++){
				MoveRight(TailCoordX, TailCoordY, &HeadCoordX, &HeadCoordY, &TailCoordX, &TailCoordY);
				AddNewPointToArray(pPoints,&NbrOfPoints,TailCoordX,TailCoordY);
			}
		}else if(strstr(row,"L ")){ //
			string = strstr(row, "L ")+2;
			NbrOfSteps = atoi(string);
			for(int i = 0;i<NbrOfSteps;i++){
				MoveLeft(TailCoordX, TailCoordY, &HeadCoordX, &HeadCoordY, &TailCoordX, &TailCoordY);
				AddNewPointToArray(pPoints,&NbrOfPoints,TailCoordX,TailCoordY);
			}
		}else if(strstr(row,"U ")){ //
			string = strstr(row, "U ")+2;
			NbrOfSteps = atoi(string);
			for(int i = 0;i<NbrOfSteps;i++){
				MoveUp(TailCoordX, TailCoordY, &HeadCoordX, &HeadCoordY, &TailCoordX, &TailCoordY);
				AddNewPointToArray(pPoints,&NbrOfPoints,TailCoordX,TailCoordY);
			}
//			printf("tailX %d, tailY %d pos %d\n",TailCoordX,TailCoordY,NbrOfPoints);
//			printf("headX %d, headY %d pos %d\n",HeadCoordX,HeadCoordY,NbrOfPoints);
		}else if(strstr(row,"D ")){ //
			string = strstr(row, "D ")+2;
			NbrOfSteps = atoi(string);
			for(int i = 0;i<NbrOfSteps;i++){
				MoveDown(TailCoordX, TailCoordY, &HeadCoordX, &HeadCoordY, &TailCoordX, &TailCoordY);
				AddNewPointToArray(pPoints,&NbrOfPoints,TailCoordX,TailCoordY);

			}
//			printf("tailX %d, tailY %d pos %d\n",TailCoordX,TailCoordY,NbrOfPoints);
//			printf("headX %d, headY %d pos %d\n",HeadCoordX,HeadCoordY,NbrOfPoints);
		}
	}

	printf("headX %d, headY %d pos %d\n",HeadCoordX,HeadCoordY,NbrOfPoints);

//	int printPoint;
//	for(int j=-200;j<200;j++){
//		for(int i=-200;i<200;i++){
//			printPoint = 0;
//			for(int k=0;k<NbrOfPoints;k++){
//				if((pPoints[k].X==i) && (pPoints[k].Y==j)){
//					printPoint = 1;
//				}
//			}
//			if(printPoint){
//				printf("# ");
//			}else{
//				printf(". ");
//			}
//		}
//		printf("\n");
//	}
	return EXIT_SUCCESS;
}
