import numpy as np
from matrix_generator import get_matrix, get_vector_b


a = get_matrix()
b = get_vector_b()


def simple_iterations_method(a, b):
    n = len(a)
    E = np.eye(n)
    q = 0.6
    eps = 0.001
    S = q * np.linalg.inv(a)
    B = E - S.dot(a)
    C = S.dot(b)
    x = np.array([[0.0 for _ in range(n)] for _ in range(2)])
    x[0] = C
    x[1] = B.dot(x[0]) + C
    
    tmp = 0
    if np.linalg.norm(B, 'fro') < 1:
        while np.linalg.norm(x[tmp + 1] - x[tmp]) > (((1 - q) / q) * eps):
            tmp += 1
            x = np.append(x, [B.dot(x[tmp]) + C], axis = 0)
    else:
        raise Exception("Norm > 1!")


print(simple_iterations_method(a, b))
