from algorythms import *
import matplotlib.pyplot as plt
import random

TIMES = 300
TO_MILISECONDS = 1000

def getProcessTime(str1, str2, func, size):
    time_res = 0

    for _ in range(TIMES):
        time_start = process_time()
        func(str1, str2, output = False)
        time_end = process_time()

        time_res += (time_end - time_start)

    return time_res / TIMES

def graphLevAndDamerauLev(timeLev):
    sizes = [0, 1, 2, 3, 4, 5, 6, 7]

    fig = plt.figure(figsize=(10, 7))
    plot = fig.add_subplot()
    plot.plot(sizes, timeLev, "g:", label = "Левенштейн")

    plt.legend()
    plt.grid()
    plt.title("Временные характеристики")
    plt.ylabel("Затраченное время (с)")
    plt.xlabel("Длина, символы")

    plt.show()

def graphDamerauLev(timeDamerauLev, timeDamerauLevRecursive,timeDamerauLevRecursiveCache):
    sizes = [0, 1, 2, 3, 4, 5, 6, 7]

    fig = plt.figure(figsize=(10, 7))
    plot = fig.add_subplot()
    plot.plot(sizes, timeDamerauLev, ":", label = "Дамерау-Левенштейн (матричный)")
    plot.plot(sizes, timeDamerauLevRecursive, "", label="Дамерау-Левенштейн (рекурсия)")
    plot.plot(sizes, timeDamerauLevRecursiveCache, "--", label="Дамерау-Левенштейн (с кэшем)")

    plt.legend()
    plt.grid()
    plt.title("Временные характеристики")
    plt.ylabel("Затраченное время (с)")
    plt.xlabel("Длина, символы")

    plt.show()

def graphDamerauLevMatrCache(timeDamerauLev, timeDamerauLevRecursiveCache):
    sizes = [0, 1, 2, 3, 4, 5, 6, 7]

    fig = plt.figure(figsize=(10, 7))
    plot = fig.add_subplot()
    plot.plot(sizes, timeDamerauLev, ":", label = "Дамерау-Левенштейн (матричный)")
    plot.plot(sizes, timeDamerauLevRecursiveCache, label="Дамерау-Левенштейн (с кэшем)")

    plt.legend()
    plt.grid()
    plt.title("Временные характеристики")
    plt.ylabel("Затраченное время (с)")
    plt.xlabel("Длина, символы")

    plt.show()

def compareAlgorithms():
    timeLev = []
    timeDamerauLev = []
    timeDamerauLevRecursive = []
    timeDamerauLevRecursiveCache = []
    str1 = ''
    str2 = ''
    for num in range(8):
        if num:
            letter = random.choice(string.ascii_lowercase)
            str1 += letter
            letter = random.choice(string.ascii_lowercase)
            str2 += letter
        print("Run with length:\t", num)
        timeLev.append(getProcessTime(str1, str2, levenshteinDistance, num))
        timeDamerauLev.append(getProcessTime(str1, str2, damerauLevenshteinDistance, num))
        timeDamerauLevRecursive.append(getProcessTime(str1, str2, damerauLevenshteinDistanceRecursive, num))
        timeDamerauLevRecursiveCache.append(getProcessTime(str1, str2, damerauLevenshteinDistanceRecurciveCache, num))

    print("\n\nЗамер времени для алгоритмов: \n")

    ind = 0
    print("Length | Levenshtein | Lev Domerau | Recursive | Cache")
    for num in range(8):
        print(" %5d | %11.6f | %11.6f | %9.6f | %.6f\n" %(num, \
            timeLev[ind] * TO_MILISECONDS, \
            timeDamerauLev[ind] * TO_MILISECONDS, \
            timeDamerauLevRecursive[ind] * TO_MILISECONDS, \
            timeDamerauLevRecursiveCache[ind] * TO_MILISECONDS))

        ind += 1

    graphLevAndDamerauLev(timeLev)
    graphDamerauLev(timeDamerauLev, timeDamerauLevRecursive, timeDamerauLevRecursiveCache)
    graphDamerauLevMatrCache(timeDamerauLev, timeDamerauLevRecursiveCache)