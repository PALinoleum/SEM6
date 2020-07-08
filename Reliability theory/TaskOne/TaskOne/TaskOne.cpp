// TaskOne.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <math.h>
#include <iostream>
#include <cstdlib>
using namespace std;

void continous(int);
void discrete(int, int, int);

int main()
{
    int n = 50;
    continous(n);
    int i = 3, j = 10, k = 1;
    discrete(i, j, k);
}

void continous(int n) {
    float x, y, mathexp = 0, disp = 0;
    float mathexp2 = 0;
    for (int i = 0; i <= n; i++) {
        //y = rand() % 5000 + 1;
        y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        x = (double) -5/13 * log(y);
        mathexp = mathexp + x;
        mathexp2 = mathexp2 + x * x;
        cout << i << "   ";
        cout << y << "   ";
        cout << x << "   ";
        cout << "\n";
    }
    mathexp = (double) 1 / n * mathexp;
    mathexp2 = (double) 1 / n * mathexp2;
    disp = mathexp2 - (mathexp * mathexp);
    cout << mathexp << "\n";
    cout << disp;
}

void discrete(int i, int j, int k) {
    float x, y, mathexp = 0, disp = 0;
    float mathexp2 = 0;
    int x0 = 0, x1 = 1, x2 = 2, x3 = 3;
    float p0 = (double)i / 2 * (i + j + k),
          p1 = (double)j / 2 * (i + j + k),
          p2 = (double)i + j / 2 * (i + j + k),
          p3 = (double)2 * k / 2 * (i + j + k);
    for (int z = 0; z < 51; z++) {
        y = rand() % 5000 + 1;
    }
}
