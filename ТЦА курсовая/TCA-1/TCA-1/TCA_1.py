import numpy as np
import math
from itertools import product

def specialPrint(a, varname):
  res = ""
  for i in range(0,len(a)):
    res += "{}{}".format(varname,i+1) if a[i]==1 or a[i]=='1'  else "!{}{}".format(varname,i+1)
  return res

def Dfunc(a, b):
  res = []
  for i in range(len(a)):
    if(b[i]=='0'):
      res.append(0)
    elif(b[i]=='1'):
      res.append(1)
  return res

def Tfunc(a, b):
  res = []
  for i in range(len(a)):
    if(a[i]!=b[i]):
      res.append(1)
    else:
      res.append(0)
  return res


f = open("C:/Users/D4rkn/source/repos/TCA-1/TCA-1/source/demofile.txt", "r", encoding='utf-8')

S_нач = []
S_кон = []
Z = []#Входной сигнал
W = []#Выходной сигнал

helparrD=[] #Функции возбуждения для D


print("Введите СКОЛЬКО ВСЕГО состояний = ",end="") #111111111!!!!!
n=int(f.readline())
print(n)

k = int(math.ceil(np.log2(int(n))))

print("k=",k)

S_нач = list(product('01',repeat=k))[:n]
print("Закодированные состояния: ",S_нач)

print("Введите количество начальных состояний = ",end="")
n = int(f.readline())
print(n,"\n")

helparrD=[]
helparrT=[]
R = []
for i in range(n):
  subarr1 = []
  subarr2 = []
  subarr3 = []
  subarrD = []
  subarrT = []

  print("Введите кол-во конечных состояний из S{} = ".format(i+1),end="")
  t = int(f.readline())
  print(t)
  
  print("Введите конечные состояния : ")
  for j in range(t):
    l = int(f.readline())
    print("\tS{} [{}]".format(l,"".join(S_нач[l-1])))
    subarr1.append(S_нач[l-1])
    subarrD.append(Dfunc(S_нач[i],S_нач[l-1]))
    subarrT.append(Tfunc(S_нач[i],S_нач[l-1]))
    #print(S_нач[i],S_нач[l-1],Dfunc(S_нач[i],S_нач[l-1]))

    print("\t\tВходной сигнал: ",end="")
    l = str(f.readline()).replace("\n","")
    print(l)
    subarr2.append(l)

    print("\t\tВыход (мили/мура): ",end="")
    l = list(str(f.readline()).replace("\n",""))
    print("".join(l))
    subarr3.append(l)

    if(l==["-"]):
      R.append(specialPrint(subarr1[-1], "t"))

  S_кон.append(subarr1)
  Z.append(subarr2)
  W.append(subarr3)
  helparrD.append(subarrD)
  helparrT.append(subarrT)
print("\nR={} (для автомата Мура)".format(R))

print(helparrD) #Матрица возбуждения для D триггера
print(helparrT) #Матрица возбуждения для T триггера

"""**Функции возбуждения D-триггеров:**"""

l=0
for kk in range(len(S_нач[0])):
  plus=False
  print("f{}=".format(l+1),end="")
  for ii in range(len(helparrD)):
    for jj in range(len(helparrD[ii])):
      #print(ii,jj,l)
      if(helparrD[ii][jj][l]==1):
        print("+" if plus==True else "",end="") #Это просто вывод плюса
        plus=True #не обращать внимание

        print(specialPrint(S_нач[ii], "t"),end="")
        print(Z[ii][jj] if Z[ii][jj]!='-' else "",end="")
  print("")
  l+=1

"""**Функции возбуждения T-триггеров:**"""

l=0
for kk in range(len(S_нач[0])):
  plus=False
  print("f{}=".format(l+1),end="")
  for ii in range(len(helparrT)):
    for jj in range(len(helparrT[ii])):
      #print(ii,jj,l)
      if(helparrT[ii][jj][l]==1):
        print("+" if plus==True else "",end="") #Это просто вывод плюса
        plus=True #не обращать внимание

        print(specialPrint(S_нач[ii], "t"),end="")
        print(Z[ii][jj] if Z[ii][jj]!='-' else "",end="")
  print("")
  l+=1

"""**Получение функций выходов:**"""

l=0
for kk in range(len(subarr3[0])):
  plus=False
  print("y{}=".format(l+1),end="")
  for ii in range(len(W)):
    for jj in range(len(W[ii])):
      #print(W[ii][jj])
      if(W[ii][jj]!=['-'] and W[ii][jj][l]=='1'):
        print("+" if plus==True else "",end="") #Это просто вывод плюса
        plus=True #не обращать внимание

        print(specialPrint(S_нач[ii], "t"),end="")
        print(Z[ii][jj] if Z[ii][jj]!='-' else "",end="")

  print("")
  l+=1

"""**🚮 ПОМОЙКА ->**"""
"""
Dfunc(list("110"), list("101"))

print(S_кон)
print(Z)
print(W)
print(helparrD)

def specialPrint(a, varname):
  res = ""
  for i in range(0,len(a)):
    if(a[i]==0 or a[i]=='0'):
      res += "¬{}{}".format(varname,i+1)
    elif(a[i]==1 or a[i]=='1'):
      res += "{}{}".format(varname,i+1)
  return res

f = open("/content/terms.txt", "r", encoding='utf-8')

print("Введите количество термов = ",end="")
n = int(f.readline())
print(n)

for i in range(n):
  l = list(str(f.readline()).replace("\n",""))
  print(specialPrint(l,"x"),end="+" if i!=n-1 else "")
"""