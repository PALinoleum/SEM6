import numpy as np
import matplotlib.pyplot as plt
import math
import scipy 
import scipy.optimize as opt
import scipy.integrate as integrate
from scipy.optimize import curve_fit

def f_T(x):
  return np.sin(np.exp(0.2*x))

def fi_1(x):
  return np.sin(x)
def fi_2(x):
  return np.sin(4*x)
def fi_3(x):
  return np.sin(9*x)

vec_x=[]#точки х
vec_y=[]#точки y точные
for i in range(1,12):
  vec_y.append([f_T(i)])
  vec_x.append(i)
print('y точные= ',vec_y)#y точные
print('y точные')
plt.plot(vec_y)
plt.show()
sigma_const=0.1 

vec_sigma=[]#сигмы i
for i in range(1,12):
  vec_sigma.append([i*sigma_const*0.1])
print('sigma=',vec_sigma)#sigma- погрешность


vec_y_s=[]#y с погрешостью
y=[]#тоже но в одномерном списке
for i in range(0,11):
  vec_y_s.append([ vec_sigma[i][0] + vec_y[i][0] ])#sigma_const*i*0.1
  y.append( vec_sigma[i][0] + vec_y[i][0])
print('vec_y_s = ',vec_y_s)#sigma+y точное
print('y с погрешостью')
plt.plot(vec_y_s)
plt.show()
K=np.zeros((11, 11))
for i in range(0,11):
  K[i][i]=pow(pow(vec_sigma[i][0],-1),2)

F=np.zeros((11, 3 ))#F 11x3

for i in range(0,11):
  F[i][0]=fi_1(vec_x[i])
  F[i][1]=fi_2(vec_x[i])
  F[i][2]=fi_3(vec_x[i])
print('F= ',F)
#Найдем a
#a=np.linalg.inv(F.transpose()* K*F)*F.transpose()*K*vec_y_s
a1=F.transpose().dot(K)
a2=a1.dot(F)
a3=np.linalg.inv(a2)
a4=a3.dot(F.transpose())
a5=a4.dot(K)
a=a5.dot(vec_y_s)
print('\n a= ',a)
res=[a[0]*fi_1(i)+a[1]*fi_2(i)+a[2]*fi_3(i) for i in range(1,12)]#z=\sum_{i=1}^n a_i *\varphi_i(x)
print('z функция')
plt.plot(res)
plt.show()
fig, ax = plt.subplots()
ax.scatter(vec_x, vec_y_s)
ax.plot(vec_x, y, 'r', lw=2, label="Theoretical")
ax.plot(vec_x, res, 'b', lw=2, label="Fit")
ax.legend()
ax.set_xlim(0, 12)
ax.set_xlabel(r"$x$", fontsize=18)
ax.set_ylabel(r"$y$", fontsize=18)
plt.show()
