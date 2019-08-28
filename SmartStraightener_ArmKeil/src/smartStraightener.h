#ifndef SMART_STRAIGHTENER_H_
#define SMART_STRAIGHTENER_H_

#include <stdbool.h>
//#include "C:\Users\245845\Projects\SmartStraig\src\ht32_board_config.h"
//#include "ht32_board_config.h"


#define INITIAL_CAPACITY  3 //the inital size of an array of data
#define SAVED_PASSES  16    //the number of previous passes the system will save data from
#define ARRAY_SIZE  50
#define TARGET_TEMP  185 //The ideal average temperature per pass (in degrees C)
#define MIN_TEMP_DROP  10 //The minimum the temperature must drop when the plates closed
							  //for it to be considered a valid pass

//data format for a temperature at a given time (along with whether the iron plates are closed or not)
typedef struct
{
	float temperature;
	int time;
	bool closed;
} record;

//contains an array of records for a single pass along with the passNum, which uniquely identifies the pass
typedef struct
{
	record passRecords[ARRAY_SIZE];
	int passNum;
	bool dataCollected;
} passData;

extern passData* passes[SAVED_PASSES]; //array holds the data from the most recent 16 passes
extern int tempError;             // the difference between TARGET_TEMP and the average temperature of the last pass
extern int numPass;               //tracks the number of passes that have occurred

extern bool start; //indicates whether a new pass has begun
extern passData currPass;
extern int currArrayIndex;
extern float startTemp;

void resetPass();
void readRecord(float temp, int time, bool closed);
float average(record * temperatures);
bool isValidPass(float average, passData data);
void calculateTempError(float avgTemp);
float getTempError();

#endif