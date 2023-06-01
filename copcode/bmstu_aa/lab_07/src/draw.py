import matplotlib.pyplot as plt
fig1 = plt.figure(figsize=(10, 7))
plot = fig1.add_subplot()
values = [10, 20, 30, 40, 50, 100, 150, 200, 250, 300, 350, 400, 450, 500]
very_slow = [1, 0.8, 0.6, 0.6, 0.6, 0.2, 0, 0, 0, 0, 0, 0, 0, 0]
slow = [0, 0.2, 0.4, 0.2, 0, 0.4, 0.2, 0, 0, 0, 0, 0, 0, 0]
avg = [0, 0, 0, 0.2, 0.4, 0.4, 0.4, 0.4, 0, 0, 0, 0, 0, 0]
fast = [0, 0, 0, 0, 0, 0, 0.4, 0.4, 0.6, 0.4, 0, 0, 0, 0]
very_fast = [0, 0, 0, 0, 0, 0, 0, 0.2, 0.4, 0.6, 1, 1, 1, 1]
not_very_fast = [0, 0.2, 0.4, 0.4, 0.6, 1, 0.6, 0.4, 0, 0, 0, 0, 0, 0]
not_very_slow = [0, 0, 0, 0.2, 0.4, 0.4, 0.8, 0.8, 0.6, 0.6, 0, 0, 0, 0]


def expert_opinion(feature):
    if feature == 'очень медленные':
        return 1
    elif feature == 'медленные':
        return 2
    elif feature == 'средние':
        return 3
    elif feature == 'быстрые':
        return 4
    elif feature == 'очень быстрые':
        return 5
    return None

plot.plot(values, very_slow, label ="«очень медленные»")
plot.plot(values, slow, "--", label="«медленные»", marker="o")
plot.plot(values, avg, "-.", label="«средние»", marker="v")
plot.plot(values, fast, ":", label="«быстрые»", marker="^")
plot.plot(values, very_fast, "--", label="«очень быстрые»", marker="<")
plot.plot(values, not_very_fast, "-.", label="«не очень быстрые»", marker=">")
plot.plot(values, not_very_slow, ":", label="«не очень медленные»", marker="s")

plt.legend()
plt.grid()
plt.title("Графики функций принадлежности числовых значений переменной термам")
plt.ylabel("μ")
plt.xlabel("Максимальная скорость автомобиля, км\ч")

plt.show()