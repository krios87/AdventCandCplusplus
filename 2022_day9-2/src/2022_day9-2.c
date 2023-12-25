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

#define BUFFER_SIZE 100000 //need to define this or add as argument when working with arrays!

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

int MoveRight(int TailX, int TailY, int* OldHeadX, int* OldHeadY, int* newTailX, int*newTailY,int prenomove){

	if(TailX>=*OldHeadX){ //dont move or previous no move
		*newTailX = TailX;
		*newTailY = TailY;
	}else {
		*newTailX = TailX+1;
		*newTailY = *OldHeadY;
	}

	(*OldHeadX)++;
	return 0;
}

int MoveLeft(int TailX, int TailY, int* OldHeadX, int* OldHeadY, int* newTailX, int*newTailY,int prenomove){
	int noMoveorDiag = 0; //straight
	if(prenomove==2){ //moved diagnoal follow oldHead
		*newTailX = *OldHeadX;
		*newTailY = *OldHeadY;
		noMoveorDiag = 2;//diag
	}else if(TailX<=*OldHeadX || (prenomove ==1)){ //dont move or previous no move
		*newTailX = TailX;
		*newTailY = TailY;
		noMoveorDiag = 1;//nomove
	}else{//tail to right of head, next step should be on same row
		*newTailX = TailX-1;
		*newTailY = *OldHeadY;
		if(TailY!=(*OldHeadY)) { //diagonal
			noMoveorDiag = 2;//diag
		}
	}
	(*OldHeadX)--;

	return noMoveorDiag;
}

int MoveUp(int TailX, int TailY, int* OldHeadX, int* OldHeadY, int* newTailX, int*newTailY,int prenomove){

	if(TailY>=*OldHeadY){ //dont move or previous no move
		*newTailX = TailX;
		*newTailY = TailY;
	}else{//tail below of head
		*newTailY = TailY+1;
		*newTailX = *OldHeadX;

	}
	(*OldHeadY)++;

	return 0;
}

