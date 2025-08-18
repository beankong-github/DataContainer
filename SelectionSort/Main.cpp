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
	// 예외 처리
	if (length < 1)
		return;

	// 외부 루프는 n-1번 반복
	for (int ix = 0; ix < length - 1; ++ix)
	{
		// 현재 순회에서 가장 왼쪽 값 찾기.
		int minIndex = ix;

		// 내부 루프는 ix에서 끝까지 반복
		for (int jx = ix; jx < length; ++jx)
		{
			// 최소값의 인덱스 찾기
			if (array[jx] < array[minIndex])
				minIndex = jx;
		}

		// 교환
		if (minIndex != ix)
			Swap(array[ix], array[minIndex]);
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
	int array[] = { 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16 };

	PrintArray(array, 16);
	SelectionSort(array, 16);
	PrintArray(array, 16);
}