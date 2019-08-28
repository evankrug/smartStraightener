
""" This Program simulates the temperature curve for a single pass of a hair straightener through a single section of hair.
Values that may need to be adjusted by the programmer include the STARTING_TEMP and TIME_INTERVAL.
Values unique to the user of the hair straightener which must be learned include the hairLength and passSpeed """

import random
import time
import Settings
import sqlite3
from threading import Thread

class TempSimulation():
    def __init__(self, learnAlg):
        #constant values (which we may need to modify later)
        #self.event = event #?????????????
        self.MAX_TEMP = 220 #Maximum allowed temperature of straightener plates
        self.MIN_TEMP = 140 # Minimum allowed temperature of straightener plates
        self.startTemp = 210 # temperature of straightener plates at the beginning of the session
        self.TIME_INTERVAL = 0.1  # time (in seconds) between temperature readings 

        self.learn = learnAlg # StraightenerLearn Object

        #values unique to the user 
        self.hairLength = 20  #length of hair
        #self.passSpeed = 2  #rate at which the straightener is passed down a section of hair
        #hairType = null  # *IN PROGRESS* Hair texture, which will affect temperature and time required

        #THIS VALUE IS FOR SIMULATION PURPOSES ONLY: lowest temperature that the straightener plates reach due to heat loss due to contact with the hair (the vertex of the curve)
        self.lowestTemp = 170 
        #self.lowestTemp = self.startTemp - 40

    #calculates time it takes to pass straightener over section of hair once given a speed hair length
    def calculatePassTime(self, speed, length):
       return length / speed

#   Calculates the coefficient for the temperature vs time equation
    def calculateCoefficient(self, timeForPass):
        return (self.startTemp - self.lowestTemp) / ((timeForPass / 2) ** 2)

    #Returns the temperature of the plates at a given time
    def tempCheck(self, currentTime, timeForPass, coeff):
        return coeff * (currentTime - (timeForPass / 2)) ** 2 + self.lowestTemp

    #Changes the starting plate temperature by the given tempChange
    def changeStartTemp(self, tempChange):
        self.startTemp += tempChange
        if self.startTemp > self.MAX_TEMP:
            self.startTemp = self.MAX_TEMP
        self.lowestTemp = self.startTemp - 40 #??????
        if self.startTemp < self.MIN_TEMP:
            self.startTemp = self.MIN_TEMP
        if self.lowestTemp < self.MIN_TEMP:
            self.lowestTemp = self.MIN_TEMP

       

    def run(self): 
        conn = sqlite3.connect('simdata.db')
        curs = conn.cursor()
        curs.execute("DROP TABLE if exists simdata")
        curs.execute("""CREATE TABLE simdata (
            time real,
            temperature real,
            closed integer
            )""")

       #This is an infinite loop simulating passes of varying speeds
        while True:
            startTime = time.time()
            passSpeed = random.randint(1, 5)
            #passSpeed = 2
            #numRecord = 1
            passTime = self.calculatePassTime(
                passSpeed, self.hairLength)  # get the pass time

            # get the coefficient for the temperature curve equation
            coefficient = self.calculateCoefficient(passTime)
            
            #insert into the data table the starting temperature and a 0 to indicate the plates are open
            currentTime = time.time() - startTime
            currentTemp = self.tempCheck(time.time() - startTime, passTime, coefficient)
            curs.execute("INSERT INTO simdata (time, temperature, closed) VALUES (?, ?, ?)", (currentTime, currentTemp, 0))
           # conn.commit()
          #  numRecord = numRecord + 1
    
            print("Start temp: {0}".format(self.startTemp))

            #This loops simulates a single pass from the time the plates close until they reopen
            while time.time() - startTime <= passTime:
                currentTime = time.time() - startTime
                currentTemp = self.tempCheck(time.time() - startTime, passTime, coefficient)
                # print current temperature
                print("Temp: {0} degrees Celsius, Time: {1} seconds.".format(currentTemp, currentTime))

                #insert into the data table the temperature at a given time, as well as a 1 to indicate the plates are closed
                curs.execute(
                    "INSERT INTO simdata (time, temperature, closed) VALUES (?, ?, ?)", (currentTime, currentTemp, 1))
            #    conn.commit()
              #  numRecord = numRecord + 1
                time.sleep(self.TIME_INTERVAL -
                           ((time.time() - startTime) % self.TIME_INTERVAL))

            #curs.execute("SELECT * FROM simdata")
           # print(curs.fetchall())  #Print all data 

            #from StraightenerLearn import StraightenerLearn
            #learn = StraightenerLearn()
            conn.commit()
            tempError = self.learn.getTempError()

            try:
                if tempError != 0:
                    self.changeStartTemp(tempError)
            except NameError:
                print("name error")


# if __name__ == "__main__":
#     simulation = TempSimulation()
#     simulation.main()
  


