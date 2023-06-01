from sorts import heapsort, selectionsort, shakersort
from proc_time import analyze_sorts

MSG = ["Пирамидальная",
       "Выбором",
       "Перемешиванием"]


if __name__ == '__main__':
    choice = 1
    while choice != 0:
        print("Меню")
        print("1. Сортировка массива:")
        print("     - Пирамидальная")
        print("     - Выбором")
        print("     - Перемешиванием")
        print("2. Замеры процессорного времени")
        print("0. Выход")

        print(">  ", end='')
        choice = int(input())

        if choice == 1:
            n = int(input("Введите длину массива: "))
            arr = list(int(input()) for _ in range(n))

            print("\n", "=" * 75)
            print("Пирамидальная сортировка")
            temp_arr = list(arr)
            print("Array: ", temp_arr)
            print("Sorted array: ", heapsort(temp_arr))

            print("\n", "=" * 75)
            print("Сортировка выбором")
            temp_arr = list(arr)
            print("Array: ", temp_arr)
            print("Sorted array: ", selectionsort(temp_arr))

            print("\n", "=" * 75)
            print("Сортировка перемешиванием")
            temp_arr = list(arr)
            print("Array: ", temp_arr)
            print("Sorted array: ", shakersort(temp_arr))
            print()

        elif choice == 2:
            analyze_sorts()
