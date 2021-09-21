#include <iostream>
#include <math.h>
using namespace std;

int gdc(int a, int b) {
    if (b == 0) return a;
    return gdc(b, a % b);
}


// resolve expression with diophantine equation
// return the number of solutions
void solve(int a, int b, int c) {
    int g = gdc(a, b);
    int x = c / g;
    int y = a / g;
    int z = b / g;
    int n = x * y * z;
    cout << n << endl;
}

int main() {
    int a, b, c;
    a= 7; b = 11; c = 13;
    solve(a, b, c);
    return 0;
}