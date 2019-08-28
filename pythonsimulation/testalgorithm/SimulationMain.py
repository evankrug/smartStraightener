
from threading import Thread

from StraightenerLearn import StraightenerLearn
learn = StraightenerLearn()

def runLearning():
    learn.run()

def runSimulation():
    from TempSimulation import TempSimulation
    sim = TempSimulation(learn)
    sim.run()


Thread(target=runSimulation).start()
Thread(target=runLearning).start()


