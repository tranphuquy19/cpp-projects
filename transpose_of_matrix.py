import numpy as np
from math import sqrt
# def transpose_of_matrix(matrix):
#     """
#     transpose of matrix
#     """
#     transpose_matrix = []
#     for i in range(len(matrix[0])):
#         transpose_matrix.append([])
#         for j in range(len(matrix)):
#             transpose_matrix[i].append(matrix[j][i])
#     return transpose_matrix


# def hadamard_product(matrix1, matrix2):
#     """
#     hadamard product
#     """
#     hadamard_product = []
#     for i in range(len(matrix1)):
#         hadamard_product.append([])
#         for j in range(len(matrix1[0])):
#             hadamard_product[i].append(matrix1[i][j] * matrix2[i][j])
#     return hadamard_product

# Cholesky matrix decomposition
def cholesky_decomposition(M):
    A = np.copy(M)
    n = A.shape[0]
    L = np.zeros_like(A)

    for k in range(n):
        L[k, k] = sqrt(A[k, k])
        L[k, k + 1:] = A[k, k + 1:] / L[k, k]
        for j in range(k + 1, n):
            A[j, j:] = A[j, j:] - L[k, j] * L[k, j:]

    return L


# main, test chord_matrix_factorization
if __name__ == '__main__':
    matrix = [[1, 3, 5], [3, 13, 23], [5, 23, 42]]
    a = np.array(matrix)
    L = cholesky_decomposition(matrix)
    LT = np.transpose(L)
    print(L)
    print(LT)
