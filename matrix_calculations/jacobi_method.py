import numpy as np
from matrix_generator import get_matrix, get_vector_b


a = get_matrix()
b = get_vector_b()


def jacobi_method(a, b):
    n = len(a)
    D = np.eye(n)
    L = np.zeros((n, n))
    R = np.zeros((n, n))
    B = np.zeros((n, n))

    for i in range(n):
        for j in range(n):
            if i == j:
                D[i][j] = a[i][j]
            elif i < j:
                R[i][j] = a[i][j]
            else:
                L[i][j] = a[i][j]
    
    D_inv = np.linalg.inv(D)
    B = -1 * D_inv.dot(L+R)
    C = D_inv.dot(b)
    x = np.array([[0.0 for _ in range(n)] for _ in range(2)])
    
    x[0] = C
    x[1] = B.dot(x[0]) + C
    eps = 0.0001
    
    tmp = 0
    while np.linalg.norm(x[tmp + 1] - x[tmp]) > (((1 - q) / q) * eps):
        tmp += 1
        x = np.append(x, [B.dot(x[tmp]) + C], axis = 0)
    
    return x


print(jacobi_method(a, b))
