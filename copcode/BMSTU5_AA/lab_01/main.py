from algorithms import *
from color import *


def main():
    output("Введите первую строку:", GREEN)  # Column
    strFirst = input(YELLOW)
    output("Введите вторую строку:", GREEN)  # Row
    strSecond = input(YELLOW)
    # output("Выбор алгоритма:\
    # 1. Расстояние Левенштейна(Матричный алгоритм)\
    # 2. Расстояние Левенштейна(Рекурсивный алгоритм)\
    # 3. Расстояние Дамерау - Левенштейна(Матричный алгоритм)\
    # 4. Расстояние Дамерау-Левенштейна (Рекурсивный алгоритм)  ", TURQUOISE)  # Row
    #     mode = input(YELLOW)

    distanceLev = Levenshtein(strFirst, strSecond, True)
    distanceDamLev = DamerauLevenshtein(strFirst, strSecond)

    output("Расстояние Левенштейна: " + str(distanceLev), GREEN)

    if distanceLev != distanceDamLev:
        output("Расстояние Дамерау-Левенштейна: " + str(distanceDamLev), GREEN)


if __name__ == "__main__":
    main()
