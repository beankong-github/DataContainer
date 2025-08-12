#include <iostream>
#include <cassert>

// stl
#include <array>

// 배열 클래스
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
		// 인덱스 범위 밖이면 assert
		assert(index >= 0 && index < size);
		return data[index];
	}

private:
	T data[size];
};


// 진입점이 필요한 이유(main)
// ㄴ> 실행용이라 즉, Application(.exe)라 필요하다. 라이브러리면 진입점 필요없음.
int main()
{
	//// 배열(Array)
	//const int arrayCount = 10;
	//int arr[arrayCount] = {}; // 초기화 방법 1. 
	//memset(arr, 0, sizeof(int) * 5);  // 초기화 방법 2.


	//// 동적 배열(Dynamic Array)
	//// 실행중에 저장공간이 변경된다.
	//int heapArrayCount = 10;
	//int* heapArray = new int[heapArrayCount];
	//memset(heapArray, 0, sizeof(int) * 5);  // 초기화 방법 2.
	//delete[] heapArray;

	// 사용자 정의 배열
	Array<int, 19> array;
	for (int i = 0; i < array.GetSize(); ++i)
	{
		array[i] = i + 1;
	}

	std::array<int, 10> stdArray;
	
	std::cin.get();
}