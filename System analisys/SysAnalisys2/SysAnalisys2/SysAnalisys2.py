import numpy as np
import matplotlib.pyplot as plt
import math
import scipy 
import scipy.optimize as opt
import scipy.integrate as integrate

global vvv

def f0(x):
  return (-0.2*x**3+1.8*x**2-1.5*x+1.3)*0.2

def f(xi):
    a=0
    b=10
    K=(0.02*(-0.5*b**4+6*b**3-7.5*b**2+13*b))-(0.02*(-0.5*a**4+6*a**3-7.5*a**2+13*a))
    return((0.02*(-0.5*xi**4+6*xi**3-7.5*xi**2+13*xi))-(0.02*(-0.5*a**4+6*a**3-7.5*a**2+13*a)))/K-vvv

my_size = 5000#1000000
V = np.random.uniform(size=my_size)
dd=[]
for i in range(len(V)):
  vvv=V[i]
  dd.append(opt.root(f,3).x)

a = 0
b = 5

x_axis = np.linspace(a,b) 
plt.plot(x_axis,np.apply_along_axis(f0,0,x_axis))
plt.show()
print("k =",integrate.quad(f0,a,b)[0])

ni = [dd[i][0]for i in range(len(V))]

plt.hist(ni,math.ceil(np.log2(my_size)*4))
plt.show()