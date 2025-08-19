#include <iostream>

#define ArraySize(array) sizeof(array)/sizeof(array[0])

template<typename T>
void Swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

// ���� ����
void InsertionSort(int* array, int length)
{
	if (length <= 1)
		return;


	// ����
	for (int ix = 1; ix < length; ++ix)
	{
		// Ű ����
		// arr[jx] - KeyValue(arr[ix]) - ...
		int keyValue = array[ix];
		int jx = ix - 1;

		// ���� 
		while (jx >= 0 && array[jx] > keyValue)
		{
			// �� �б�
			// arr[jx] - arr[jx] 
			array[jx + 1] = array[jx];
			--jx;
		}

		// Ű ����
		array[jx + 1] = keyValue;

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

}