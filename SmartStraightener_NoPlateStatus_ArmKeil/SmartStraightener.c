//This is a variant of the other smartStraightener project in which no plate status/ plate closure variable is used, and real time is used


#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <time.h>
#include "SmartStraightener.h"


int tempError = 0;    // the difference between TARGET_TEMP and the average temperature of the last pass

bool start = false; //indicates whether a new pass has begun


//////////////////used for differentirating passes
bool tempDecreasing = false;
bool tempIncreasing = false;
bool trough = false;
bool crest = false;
bool closed = false;
bool plateClosureOccurred = false;
clock_t startTime;
clock_t currentTime;
////////////////////

passData currPass;
int currArrayIndex = 0;
float startTemp = 210;

void resetPass();
void readRecord(float temp, int time);
int findCurrPassStart(float temperatures[]);
float average(float temperatures[]);
bool isValidPass(float average, passData data);
void calculateTempError(float avgTemp);
float getTempError();
void adjustStartTemp(float* startTemp);
void checkPlateStatus();
clock_t getTime();
int getElapsedTime();

/*
Empties the array of records in preparation for reading the next pass
*/
void resetPass() {
	start = false;
	plateClosureOccurred = false;
	memset(currPass.passRecords, 0, sizeof(currPass.passRecords));  //clears the array of records in currPass
	currArrayIndex = 0;

	//if (numPass == SAVED_PASSES - 1)
	//{
	//	for (int i = 0; i < SAVED_PASSES - 1; i++) {
	//		passes[i] = passes[i + 1]; //delete oldest pass data to make room for new data
	//	}
	//}
}
/**
 * Reads in current temperature and timestamp
 */
void readRecord(float temp, int time) 
{
	if (!closed && start && plateClosureOccurred) //plates not closed
	{
		if (!currPass.dataCollected) {
			float avg = average(currPass.passRecords);
			currPass.dataCollected = true;
			bool isPass = isValidPass(avg, currPass);

			//If currPass is a valid pass, add it to the array of passes and calculate error
			if (isPass) {
				//passes[numPass] = &currPass;
				calculateTempError(avg);
			}
			//else if (!isPass) //???? 
			//{
			//	if (numPass <= SAVED_PASSES) {
			//		numPass--;
			//	}
			//}
		}
		resetPass();
	}
	if (!start) //plates closed
	{
		start = true;
		//if (numPass < SAVED_PASSES) //only increment numPass if there are fewer than 16 passdata datasets
		//{
		//	numPass++;
		//}
		//currPass.passNum = numPass; //set passNum for new pass
		currPass.dataCollected = false; //new passdata not yet saved	
	}
	if (start)  
	{
		record rec = { temp, time};
		currPass.passRecords[currArrayIndex] = rec;
		checkPlateStatus();
		++currArrayIndex;
	}

//	checkPlateStatus();
}

//this function probably not needed
//void findCurrPassStart()
//{
//	int i = currArrayIndex;
//	float secRec = currPass.passRecords[i].temperature;
//	float firstRec = currPass.passRecords[i - 1].temperature;
//	bool troughFound = false; //true when minimum temperature of pass is found
//	bool peakFound = false;   // true when maximum temperature of pass (at beginning of pass) is found
//	while (!troughFound || !peakFound)
//	{
//		if (firstRec > secRec)
//			troughFound = true;
//		if (troughFound && secRec > firstRec)
//			peakFound = true;
//		i--;
//		secRec = currPass.passRecords[i].temperature;
//		firstRec = currPass.passRecords[i - 1].temperature;
//	}
//}

