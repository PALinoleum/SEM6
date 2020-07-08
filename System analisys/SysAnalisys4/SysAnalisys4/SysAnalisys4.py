import numpy as np
import matplotlib.pyplot as plt
import math
import scipy 
import scipy.optimize as opt
import scipy.integrate as integrate

# вектор измерений
R=np.array([
            [3.4937157447E+01],
            [3.9217826917E+01],
            [4.3946907873E+01],
            [6.0966165241E+01],
            [1.5956946183E+02],
            [2.4303455087E+02],
            [3.5896107983E+02],
            [5.1724348631E+02],
            [7.3046973513E+02],
            [1.3928491165E+03],])
# диагональные элементы корреляционной матрицы
k11 =   4.8850591911E-05
k22 =   6.1568024980E-05
k33 =   7.7256954633E-05
k44 =   1.4869168126E-04
k55 =   1.0187841552E-03
k66 =   2.3623444723E-03
k77 =   5.1530493014E-03
k88 =   1.0699149788E-02
k99 =   2.1343240958E-02
k1010 = 7.7474502401E-02
# корреляционная матрица
Kv = np.zeros((10, 10))
di = np.diag_indices_from(Kv)
Kv[di] = [k11, k22, k33, k44, k55, k66, k77, k88, k99, k1010]
# дельта
delta = 0.000001
# оцениваемые параметры
x1 = 3
x2 = 10

x1add = x1+delta
x2add = x2+delta

x1sub = x1-delta
x2sub = x2-delta

# система ДУ
def dx1_dt(t, x1,x2):
  return np.log(x2*x2 + 2) + t
def dx2_dt(t, x1,x2):
  return x2/2 + np.abs(x1) * np.sqrt(3)
# измеряемая функция
def s(x1,x2):
  return 3*x1 + 2*x2

# шаг интегрирования
step = 1.0E-2
# количество шагов измерений
arr_N = [50, 60, 70, 100, 200, 250, 300, 350, 400, 500]

# Метод Рунге Кутта (4 порядок точности)
def RK45(f1, f2, x10, x20, step, N):#N должно быть на 1 больше чем max элемент  в массиве arr_N
  h=step 
  H=h/2
  X1=[]
  X2=[]
  x1 = [x10] 
  x2 = [x20] 
  for i in range(N): 
    k11 = f1((i+1)*h, x1[-1], x2[-1]) 
    k12 = f2((i+1)*h, x1[-1], x2[-1]) 
    k21 = f1((i+1)*h + H, x1[-1] + H*k11, x2[-1] + H*k12) 
    k22 = f2((i+1)*h + H, x1[-1] + H*k11, x2[-1] + H*k12) 
    k31 = f1((i+1)*h + H, x1[-1] + H*k21, x2[-1] + H*k22) 
    k32 = f2((i+1)*h + H, x1[-1] + H*k21, x2[-1] + H*k22) 
    k41 = f1((i+1)*h + h, x1[-1] + h*k31, x2[-1] + h*k32) 
    k42 = f2((i+1)*h + h, x1[-1] + h*k31, x2[-1] + h*k32) 
    x1.append(x1[-1] + (h/6)*(k11 + 2*k21 + 2*k31 + k41)) 
    x2.append(x2[-1] + (h/6)*(k12 + 2*k22 + 2*k32 + k42)) 
    for j in range(len(arr_N)):
      if( arr_N[j]==(i+1) ):
        X1.append(x1[-1] + (h/6)*(k11 + 2*k21 + 2*k31 + k41)) 
        X2.append(x2[-1] + (h/6)*(k12 + 2*k22 + 2*k32 + k42)) 
  return X1, X2 


def Get_vectors2():
  NN = max(arr_N)+1
  s1_add = []
  X11,X22 = RK45(dx1_dt, dx2_dt, x1add, x2, step, NN) 
  for i in range(len(X11)):
    s1_add.append(s(X11[i], X22[i]))

  s1_sub = []
  X11,X22 = RK45(dx1_dt, dx2_dt, x1sub, x2, step, NN) 
  for i in range(len(X11)):
    s1_sub.append(s(X11[i], X22[i]))

  s2_add = []
  X11, X22 = RK45(dx1_dt, dx2_dt, x1, x2add, step, NN) 
  for i in range(len(X11)):
    s2_add.append(s(X11[i], X22[i]))

  s2_sub = []
  X11,X22 = RK45(dx1_dt, dx2_dt, x1, x2sub, step, NN) 
  for i in range(len(X11)):
    s2_sub.append(s(X11[i], X22[i]))

  ss= []
  X11, X22 = RK45(dx1_dt, dx2_dt, x1, x2, step, NN) 
  for i in range(len(X11)):
    ss.append(s(X11[i],X22[i]) )
  return s1_add, s1_sub, s2_add, s2_sub, ss


def Get_L(s1_add,s1_sub,s2_add,s2_sub):
  L = []  
  ddq = 1/(2*delta)
  L = np.zeros((2, len(s1_add) ))
  for i in range( len(s1_add) ):
    tx1 = s1_add[i]-s1_sub[i]
    tx2 = s2_add[i]-s2_sub[i]
    tx1 = tx1*ddq
    tx2 = tx2*ddq
    L[0][i] = tx1
    L[1][i] = tx2
  return L

def Get_a(Kv,L,dR):
  a1 = np.dot(L,Kv)
  a2 = np.dot(a1,L.transpose())
  a3 = np.linalg.inv(a2)  #K_тетта - корреляционная матрица оцениваемых параметров
  a4 = np.dot(a3,L)
  a5 = np.dot(a4,Kv)
  dq = a5.dot(dR)
  return  dq, a3

##########################################################################################################
Kv = np.linalg.inv(Kv) # Kv в -1
k = 0
coun = 50
while(k < coun):
  k = k + 1
  s1_add, s1_sub, s2_add, s2_sub, ss = Get_vectors2()
  L = Get_L(s1_add,s1_sub,s2_add,s2_sub)
  
  dR = np.zeros((10,1))
  for i in (range(len(ss))):
    dR[i][0] = R[i][0]-ss[i]
  
  a, K_o = Get_a(Kv,L,dR)  #delta teta - величина подшагивания

  md = np.sqrt(a[0][0]*a[0][0]+a[1][0]*a[1][0]) 
  x1 = x1 + a[0][0] 
  x2 = x2 + a[1][0] 
  x1add = x1 + delta
  x2add = x2 + delta
  x1sub = x1 - delta
  x2sub = x2 - delta
  if(md < 10E-6):   #если модуль вектора меньше погрешности
    break

print("Количество итераций = {}".format(k))
print('Оцениваемые параметры:\nx_01 = ', x1,';  x_02 = ', x2)
print('Вектор подшагивания Δϴ = ', md)
print("Корреляционная матрицу погрешностей оценки неизвестных параметров K_ϴ:\n", K_o)