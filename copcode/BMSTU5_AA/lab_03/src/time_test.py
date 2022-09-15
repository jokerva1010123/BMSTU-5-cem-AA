import sys
import time
import random
import numpy as np  # np.array([random.randint(0, 1000) for i in range(100)])
import copy

from sort import *


def get_random_array(n):
    array = []

    for i in range(n):
        array.append(random.randint(0, 20000))

    return array


def get_best_array(n):
    array = []

    for i in range(n):
        array.append(i)

    return array


def get_worst_array(n):
    array = []

    for i in range(n):
        array.append(n - i)

    return array


def get_calc_time(func, arr):
    t2 = time.process_time()
    func(arr)
    t1 = time.process_time() - t2

    return t1


def measure_time(get_array, n1, n2, st, it):
    t_bubble = []
    t_insert = []
    t_quick = []

    for n in range(n1, n2, st):
        print(n, ' ', time.time())
        t = 0

        for i in range(it):
            arr = get_array(n)
            t += get_calc_time(sort_bubble, arr)

        t_bubble.append(round(t / it, 4))
        t = 0

        for i in range(it):
            arr = get_array(n)
            t += get_calc_time(sort_insert, arr)

        t_insert.append(round(t / it, 4))
        t = 0

        for i in range(it):
            arr = get_array(n)
            t += get_calc_time(quick_sort, arr)

        t_quick.append(round(t / it, 4))

    return (t_bubble, t_insert, t_quick)


n1 = 100
n2 = 1000
h = 200

result = measure_time(get_best_array, n1, n2 + 1, h, 100)

print(result)

# def TimeTest(arr, countOperations, f):
#     t1 = time.process_time()
#     for _ in range(countOperations):
#         f(arr)
#     t2 = time.process_time()
#     return round(t2 - t1, 4)


# sys.setrecursionlimit(1500)
# COUNT = 500
# bubble_time = list()
# insert_time = list()
# quick_time = list()
# size = [100, 200, 300, 500, 600, 700, 1000]
# for a in size:
#     # arr = list(range(a, 0, -1))
#     arr = np.array([random.randint(0, 1000) for i in range(a)])

#     quick_time.append(TimeTest(copy.copy(arr), COUNT, quick_sort))

#     insert_time.append(TimeTest(copy.copy(arr), COUNT, sort_insert))

#     bubble_time.append(TimeTest(copy.copy(arr), COUNT, sort_bubble))

#     print(a)

# print()
# print(bubble_time)
# print(insert_time)
# print(quick_time)
