#include <iostream>
using namespace std;

int gdc(int a, int b) {
    if (b == 0) return a;
    return gdc(b, a % b);
}

int lcm(int a, int b) {
    return a * b / gdc(a, b);
}

// gcc lcm.cpp -lstdc++ -o lcm.out && ./lcm.out 42 72

int main(int argc, char const *argv[]) {
    int a = stoi(argv[1]);
    int b = stoi(argv[2]);

    cout << lcm(a, b) << endl;
    return 0;
}