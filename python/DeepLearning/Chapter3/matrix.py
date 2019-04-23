import numpy as np
import ActivationFunc as af

class CheckMatrix:
    def __init__(self):
        pass
    def DisplayMatrix(self,x):
        print("contents of dimension = \n"+str(x))
        print("Num of dimension = "+str(np.ndim(x)))
        print("Shape of dimension"+str(x.shape))
        print("")

    def CalucMatrix(self,x,z):
        print(x)
        print("  X  ")
        print(z)
        print("  =  ")
        print(np.dot(x,z))
        print(" ")

d1 = np.array([1,2,3,4])
d2 = np.array([[1,2],[3,4],[5,6]])
d3 = np.array([[1,2,3],[4,5,6]])

check = CheckMatrix()
check.DisplayMatrix(d1)
check.DisplayMatrix(d2)

check.CalucMatrix(d3,d2)
ac = af.ActivationFunc()

x = np.array([1.0,0.5])
W1 = np.array([[0.1,0.3,0.5],[0.2,0.4,0.6]])
B1 = np.array([0.1,0.2,0.3])

A1 = np.dot(x,W1)+B1
Z1 = ac.Sigmoid(A1)
print("nural caluc\n"+str(A1)+"\n"+str(Z1))