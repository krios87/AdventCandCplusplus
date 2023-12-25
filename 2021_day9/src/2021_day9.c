/*
 ============================================================================
 Name        : 2021_day9.c
 Author      : Kristofer
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include<string.h>

//https://adventofcode.com/2021/day/9

struct OceanDepth {
	int value;
	int isCandidate;
	int basinNumber;
};

void Depth_init(struct OceanDepth* self){
	self->value = 0;
	self->isCandidate=0;
	self->basinNumber=0;
}

struct OceanDepth* OceanDepth_create(){
	struct OceanDepth* result = (struct OceanDepth*) malloc(sizeof(struct OceanDepth));
	Depth_init(result);
	return result;
}

void RemoveCandidate(struct OceanDepth* Candidate){
	Candidate->isCandidate=0;
}

int ReturnVal(struct OceanDepth* Depth){
	return Depth->value;
}

int CheckPreviousDepth(struct OceanDepth** Depth,int i, int j){
	int returnval;
	if(i==0){
		returnval= 9;
	}else{
		returnval = Depth[i-1][j].value;
	}

	return returnval;
}

int CheckUpperDepth(struct OceanDepth **Depth,int i, int j){
	int returnval;
	if(j==0){
		returnval= 9;
	}else{
		returnval = Depth[i][j-1].value;
	}

	return returnval;
}

int CheckBasin(struct OceanDepth** Depth,int Columns, int Rows, int i, int j,int basinNumber){

	int retval;
	retval = 0;
	if((i<0) || (j<0) || (i>=Columns) || (j>=Rows)){
		retval = 0;
	}else if((Depth[i][j].value==9) ||(Depth[i][j].basinNumber!=0) ){ //dont count values 9 + ones which basin already have been set.
		retval = 0;
	} else{
		Depth[i][j].basinNumber = basinNumber;

		retval =  1;
		retval += CheckBasin(Depth,Columns,Rows,i,j-1,basinNumber);//check upper
		retval += CheckBasin(Depth,Columns,Rows,i-1,j,basinNumber);//check left
		retval += CheckBasin(Depth,Columns,Rows,i,j+1,basinNumber);//check lower
		retval += CheckBasin(Depth,Columns,Rows,i+1,j,basinNumber);//check right
	}


	return retval;
}

void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are greater than key, to one position ahead
		of their current position */
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}


int main(void) {
	FILE *myfile;
			myfile = fopen("../../../Advent/2021_day9.txt", "r");
			char *buff;
			int size = 10000;
			buff = malloc(size*sizeof(char));
			int i,j,k,nbrRows;
			j=0;
			int Arraysize = 110;
			struct OceanDepth **Depth = (struct OceanDepth **)malloc(Arraysize*sizeof(struct OceanDepth));
			for(i=0;i<Arraysize;i++)
				Depth[i]=(struct OceanDepth *)malloc(Arraysize*sizeof(struct OceanDepth));

			//[Arraysize][Arraysize];

			for(i=0;i<Arraysize;i++){
				for(j=0;j<Arraysize;j++){
					Depth_init(&Depth[i][j]);
				}
			}

			i=j=nbrRows=0;
			int linelength=0;
			int value;
			int xvalue=9;
			int yvalue=9;
			while(fgets(buff, size, myfile)) { //get file row (until \n)
				linelength= strlen(buff)-2;
				for(i=0;i<linelength;i++){
					char digit[2]={'\0','\0'};
					strncpy(digit,buff+i,1);
					value = atoi(digit);

					Depth[i][j].value=value;
					xvalue = CheckPreviousDepth(Depth,i,j);
					yvalue = CheckUpperDepth(Depth,i,j);

					Depth[i][j].isCandidate=1;

					if(xvalue > value){
						if(i>0){
							RemoveCandidate(&Depth[i-1][j]);
						}

					}else{
						RemoveCandidate(&Depth[i][j]);
					}
					if(yvalue>value){

						if(j>0){
							RemoveCandidate(&Depth[i][j-1]);
						}
					}else{
						RemoveCandidate(&Depth[i][j]);
					}
				}

				j++;
				nbrRows=j;
			}

			int sum = 0;

			for(j=0;j<nbrRows;j++){
				for(i=0;i<linelength;i++){
					if(Depth[i][j].isCandidate){
						sum += Depth[i][j].value +1;
					}
				}
			}


			//part 2
			int Basins[1000];
			for(i=0;i<1000;i++)
				Basins[i]=0;

			k=0;
			for(j=0;j<nbrRows;j++){
				for(i=0;i<linelength;i++){
					if(Depth[i][j].isCandidate){
							Basins[k] = CheckBasin(Depth,linelength,nbrRows,i,j,1);
							k++;
					}
				}
			}

			int biggest[3];
			biggest[0]=biggest[1]=biggest[2] = 0;



			for(i=0;i<k;i++){
				if(Basins[i]>=biggest[0]){
					biggest[2]=biggest[1];
					biggest[1]=biggest[0];
					biggest[0]=Basins[i];
				}
			}

			insertionSort(Basins,k);
			int calc = Basins[k-1]*Basins[k-2]*Basins[k-3];
			printf("\nbiggest: %d %d %d", Basins[k-1],Basins[k-2], Basins[k-3]);
			printf("\ncalc: %d", calc);

	return EXIT_SUCCESS;
}
