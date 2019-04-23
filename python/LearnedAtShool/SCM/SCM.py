import numpy as np
import math as mt

class QnConfig:
    def __init__(self,A,B,r,z,Z):
        self.A = A
        self.B = B
        self.r = r
        self.z = z
        self.Z = Z

    def Pn_of_Point(self):
        X = 1/(mt.sqrt( mt.pow(self.r,2) + mt.pow(self.z - self.Z,2) ))
        Y = 1/(mt.sqrt( mt.pow(self.r,2) + mt.pow(self.z + self.Z,2) ))
        
        Pn = 1/(4*mt.pi*8.854e-12)*(X-Y)
        return Pn
  
    def Pn_of_Line(self):

        Lambda = 1

        O = self.B-self.z+mt.sqrt( mt.pow(self.r,2) + mt.pow(self.B - self.Z,2) )
        P = self.A-self.z+mt.sqrt( mt.pow(self.r,2) + mt.pow(self.A - self.Z,2) )
        Q = self.B+self.z+mt.sqrt( mt.pow(self.r,2) + mt.pow(self.B + self.Z,2) )
        R = self.A+self.z+mt.sqrt( mt.pow(self.r,2) + mt.pow(self.A + self.Z,2) )

        Pn = ( Lambda/(4*mt.pi*8.854e-12) )*mt.log( (O/P) * (Q/R) )
        
        return Pn

def Generate_Classes(n):
    obj = [QnConfig(1,1,1,1,1)] * n
    
    return obj

print(Point_Q1)
# Point_Q2 = QnConfig()
# Point_Q3 = QnConfig()
