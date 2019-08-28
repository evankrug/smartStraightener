#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#include "smartStraightener.h"

passData currPass = {0};
int currArrayIndex = 0;
passData* passes[SAVED_PASSES]; //POSSIBLY UNNECESSARY
int tempError = 0; // the difference between TARGET_TEMP and the average temperature of the last pass
int numPass = -1;  
float startTemp = 210;
bool start = false;

void resetPass()
{
	start = false;
	memset(currPass.passRecords, 0, sizeof(currPass.passRecords));  //clears the array of records in currPass
	
	currArrayIndex = 0;

	if (numPass == (SAVED_PASSES - 1)) // -1????
	{
		for (int i = 0; i < SAVED_PASSES - 1; i++)
		{
			passes[i] = passes[i + 1]; //delete oldest pass data to make room for new data
		}
	}
}
/**
 * Reads in current temperature and timestamp
 */
void readRecord(float temp, int time, bool closed)
{
	if (!closed && start)
	{
		if (!currPass.dataCollected) {
			float avg = average(currPass.passRecords);
			currPass.dataCollected = true;
			bool isPass = isValidPass(avg, currPass);

			//If currPass is a valid pass, add it to the array of passes and calculate error
			if (isPass) {
				passes[numPass] = &currPass;
				calculateTempError(avg);
			}
			else if (!isPass) //???? 
			{
				if (numPass <= SAVED_PASSES)
				{
					numPass--;
				}
			}
		}
		resetPass();
	}
	if (closed && !start)
	{
		start = true;
		if (numPass < SAVED_PASSES) //only increment numPass if there are fewer than 16 passdata datasets
		{
			numPass++;
		}
		currPass.passNum = numPass; //set passNum for new pass
		currPass.dataCollected = false; //new passdata not yet saved
	}
	if (closed && start)
	{
		record rec = { temp, time, closed };
		currPass.passRecords[currArrayIndex++] = rec;
		//insertArray(&currPass.passRecords, rec); //insert new record into current array
	}
}
/*
find average temperature during the last pass
*/
float average(record * records)
{
	float sumTemp = 0;
	float temperature = 0;

	int i = 0;
	int index = 0;
	temperature = records[i].temperature;
	while (temperature > 0)
	{
		sumTemp += temperature;
		i++;
		index = i * sizeof(record);
		temperature = records[index].temperature;
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
	if (data.passRecords[0].temperature != NULL)  //!!?
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