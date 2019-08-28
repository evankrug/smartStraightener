
#Import Library
import sqlite3
import random
import time
from threading import Thread

#need to differentiate passes; perhaps compare each and every data point, and once one is lower than the previous, that indicates new pass?

class StraightenerLearn(): 
    def __init__(self):
        self.TARGET_TEMP = 185  # goal is to keep the plates at this temperature
        self.tempError = 0
       # self.event = event

    #Handle data
    # def loadAllData(self, conn):
    #     curs = conn.cursor()
    #     curs.execute("SELECT * FROM simdata")
    #     lines = curs.fetchall()
    #     dataset = list(lines)
    #     for i in range(len(dataset)):
    #         dataset[i] = [float(x) for x in dataset[i]]
    #     return dataset

    #determines the index of the first temperature reading of the previous "pass"
    def findPassStart(self, numTemps, tempList):
        i = numTemps - 2
        j = numTemps - 1

        startFound = False
        troughFound = False
        endFound = False

        while not startFound:
            temp2 = tempList[j]
            temp1 = tempList[i]
            if endFound and troughFound and not startFound:
                if temp2 > temp1:
                    startFound = True
                    return j
            else:
                if endFound and not troughFound:
                    if temp1 > temp2:
                        troughFound = True
                if not endFound:
                    if temp2 > temp1: 
                        endFound = True
            i = i - 1
            j = j - 1


    #find average temperature during the last pass
    def average(self, conn):
        curs = conn.cursor()
        curs.execute("SELECT temperature FROM simdata")
        tempTotalList = curs.fetchall()
        tempTotal = len(tempTotalList)

        passStartIndex = self.findPassStart(tempTotal, tempTotalList)
        
        #need to determine number of temperatures in the table and limit the selection to the last set and then fetchall
        curs.execute("SELECT temperature FROM simdata limit {0} , {1}".format(
            passStartIndex, tempTotal))
        passTemperatureList = curs.fetchall()

        sumTemp = sum([pair[0] for pair in passTemperatureList])
        numTemps = len(passTemperatureList)
        average = sumTemp / numTemps
        return average

    #calculates the difference between the target temperature and the average temperature
    def calculateTempError(self, avgTemp):
        tErr = self.TARGET_TEMP - avgTemp
        self.tempError = tErr

    #Returns the difference between the target temperature and the average temperature
    def getTempError(self):
        try:
            return self.tempError
        except AttributeError:
            return 0

    def run(self):
        runNum = 0
        plateopenings = 1
        while True: 
            conn = sqlite3.connect('simdata.db')
           # dataset = self.loadAllData(conn)         
            
           # print('Loaded data file {0} with {1} rows'.format(conn, len(dataset)))
           # print('Data: {0}'.format(dataset))

            #if plate is open, find the average temperature among all previous data points since the last time 
            # the plates were closed
            curs = conn.cursor()
            curs.execute("SELECT closed, COUNT(*) FROM simdata WHERE closed = 0 GROUP BY closed")
            openCount = curs.fetchall()
            if not openCount:
                pass
            else:
                openTuple = openCount[0]
                numOpen = openTuple[1]
                if(numOpen > plateopenings):
                    avgTemp = self.average(conn) #find average temperature on last pass
                    self.calculateTempError(avgTemp) #determine the difference between the target temperature and average temperature
                    plateopenings += 1
            

              #  print('Data: {0}'.format(dataset))
            #time.sleep(0.1)

""" if __name__ == "__main__":
    alg = StraightenerLearn()
    alg.main() """


learn = StraightenerLearn()

def runSimulation():
    from TempSimulation import TempSimulation
    sim = TempSimulation(learn)
    sim.run()
def runLearning():
    learn.run()

Thread(target=runSimulation).start()
Thread(target=runLearning).start()

