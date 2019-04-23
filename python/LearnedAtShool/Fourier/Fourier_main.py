import matplotlib.pyplot as plt
import numpy as np

import Fourier_Series as FS

Num_of_Iter = int(input("input N>>"))

wave  = FS.FourierFunctions_with_PI(N=Num_of_Iter,Lambda=4)
wave2 = FS.FourierFunctions_with_PI(N=Num_of_Iter,Lambda=4)
wave3 = FS.FourierFunctions_with_PI(N=Num_of_Iter,Lambda=4)

(x,y) = wave.Square_Wave()
(x2,y2) = wave2.Sawtooth_Wave()
(x3,y3) = wave3.Triangle_Wave()

y2 = np.dot(y2,0.5)     #Square Wave of Amplitude was reduce half

# plt.plot(x,y,'-',color='blue',label='N={}'.format(Num_of_Iter))
plt.plot(x,y,'-',color='red',label='Square Wave')
plt.plot(x2,y2,'-',color='blue',label='Sawtooth Wave')
plt.plot(x3,y3,'-',color='green',label='Triangle Wave')

plt.title("Fourier Series")
plt.xlabel('Anlge(°)')
plt.ylabel('Amplitude(-)')

plt.grid(which='major',color='black',linestyle='--')
plt.grid(which='minor',color='black',linestyle='--')

plt.legend(loc='best')

plt.show()