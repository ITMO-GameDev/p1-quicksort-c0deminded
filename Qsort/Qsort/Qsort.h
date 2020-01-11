#pragma once

const int expProp = 100;
template <typename T, typename Comparer>
void sort(T *first, T *last, Comparer comp) {
	int length = last - first + 1;

	if (length >= 2) {
		if (length < expProp)
			insertion_sort(first, last, comp);
		else
			quicksort(first, last, comp);
	}
	return;
}

template<typename T>
void swap(T* a, T* b) {
	T t = *a;
	*a = *b;
	*b = t;
	return;
}

template <typename T, typename Comparer>
void insertion_sort(T *first, T *last, Comparer comp) {
	int length = last - first + 1;
	for (int i = 1; i < length; i++)
		for (int j = i; j > 0 && !comp(*(first + j - 1), *(first + j)); j--)
			swap(first + j - 1, first + j);
}

template <typename T, typename Comparer>
T median(T *first, T *last, Comparer comp) {
	T tmp_array[3];
	T* middle = first + (last - first) / 2;
	tmp_array[0] = *first;
	tmp_array[1] = *middle;
	tmp_array[2] = *last;
	insertion_sort(tmp_array, tmp_array + (std::size(tmp_array) - 1), comp);
	return tmp_array[1];
}

template <typename T, typename Comparer>
void quicksort(T *first, T *last, Comparer comp) {
	int length = last - first + 1;

	T pivot = median(first, last, comp);

	int left = 0;
	int right = length - 1;
	while (left <= right) {
		while (comp(first[left], pivot))
			left++;
		while (comp(pivot, first[right]))
			right--;
		if (left <= right) {
			swap(&first[left], &first[right]);
			left++;
			right--;
		}
	}

	if (right > 0)
		sort(first, first + right, comp);
	if (length > left)
		sort(first + left, last, comp);
}
