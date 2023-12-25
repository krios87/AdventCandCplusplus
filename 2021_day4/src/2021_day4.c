/*
 ============================================================================
 Name        : 2021_day4.c
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
//#include <bingo.h>
int getNumber(char buffer[],int rowlength, int numbers[]);

//https://adventofcode.com/2021/day/4

// Source file
struct Point {
   int x;
   int y;
};

int testfunc(struct Point* hej){
	return 0;
}

// Constructor (without allocation)
void Point__init(struct Point* self, int x, int y) {
  self->x = x;
  self->y = y;
 }

// Allocation + initialization (equivalent to "new Point(x, y)")
struct Point* Point__create(int x, int y) {
   struct Point* result = (struct Point*) malloc(sizeof(struct Point));
   Point__init(result, x, y);
   return result;
}

// Destructor (without deallocation)
void Point__reset(struct Point* self) {
}

// Destructor + deallocation (equivalent to "delete point")
void Point__destroy(struct Point* point) {
  if (point) {
     Point__reset(point);
     free(point);
  }
}

// Equivalent to "Point::x()" in C++ version
int Point__x(struct Point* self) {
   return self->x;
}

// Equivalent to "Point::y()" in C++ version
int Point__y(struct Point* self) {
   return self->y;
}


//matrix type:

struct BingoBoard {
	int matrix[5][5];
	int crosses[5][5]; //set to 1 from 0 if number is found, should be initialized to 0
	int hasBingo;
};

// Constructor (without allocation)
void Board_init(struct BingoBoard* self) {
	int i,j;

	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			self->matrix[i][j] = 0;
			self->crosses[i][j] = 0;
		}
	}
	self->hasBingo = 0;
 }

// Allocation + initialization
struct BingoBoard* Board_create() {
   struct BingoBoard* result = (struct BingoBoard*) malloc(sizeof(struct BingoBoard));
   Board_init(result);
   return result;
}

int AddMatrix(struct BingoBoard* board, int matrix[5][5], int size){
	int i,j;
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			board->matrix[i][j] = matrix[i][j];
		}
	}
	return 0;
}

int FindNumber(struct BingoBoard* board, int number){
	int found;
	int i,j;
	found = 0;
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			if(number == board->matrix[i][j]){
				found = 1;
				board->crosses[i][j] = 1;
				return found;
			}
		}
	}
	return found;
}

int CheckBingo(struct BingoBoard* board){
	int isBingorow,isBingocol;
	int i,j;

	isBingorow = isBingocol = 0;
	for(i=0;i<5;i++){
		isBingorow = 1;
		for(j=0;j<5;j++){
			isBingorow = (isBingorow && (board->crosses[i][j]));
		}
		if(isBingorow){
			board->hasBingo = 1;
			return isBingorow;
		}
	}


	for(i=0;i<5;i++){
		isBingocol = 1;
		for(j=0;j<5;j++){
			isBingocol = (isBingocol && (board->crosses[j][i]));
		}
		if(isBingocol){
			board->hasBingo = 1;
			return isBingocol;
		}
	}



	return isBingorow | isBingocol;
}

int calcsumNotChecked(struct BingoBoard* board,int boardnum){
	int sum;
	int i,j;
	sum = 0;

	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			if(board->crosses[i][j]==0){
				sum += board->matrix[i][j];
			}
		}
	}
	return sum;
}

int main(void) {

	FILE *myfile;
		myfile = fopen("../../../Advent/2021_day4.txt", "r");
		char buff[555];
		int i,j,k,l;
		int size = 10000;
		int valarray[size];
		int randomnumbers[size];
		int rowlength,matrixnumber;

		for(j=0;j<size;j++){
			randomnumbers[j]=0;
		}

		i=0;
		k=0;
		l=0;
		matrixnumber=0;
		int newrow = 0;
		int row = 0;
		int rowmatrix[5][5];
		int onerow[5];
		int sizematrix;
		int RandomNumbers;

		//struct Point *mypoint = Point__create(8,2);
		struct BingoBoard *Board[500];

		for(i=0;i<500;i++){

			Board[i] = Board_create();
		}


		j=0;
		while(fgets(buff, 555, myfile)) { //get file row (until \n)
			rowlength=strlen(buff);

			if(j==0){
				getNumber(buff,rowlength-1, randomnumbers); //rowlength -1 since we have both CR + LF in end of each line
				RandomNumbers = rowlength-1;
			}
			else{

				if(rowlength >5){//found a matrixstart
					if(newrow==1){
						row = 0;
					}
					getNumber(buff,rowlength-1, onerow);

					for(k=0;k<5;k++){
						rowmatrix[row][k] = onerow[k];

					}

					row++;
					newrow = 0;

				}
				else if (j>2){
					//make matrix class and array of these bingo brickor
					AddMatrix(Board[matrixnumber],rowmatrix,5);
					matrixnumber++;
					newrow=1;
				}

			}


			j++;
		}



		int leftNoBingo = matrixnumber;
		int lastResult,lastBingoBoard,multresult;
		lastResult =lastBingoBoard = multresult = 0;

		for(i=0;i<RandomNumbers;i++){

			for(j=0;j<matrixnumber;j++){
				FindNumber(Board[j],randomnumbers[i]);

				if((Board[j]->hasBingo) == 0){

					if (CheckBingo(Board[j])){

						leftNoBingo--;

						lastResult = calcsumNotChecked(Board[j],j);
						lastBingoBoard = j;
						multresult = lastResult * randomnumbers[i];


					}

				}

			}

		}
		printf("result: %d board %d multres %d \n",leftNoBingo,lastBingoBoard,multresult);



	return EXIT_SUCCESS;
}

int getNumber(char buff[],int rowlength, int numbers[]){ //function needs a new line at the end otherwise it wont get right value for last in matrix
	int i,k,l;
	i = k = l = 0;
	char number[3];
	int lastwasnumber = 0;
	number[0]=number[1]=number[2]=0;

	for(i=0;i<rowlength;i++){
		if(isdigit((int)buff[i])){

			number[k]=buff[i];
			k++;
			lastwasnumber = 1;
		}else if(lastwasnumber) {
			numbers[l] = atoi(number);
			l++;
			number[0]=number[1]=number[2]=0;
			k=0;
			lastwasnumber = 0;

		}


	}

	return l; //size
}
