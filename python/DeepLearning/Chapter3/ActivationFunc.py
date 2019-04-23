import numpy as np
import matplotlib.pylab as pl

class ActivationFunc:
    def __init__(self):
        pass
    def StepFunc(self,x):
        return np.array(x > 0,dtype=np.int)

    def Sigmoid(self,x):
        return 1/(1+np.exp(-x))

    def Relu(self,x):
        return np.maximum(0,x)

x = np.arange(-5.0,5.0,0.1)
point = ActivationFunc()
y = point.Relu(x)
# y = point.StepFunc(x)
pl.plot(x,y)
pl.ylim(-0.1,5)
pl.show()