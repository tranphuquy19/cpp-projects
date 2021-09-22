#include <iostream>
#include <math.h>

using namespace std;

// #############################################################################
double euclidean_norm(double *v, int n) {
    double norm = 0;
    for (int i = 0; i < n; i++) {
        norm += v[i] * v[i];
    }
    norm = sqrt(norm);
    return norm;
}

// max of column
double max_column(double **matrix, int n, int m) {
    double max = matrix[0][0];
    for (int i = 0; i < n; i++) {
        if (matrix[i][m] > max) {
            max = matrix[i][m];
        }
    }
    return max;
}

// return max scalar of vector
double max_vector(double *v, int n) {
    double max = v[0];
    for (int i = 0; i < n; i++) {
        if (v[i] > max) {
            max = v[i];
        }
    }
    return max;
}

double norm_1_matrix(double A[][3], int n, int m) {
    double columns[3] = {0, 0, 0};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            columns[j] += fabs(A[i][j]);
        }
    }
    return max_vector(columns, m);
}

void print_vector(double *v, int n) {
    for (int i = 0; i < n; i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

void print_matrix(double m[][3], int n, int m_size) {
    for (int i = 0; i < n; i++) {
        print_vector(m[i], m_size);
    }
}

int main() {
    double v[3] = {1, 2, 3};
    cout << euclidean_norm(v, 3) << endl;

    double m[3][3] = {{5, -4, 2}, {-1, 2, 3}, {-2, 1, 0}};
    cout << norm_1_matrix(m, 3, 3) << endl;

    return 0;
}