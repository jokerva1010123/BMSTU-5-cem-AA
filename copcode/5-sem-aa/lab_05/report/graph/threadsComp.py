import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
x = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]
y1 = [1645, 2265, 3855, 5521, 6124, 6724, 9355, 9999, 11742, 12212]
y2 = [472, 2028, 3371, 3815, 4265, 5670, 6175, 6602, 8080, 9569]
fig, ax = plt.subplots()
# Построение графика
plt.xlabel("Количество заявок")
plt.ylabel("Время выполнения (мс)")
plt.plot(x, y1, label = "Последовательное выполнение")
plt.plot(x, y2, label = "Конвейер")
plt.legend()
plt.show()

