// Build command: gcc matrix_utils.cpp -lstdc++ -lm -o matrix_utils.out

#include <iostream>
#include <math.h>
using namespace std;

void swap(int &a, int &b);
void transpose(int matrix[][3]);
int det_of_matrix(int matrix[][3], int n);
void add(int matrix1[][3], int matrix2[][3], int matrix3[][3]);
void multiply(int matrix1[][3], int matrix2[][3], int matrix3[][3]);
void print(int matrix[][3]);

// swap
void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

// add two matrices, matrix3 is output matrix
void add(int matrix1[][3], int matrix2[][3], int matrix3[][3])
{
    int i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            matrix3[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
}

// multiply two matrices
void multiply(int matrix1[][3], int matrix2[][3], int matrix3[][3])
{
    int i, j, k;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            matrix3[i][j] = 0;
            for (k = 0; k < 3; k++)
            {
                matrix3[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

// tranpose of matrix
void transpose(int matrix[][3])
{
    int i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = i + 1; j < 3; j++)
        {
            swap(matrix[i][j], matrix[j][i]);
        }
    }
}

// det of matrix
int det_of_matrix(int matrix[][3], int n)
{
    int det = 0;
    int submatrix[3][3];
    if (n == 2)
        return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
    else
    {
        for (int x = 0; x < n; x++)
        {
            int subi = 0;
            for (int i = 1; i < n; i++)
            {
                int subj = 0;
                for (int j = 0; j < n; j++)
                {
                    if (j == x)
                        continue;
                    submatrix[subi][subj] = matrix[i][j];
                    subj++;
                }
                subi++;
            }
            det = det + (pow(-1, x) * matrix[0][x] * det_of_matrix(submatrix, n - 1));
        }
    }
    return det;
}

// inverse of matrix 3 x 3
void inverse_of_matrix(int mat[][3], float det)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            printf("%.2f\t", ((mat[(j + 1) % 3][(i + 1) % 3] * mat[(j + 2) % 3][(i + 2) % 3]) - (mat[(j + 1) % 3][(i + 2) % 3] * mat[(j + 2) % 3][(i + 1) % 3])) / det);
        printf("\n");
    }
}

// print the matrix
void print(int matrix[][3])
{
    int i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// main
int main()
{
    int matrix1[3][3] = {
        {9, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};

    int matrix2[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};

    int matrix3[3][3];

    transpose(matrix1);
    cout << "transpose of matrix1: " << endl;
    print(matrix1);

    cout << "det of matrix1: " << det_of_matrix(matrix1, 3) << endl;

    float det = (float)det_of_matrix(matrix1, 3);
    inverse_of_matrix(matrix1, det);

    add(matrix1, matrix2, matrix3);
    cout << "matrix1 + matrix2: " << endl;
    print(matrix3);

    multiply(matrix1, matrix2, matrix3);
    cout << "matrix1 * matrix2: " << endl;
    print(matrix3);

    return 0;
}