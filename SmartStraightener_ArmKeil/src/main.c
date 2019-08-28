#include "ht32f5xxxx_01.h"

#include <stdbool.h>
#include "smartStraightener.h"



int main()
{

	float temp = startTemp;
	int time = 0;
	bool plateStatus = false;

	readRecord(temp, time, plateStatus);
	while (true)
	{
		startTemp = startTemp + tempError;
		time = 0;
		plateStatus = false;
		readRecord(temp, time, plateStatus);
		plateStatus = true;
		while (temp > 140) {
			readRecord(temp, time, plateStatus);
			temp = temp - 3;
			time++;
		}
		while (temp < startTemp) {
			readRecord(temp, time, plateStatus);
			temp = temp + 2;
			time++;
		}
	}
	return 0;

}
