import numpy as np

class TheoryCircuit:
    def __init__(self,Weight,Bias):
        self.Weight = Weight
        self.Bias = Bias
        print("Weight={},Bias={}".format(Weight,Bias))
        print("Intialized")

    def Circuit(self,x1,x2):
        tmp = self.Weight[0]*x1 + self.Weight[1]*x2 + self.Bias
        if(tmp <= 0):
            return 0
        else :
            return 1
        
    class xor:
        def __init__(self,And,Or,nand):
            self.And = And
            self.Or = Or
            self.nand = nand
    
        def XOR(self,x1,x2):
            s1 = self.nand.Circuit(x1,x2)
            s2 = self.Or.Circuit(x1,x2)
            return self.And.Circuit(s1,s2)

w = np.array([0.5,0.5])
b = -0.7
AND = TheoryCircuit(w,b)

print(AND.Circuit(0,0))    
print(AND.Circuit(0,1))    
print(AND.Circuit(1,0))    
print(AND.Circuit(1,1))    

w = np.array([-0.5,-0.5])
b = 0.7
NAND = TheoryCircuit(w,b)
print(NAND.Circuit(0,0))    
print(NAND.Circuit(1,0))    
print(NAND.Circuit(0,1))    
print(NAND.Circuit(1,1))    

w = np.array([0.5,0.5])
b = -0.2
OR = TheoryCircuit(w,b)

XOR = TheoryCircuit.xor(AND,OR,NAND)
print(XOR.XOR(0,0))    
print(XOR.XOR(1,0))    
print(XOR.XOR(0,1))    
print(XOR.XOR(1,1))    
