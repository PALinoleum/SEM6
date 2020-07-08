import numpy as np
import pandas as pd

import numpy as np
import pandas as pd

class Term:
  def __init__(self):
    self.skleen = false
    pass
  
  def print(self):
    pass

class Level:
  def __init__(self, id, n):
    self.id = id
    self.n = n
    self.terms = [[]]*(n+1)

  def putTerm(self, term):
    self.terms[list(term).count("1")] = self.terms[list(term).count("1")]+[tuple(term)]

  def clearfree(self):
    i=0
    while i < len(self.terms):
      #print(i)
      if(self.terms[i]==[]):
        del(self.terms[i])
        #print(self.terms)
        i-=1
      i+=1
      #levels[0].terms[1]==[]
      
f = open("C:/Users/D4rkn/source/repos/TCA-2/TCA-2/source/demofile.txt", "r", encoding='utf-8')

levels=[]
m = int(f.readline())
n = int(f.readline())
print("m={}, n={}".format(m,n))
levels.append(Level(0,n))

print("Введите термы:")
for i in range(m):
  t = str(f.readline()).replace("\n","")
  print(t)
  levels[0].putTerm(t)
  pass

levels[0].clearfree()
print(levels[0].terms)

print("\nТо что не склеилось:")
for i in range(0,n):
  levelset1=set()
  levelset2=set()

  levels[i].clearfree()
  newlevel = Level(0,n)
  for j in range(0,len(levels[i].terms)-1):
    for k in range(0,len(levels[i].terms[j])):
      if(len(levels[i].terms[j][k])!=0):
        for g in range(0,len(levels[i].terms[j+1])):
          levelset1.update({''.join(levels[i].terms[j][k])},{''.join(levels[i].terms[j+1][g])})
          #levelset1.update({(levels[i].terms[j][k])},{levels[i].terms[j+1][g]}) 

          #print("{} - {} = {}".format(levels[i].terms[j][k],levels[i].terms[j+1][g],np.array(levels[i].terms[j][k])!=np.array(levels[i].terms[j+1][g])))
          if(sum(np.array(levels[i].terms[j][k])!=np.array(levels[i].terms[j+1][g]))==1):
            newterm = np.array(levels[i].terms[j][k])
            newterm[np.where(np.array(levels[i].terms[j][k])!=np.array(levels[i].terms[j+1][g]))[0][0]] = "-"
            #print(newterm)
            newlevel.putTerm(newterm)
            #print(newlevel.terms)
            levelset2.update({''.join(levels[i].terms[j][k])},{''.join(levels[i].terms[j+1][g])})#({(levels[i].terms[j][k])},{levels[i].terms[j+1][g]})
  #print(newlevel.terms)
  levels.append(newlevel)

  #print(levelset1,"\n",levelset2)
  sets_difference = levelset1-levelset2
  if (len(levelset2) != 0):
    print("\t Уровень №{} : {}".format(i+1,levelset1-levelset2))
  else:
    print("\t Уровень №{} : {}".format(i+1,levels[i].terms))
