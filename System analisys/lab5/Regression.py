from pprint import pprint

import numpy as np
order = 2
x = np.array([
    (8.0, 12.0),
    (7.0, 4.0),
    (9.0, 11.0),
    (5.0, 9.0),
    (8.0, 8.0),
    (4.0, 6.0),
    (5.0, 11.0),
    (10.0, 17.0),
    (6.0, 11.0),
    (4.0, 9.0),
    (5.0, 16.0),
    (4.0, 7.0),
])
y = np.array([
    434.6056050,
    99.4576048,
    426.5185028,
    219.8754453,
    261.1813246,
    113.2138322,
    293.0785722,
    811.3168444,
    325.0937345,
    209.3121888,
    506.5148699,
    140.8936827,
])
F = x
for i in range(order+1):
    for j in range(order+1-i):
        F = np.hstack((F,x[:,0].reshape(len(x),1)**i*x[:,1].reshape(len(x),1)**j))
F = F[:,3:]
pprint(F)
Y = y.reshape(len(x),1)
a = np.linalg.inv(F.transpose()@F)@F.transpose()@Y
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

