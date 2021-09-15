#include <iostream>
using namespace std;

int gdc(int a, int b) {
    if (b == 0) return a;
    return gdc(b, a % b);
}

// gcc gdc.cpp -lstdc++ -o gdc.out && ./gdc.out

int main(int argc, char const *argv[]) {
    int a, b;
    cin >> a >> b;
    cout << gdc(a, b) << endl;
    return 0;
}