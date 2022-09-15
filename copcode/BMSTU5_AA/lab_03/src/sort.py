
def sort_bubble(arr):
    n = len(arr) - 1

    for i in range(n):
        for j in range(n - i):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j+1] = arr[j+1], arr[j] 

    return arr


def sort_insert(arr):
    n = len(arr)

    for i in range(1, n):
        temp = arr[i]
        j = i
        while j > 0 and arr[j - 1] > temp:
            arr[j] = arr[j - 1]
            j -= 1
        arr[j] = temp

    return arr


def sort_quick_recursion(arr, begin, end):
    if begin < end:
        # Опорная точка. pivot.
        p = begin
        for i in range(begin + 1, end):
            if arr[i] < arr[begin]:
                p += 1
                arr[p], arr[i] = arr[i], arr[p]
        arr[begin], arr[p] = arr[p], arr[begin] 
        
        sort_quick_recursion(arr,  begin, p)
        sort_quick_recursion(arr, p + 1, end)

    return arr

def quick_sort(arr):
    return sort_quick_recursion(arr, 0, len(arr) - 1)


    
