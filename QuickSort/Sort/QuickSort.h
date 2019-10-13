#pragma once

#ifndef QuickSort
#define QuickSort

template<typename T, typename Compare>
void Sort(T* first, T* last, Compare comp) {
	int size = Size(first, last);
	if (size < 2) {
		return;
	}

	T* pivot = Partition(first, last, RandPivot(first, last), comp);

	Sort(first, pivot - 1, comp);
	Sort(pivot + 1, last, comp);
}

template <typename T, typename Comp>
T* Partition(T* first, T* last, T* pivot, Comp comp) {
	int length = Size(first, last);

	T* i = first;

	T pivotValue = *pivot;
	Swap(pivot, last);

	for (T* j = first; j != last; j++)
	{
		if (!comp(pivotValue, *j)) {
			Swap(i, j);

			i++;
		}
	}

	Swap(i, last);

	return i;
}

template<typename T, typename Compare>
void InsertionSort(T* first, T* last, Compare comp) {
	int size = Size(first, last);
	for (int i = 1; i < size; i++)
		for (int j = i; j > 0 && !comp(*(first + j - 1), *(first + j)); j--)
			Swap(first + j - 1, first + j);
}

template<typename T>
T* RandPivot(T* first, T* last) {
	int randInt = rand() % 3 + 1;
	if (randInt == 1) {
		return first;
	}
	if (randInt == 2) {
		return last;
	}
	int size = Size(first, last);
	return first + size / 2;
}

template<typename T>
void Swap(T* first, T* second) {
	T temp = *first;
	*first = *second;
	*second = temp;
	return;
}

template<typename T>
int Size(T* first, T* last) {
	return last - first + 1;
}
#endif