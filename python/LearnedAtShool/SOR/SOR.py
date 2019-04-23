import numpy as np
import matplotlib.pyplot as plt

Debug = 0

omega = 2.0    #Acceleration factor 
Fai_e = 50.0    #Default Field Value

Num_Of_Iter = 20    #Number of Iteration

Fai_upper = 100.0   #Upper Field Value
Fai_lower = 0.0     #Lower Field Value

Fai_a = 0           #Definition of Elements
Fai_b = 1
Fai_c = 2
Fai_d = 3

x = np.arange(0,Num_Of_Iter)            #Arrange from 0 to Number of Iteration on array
y = np.array([[Fai_e]*Num_Of_Iter]*4)   #Declare four arrays for Fai
# Fai_a = [0,1,2,3,....,Iteratioin]
# Fai_b = [0,1,2,3,....,Iteratioin]
# fai_c = [0,1,2,3,....,Iteratioin]
# fai_d = [0,1,2,3,....,Iteratioin]

for n in x-1:
    y[Fai_a][n+1] = y[Fai_a][n] + omega *((Fai_upper+y[Fai_b][n])/2.0-y[Fai_a][n])
    y[Fai_b][n+1] = y[Fai_b][n] + omega *((y[Fai_a][n+1]+y[Fai_c][n]+Fai_upper+Fai_lower)/4.0-y[Fai_b][n])
    y[Fai_c][n+1] = y[Fai_c][n] + omega *((y[Fai_b][n+1]+y[Fai_d][n]+Fai_upper+Fai_lower)/4.0-y[Fai_c][n])
    y[Fai_d][n+1] = y[Fai_d][n] + omega *((y[Fai_c][n+1]+Fai_e+Fai_upper+Fai_lower)/4.0-y[Fai_d][n])

if Debug == 1:
    print(y)

plt.ylim(-np.max(y) if (np.min(y)<0) else 0,np.max(y)+5)

plt.plot(x,y[Fai_a],'o-',color='r',label='Fai_a')
plt.plot(x,y[Fai_b],'o-',color='g',label='Fai_b')
plt.plot(x,y[Fai_c],'o-',color='b',label='Fai_c')
plt.plot(x,y[Fai_d],'o-',color='y',label='Fai_d')

plt.legend(loc="best")

plt.title("Successive Over-Relaxation(SOR method)")

plt.xlabel('Iteration(times)')

plt.ylabel('Fai(V/m)')

plt.grid(which='major',color='black',linestyle='--')
plt.grid(which='minor',color='black',linestyle='--')

message = "\
Condition\n\
omega:{0}\n\
Number of Iteration:{1}\
".format(str(omega),Num_Of_Iter)

plt.text(5.0,10,message)

plt.show()