import numpy as np
import math
import time

from color import *


def SeqEditOper(matrix, str1, str2):  # Sequence of editorial operations
    result = list()
    i, j = len(matrix) - 1, len(matrix[0]) - 1
    while (i or j):
        a, b, c = matrix[i - 1][j - 1], matrix[i - 1][j], matrix[i][j - 1]

        if b >= a <= c:
            if a == matrix[i][j]:
                result.append('M')
            else:
                result.append('R')
            if j:
                j -= 1
            if i:
                i -= 1
        elif a >= b <= c:
            result.append('D')
            if i:
                i -= 1
        else:
            result.append('I')
            if j:
                j -= 1

    result = result[::-1]
    print("\n    ", end="")
    for i in range(len(result)):
        print("{:5}".format(result[i]), end="")
    print("\n__________\n")

    i, j = 0, 0
    for elem in result:
        if elem == 'D':
            str1 = str1[0:i] + str1[i + 1:]
        elif elem == 'I':
            str1 = str1[0:i] + str2[j] + str1[i:]
        elif elem == 'R':
            str1 = str1[0:i] + str2[j] + str1[i + 1:]
        if elem != 'D':
            i += 1
            j += 1

        if elem in ['D', 'I', 'R']:  # Удаление, вставка, замена
            print(GREEN, elem, YELLOW, end=': ')
        else:
            print(YELLOW, elem, YELLOW, end=': ')

        print(str1, ' ---> ', str2)
    print()


def OutputMatrix(matrix, strFirst, strSecond):
    print("\n__________\n")
    print("\nMatrix:\n")
    print("    " * 2, end=" ")
    for i in range(len(strSecond)):
        print("{:5}".format(strSecond[i]), end="")

    for i in range(len(matrix)):
        print()
        for j in range(len(matrix[i])):
            if j == 0 and i > 0:
                print(strFirst[i - 1], end="")
            else:
                print(end=" ")
            print("{:4d}".format(matrix[i][j]), end="")
    print()


def Levenshtein(strFirst, strSecond, flag=False):
    n, m = len(strFirst), len(strSecond)
    matrix = np.full((n + 1, m + 1), 0)  # math.inf)

    matrix[0][0] = 0
    for i in range(1, n + 1):
        matrix[i][0] = i
    for i in range(1, m + 1):
        matrix[0][i] = i

    for i in range(1, n + 1):
        for j in range(1, m + 1):
            matrix[i][j] = min(
                matrix[i - 1][j - 1] +
                int(not(strFirst[i-1] == strSecond[j-1])),  # R
                matrix[i - 1][j] + 1,                       # D
                matrix[i][j - 1] + 1)                       # I

    if flag:
        OutputMatrix(matrix, strFirst, strSecond)
        SeqEditOper(matrix, strFirst, strSecond)

    return matrix[-1][-1]


def LevenshteinRecursion(strFirst, strSecond):
    if (strFirst == "" or strSecond == ""):
        return abs(len(strFirst) - len(strSecond))

    temp = 0 if strFirst[-1] == strSecond[-1] else 1
    return min(
        LevenshteinRecursion(strFirst, strSecond[:-1]) + 1,           # I
        LevenshteinRecursion(strFirst[:-1], strSecond) + 1,           # D
        LevenshteinRecursion(strFirst[:-1], strSecond[:-1]) + temp    # R
    )


def DamerauLevenshtein(strFirst, strSecond, flag=False):
    n, m = len(strFirst), len(strSecond)
    matrix = np.full((n + 1, m + 1), 0)  # math.inf)

    matrix[0][0] = 0
    for i in range(1, n + 1):
        matrix[i][0] = i
    for i in range(1, m + 1):
        matrix[0][i] = i

    for i in range(1, n + 1):
        for j in range(1, m + 1):
            matrix[i][j] = min(
                matrix[i - 1][j - 1] +
                int(not(strFirst[i-1] == strSecond[j-1])),  # R
                matrix[i - 1][j] + 1,                       # D
                matrix[i][j - 1] + 1)                       # I
            if i > 1 and j > 1 and strFirst[i - 1] == strSecond[j - 2] \
                    and strFirst[i-2] == strSecond[j-1]:
                matrix[i][j] = min(matrix[i][j], matrix[i-2][j-2] + 1)  # T

    if flag:
        OutputMatrix(matrix, strFirst, strSecond)
    return matrix[-1][-1]


def DamerauLevenshteinRecursion(strFirst, strSecond):
    if (strFirst == "" or strSecond == ""):
        return abs(len(strFirst) - len(strSecond))

    temp = 0 if strFirst[-1] == strSecond[-1] else 1
    result = min(
        DamerauLevenshteinRecursion(
            strFirst, strSecond[:-1]) + 1,           # I
        DamerauLevenshteinRecursion(
            strFirst[:-1], strSecond) + 1,           # D
        DamerauLevenshteinRecursion(
            strFirst[:-1], strSecond[:-1]) + temp    # R
    )

    if len(strFirst) > 1 and len(strSecond) > 1 and \
            strFirst[-1] == strSecond[-2] and strFirst[-2] == strSecond[-1]:
        result = min(result, DamerauLevenshteinRecursion(
            strFirst[:-2], strSecond[:-2]) + 1)  # T

    return result
