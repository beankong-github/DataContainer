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
	// �ε��� �ʱ�ȭ
	int leftIndex = 0;
	int rightIndex = 0;
	int mergedIndex = 0;

	// ����/������ �迭�� ��Ҹ� ���� �� ���� �迭�� ��Ҹ� array�� ����
	while (leftIndex < leftArrayLength && rightIndex < rightArrayLength)
	{
		// ũ�� ��
		// 1. ������ �� �۰ų� ���� ��� -> ���� �迭�� ���� ����
		if (leftArray[leftIndex] <= rightArray[rightIndex])
		{
			array[mergedIndex] = leftArray[leftIndex];
			++leftIndex;
		}
		// 2. �������� �� ���� ��� -> ������ �迭�� ���� ����
		else
		{
			array[mergedIndex] = rightArray[rightIndex];
			++rightIndex;
		}

		// ���� �迭�� �ε��� ���� ó��
		++mergedIndex;
	}

	// ���� �ִ� ��� ����
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
	// ���� ó�� (��� �Լ� ���� ����)
	if (length <= 1)
		return;

	// �迭 ����
	int mid = length / 2;

	// ���ҵ� �� �迭�� ���� Ȯ��
	int* leftArray = new int[mid];
	memset(leftArray, 0, sizeof(int) * mid);
	int* rightArray = new int[length - mid];
	memset(rightArray, 0, sizeof(int) *(length- mid));

	// �� ����
	//for (int ix = 0; ix < mid; ++ix)
	//{
	//	leftArray[ix] = array[ix];
	//}

	// ���� �迭�� �� ����. 0~mid
	memcpy(leftArray, array, sizeof(int) * mid);
	// ������ �迭�� �� ����, mid~(length-mid)
	memcpy(rightArray, array+mid, sizeof(int) *(length- mid));

	// ���� �迭�� ���� ���� ����
	MergeSort(leftArray, mid);
	// ������ �迭�� ���� ���� ����
	MergeSort(rightArray, length - mid);
	// ����
	Merge(array, leftArray, mid, rightArray, length - mid);

	PrintArray(array, length);

	// �޸� ����
	delete[] leftArray;
	delete[] rightArray;
}
