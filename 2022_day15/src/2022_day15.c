/*
 ============================================================================
 Name        : 2022_day15.c
 Author      : Kristofer
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//https://adventofcode.com/2022/day/15
typedef struct{
	int SensorX;
	int SensorY;
	int distance;
	int BeakonX;
	int BeakonY;

} Sensor;

int calcdistance(Sensor* sensor,int CoordX, int CoordY){
	int distance = 0;

	distance = abs(CoordX - sensor->SensorX)+abs(CoordY - sensor->SensorY); 

	return distance;
}

int main(void) {
	FILE *myfile;
		myfile = fopen("../../../Advent/2022_day15.txt", "r");
		char *row;
		int size = 5000;
		row = malloc(size*sizeof(char));
		int i;
		int minX = 0;
		int minY = 0;
		int maxX = 0;
		int maxY = 0;
		int nbrOfSensors = 0;

		//get number of sensors
		while(fgets(row, size, myfile)){
			nbrOfSensors++;
		}

		Sensor Sensors[nbrOfSensors];
		memset(Sensors,0,sizeof(Sensors));


		myfile = fopen("../../../Advent/2022_day15.txt", "r");

		i = 0;
		while(fgets(row, size, myfile)){ //get file row (until \n or EOF) and add 0 to string
			char *line;// = row;
			strtok(row, ":");
			line = strtok(NULL, ":");
			int sensorX = atoi(strstr(row,"Sensor at x=")+12);
			int sensorY = atoi(strstr(row,"y=")+2);

			int beakonX = atoi(strstr(line,"x=")+2);
			int beakonY = atoi(strstr(line,"y=")+2);
			int distance = abs(sensorX-beakonX)+ abs(sensorY-beakonY);
			Sensors[i].BeakonX = beakonX;
			Sensors[i].BeakonY = beakonY;
			Sensors[i].SensorX = sensorX;
			Sensors[i].SensorY = sensorY;
			Sensors[i].distance = distance;
			i++;

			//getmaxmin values:
			int TestX = sensorX - distance;
			int TestY = sensorY - distance;
			int TestMaxX = sensorX + distance;
			int TestMaxY = sensorY + distance;

			if(TestX < minX){
				minX = TestX;
			}

			if(TestY < minY){
				minY = TestY;
			}

			if(maxX < TestMaxX){
				maxX = TestMaxX;
			}

			if(maxY <TestMaxY){
				maxY = TestMaxY;
			}
		}


		int sum = 0;
		int ycoord = 2000000;
		//int ycoord = 10;




		for(int x=minX;x<=maxX;x++){
			for(int Sens=0; Sens<nbrOfSensors;Sens++){
				if(calcdistance(&Sensors[Sens],x,ycoord)<=Sensors[Sens].distance){ //check if within distance for any of the sensors
					sum++;

					for(int k=0;k<nbrOfSensors;k++){
						if((Sensors[k].BeakonX == x) && (Sensors[k].BeakonY == ycoord)){ //remove spots with beakons
							sum--;
							break;
						}
					}

					break;
				}
			}
		}

		//int searchXmax=20;
		//int searchYmax=20;

		int searchXmax=4000000;
		int searchYmax=4000000;

		int ymax,xmax,xdir,ydir;
		int found = 0;
		int done = 0;
		for(int Sens=0; Sens<nbrOfSensors;Sens++){

			for(int dir=0; dir<4; dir++){

					if(dir == 0){
						xdir = 1;
						ydir = 1;
					}else if (dir ==1){
						xdir = -1;
						ydir = 1;
					} else if (dir ==2){
						xdir = 1;
						ydir = -1;
					} else if (dir ==3){
						xdir = -1;
						ydir = -1;
					}

					if(done == 1){
						break;
					}

					//search just around the edges of each sensor distance (to closest beakon)
					//some searched more than needed but there should only be one solution
					for(int ydist=0;ydist<=(Sensors[Sens].distance+1);ydist++){
						found = 0;
						xmax = Sensors[Sens].SensorX + xdir*(Sensors[Sens].distance+1-ydist);
						ymax = Sensors[Sens].SensorY + ydir*(ydist);

						for(int Sens2=0; Sens2<nbrOfSensors;Sens2++){

							if(calcdistance(&Sensors[Sens2],xmax,ymax)<=Sensors[Sens2].distance){ //check if within distance for any of the sensors
								found = 1;
								break;
							}
						}

						if((found == 0) && (0<=xmax) &&(xmax<=searchXmax) && (0<=ymax) &&(ymax <=searchYmax)){

							printf("result2 %ld \n",((long)xmax)*((long)4000000)+(long)ymax);
							done = 1;
							break;
						}



					}



			}
		}



		printf("result1: %d\n",sum);
	return EXIT_SUCCESS;
}
