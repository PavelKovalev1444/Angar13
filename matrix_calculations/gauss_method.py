import numpy as np
from matrix_generator import get_matrix, get_vector_b


a = get_matrix()
b = get_vector_b()


def gauss_method(a, b):
    n = len(a)
    for k in range(n - 1):
        for i in range(k + 1, n):
            r = a[i][k] / a[k][k]
            for j in range(k, n):
                a[i][j] = a[i][j] - (r * a[k][j])
            b[i] = b[i] - (r * b[k])

    ans = [1] * n
    for k in range(n - 1, -1, -1):
        ans[k] = ((b[k] - sum([a[k][j] * ans[j] for j in range(k + 1, n)])) / a[k][k])
    
    return ans


print(gauss_method(a, b))
