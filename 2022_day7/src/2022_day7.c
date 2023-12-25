/*
 ============================================================================
 Name        : 2022_day7.c
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

//https://adventofcode.com/2022/day/7
void insertionSort(int arr[], int n)
{
    int i, key, j;
    for(i = 1; i < n; i++){
        key = arr[i];
        j = i - 1;
        while(j >= 0 && arr[j] > key){
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

struct Node{
	int NbrOfChilds;
	struct Node* children[10]; //max 10 children. Could dynamically reallocate memory instead
	struct Node* parent;
	char name[20];
	int value;
};

struct Node* createNewNode(char* name){

	struct Node* newNode = malloc(sizeof(struct Node));
	newNode->NbrOfChilds=0;
	newNode->value = 0;
	strcpy(newNode->name,name);
	return newNode;
}

void createChildNode(struct Node* pParent, char* name){
	struct Node* newNode = createNewNode(name);
	pParent->children[pParent->NbrOfChilds++] = newNode;
	newNode->parent = pParent;
}

struct Node* getChildFromName(struct Node* node, char* name){
	struct Node* returnNode = NULL;
	if(node->NbrOfChilds > 0){
		for(int i=0;i<node->NbrOfChilds;i++){
			if(!strcmp(name,node->children[i]->name)){
				returnNode = node->children[i];
				break;
			}
		}
	}
	return returnNode;
}

void SaveValuesInArray(struct Node* node,int* valueArray, int* myarrayIndex){

	valueArray[*myarrayIndex] = node->value;
	(*myarrayIndex)++;

	if(node->NbrOfChilds>0){
		for(int i=0;i<(node->NbrOfChilds);i++){
			SaveValuesInArray(node->children[i],valueArray,myarrayIndex);
		}
	}
}

int main(void) {

	FILE *myfile;
	myfile = fopen("../../../Advent/2022_day7.txt", "r");
	char *row;
	int size = 500;
	row = malloc(size*sizeof(char));
	int i;
	struct Node* root;
	char* string;

	struct Node* currentNode;
	struct Node* tmpNode;
	root = createNewNode("\\");

	currentNode = root;
	i=0;
	while(fgets(row, size, myfile)){ //get file row (until \n or EOF) and add 0 to string

			if(strstr(row, "cd ..")){ //move step back/up (set current to parent)
				currentNode = currentNode->parent;
			}else if(strstr(row,"cd ") && (i!=0)){ //move step down (skip first row)
				string = strstr(row, "cd ")+3;
				currentNode = getChildFromName(currentNode,string);
			}else if(strstr(row,"dir ")){  //create directory if it does not exist
				//printf("row: %s",row);
				string = strstr(row, "dir ")+4;
				if(getChildFromName(currentNode,string)==NULL){
					createChildNode(currentNode,string);
				}
			} else if(isdigit((int)*row)){ //store value in currentNode and its parents
				int value = atoi(row);
				currentNode->value += value;

				tmpNode = currentNode;
				while(tmpNode->parent){//if parent then add value to parent
					tmpNode = tmpNode->parent;
					tmpNode->value +=value;
				}
			}

			i++;
	}


	int mysize = 10000;
	int myArray[mysize];
	int sum =0;
	memset(myArray,0,sizeof(myArray));

	int arrayIndex = 0;
	SaveValuesInArray(root,myArray,&arrayIndex);

	//part1
	for(int i=0;i<arrayIndex;i++){
		sum+=(myArray[i]<=100000)*myArray[i]; //summarize only less than 100000
	}

	printf("sum: %d \n",sum);

	//part2
	insertionSort(myArray,arrayIndex);//sort only for up to arrayIndex (nbr of folders)
	int unused = 70000000-root->value;
    int neededSpace = 30000000 - unused;

	for(int i=0;i<arrayIndex;i++){
		if(myArray[i]>neededSpace){
			printf("result2: %d \n",myArray[i]);
			break;
		}
	}

	return EXIT_SUCCESS;
}
