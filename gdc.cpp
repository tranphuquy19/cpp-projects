#include <iostream>
using namespace std;

int gdc(int a, int b) {
    if (b == 0) return a;
    return gdc(b, a % b);
}

// gcc gdc.cpp -lstdc++ -o gdc.out && ./gdc.out 42 72

int main(int argc, char const *argv[]) {
    int a = stoi(argv[1]);
    int b = stoi(argv[2]);

    cout << gdc(a, b) << endl;
    return 0;
}