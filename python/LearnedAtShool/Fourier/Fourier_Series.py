import matplotlib.pyplot as plt
import numpy as np
import math as mt

class FourierFunctions_with_PI:
    def __init__(self,N,Lambda):
        self.N = N
        Half_Num_of_Array = Lambda / 2
        self.Angle = np.arange(-(360+1)*Half_Num_of_Array,(360+1)*Half_Num_of_Array)
        self.Yaxis = np.array([0.0]*(360+1)*Lambda)
        
    def Sawtooth_Wave(self):
        for n in range(1,self.N+1):
            for (i,theta) in enumerate(self.Angle):
                self.Yaxis[i] += (mt.pow(-1,n+1)/n)*mt.sin(n*mt.pi*theta/180.0)

        return self.Angle,np.dot(self.Yaxis,2)

    def Triangle_Wave(self):
        for n in range(1,self.N+1):
            for (i,theta) in enumerate(self.Angle):
                self.Yaxis[i] += 2*(1-mt.pow(-1,n))/(mt.pow(n,2)*mt.pow(mt.pi,2))*mt.cos(n*mt.pi*theta/180.0)
        
        return self.Angle,(0.5 - self.Yaxis)

    def Square_Wave(self):
        for n in range(1,self.N+1):
            for (i,theta) in enumerate(self.Angle):
                self.Yaxis[i] += (1-mt.pow(-1,n))/(n*mt.pi)*mt.sin(n*mt.pi*theta/180.0)
        
        return self.Angle,(0.5 + self.Yaxis)



class FourierFunctions_with_2L:
    def __init__(self,N,Lambda):
        self.N = N

        self.l = np.arange(-Lambda,Lambda,step=0.01)
        self.Yaxis = np.array([0.0]*(2*Lambda*100))
        
    def Square_Wave(self):
        for n in range(1,self.N+1):
            for (i,x) in enumerate(self.l):
                self.Yaxis[i] += ((1-mt.pow(-1,n))/(n*mt.pi))*mt.sin(n*mt.pi*x)

        return self.l,(0.5 + self.Yaxis)
    