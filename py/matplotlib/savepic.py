#!coding:utf-8

import matplotlib.pyplot as plt
import numpy as np

x = np.arange(1,5)
#print type(x)      #<type 'numpy.ndarray'>
plt.plot(x, x*1.5, label='Normal')
plt.plot(x, x*3.0, label='Fast')
plt.plot(x, x/3.0, label='Slow')
plt.legend(loc='upper right')     #图例显示的位置
#plt.show()
plt.savefig('plot123.png')

