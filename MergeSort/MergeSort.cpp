#include "MergeSort.h"

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


void Merge(int* array, int* leftArray, int leftArrayLength, int* rightArray, int rightArrayLength)
{
	// 인덱스 초기화
	int leftIndex = 0;
	int rightIndex = 0;
	int mergedIndex = 0;

	// 왼쪽/오른쪽 배열의 요소를 비교해 더 작은 배열의 요소를 array에 복사
	while (leftIndex < leftArrayLength && rightIndex < rightArrayLength)
	{
		// 크기 비교
		// 1. 왼쪽이 더 작거나 같은 경우 -> 왼쪽 배열의 것을 선택
		if (leftArray[leftIndex] <= rightArray[rightIndex])
		{
			array[mergedIndex] = leftArray[leftIndex];
			++leftIndex;
		}
		// 2. 오른쪽이 더 작은 경우 -> 오른쪽 배열의 것을 선택
		else
		{
			array[mergedIndex] = rightArray[rightIndex];
			++rightIndex;
		}

		// 병합 배열의 인덱스 증가 처리
		++mergedIndex;
	}

	// 남아 있는 요소 병합
	while (leftIndex < leftArrayLength)
	{
		array[mergedIndex] = leftArray[leftIndex];
		++leftIndex;
		++mergedIndex;
	}

	while (rightIndex < rightArrayLength)
	{
		array[mergedIndex] = rightArray[rightIndex];
		++rightIndex;
		++mergedIndex;
	}

}

void MergeSort(int* array, int length)
{
	// 예외 처리 (재귀 함수 종료 조건)
	if (length <= 1)
		return;

	// 배열 분할
	int mid = length / 2;

	// 분할될 두 배열의 공간 확보
	int* leftArray = new int[mid];
	memset(leftArray, 0, sizeof(int) * mid);
	int* rightArray = new int[length - mid];
	memset(rightArray, 0, sizeof(int) *(length- mid));

	// 값 복사
	//for (int ix = 0; ix < mid; ++ix)
	//{
	//	leftArray[ix] = array[ix];
	//}

	// 왼쪽 배열에 값 복사. 0~mid
	memcpy(leftArray, array, sizeof(int) * mid);
	// 오른쪽 배열에 값 복사, mid~(length-mid)
	memcpy(rightArray, array+mid, sizeof(int) *(length- mid));

	// 왼쪽 배열에 대해 병합 정렬
	MergeSort(leftArray, mid);
	// 오른쪽 배열에 대해 병합 정렬
	MergeSort(rightArray, length - mid);
	// 병합
	Merge(array, leftArray, mid, rightArray, length - mid);

	PrintArray(array, length);

	// 메모리 정리
	delete[] leftArray;
	delete[] rightArray;
}
