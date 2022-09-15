import time
import numpy as np
import random

from matrix_multiplication import *
from matrix import Matrix


def TimeTest(matrixA, matrixB, countOperations, f):
    t1 = time.process_time()
    for _ in range(countOperations):
        f(matrixA, matrixB)
    t2 = time.process_time()
    return round(t2 - t1, 4)


# size = range(11, 101, 10)
# print(size)
# array1 = list()
# array2 = list()
# array3 = list()
# for n in [101]:
#     matrixA = Matrix(n, n)
#     matrixB = Matrix(n, n)  # np.random.random((n, n))
#     matrixA.fill(np.random.random((n, n)))
#     matrixB.fill(np.random.random((n, n)))
#     array1.append(TimeTest(matrixA, matrixB, 50, multiplication))
#     array2.append(TimeTest(matrixA, matrixB, 50, WinogradMult))
#     array3.append(TimeTest(matrixA, matrixB, 50, WinogradOptimization))
#     print(array1)

# print(array1, array2, array3)

# [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]
# multiplication = [0.1659, 1.2984, 4.2817, 10.2096, 20.0939, 34.8193, 55.5672, 87.3287, 125.4393, 178.7763]
# WinogradMult = [0.1283, 0.9233, 2.9916, 7.0258, 13.6765, 23.5873, 38.4858, 59.8075, 86.0822, 121.201]
# WinogradOptimization = [0.0561, 0.4111, 1.3374, 3.1658, 6.1203, 12.3997, 18.9571, 28.3732, 40.7075, 56.4076]
#
# [11, 21, 31, 41, 51, 61, 71, 81, 91]
# [0.2165, 1.4288, 4.619, 10.6453, 20.2012, 35.3632, 58.5323, 88.6608, 125.916]
# [0.1731, 1.0691, 3.3009, 7.5519, 14.43, 25.6929, 41.9793, 62.4315, 87.5135]
# [0.0891, 0.5213, 1.5841, 3.5756, 6.8016, 13.4514, 20.9525, 30.1312, 43.4626]
