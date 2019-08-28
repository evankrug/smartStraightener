
//#include <stdio.h>
//#include "sqlite3.h"

typedef int bool;
#define false 0
#define true 1

typedef struct
{
    double temperature;
    double time;
    bool closed;
} record;
typedef struct {
    record *passRecords;
    int passNum;
} passData;
const int SAVED_PASSES = 16;
const int TARGET_TEMP = 185;
passData passes[16];
int tempError = 0;
int passNum = 0;

record makeRecord(double temp, double time, bool closed)
{
    record rec = {temp, time, closed};
    return rec;
}
passData makePass(record rec, int passNum)
{
    passes[passNum].passRecords = *rec;
}

void addPassData(passData passTemps)
{
    passes[passNum++] = passTemps;
}

int findPassStart(int numTemps, int tempList[])
{
    int i = numTemps - 2;
    int j = numTemps - 1;
    bool startFound = false;
    bool troughFound = false;
    bool endFound = false;

    while (!startFound)
    {
        int temp2 = tempList[j];
        int temp1 = tempList[i];
        if (endFound && troughFound && !startFound)
        {
            if (temp2 > temp1)
                startFound = true;
            return j;
        }
        else
        {
            if (endFound && !troughFound)
                if (temp1 > temp2)
                    troughFound = true;
            if (!endFound)
                if (temp2 > temp1)
                    endFound = true;
        }
        i = i - 1;
        j = j - 1;
    }
}
    //find average temperature during the last pass
    double average()
    {
        // curs = conn.cursor()
        // curs.execute("SELECT temperature FROM simdata")
        //  tempTotalList = curs.fetchall()
        //  tempTotal = len(tempTotalList)

        //int passStartIndex = findPassStart(tempTotal, tempTotalList);

        //need to determine number of temperatures in the table and limit the selection to the last set and then fetchall
        //        curs.execute("SELECT temperature FROM simdata limit {0} , {1}".format(
        //          passStartIndex, tempTotal))
        //      passTemperatureList = curs.fetchall()

    double sumTemp = sum([pair[0] for pair in passTemperatureList]);
    int numTemps = len(passTemperatureList);
    double average = sumTemp / numTemps;
    return average;
    }

    //calculates the difference between the target temperature and the average temperature
    void calculateTempError(avgTemp)
    {
        double tErr = TARGET_TEMP - avgTemp;
        tempError = tErr;
    }

    //Returns the difference between the target temperature and the average temperature
    double getTempError()
    {
        return tempError;
    }

    void run()
    {
        int plateopenings = 1;
        while(true)
        { 
            // conn = sqlite3.connect('simdata.db');   
            // curs = conn.cursor();
            // curs.execute("SELECT closed, COUNT(*) FROM simdata WHERE closed = 0 GROUP BY closed");
            // openCount = curs.fetchall();
            // if not openCount:
            //     pass
            // else:
            //     openTuple = openCount[0];
            //     numOpen = openTuple[1];
            //     if(numOpen > plateopenings):
            //         avgTemp = self.average(conn) //find average temperature on last pass
            //         self.calculateTempError(avgTemp) //determine the difference between the target temperature and average temperature
            //         plateopenings += 1;
        }
    }

