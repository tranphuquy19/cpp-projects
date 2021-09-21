def transpose_of_matrix(matrix):
    """
    transpose of matrix
    """
    transpose_matrix = []
    for i in range(len(matrix[0])):
        transpose_matrix.append([])
        for j in range(len(matrix)):
            transpose_matrix[i].append(matrix[j][i])
    return transpose_matrix

def matrix_pro

def hadamard_product(matrix1, matrix2):
    """
    hadamard product
    """
    hadamard_product = []
    for i in range(len(matrix1)):
        hadamard_product.append([])
        for j in range(len(matrix1[0])):
            hadamard_product[i].append(matrix1[i][j] * matrix2[i][j])
    return hadamard_product

