#include <stdio.h>
#include <stddef.h>
int const INITIAL_CAPACITY = 3; //the inital size of an array of data
int const SAVED_PASSES = 16;    //the number of previous passes the system will save data from;;
int const TARGET_TEMP = 185; //The ideal average temperature per pass (in degrees C)
int const MIN_TEMP_DROP = 10; //The minimum the temperature must drop when the plates closed
                              //for it to be considered a valid pass

typedef enum 
{
    false,
    true
} bool;

//data format for a temperature at a given time (along with whether the iron plates are closed or not)
typedef struct
{
	double temperature;
	double time;
	bool closed;
} record;
typedef struct
{
    record *array;
    size_t used;
    size_t size;
} Array;

//contains an array of records for a single pass along with the passNum, which uniquely identifies the pass
typedef struct
{
    Array passRecords;
    int passNum;
	bool dataCollected;
} passData;

passData* passes[16]; //array holds the data from the most recent 16 passes
int tempError = 0;             // the difference between TARGET_TEMP and the average temperature of the last pass
int numPass = -1;               //tracks the number of passes that have occurred
//single pass variables
bool start = false; //indicates whether a new pass has begun
//int currArraySize = 0;
Array currArr;
passData currPass;
//int currArrayIndex = 0;
//int capacity = INITIAL_CAPACITY;

void resetPass();
void readRecord(double temp, double time, bool closed);
double average(Array *temperatures);
bool isValidPass(double average, passData data);
void calculateTempError(avgTemp);
double getTempError();
void initArray(Array* a, size_t initialSize);
void insertArray(Array* a, record element);
void freeArray(Array* a);

void resetPass()
{
    start = false;
    //currArraySize = 0;
    //currArrayIndex = 0;
    //int capacity = INITIAL_CAPACITY;
	freeArray(&currPass.passRecords); //clear currPass passrecords for new pass
    if (numPass == SAVED_PASSES - 1) // -1????
    {
        for(int i = 0; i < SAVED_PASSES - 1; i++)
        {
            passes[i] = passes[i+1]; //delete oldest pass data to make room for new data
        }
    }
}
/**
 * Reads in current temperature and timestamp
 */
void readRecord(double temp, double time, bool closed)
{
    if (!closed && start)
    {
		if (currPass.dataCollected == false) {
			//double avg = average(currPass); //find average temperature of the newly-completed pass
			double avg = average(&currPass.passRecords);
			currPass.dataCollected = true;
			//double avg = average(numPass);
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
			initArray(&currPass.passRecords, INITIAL_CAPACITY); //initialize array
			//freeArray(&currPass.passRecords); //clear currPass passrecords for new pass
			
			//currArr = passes[numPass]->passRecords;  //new pass
			//passes[numPass]->passNum = numPass; //set passNum for new pass
			//passes[numPass]->dataCollected = false; //new passdata not yet saved
			//initArray(&currArr, currArraySize); //insert element into existing array

		
    }
    if (closed && start)
    {
        record rec = {temp, time, closed};
		insertArray(&currPass.passRecords, rec); //insert new record into current array
 
    }
}
/*
find average temperature during the last pass
*/
double average(Array *temperatures)
{
    double sumTemp = 0;
	double temperature = 0;
	/*
	for (int i = 0; i < temperatures->size; i++) {
		temperature = temperatures->array[i].temperature;
		sumTemp += temperature;
	}
	*/
	int i = 0;
	temperature = temperatures->array[i].temperature;
	while (temperature >= 0)
	{	
		sumTemp += temperature;
		temperature = temperatures->array[++i].temperature;
	}
	//sumTemp += data.passRecords.array[i].temperature;
	//sumTemp += (*(record *)&data.passRecords.array[i]).temperature; //???
	
	
    double average = sumTemp / i;
    return average;
}
/*
* Checks of a set of records is a valid pass
*/
bool isValidPass(double average, passData data)
{
	double max = 0;
	if (data.passRecords.array != NULL)
	{
		max = data.passRecords.array[0].temperature; //initialize max temperature to the first temperature
		for (int i = 0; i < data.passRecords.size; i++) {
			if (data.passRecords.array[i].temperature > max)
				max = data.passRecords.array[i].temperature;
		}
	}
    double delta = max - average;
    if (delta < MIN_TEMP_DROP)
        return false;
    return true;
}
/*
* calculates the difference between the target temperature and the average temperature
*/
void calculateTempError(double avgTemp)
{
    int target = TARGET_TEMP;
    double tErr = (target - avgTemp);
    tempError = tErr;
}
/*
* Returns the difference between the target temperature and the average temperature
*/
double getTempError()
{
    return tempError;
}

/**
* Initializes an array
*/
void initArray(Array *a, size_t initialSize)
{
    a->array = (record *)malloc(initialSize * sizeof(record));
    a->used = 0;
    a->size = initialSize;
}

/**
* Inserts new element into the given array
*/
void insertArray(Array *a, record element)
{
    // a->used is the number of used entries, because a->array[a->used++] updates a->used only *after* the array has been accessed.
    // Therefore a->used can go up to a->size
    if (a->used == a->size)
    {
        a->size *= 2;
        a->array = (record *)realloc(a->array, a->size * sizeof(record));
    }
    a->array[a->used++] = element;
}
/**
* Frees space occupied by the given array
*/
void freeArray(Array *a)
{
    free(a->array);
    a->array = NULL;
    a->used = a->size = 0;
}

int main()
{
	double temp = 210;
	double time = 0;
	bool plateStatus = false;
	readRecord(temp, time, plateStatus);
    while (true)
    {
		time = 0;
		plateStatus = false;
		readRecord(temp, time, plateStatus);
		plateStatus = true;
		while (temp > 140) {
			readRecord(temp, time, plateStatus);
			temp = temp - 3;
			time++;
		}
		while (temp < 205) {
			readRecord(temp, time, plateStatus);
			temp = temp + 2;
			time++;
		}
    }
    return 0;
}

/**
* Adds record to the array of recordsand increases the array capacity if necessary
* /
// void push(record *arr, int index, record value, int *size, int *capacity)
// {
//     if (*size > *capacity)
//     {
//         realloc(arr, sizeof(arr) * 2);
//         *capacity = sizeof(arr) * 2;
//     }
//     arr[index] = value;
//     *size = *size + 1;
// }
//resets pass variables

//int findPassStart(int numTemps, int tempList[])
//{
//	int i = numTemps - 2;
//	int j = numTemps - 1;
//	bool startFound = false;
//	bool troughFound = false;
//	bool endFound = false;
//
//	while (!startFound)
//	{
//		int temp2 = tempList[j];
//		int temp1 = tempList[i];
//		if (endFound && troughFound && !startFound)
//		{
//			if (temp2 > temp1)
//				startFound = true;
//			return j;
//		}
//		else
//		{
//			if (endFound && !troughFound)
//				if (temp1 > temp2)
//					troughFound = true;
//			if (!endFound)
//				if (temp2 > temp1)
//					endFound = true;
//		}
//		i = i - 1;
//		j = j - 1;
//	}
//}
*/
