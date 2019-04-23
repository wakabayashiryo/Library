import numpy as np

class OutputLayer:
    def __init__(self):
        pass
    def Softmax(self,x):
        exp_a = np.exp(x)
        exp_sum = np.sum(exp_a)
        return exp_a/exp_sum

    def Softmax2(self,x):
        arr_max = np.max(x)
        exp_a = np.exp(x-arr_max)
        exp_sum = np.sum(exp_a)
        return exp_a/exp_sum

ol = OutputLayer()
Z1 = np.array([0.3,2.9,4.0])
print(ol.Softmax2(Z1))
print(np.sum(ol.Softmax2(Z1)))
