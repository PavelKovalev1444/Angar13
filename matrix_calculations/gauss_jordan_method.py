import numpy as np
from matrix_generator import get_matrix, get_vector_b


a = get_matrix()
b = get_vector_b()


def gauss_jordan_method(a, b):
    n = len(a)
    for k in range(n):
        for i in range(n):
            if i != k:
                r = a[i][k] / a[k][k]
                b[i] = b[i] - (r * b[k])
                for j in range(k, n):
                    a[i][j] = a[i][j] - (r * a[k][j])

    ans = [1] * n
    for i in range(n):
        ans[i] = (b[i]/a[i][i])
    
    return ans


print(gauss_jordan_method(a, b))
