from time import process_time
from sorts import heapsort, selectionsort, shakersort
import matplotlib.pyplot as plt
import random


def generate_random_array(n):
    arr = []
    for _ in range(n):
        arr.append(random.randint(-100, 100))
    return arr


def generate_sorted_array(n):
    arr = []
    for i in range(n):
        arr.append(i)
    return arr


def get_proc_time(arr, func, n):
    time = 0
    for _ in range(n):
        temp_arr = list(arr)
        start = process_time()
        func(temp_arr)
        stop = process_time()
        time += stop - start
    return time / n


def get_plots(arr_len, times, msg):
    time_1 = [times[i][0] for i in range(len(times))]
    time_2 = [times[i][1] for i in range(len(times))]
    time_3 = [times[i][2] for i in range(len(times))]

    plt.figure(1)
    plt.title(msg)
    plt.plot(arr_len, time_1, label='Пирамидальная')
    plt.plot(arr_len, time_2, label='Выбором')
    plt.plot(arr_len, time_3, label='Перемешиванием')
    plt.xlabel('Длина массива')
    plt.ylabel('Время')
    plt.legend(loc='best', fontsize=12)
    plt.grid(True)
    plt.show()


def get_times(arr, i):
    proc_time_1 = get_proc_time(arr, heapsort, 500)
    proc_time_2 = get_proc_time(arr, selectionsort, 500)
    proc_time_3 = get_proc_time(arr, shakersort, 500)
    print("|{:^8}|{:^25.6f}|{:^25.6f}|{:^25.6f}|".format(i, proc_time_1, proc_time_2, proc_time_3))
    print("|{:^8}|{:^25}|{:^25}|{:^25}|".format("-" * 8, "-" * 25, "-" * 25, "-" * 25))
    return [proc_time_1, proc_time_2, proc_time_3]


def analyze_sorts():
    max_len = 2000
    step = 200
    print("|{:^8}|{:^77}|".format("-" * 8, "-" * 77))
    print("|{:^8}|{:^25}|{:^25}|{:^25}|".format("", "Пирамидальная", "Выбором", "Перемешиванием"))
    print("|{:^8}|{:^25}|{:^25}|{:^25}|".format("-" * 8, "-" * 25, "-" * 25, "-" * 25))
    arr_len = [i for i in range(0, max_len, step)]

    # Неотсортированный массив
    times = []
    print("|{:^86}|".format("Неотсортированный массив"))
    print("|{:^86}|".format("-" * 86))
    for i in range(0, max_len, step):
        arr = generate_random_array(i)
        times.append(get_times(arr, i))
    get_plots(arr_len, times, "Неотсортированный массив")

    # Отсортированный по возрастанию массив
    times = []
    print("|{:^86}|".format("Отсортированный по возрастанию массив"))
    print("|{:^86}|".format("-" * 86))
    for i in range(0, max_len, step):
        arr = generate_sorted_array(i)
        times.append(get_times(arr, i))
    get_plots(arr_len, times, "Отсортированный по возрастанию массив")

    # Отсортированный по убыванию массив
    times = []
    print("|{:^86}|".format("Отсортированный по убыванию массив"))
    print("|{:^86}|".format("-" * 86))
    for i in range(0, max_len, step):
        arr = generate_sorted_array(i)
        arr.reverse()
        times.append(get_times(arr, i))
    get_plots(arr_len, times, "Отсортированный по убыванию массив")

