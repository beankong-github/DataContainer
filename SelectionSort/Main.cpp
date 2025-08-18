#include <iostream>

#define ArraySize(array) sizeof(array)/sizeof(array[0])

template<typename T>
void Swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

void SelectionSort(int* array, int length)
{
	// ���� ó��
	if (length < 1)
		return;

	// �ܺ� ������ n-1�� �ݺ�
	for (int ix = 0; ix < length - 1; ++ix)
	{
		// ���� ��ȸ���� ���� ���� �� ã��.
		int minIndex = ix;

		// ���� ������ ix���� ������ �ݺ�
		for (int jx = ix; jx < length; ++jx)
		{
			// �ּҰ��� �ε��� ã��
			if (array[jx] < array[minIndex])
				minIndex = jx;
		}

		// ��ȯ
		if (minIndex != ix)
			Swap(array[ix], array[minIndex]);
	}
}

// �迭 ��� �Լ�.
void PrintArray(int array[], int length)
{
	for (int ix = 0; ix < length; ++ix)
	{
		std::cout << array[ix];

		if (ix < length - 1)
		{
			std::cout << ", ";
		}
	}

	std::cout << "\n";
}

int main()
{
	int array[] = { 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16 };

	PrintArray(array, 16);
	SelectionSort(array, 16);
	PrintArray(array, 16);
}