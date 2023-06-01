from time import process_time, time
from copy import deepcopy
from matplotlib import pylab
import matplotlib.pyplot as plt

class InfoCity(object):
	country = str()

	def __init__(self, country):
		self.country = country

	def __str__(self):
		return "Population: {0}".format(self.country)

class Dictionary(object):
    data = dict()
    f = open('resBFS.txt', 'w')
    f1 = open('resBS.txt', 'w')

    def __init__(self, file_name):
        #self.data = dict()
        self.LoadData(file_name)

    def __getitem__(self, key):
        return self.data.get(key)

    def LoadData(self, file_name):
        f = open(file_name, 'r')

        for line in f:
            array = line.split(',')
            key = array[1]
            self.data[key] = InfoCity(array[2])

        f.close()
    
    def sorting_by_keys(self):
        new_dict = dict()
        list_keys = list(self.data.keys())
        list_keys.sort()

        for i in list_keys:
            new_dict[i] = self.data[i]

        return new_dict

    def sorting_by_values(self, data):
        new_dict = dict()

        list_d = list(data.items())
        list_d.sort(key=lambda i: i[1], reverse=True)
        for elem in list_d:
            new_dict[elem[0]] = elem[1]

        return new_dict

    def BruteForceSearch(self, key):
        k = 0
        kk = list(self.data.keys())
        for elem in self.data:
            k += 1
            if key == elem:
                self.f.write(f"{kk.index(key)},{key},{k}\n")
                return self.data[elem]
        return -1

    def BruteForceSearchCount(self, key):
        k = 0
        kk = list(self.data.keys())
        for elem in self.data:
            k += 1
            if key == elem:
                self.f.write(f"{kk.index(key)},{key},{k}\n")
                return k
        return k

    def BinarySearch(self, key, list_keys):
        l, r = 0, len(list_keys) - 1
        k = 0
        g = 0
        kk = list(self.data.keys())
        while l <= r:
            middle = (r + l) // 2  # (l + (r - l) // 2)
            elem = list_keys[middle]
            k += 1
            if elem == key:
                g += 1
                self.f1.write(f"{kk.index(key)},{key},{k}, {g}\n")
                return self.data[elem]
            elif elem < key:
                l = middle + 1
            else:
                r = middle - 1
            g += 2
        return -1

    def BinarySearchCount(self, key, list_keys):
        l, r = 0, len(list_keys) - 1
        k = 0
        g = 0
        kk = list(self.data.keys())
        while l <= r:
            middle = (r + l) // 2  # (l + (r - l) // 2)
            elem = list_keys[middle]
            k += 1
            if elem == key:
                g += 1
                self.f1.write(f"{kk.index(key)},{key},{k}, {g}\n")
                return k + g
            elif elem < key:
                l = middle + 1
            else:
                r = middle - 1
            g += 2
        return k + g

def get_time_search(f, data, key, all_k):
    sum = 0
    for i in range(300):
        start = process_time()
        if (f == 1):
            data.BruteForceSearch(key)
        if (f == 2):
            data.BinarySearch(key, all_k)
        sum += (process_time() - start)
    return sum

def get_count_search(f, data, key, all_k):
    if f == 1:
        return data.BruteForceSearchCount(key)
    elif f == 2:
        return data.BinarySearchCount(key, all_k)

def test_time(data):
    x_11list = list(data.data.keys())
    x_list = [i for i in range(len(x_11list))] 
    time_simple = []
    time_bin = []   
    list_keys = list(data.data.keys())
    for i in list_keys:
        time_simple.append(get_time_search(1, data,i, 0))

    new_dict = data.sorting_by_keys()
    list_keys = list(new_dict.keys())
    lk = list(data.data.keys())
    for i in lk:
        time_bin.append(get_time_search(2, data, i, list_keys))

    x1_list = []
    time_simple1 = []
    time_bin1 = []

    for i in range(len(x_list)):
        if i % 15 == 0:
            x1_list.append(i)
            time_simple1.append(time_simple[i])
            time_bin1.append(time_bin[i])

    pylab.xlabel('Индекс ключа')
    pylab.ylabel('Время, секунды')
    pylab.plot(x1_list, time_simple1, 'r--', label='Полный перебор')
    pylab.plot(x1_list, time_bin1, color='yellow', label='Бинарный поиск')
    pylab.legend(loc='upper left')
    pylab.show()

def test_cmp(data):
    x_11list = list(data.data.keys())
    x_list = [i for i in range(len(x_11list))] 
    cnt_simple = []
    cnt_bin = []   
    list_keys = list(data.data.keys())
    for i in list_keys:
        cnt_simple.append(get_count_search(1, data,i, 0))

    new_dict = data.sorting_by_keys()
    list_keys = list(new_dict.keys())
    lk = list(data.data.keys())
    for i in lk:
        cnt_bin.append(get_count_search(2, data, i, list_keys))

    plt.ylabel('Количество сравнений')
    plt.figure(figsize=(15, 15))
    plt.bar(x_list, cnt_simple, color='#0504aa')
    ax = plt.gca()
    ax.tick_params(axis='x', labelrotation=90)
    ax.set_xticklabels([])
    plt.savefig('./png1.png')
    plt.gcf().clear()

    plt.ylabel('Количество сравнений')
    plt.figure(figsize=(15, 15))
    plt.bar(x_list, cnt_bin, color='#0504aa')
    ax = plt.gca()
    ax.tick_params(axis='x', labelrotation=90)
    ax.set_xticklabels([])
    plt.savefig('png2.png')
    plt.gcf().clear()

    x = zip(x_list, cnt_bin)
    xs = sorted(x, key=lambda tup: tup[1], reverse=True)
    keys = [x[0] for x in xs]
    results_k = [x[1] for x in xs]

    plt.ylabel('Количество сравнений')
    plt.bar(x_list, results_k, color='#0504aa')
    ax = plt.gca()
    ax.tick_params(axis='x', labelrotation=90)
    ax.set_xticklabels([])
    plt.savefig('png3.png')
    plt.gcf().clear()


def main():
    data = Dictionary('info.csv')
    #test_cmp(data)
    test_time(data)
    key = input('Словарь содержит следующую структуру\n \
    key - Город; value - Население\n Введите ключ: ')

    if key == '':
        print('Ошибка при вводе ключа, пожалуйста, повторите ввод\n')
        key = input('Введите ключ: ')

    a = data.BruteForceSearch(key)
    print("Value 1 (BFS): {0}".format(data.BruteForceSearch(key)))

    new_dict = data.sorting_by_keys()
    list_keys = list(new_dict.keys())
    print("Value 2 (BS): {0}".format(data.BinarySearch(key, list_keys)))

    list_keys = list(data.data.keys())
    for i in list_keys:
        data.BruteForceSearch(i)

    new_dict = data.sorting_by_keys()
    list_keys = list(new_dict.keys())
    lk = list(data.data.keys())
    for i in lk:
        data.BinarySearch(i,list_keys)
    data.f.close()
    data.f1.close()

    
main()