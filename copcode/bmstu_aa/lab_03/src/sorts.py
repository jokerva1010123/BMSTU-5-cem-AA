# Перестройка сортирующего дерева (максимумы в конец)
def heapify(arr, n, i):
    largest = i
    left = 2 * i + 1
    right = 2 * i + 2

    if left >= n and right >= n:
        return

    if left < n and arr[i] < arr[left]:
        largest = left

    if right < n and arr[largest] < arr[right]:
        largest = right

    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]
        heapify(arr, n, largest)


# Пирамидальная сортировка
def heapsort(arr):
    n = len(arr)

    # Формирование первоначального сортирующего дерева
    for i in range(n, -1, -1):
        heapify(arr, n, i)

    for i in range(n - 1, 0, -1):
        arr[i], arr[0] = arr[0], arr[i]
        heapify(arr, i, 0)

    return arr


# Выбором
def selectionsort(arr):
    for i in range(len(arr)):
        minind = i
        for j in range(i+1, len(arr)):
            if arr[j] < arr[minind]:
                minind = j
        arr[i], arr[minind] = arr[minind], arr[i]
    return arr


# Шейкер (сортировка перемешиванием)
def shakersort(arr):
    left = 0
    right = len(arr) - 1
    while left < right:
        r_new = left
        for i in range(left, right):
            if arr[i] > arr[i + 1]:
                arr[i], arr[i + 1] = arr[i + 1], arr[i]
                r_new = i
        right = r_new
        l_new = right
        for i in range(right - 1, left - 1, -1):
            if arr[i] > arr[i + 1]:
                arr[i], arr[i + 1] = arr[i + 1], arr[i]
                l_new = i
        left = l_new
    return arr