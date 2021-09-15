#include <iostream>
using namespace std;

int gdc(int a, int b) {
    if (b == 0) return a;
    return gdc(b, a % b);
}

int lcm(int a, int b) {
    return a * b / gdc(a, b);
}

// gcc lcm.cpp -o lcm.out && ./lcm.out

int main(int argc, char const *argv[]) {
    int a, b;
    cin >> a >> b;
    cout << lcm(a, b) << endl;
    return 0;
}