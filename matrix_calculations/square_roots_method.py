import numpy as np
import math
from matrix_generator import get_matrix, get_vector_b


a = get_matrix()
b = get_vector_b()


def square_root_method(a, b):
    n = len(a)
    d = np.eye(n)
    s = np.zeros((n, n))

    for i in range(n):
        d[i][i] = np.sign(a[i][i]-sum([s[p][i]*s[p][i]*d[p][p] for p in range(i)]))
        s[i][i] = np.sqrt(np.abs(a[i][i] - sum([s[p][i]*s[p][i]*d[p][p] for p in range(i)])))
        for j in range(i, n):
            s[i][j] = (a[i][j]-sum([s[p][i]*s[p][j]*d[p][p] for p in range(i)]))/(d[i][i]*s[i][i])
    
    st = s.transpose().dot(d)
    
    array_y = [1] * n # y
    for k in range(n):
        array_y[k] = (b[k] - sum([st[k][j] * array_y[j] for j in range(k)]))/st[k][k]
    
    array_x = [1] * n # x
    for k in range(n - 1, -1, -1):
        array_x[k] = (array_y[k] - sum([s[k][j] * array_x[j] for j in range(k + 1, n)]))/s[k][k]
    
    return array_x


print(square_root_method(a, b))
