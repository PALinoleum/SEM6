def f1(t1, x1, x2, x3):
    z1 = not t1 and x1
    z2 = x1 and not x2
    z3 = not x1 and not x3
    
    u1 = not t1 and x1
    u2 = x3 and z1
    u3 = not t1 and z2
    u4 = not x3 and z1
    u5 = not x2 and z3
    u6 = t1 and not x2
    u7 = not t1
    u8 = not x2

    v1 = u5 or u6

    y1 = u1
    y2 = u2 or u3
    y3 = u4 or v1
    f1 = u7 or u8
    print("Триггер: {}, Выходы: {} {} {}".format(int(f1), int(y1), int(y2), int(y3)))
    return f1, y1, y2, y3

t1 = 0

print("Введите входы х1, х2, х3: ")
x1 = int(input('x1 = '))
x2 = int(input('x2 = '))
x3 = int(input('x3 = '))

while x1 == 0 or x1 == 1 or x2 == 0 or x2 == 1 or x3 == 0 or x3 == 1:
    t1, x1, x2, x3 = f1(t1, x1, x2, x3) 
    print("Введите входы х1, х2, х3: ")
    x1 = int(input('x1 = '))
    x2 = int(input('x2 = '))
    x3 = int(input('x3 = '))