#pragma once

template<typename T>
void Swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

int Partition(int* arr, int left, int right);

void QuickSort(int* arr, int left, int right);