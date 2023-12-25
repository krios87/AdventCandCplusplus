/*
 ============================================================================
 Name        : 2022_day5.c
 Author      : Kristofer
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MaxStackSize 60 //no more than 60 items can be stacked

//https://adventofcode.com/2022/day/5
typedef struct{
	char array[MaxStackSize];
	int size;
} Stack;

void Stack_init(Stack* self){
	self->size = 0;
	memset(self->array,0,MaxStackSize*sizeof(char));
}

int addPosition(Stack* stack, char c,int position){

	if(stack->size > position){
		for(int i = stack->size; i >position; i--){
			stack->array[i] = stack->array[i-1];
		}
	}
	stack->array[position] = c;
	stack->size++;

	return 1;
}

int addTop(Stack* stack, char c){

	stack->array[stack->size]=c;
	stack->size++;

	return 1;
}

char getTop(Stack* stack){
	return stack->array[stack->size-1];
}

char removeTop(Stack* stack){

	char removed = 0;
	if(stack->size == 0){
		removed = 0;
	}else{
		removed = stack->array[stack->size-1];
		stack->array[--stack->size]=0;
	}

	return removed;
}
int main(void) {


	int NbrOfStacks = 10;
	Stack *Stacks = (Stack *)malloc(NbrOfStacks*sizeof(Stack));
	for(int i=0;i<NbrOfStacks;i++)
		Stack_init(&Stacks[i]);

	FILE *myfile;
	myfile = fopen("C:/Users/kristoferrosquist/Desktop/Training/Christmas_Calendar/2022/day5_input.txt", "r");
	char *row;
	int size = 500;
	row = malloc(size*sizeof(char));
	char *pItem;
	char *substring;

	int NumberMove, From, To;
	int finishedStack = 0;
	char removed;
	int sizeToRack =0;

		while(fgets(row, size, myfile)){ //get file row (until \n or EOF) and add 0 to string

			if(!finishedStack){ //before move commands fill the stacks
				pItem = strchr(row,'[');
				while(pItem){ //as long as we find [ we add character to stack
					addPosition(&Stacks[(pItem - row)/4],*(pItem+1),0); //each is 4 char wide, given as index
					pItem = strchr(pItem+=4,'[');
				}

				if(*row == 13){ //CR
					finishedStack = 1;
				}

			}else{
				//get number:
				substring = strstr(row, "move ")+5; //point to after "move ", atoi converts the first number in string.
				NumberMove = atoi(substring);

				//get from:
				substring = strstr(row, "from ")+5;
				From = atoi(substring)-1;

				//get to:
				substring = strstr(row, "to ")+3;
				To = atoi(substring)-1;


				sizeToRack = Stacks[To].size; //for solution2

				//Start moving!
				for(int i=0;i<NumberMove;i++){
					removed = removeTop(&Stacks[From]);
					//solution1:
					//addTop(&Stacks[To],removed);
					//solution2:
					addPosition(&Stacks[To],removed,sizeToRack);
				}

			}

		}

		for(int i=0;i<9;i++){
			printf("%c",getTop(&Stacks[i]));
		}

	return EXIT_SUCCESS;
}
