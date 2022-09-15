from matrix import Matrix
import numpy as np


def multiplication(matrixA, matrixB):
    n = matrixA.n
    m = matrixB.m
    q = matrixB.n

    matrixC = Matrix(n, m)

    for i in range(n):
        for j in range(m):
            for k in range(q):
                matrixC[i][j] += (matrixA[i][k] * matrixB[k][j])

    return matrixC


def WinogradMult(matrixA, matrixB):
    n = matrixA.n
    m = matrixB.m
    q = matrixB.n

    matrixC = Matrix(n, m)

    tempA = np.full(n, 0)
    for i in range(n):
        for j in range(1, q, 2):
            tempA[i] += matrixA[i][j - 1] * matrixA[i][j]

    tempB = np.full(m, 0)
    for i in range(m):
        for j in range(1, q, 2):
            tempB[i] += matrixB[j - 1][i] * matrixB[j][i]

    for i in range(n):
        for j in range(m):
            matrixC[i][j] -= (tempA[i] + tempB[j])
            for k in range(1, q, 2):
                matrixC[i][j] += (matrixA[i][k-1] + matrixB[k][j]) * \
                    (matrixA[i][k] + matrixB[k-1][j])
    if q % 2:
        for i in range(n):
            for j in range(m):
                matrixC[i][j] += matrixA[i][q-1] * matrixB[q-1][j]

    return matrixC


print(0b11)


def WinogradOptimization(matrixA, matrixB):
    n = matrixA.n
    m = matrixB.m
    q = matrixB.n

    matrixC = Matrix(n, m)

    # Оптимизация: Не вызываем метод библиотеки,
    # А создаем массив с помощью генератора.
    tempA = [0 for i in range(n)]
    for i in range(n):
        for j in range(1, q, 2):
            tempA[i] += matrixA[i][j - 1] * matrixA[i][j]

    tempB = [0 for i in range(m)]
    for i in range(m):
        for j in range(0b1, q, 0b10):
            tempB[i] += matrixB[j - 1][i] * matrixB[j][i]

    for i in range(n):
        for j in range(m):
            # Оптимизация: не обращаемся каждый раз к matrixC[i][j],
            # А создаем промежуточный буфер.
            buf = -(tempA[i] + tempB[j])
            for k in range(1, q, 2):
                buf += (matrixA[i][k-1] + matrixB[k][j]) * \
                    (matrixA[i][k] + matrixB[k-1][j])
            matrixC[i][j] = buf

    # Оптимизация: q % 2 заменяем на q & 1.
    # Побитывые операции работают быстрее.
    if q & 1:
        for i in range(n):
            for j in range(m):
                matrixC[i][j] += matrixA[i][q-1] * matrixB[q-1][j]

    return matrixC


#     n = matrixA.n
#     m = matrixB.m
#     q = matrixB.n
#     d = (int)(q / 2)

#     matrixC = Matrix(n, m)

#     tempA = np.full(n, 0)
#     for i in range(n):
#         tempA[i] += matrixA[i][0] * matrixA[i][1]
#         for j in range(2, d):
#             tempA[i] += matrixA[i][2*j-1] * matrixA[i][2*j]

#     tempB = np.full(m, 0)
#     for i in range(m):
#         tempB[i] += matrixB[1][i] * matrixB[0][i]
#         for j in range(1, d):
#             tempB[i] += matrixB[2*j-1][i] * matrixB[2*j][i]

#     for i in range(n):
#         for j in range(m):
#             matrixC[i][j] -= (tempA[i] + tempB[j])
#             for k in range(1, q, 2):
#                 matrixC[i][j] += (matrixA[i][k - 1] + matrixB[k][j]) * \
#                     (matrixA[i][k] + matrixB[k - 1][j])
#     if q % 2:
#         for i in range(n):
#             for j in range(m):
#                 matrixC[i][j] += matrixA[i][q-1] * matrixB[q-1][j]

#     return matrixC
