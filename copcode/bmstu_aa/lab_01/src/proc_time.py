from time import process_time
from algorithms import levenstein, damerau_levenstein, damerau_levenstein_recursive, damerau_levenstein_recursive_cache_matrix
import matplotlib.pyplot as plt
import random
import string


def generate_random_string(length):
    letters = string.ascii_lowercase
    rand_string = ''.join(random.choice(letters) for _ in range(length))
    return rand_string


def get_proc_time(str_1, str_2, func, n):
    time = 0
    for _ in range(n):
        start = process_time()
        func(str_1, str_2)
        stop = process_time()
        time += stop - start
    return time / n


def get_plots(arr_len, times):
    time_1 = [times[i][0] for i in range(len(times))]
    time_2 = [times[i][1] for i in range(len(times))]
    time_3 = [times[i][2] for i in range(len(times))]
    time_4 = [times[i][3] for i in range(len(times))]

    plt.figure(1)
    plt.plot(arr_len, time_1, label='Левенштейн')
    plt.plot(arr_len, time_2, label='Д-Л')
    plt.legend(loc='best', fontsize=12)
    plt.xlabel('Длина строки')
    plt.ylabel('Время, мс')
    plt.grid(True)
    plt.show()

    plt.figure(2)
    plt.plot(arr_len, time_2, label='Д-Л')
    plt.plot(arr_len, time_3, label='Д-Л (рек)')
    plt.plot(arr_len, time_4, label='Д-Л (рек с кешем)')
    plt.legend(loc='best', fontsize=12)
    plt.xlabel('Длина строки')
    plt.ylabel('Время, мс')
    plt.grid(True)
    plt.show()

    plt.figure(3)
    plt.plot(arr_len, time_2, label='Д-Л')
    plt.plot(arr_len, time_4, label='Д-Л (рек с кешем)')
    plt.legend(loc='best', fontsize=12)
    plt.xlabel('Длина строки')
    plt.ylabel('Время, мс')
    plt.grid(True)
    plt.show()


def analize_algorithm():
    number = 11
    print("|{:^8}|{:^20}|{:^77}|".format("-" * 8, "-" * 20, "-" * 77))
    print("|{:^8}|{:^20}|{:^77}|".format("", "", "Дамерау-Левенштейн"))
    print("|{:^8}|{:^20}|{:^77}|".format("Длина", "Левенштейн", "-" * 77))
    print("|{:^8}|{:^20}|{:^25}|{:^25}|{:^25}|".format("", "", "обычный", "рекурсивный", "рекурсивный с кешем"))
    print("|{:^8}|{:^20}|{:^25}|{:^25}|{:^25}|".format("-" * 8, "-" * 20, "-" * 25, "-" * 25, "-" * 25))
    times = []
    arr_len = [i for i in range(number)]
    for i in range(number):
        str_1 = generate_random_string(i)
        str_2 = generate_random_string(i)
        proc_time_1 = get_proc_time(str_1, str_2, levenstein, 10000)
        proc_time_2 = get_proc_time(str_1, str_2, damerau_levenstein, 10000)
        proc_time_3 = get_proc_time(str_1, str_2, damerau_levenstein_recursive, 50)
        proc_time_4 = get_proc_time(str_1, str_2, damerau_levenstein_recursive_cache_matrix, 10000)
        print("|{:^8}|{:^20.6f}|{:^25.6f}|{:^25.6f}|{:^25.6f}|".format(i, proc_time_1, proc_time_2, proc_time_3, proc_time_4))
        # print("|{:^8}|{:^20.6e}|{:^25.6e}|{:^25.6e}|{:^25.6e}|".format(i, proc_time_1, proc_time_2, proc_time_3, proc_time_4))
        print("|{:^8}|{:^20}|{:^25}|{:^25}|{:^25}|".format("-" * 8, "-" * 20, "-" * 25, "-" * 25, "-" * 25))
        times.append([proc_time_1, proc_time_2, proc_time_3, proc_time_4])

    get_plots(arr_len, times)




