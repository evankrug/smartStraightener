#include "ht32f5xxxx_01.h"

#include <stdbool.h>
//#include <windows.h>
#include "SmartStraightener.h"


//simulates data

int main() {
	startTime = getTime();

	float temp = startTemp;
	int time = 0;
	
	//readRecord(temp, time);
	while (true) {
		adjustStartTemp(&startTemp);
		time = 0;
	
		readRecord(temp, time);
		while (temp > 140) {
			readRecord(temp, time);
			temp = temp - 3;
			time = getElapsedTime();
			Sleep(500);
		}
		while (temp < startTemp) {
			readRecord(temp, time);
			temp = temp + 2;
			time = getElapsedTime();
			Sleep(500);
		}
	}
}