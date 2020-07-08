#!/usr/bin/env python
# coding: utf-8

# In[57]:


import numpy as np
order = 3
x = np.array([
    (7.0, 7.0),
    (5.0, 12.0),
    (7.0, 15.0),
    (2.0, 1.0),
    (11.0, 7.0),
    (3.0, 2.0),
    (3.0, 5.0),
    (9.0, 15.0),
    (3.0, 15.0),
    (7.0, 8.0),
    (4.0, 14.0),
    (5.0, 10.0)
])
y = np.array([
   383.9852410,
   787.7938352,
   1671.2846123,
   13.3291853,
   583.8121339,
   32.8034594,
   115.0882527,
   2125.4422674,
   772.1392667,
   527.2359452,
   883.1937554,
   572.7850655
])
F = x
for i in range(order+1):
    for j in range(order+1-i):
        F = np.hstack((F,x[:,0].reshape(len(x),1)**i*x[:,1].reshape(len(x),1)**j))
F = F[:,3:]
Y = y.reshape(len(x),1)
hat_Y = [0,0,0,0,0,0,0,0,0,0,0,0]
a = np.linalg.inv(F.transpose()@F)@F.transpose()@hat_Y
hat_Y = F@a
av_Y = sum(Y)/len(Y)
Q = sum((y[i]-av_Y)**2 for i,_ in enumerate(y))
QR = sum((hat_Y[i]-av_Y)**2 for i,_ in enumerate(hat_Y))
Qost = sum((hat_Y[i]-y[i])**2 for i,_ in enumerate(hat_Y))

print("порядок полинома = ",order)
print("очередность степеней в a (первое число - степень х1, второе - степень х2):")
for i in range(order+1):
    for j in range(order+1-i):
        if i+j:
            print(i,j)
print("a=",a.reshape(1,len(a)))
print("по QR R^2= ",QR/Q)
print("по Qost R^2= ",1-Qost/Q)


