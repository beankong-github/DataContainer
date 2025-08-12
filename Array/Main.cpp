#include <iostream>
#include <cassert>

// stl
#include <array>

// �迭 Ŭ����
template<typename T, int size>
class Array
{
public:
	Array()
	{
		memset(data, 0, sizeof(T) * size);
	}

	int GetSize() const { return size; }

	T& operator[](int index)
	{
		// �ε��� ���� ���̸� assert
		assert(index >= 0 && index < size);
		return data[index];
	}

private:
	T data[size];
};


// �������� �ʿ��� ����(main)
// ��> ������̶� ��, Application(.exe)�� �ʿ��ϴ�. ���̺귯���� ������ �ʿ����.
int main()
{
	//// �迭(Array)
	//const int arrayCount = 10;
	//int arr[arrayCount] = {}; // �ʱ�ȭ ��� 1. 
	//memset(arr, 0, sizeof(int) * 5);  // �ʱ�ȭ ��� 2.


	//// ���� �迭(Dynamic Array)
	//// �����߿� ��������� ����ȴ�.
	//int heapArrayCount = 10;
	//int* heapArray = new int[heapArrayCount];
	//memset(heapArray, 0, sizeof(int) * 5);  // �ʱ�ȭ ��� 2.
	//delete[] heapArray;

	// ����� ���� �迭
	Array<int, 19> array;
	for (int i = 0; i < array.GetSize(); ++i)
	{
		array[i] = i + 1;
	}

	std::array<int, 10> stdArray;
	
	std::cin.get();
}