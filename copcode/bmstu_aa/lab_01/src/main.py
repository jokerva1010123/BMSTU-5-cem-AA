from algorithms import levenstein, damerau_levenstein, damerau_levenstein_recursive, damerau_levenstein_recursive_cache_matrix
from proc_time import analize_algorithm
from tests import test_algorithm

MSG = ["Алгоритм Левенштейна",
       "Алгоритм Дамерау-Левенштейна (нерекурсивный)",
       "Алгоритм Дамерау-Левенштейна (рекурсивный)",
       "Алгоритм Дамерау-Левенштейна (рекурсивный с кешем)"]


if __name__ == '__main__':
    choice = 1
    while choice != 0:
        print("Меню")
        print("1. Работа алгоритмов:")
        print("     - Левенштейн")
        print("     - Дамерау-Левенштейн (нерекурсивный)")
        print("     - Дамерау-Левенштейн (рекурсивный)")
        print("     - Дамерау-Левенштейн (рекурсивный с кешем)")
        print("2. Замеры процессорного времени")
        print("3. Тестирование алгоритмов")
        print("0. Выход")

        print(">  ", end='')
        choice = int(input())

        # str_1 = "увлечение"
        # str_2 = "развлечения"

        if choice == 1:
            str_1 = input("Введите первое слово: ")
            str_2 = input("Введите второе слово: ")

            print("\n", "=" * 75)
            print(MSG[0])
            levenstein(str_1, str_2, True)

            print("\n", "=" * 75)
            print(MSG[1])
            damerau_levenstein(str_1, str_2, True)

            print("\n", "=" * 75)
            print(MSG[2])
            print("Ответ: ", damerau_levenstein_recursive(str_1, str_2))

            print("\n", "=" * 75)
            print(MSG[3])
            damerau_levenstein_recursive_cache_matrix(str_1, str_2, True)
        elif choice == 2:
            analize_algorithm()
        elif choice == 3:
            test_algorithm(levenstein, MSG[0], 0)
            test_algorithm(damerau_levenstein, MSG[1], 1)
            test_algorithm(damerau_levenstein_recursive, MSG[2], 2)
            test_algorithm(damerau_levenstein_recursive_cache_matrix, MSG[3], 3)
