def test_algorithm(func, func_name, num):
    tests = [["", "", 0, 0, 0, 0],
             ["", "hugo", 4, 4, 4, 4],
             ["applejack", "", 9, 9, 9, 9],
             ["house", "house", 0, 0, 0, 0],
             ["car", "cars", 1, 1, 1, 1],
             ["decode", "decoding", 3, 3, 3, 3],
             ["class", "clsas", 2, 1, 1, 1],
             ["kingtoys", "ikdfotpq", 7, 6, 6, 6],
             ["unique", "nueqeu", 5, 3, 3, 3],
             ["qwertyuiop", "wqreytiupo", 6, 5, 5, 5],
             ["sweetbloody", "croatlbiawe", 10, 9, 9, 9]]

    print("-" * 30)
    print("Testing {}".format(func_name))
    for test in tests:

        if (func(test[0], test[1]) == test[2 + num]):
            if test[0] == '':
                test[0] = "'Пустая строка'"
            if test[1] == '':
                test[1] = "'Пустая строка'"
            print("SUCCESS: {}, {}, res = {}".format(test[0], test[1], test[2 + num]))
        else:
            print("FAILED")