int findCurrPassStart(float temperatures[])
{
	int i = currArrayIndex;
	float secRec = currPass.passRecords[i].temperature;
	float firstRec = currPass.passRecords[i - 1].temperature;
	bool troughFound = false; //true when minimum temperature of pass is found
	bool peakFound = false;   // true when maximum temperature of pass (at beginning of pass) is found
	while (!troughFound || !peakFound)
	{
		secRec = currPass.passRecords[i].temperature;
		firstRec = currPass.passRecords[i - 1].temperature;
		if (firstRec > secRec)
			troughFound = true;
		if (troughFound && secRec > firstRec)
			peakFound = true;
		i--;
	}
	return secRec;
}

/*
Infers whether the plates are closed based on the last three temperature readings 
*/
void checkPlateStatus() 
{
	if (currArrayIndex < 2) //if data collection just began, there's no way to tell whether plates are closed just from current temperature
		return;
	float currTemp = currPass.passRecords[currArrayIndex].temperature;
	float prevTemp = currPass.passRecords[currArrayIndex - 1].temperature;
	float prevPrevTemp = currPass.passRecords[currArrayIndex - 2].temperature;

	if (currTemp < prevTemp && prevTemp < prevPrevTemp) //this condition confirms that the temperature is decreasing, which, in theory, should indicate that the plates are closed
	{
		trough = false;
		crest = false;
		tempDecreasing = true;
		tempIncreasing = false;
		closed = true;
		plateClosureOccurred = true;
	}
	if (currTemp > prevTemp && prevTemp > prevPrevTemp) //this condition confirms that the temperature is increasing
	{
		trough = false;
		crest = false;
		tempDecreasing = false;
		tempIncreasing = true;
	}
	if (currTemp > prevTemp && prevTemp < prevPrevTemp) //this condition confirms that a local minimum temperature has been reached, (and it is stored in the variable "prevTemp")
	{
		trough = true;
		crest = false;
		tempDecreasing = false;
		tempIncreasing = false;
		closed = true;
		plateClosureOccurred = true;
	}
	if (currTemp < prevTemp && prevTemp > prevPrevTemp) //ATTENTION!: not getting to this point, likely due to duplicate temperature level readings; we'll need something more robust
	{
		trough = false;
		crest = true;
		tempDecreasing = false;
		tempIncreasing = false;
		closed = false;
	}
}

/*
find average temperature during the last pass
*/
float average(float temperatures[])
{
	float sumTemp = 0;
	float temperature = 0;
	int startIndex = findCurrPassStart(temperatures); //Find index of first record in pass
	int i = startIndex;
	int index = 0;
	//temperature = temperatures->array[i].temperature;
	temperature = temperatures[i];
	while (temperature > 0)
	{
		sumTemp += temperature;
		//temperature = temperatures->array[++i].temperature;
		i++;
		index = i * sizeof(record);
		temperature = temperatures[index];
	}
	float average = sumTemp / i;
	return average;
}
/*
* Checks of a set of records is a valid pass
*/
bool isValidPass(float average, passData data)
{
	float max = 0;
	if (data.passRecords != NULL)
	{
		max = data.passRecords[0].temperature; //initialize max temperature to the first temperature
		for (int i = 0; i < ARRAY_SIZE; i++) {
			if (data.passRecords[i].temperature > max)
				max = data.passRecords[i].temperature;
		}
	}
	float delta = max - average;
	if (delta < MIN_TEMP_DROP)
		return false;
	return true;
}
/*
* calculates the difference between the target temperature and the average temperature
*/
void calculateTempError(float avgTemp)
{
	int target = TARGET_TEMP;
	float tErr = (target - avgTemp);
	tempError = tErr;
}
/*
* Returns the difference between the target temperature and the average temperature
*/
float getTempError()
{
	return tempError;
}

void adjustStartTemp(float* startTemp)
{
	startTemp = startTemp + tempError;
	if (startTemp > MAX_TEMP)
		startTemp = MAX_TEMP;
	if (startTemp < MIN_TEMP)
		startTemp = MIN_TEMP;
}

clock_t getTime()
{
	return clock();
}

int getElapsedTime()
{
	(getTime() - startTime) / CLOCKS_PER_SEC;
}

