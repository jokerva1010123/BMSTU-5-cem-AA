from algorithms import *
from color import *
import time
import sys


def TimeTest(strFirst, strSecond, countOperations):
    print("Длина первой строки = ", len(strFirst))
    print("Длина второй строки = ", len(strSecond))

    t1 = time.process_time()
    for _ in range(countOperations):
        Levenshtein(strFirst, strSecond)
    t2 = time.process_time()
    print("Левенштейн = ", t2 - t1)

    t1 = time.process_time()
    for _ in range(countOperations):
        LevenshteinRecursion(strFirst, strSecond)
    t2 = time.process_time()
    print("Левенштейн (рекурсия)= ", t2 - t1)

    t1 = time.process_time()
    for _ in range(countOperations):
        DamerauLevenshtein(strFirst, strSecond)
    t2 = time.process_time()
    print("Дамерау-Левенштейн = ", t2 - t1)

    t1 = time.process_time()
    for _ in range(countOperations):
        DamerauLevenshteinRecursion(strFirst, strSecond)
    t2 = time.process_time()
    print("Дамерау-Левенштейн (рекурсия)= ", t2 - t1)


# sys.setrecursionlimit(1500)
