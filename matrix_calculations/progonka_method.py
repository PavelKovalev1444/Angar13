import numpy as np
from matrix_generator import get_matrix, get_vector_b


a = get_matrix()
b = get_vector_b()


def progonka_method(a, r):
    n = len(a)
    c = np.array([0.0] * n) 
    d = np.array([0.0] * n) 
    b = np.array([0.0] * n) 
    for i in range(n):
        for j in range(n):
            if i == j:
                c[i] = a[i][j]
            elif i == j + 1:
                b[i] = a[i][j]
            elif i + 1 == j:
                d[i] = a[i][j]

    delta = np.array([0.0] * 10) 
    _lambda = np.array([0.0] * 10)

    for i in range(n):
        delta[i] = -(d[i] / (c[i] + b[i] * delta[i-1]))
        _lambda[i] = ((r[i] - b[i] * _lambda[i-1]) / (c[i] + b[i] * delta[i-1]))


    ans = np.array([0.0] * 5) 
    ans[n - 1] = ((r[n - 1] - b[n - 1] * _lambda[n - 2]) / (c[n - 1] + b[n - 1] * delta[n-2]))
    for i in range(n - 2, -1, -1):
        ans[i] = delta[i] * ans[i + 1] + _lambda[i]
    
    return ans


print(progonka_method(a, b))
