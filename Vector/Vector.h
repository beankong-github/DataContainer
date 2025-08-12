#pragma once
#include <cassert>

template<typename T>
class Vector
{
public:
	Vector()
		:size(0), capacity(2)
	{
		data = new T[capacity];
	}

	// RAII
	~Vector()
	{
		if (data)
		{
			delete[] data;
		}
	}

	// 데이터 추가 함수
	void PushBack(const T& data)
	{
		if (size == capacity)
		{
			ReAllocate(capacity*2);
			
		}

		// 마지막 요소 다음 위치에 새로운 값 저장
		data[size] = value;
		// 저장된 요소의 크기 증가
		++size;
	}

	// Getter
	int Size() const { return size; }
	int Capacity() const { return capacity; }
	T* Data() const { return data; }

	const T& operator[](int index) const
	{
		assert(index > -1 && index < size);
		return data[index];
	}

private:
	void ReAllocate(int newCapacity)
	{
		// todo 재할당
		// 1. 새로운 공간 할당
		//int newCapacity = capacity * 2;
		T* newBlock = new T[newCapacity];
		memset(newBlock, 0, sizeof(T) * newCapacity);

		// 2. 기존 값 복사/이동
		//for (int i = 0; i < capacity; ++i)
		//{
		//	newBlock[i] = data[i];
		//}

		memcpy_s(newBlock, newCapacity, sizeof(T) * capacity);

		// 3. 다 쓴 메모리 공간 해제 및 업데이트
		delete[] data;
		data = newBlock;
		capacity = newCapacity;
	}

private:
	// 자료 컨테이너
	T* data = nullptr;
	// 배열에 저장된 데이터 수
	int size = 0;
	// 미리 확보해둔 저장 공간의 크기
	int capacity = 0;
};