int MoveDown(int TailX, int TailY, int* OldHeadX, int* OldHeadY, int* newTailX, int*newTailY,int prenomove){
	int noMoveorDiag = 0; //straight
	if(prenomove==2){ //moved diagnoal follow oldHead
		*newTailX = *OldHeadX;
		*newTailY = *OldHeadY;
		noMoveorDiag = 2;//diag
	}else if(TailY<=*OldHeadY  || (prenomove ==1)){ //dont move or previous no move
		*newTailX = TailX;
		*newTailY = TailY;
		noMoveorDiag = 1;//nomove
	}else{//tail above of head
		*newTailY = TailY-1;
		*newTailX = *OldHeadX;

		if(TailX!=(*OldHeadX)) { //diagonal
			noMoveorDiag = 2;//diag
		}
	}

	(*OldHeadY)--;

	return noMoveorDiag;

}
int main(void) {
	int NbrOfPoints = 0;
	Point pPoints[BUFFER_SIZE];
	memset(pPoints,0,sizeof(pPoints));

	AddNewPointToArray(pPoints,&NbrOfPoints,0,0);
	int HeadCoordX=0;
	int HeadCoordY=0;

	FILE *myfile, *myfile2;
	char *row;
	int size = 200;
	char* string;
	row = malloc(size*sizeof(char));
	int NbrOfSteps = 0;
	int diagmove = 0;
	int aTailCoordX[9];
	int aTailCoordY[9];
	memset(aTailCoordX,0,sizeof(aTailCoordX));
	memset(aTailCoordY,0,sizeof(aTailCoordY));

	myfile = fopen("C:/Users/kristoferrosquist/Desktop/Training/Christmas_Calendar/2022/day9_input.txt", "r");
	//get map size and allocate memory

	myfile2 = fopen("C:/Users/kristoferrosquist/Desktop/Training/Christmas_Calendar/2022/day9_output.txt", "w");
	int rowNbr = 0;
	while(fgets(row, size, myfile)){ //get file row (until \n or EOF) and add 0 to string


		////WE need to check when the one in front is not moving! the one in front can also move diagonal!!
		//printf("%s",row);
		if(strstr(row,"R ")){ //
			string = strstr(row, "R ")+2;
			NbrOfSteps = atoi(string);
			for(int i = 0;i<NbrOfSteps;i++){
				diagmove = MoveRight(aTailCoordX[0], aTailCoordY[0], &HeadCoordX, &HeadCoordY, &aTailCoordX[0], &aTailCoordY[0],0);
//				for(int j=1;j<10;j++){
//					diagmove = MoveRight(aTailCoordX[i], aTailCoordY[i], &aTailCoordX[i-1], &aTailCoordY[i-1], &aTailCoordX[i], &aTailCoordY[i],diagmove);
//				}
//				AddNewPointToArray(pPoints,&NbrOfPoints,aTailCoordX[0],aTailCoordY[0]);
			}
		}else if(strstr(row,"L ")){ //
			string = strstr(row, "L ")+2;
			NbrOfSteps = atoi(string);
			for(int i = 0;i<NbrOfSteps;i++){
				diagmove = MoveLeft(aTailCoordX[0], aTailCoordY[0], &HeadCoordX, &HeadCoordY, &aTailCoordX[0], &aTailCoordY[0],0);
				for(int j=1;j<10;j++){
					diagmove = MoveLeft(aTailCoordX[i], aTailCoordY[i], &aTailCoordX[i-1], &aTailCoordY[i-1], &aTailCoordX[i], &aTailCoordY[i],diagmove);
				}
				AddNewPointToArray(pPoints,&NbrOfPoints,aTailCoordX[8],aTailCoordY[8]);
			}
		}else if(strstr(row,"U ")){ //
			string = strstr(row, "U ")+2;
			NbrOfSteps = atoi(string);
			for(int i = 0;i<NbrOfSteps;i++){
				diagmove = MoveUp(aTailCoordX[0], aTailCoordY[0], &HeadCoordX, &HeadCoordY, &aTailCoordX[0], &aTailCoordY[0],0);
//				for(int j=1;j<10;j++){
//					diagmove = MoveUp(aTailCoordX[i], aTailCoordY[i], &aTailCoordX[i-1], &aTailCoordY[i-1], &aTailCoordX[i], &aTailCoordY[i],diagmove);
//				}
				AddNewPointToArray(pPoints,&NbrOfPoints,aTailCoordX[8],aTailCoordY[8]);
			}
		}else if(strstr(row,"D ")){ //
			string = strstr(row, "D ")+2;
			NbrOfSteps = atoi(string);
			for(int i = 0;i<NbrOfSteps;i++){
				diagmove = MoveDown(aTailCoordX[0], aTailCoordY[0], &HeadCoordX, &HeadCoordY, &aTailCoordX[0], &aTailCoordY[0],0);
				for(int j=1;j<10;j++){
					diagmove = MoveDown(aTailCoordX[i], aTailCoordY[i], &aTailCoordX[i-1], &aTailCoordY[i-1], &aTailCoordX[i], &aTailCoordY[i],diagmove);
				}
				AddNewPointToArray(pPoints,&NbrOfPoints,aTailCoordX[8],aTailCoordY[8]);
			}
		}

//					printf("tailX %d, tailY %d pos %d\n",aTailCoordX[9],aTailCoordY[9],NbrOfPoints);
//					printf("headX %d, headY %d pos %d\n",HeadCoordX,HeadCoordY,NbrOfPoints);

			int areasize = 40;

			if(rowNbr ==1){
			for(int i=areasize;i>-areasize;i--){
				for(int j=-areasize;j<areasize;j++){
					if((HeadCoordY==i) && (HeadCoordX==j)){
						fprintf(myfile2,"H ");
					}else if(aTailCoordY[0]==i && (aTailCoordX[0]==j)){
						fprintf(myfile2,"1 ");
					}else if(aTailCoordY[1]==i && (aTailCoordX[1]==j)){
						fprintf(myfile2,"2 ");
					}else if(aTailCoordY[2]==i && (aTailCoordX[2]==j)){
						fprintf(myfile2,"3 ");
					}else if(aTailCoordY[3]==i && (aTailCoordX[3]==j)){
						fprintf(myfile2,"4 ");
					}else if(aTailCoordY[4]==i && (aTailCoordX[4]==j)){
						fprintf(myfile2,"5 ");
					}else if(aTailCoordY[5]==i && (aTailCoordX[5]==j)){
						fprintf(myfile2,"6 ");
					}else if(aTailCoordY[6]==i && (aTailCoordX[6]==j)){
						fprintf(myfile2,"7 ");
					}else if(aTailCoordY[7]==i && (aTailCoordX[7]==j)){
						fprintf(myfile2,"8 ");
					}else if(aTailCoordY[8]==i && (aTailCoordX[8]==j)){
						fprintf(myfile2,"9 ");
					}else{
						fprintf(myfile2,". ");
					}
				}
				fprintf(myfile2,"\n");
			}
			}
			rowNbr++;
	}

	printf("headX %d, headY %d pos %d\n",HeadCoordX,HeadCoordY,NbrOfPoints);
	printf("Tailx %d, TailY %d pos %d\n",aTailCoordX[8],aTailCoordY[8],NbrOfPoints);

	return EXIT_SUCCESS;
}
