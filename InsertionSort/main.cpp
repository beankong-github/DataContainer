#include <iostream>

#define ArraySize(array) sizeof(array)/sizeof(array[0])

template<typename T>
void Swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

// 삽입 정렬
void InsertionSort(int* array, int length)
{
	if (length <= 1)
		return;


	// 정렬
	for (int ix = 1; ix < length; ++ix)
	{
		// 키 추출
		// arr[jx] - KeyValue(arr[ix]) - ...
		int keyValue = array[ix];
		int jx = ix - 1;

		// 값을 
		while (jx >= 0 && array[jx] > keyValue)
		{
			// 값 밀기
			// arr[jx] - arr[jx] 
			array[jx + 1] = array[jx];
			--jx;
		}

		// 키 삽입
		array[jx + 1] = keyValue;

	}
}

// 배열 출력 함수.
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