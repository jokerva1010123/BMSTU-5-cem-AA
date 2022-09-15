from arr import *
from sort import *
from color import *

def main():
	arr = inputArr()

	output("Введенный массив:", GREEN)
	outputArr(arr)

	arr_bubble = sort_bubble(arr)

	output("Отсортированный массив (Пузырек):", GREEN)
	outputArr(arr_bubble)

	arr_insert = sort_insert(arr)
	output("Отсортированный массив (Вставками):", GREEN)
	outputArr(arr_insert)

	arr_quick = quick_sort(arr)
	output("Отсортированный массив (Quick sort):", GREEN)
	outputArr(arr_quick)

if __name__ == "__main__":
	main()	
