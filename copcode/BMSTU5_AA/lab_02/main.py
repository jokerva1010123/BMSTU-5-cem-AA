from matrix_multiplication import *
from matrix import *
from color import *


def main():
    output("МАТРИЦА A", BLUE)
    n = int(input(GREEN + "Введите кол-во строк: "))
    m = int(input(GREEN + "Введите кол-во столбцов: "))
    output("Введите матрицу:", GREEN)
    matrixA = Matrix(n, m, [[int(j) for j in input(GREEN).split()]
                            for i in range(n)])

    output("МАТРИЦА B", BLUE)
    k = int(input(GREEN + "Введите кол-во строк: "))
    l = int(input(GREEN + "Введите кол-во столбцов: "))
    output("Введите матрицу:", GREEN)
    matrixB = Matrix(k, l, [[int(j) for j in input(GREEN).split()]
                            for i in range(k)])

    if m != k:
        output("Некорректные размеры матриц!", RED)
        return

    matrixC = multiplication(matrixA, matrixB)
    print('multiplication')
    matrixC.output()
    matrixC2 = WinogradOptimization(matrixA, matrixB)
    print('multiplication 2:')
    matrixC2.output()
    # matrixC = WinogradMult(matrixA, matrixB)
    # print('Winograd multiplication')
    # matrixC.output()
    # matrixC = WinogradOptimization(matrixA, matrixB)
    # print('WinogradOptimization')
    # matrixC.output()


if __name__ == "__main__":
    main()
