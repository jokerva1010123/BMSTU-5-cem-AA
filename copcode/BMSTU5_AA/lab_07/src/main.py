from dictionary import Dictionary
from time import clock

COUNT = 10000
GREEN = '\033[32m'
YELLOW = '\033[33m'
BLUE = '\033[34m'


def main():
    data = Dictionary('world.csv')

    print(YELLOW)
    key = input("Input key: ")
    if key == '':
        return

    print(BLUE)
    print("\nValue:\n{0}\n".format(data.SequentialSearch(key)))

    t1 = clock()
    for _ in range(COUNT):
        data.SequentialSearch(key)
    t2 = clock()
    print(GREEN)
    print("Time sequential search: {0}\n".format(t2 - t1))

    t1 = clock()
    new_dict = data.sorting_by_keys()
    list_keys = list(new_dict.keys())
    t2 = clock()
    # print(YELLOW)
    # print("Sorting time : {0}".format(t2 - t1))

    t1 = clock()
    for _ in range(COUNT):
        data.BinarySearch(key, list_keys)
    t2 = clock()
    print(GREEN)
    print("Time binary search: {0}\n".format(t2 - t1))

    t1 = clock()
    new_dict = data.parser()
    t2 = clock()
    # print(YELLOW)
    # print("Data preparation: {0}".format(t2 - t1))

    t1 = clock()
    for _ in range(COUNT):
        data.Search(key, new_dict)
    t2 = clock()
    print(GREEN)
    print("Time search: {0}".format(t2 - t1))


if __name__ == "__main__":
    main()
