/*
 ============================================================================
 Name        : 2022_day8.c
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

//https://adventofcode.com/2022/day/8

//not needed put in other function!
//int isLower(char** tree,int Columns, int Rows, int iCol, int iRow,char height){
//
//	int islower,isLowerLeft,isLowerRight,isLowerUp,isLowerDown;
//	isLowerLeft = isLowerRight = isLowerUp = isLowerDown = 1;
//
//	if((iCol==0) || (iRow==0) || (iCol==(Columns-1)) || (iRow==(Rows-1))){
//		islower = 1;
//	} else{
//
//		for(int i=iCol-1;i>-1;i--) //check left
//			isLowerLeft &= tree[i][iRow] < height;
//
//		for(int i=iCol+1;i<Columns;i++)//check right
//			isLowerRight &= tree[i][iRow] < height;
//
//		for(int i=iRow+1;i<Rows;i++)//check down
//			isLowerUp &= tree[iCol][i] < height;
//
//		for(int i=iRow-1;i>-1;i--)//check up
//			isLowerDown &= tree[iCol][i] < height;
//
//		islower = isLowerLeft | isLowerRight | isLowerUp | isLowerDown;
//	}
//	return islower;
//}

void program1(void);


void (*myprogramptr[2])(void) = {program1};

int CalcDist(char** tree,int Columns, int Rows, int iCol, int iRow,char height, int* visible){
	int calcDist, calcLeft,CalcRight,calcUp,calcDown,isEdge;
	int isvisible = 1;
	int isLowerLeft,isLowerRight,isLowerUp,isLowerDown;
	isLowerLeft = isLowerRight = isLowerUp = isLowerDown = 1;
	calcDist = calcLeft = CalcRight = calcUp = calcDown = 0;
	isEdge = (iCol==0) || (iRow==0) || (iCol==(Columns-1)) || (iRow==(Rows-1));

	if(!isEdge){

		//instead of 4 for loops set direction and start point and do 1 loop over which is looped 4 times
		for(int i=iCol-1;i>-1;i--){ //check left
			calcLeft++;
			if(tree[i][iRow] >= height){
				isLowerLeft = 0;
				break;
			}
		}

		for(int i=iCol+1;i<(Columns);i++){//check right
			CalcRight++;
			if(tree[i][iRow] >= height){
				isLowerRight = 0;
				break;
			}
		}

		for(int i=iRow+1;i<(Rows);i++){//check down
			calcDown++;
			if(tree[iCol][i] >= height){
				isLowerUp = 0;
				break;
			}
		}

		for(int i=iRow-1;i>-1;i--){//check up
			calcUp++;
			if(tree[iCol][i] >= height){
				isLowerDown = 0;
				break;
			}
		}
		isvisible = isLowerLeft | isLowerRight | isLowerUp | isLowerDown;
		calcDist = calcLeft * CalcRight * calcUp * calcDown;
	}

	*visible += isvisible;
	return calcDist;
}

int main(void) {
	FILE *myfile;
	char *row;
	int size = 5000;
	int rowIndex= 0;
	int NbrOfColumns =0;
	int NbrOfRows = 0;
	char **Map;

	row = malloc(size*sizeof(char));

	myfile = fopen("D:/DATA/Backup/ESS/Desktop/Training/Christmas_Calendar/2022/day8_input.txt", "r");
	//get map size and allocate memory
	while(fgets(row, size, myfile)){ //get file row (until \n or EOF) and add 0 to string
		if(rowIndex == 0){
			NbrOfColumns = strlen(row)-2; //length minus CR LF on my file
			Map = (char **) malloc(NbrOfColumns*sizeof(char*));
		}
		rowIndex++;
	}
	NbrOfRows = rowIndex;

	for(int i=0;i<NbrOfColumns;i++)
		Map[i] = (char *) malloc(NbrOfRows*sizeof(char));

	//store heights:
	rowIndex = 0;
	myfile = fopen("D:/DATA/Backup/ESS/Desktop/Training/Christmas_Calendar/2022/day8_input.txt", "r");
	while(fgets(row, size, myfile)){

		//save heights.
		for(int colIndex=0;colIndex<NbrOfColumns;colIndex++)
			Map[colIndex][rowIndex] = (*(row+colIndex)); //only relative value matters

		rowIndex++;
	}

	//assignment 1
	int countvisible = 0;
//	for(int j=0;j<(NbrOfRows);j++){  //not needed, in other function!
//		for(int i=0;i<(NbrOfColumns);i++){
//			countvisible += isLower(Map,NbrOfColumns, NbrOfRows, i, j,Map[i][j]);
//		}
//	}

	//assignment 2
	int maxdist = 0;
	int tempdist = 0;
	int tempCompare;
	for(int j=0;j<(NbrOfRows);j++){
		for(int i=0;i<(NbrOfColumns);i++){
			tempdist = CalcDist(Map,NbrOfColumns, NbrOfRows, i, j,Map[i][j],&countvisible);
			tempCompare = (tempdist>maxdist); //if true set tempdist otherwise maxdist
			maxdist = tempdist * tempCompare+(!tempCompare)*maxdist;
		}

	}

	printf("count: %d maxdist: %d ",countvisible,maxdist);
	return EXIT_SUCCESS;
}
