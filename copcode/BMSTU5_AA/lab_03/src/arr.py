
def inputArr():
    n = int(input("Введите n: "))
    arr = list()

    if (not n):
        return
    for _ in range(n):
        arr.append(int(input("Введите элемент: ")))

    return arr


def outputArr(arr):
    for i in range(len(arr)):
        print(arr[i], end=" ")
    print()
