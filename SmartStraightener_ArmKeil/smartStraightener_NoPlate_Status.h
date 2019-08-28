//This is a variant of the other smartStraightener project in which no plate status/ plate closure variable is used, and real time is used

#ifndef SMART_STRAIGHTENER_H_
#define SMART_STRAIGHTENER_H_

#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <time.h>

//#include "ht32_board_config.h"


#define INITIAL_CAPACITY  3 //the inital size of an array of data
#define SAVED_PASSES  16    //the number of previous passes the system will save data from
#define ARRAY_SIZE  50
#define TARGET_TEMP  185 //The ideal average temperature per pass (in degrees C)
#define MIN_TEMP_DROP  10 //The minimum the temperature must drop when the plates closed
							  //for it to be considered a valid pass
#define MAX_TEMP 220 
#define MIN_TEMP 140	



//data format for a temperature at a given time (along with whether the iron plates are closed or not)
typedef struct
{
	float temperature;
	int time;
} record;

//contains an array of records for a single pass along with the passNum, which uniquely identifies the pass
typedef struct
{
	record passRecords[ARRAY_SIZE];
	int passNum;
	bool dataCollected;
} passData;


extern int tempError;             // the difference between TARGET_TEMP and the average temperature of the last pass

extern bool start; //indicates whether a new pass has begun
extern passData currPass;
extern int currArrayIndex;
extern float startTemp;


//////////////////used for differentirating passes
bool tempDecreasing;
bool tempIncreasing;
bool trough;
bool crest;
bool closed;
bool plateClosureOccurred;
clock_t startTime;
clock_t currentTime;
////////////////////

void resetPass();
void readRecord(float temp, int time);
int findCurrPassStart(float temperatures[]);
void checkPlateStatus();
float average(float temperatures[]);
bool isValidPass(float average, passData data);
void calculateTempError(float avgTemp);
float getTempError();
void adjustStartTemp(float* startTemp);

clock_t getTime();

int getElapsedTime();



#endif