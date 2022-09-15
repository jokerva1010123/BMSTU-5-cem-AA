from world_info import WorldInfo


class Dictionary(object):
    data = dict()

    def __init__(self, file_name):
        self.LoadData(file_name)

    def LoadData(self, file_name):
        f = open(file_name, 'r')

        for line in f:
            array = line.split(',')
            key = array[1]
            self.data[key[1:-1]] = WorldInfo(array[2],
                                             int(array[3]), array[4], int(array[5]), int(array[6]))
            # print(self.data[array[1]])

        f.close()

    def Log(self):
        for elem in self.data:
            print(elem)
            print(self.data.setdefault(elem))

    def __getitem__(self, key):
        return self.data.get(key)

    def sorting_by_keys(self):
        new_dict = dict()
        list_keys = list(self.data.keys())
        list_keys.sort()

        for i in list_keys:
            new_dict[i] = self.data[i]
            # print(i, ':', self.data[i])

        return new_dict

    def sorting_by_values(self, data):
        new_dict = dict()

        list_d = list(data.items())
        list_d.sort(key=lambda i: i[1], reverse=True)
        for elem in list_d:
            # print(elem[0], elem[1])
            new_dict[elem[0]] = elem[1]

        return new_dict

    def SequentialSearch(self, key):
        for elem in self.data:
            if key == elem:
                return self.data[elem]
        return -1

    def BinarySearch(self, key, list_keys):
        l, r = 0, len(list_keys) - 1

        while l <= r:
            middle = (r + l) // 2  # Оптимизация ? (l + (r - l) // 2)
            elem = list_keys[middle]

            if elem == key:
                return self.data[elem]

            elif elem < key:
                l = middle + 1

            else:
                r = middle - 1

        return -1

    def parser(self):
        # Разбиваем по буквам алфавита и
        # Сортируем (по убыванию) по кол-ву элементов в каждой букве.
        count_dict = {i: 0 for i in "ABCDEFGHIJKLMNOPQRSTUVWXYZ"}
        # count_dict будет содрежать
        # Кол-во слов для каждой буквы.
        for key in self.data:
            count_dict[key[0]] += 1

        # Сортируем по убыванию значений.
        count_dict = self.sorting_by_values(count_dict)

        # Создаем новый словарь (он будет отсортирован
        # по убыванию кол-ва значений.
        new_dict = {i: dict() for i in count_dict}

        # Заполняем новый словарь.
        for key in self.data:
            new_dict[key[0]].update({key: self.data[key]})

        # for key in new_dict:
        # 	print(key, '\n\n')
        # 	for elem in new_dict[key]:
        # 		print(elem, new_dict[key][elem], "\n")

        return new_dict

    def Search(self, key, new_dict):
        for k in new_dict:
            # Если нашли нужную букву
            if key[0] == k:
                # То начинаем искать.
                for elem in new_dict[k]:
                    if elem == key:
                        return new_dict[k][elem]
                # Если не нашли среди слов, которые были
                # На искомую букву, значит в словаре нет такого слова.
                return -1

        return -1
