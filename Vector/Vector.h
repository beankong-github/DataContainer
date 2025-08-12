#pragma once
#include <cassert>


// 반복자
// 원시 포인터를 캡슐화한 클래스
// 모든 자료구조의 반복 처리를 통일하기 위해 STL에서 사용
template<typename Vector>
class VectorIterator
{
public:
	using ValueType = typename Vector::ValueType;
	using PointerType = ValueType*;
	using ReferenceType = ValueType&;

public:
	VectorIterator(PointerType ptr)
		: ptr(ptr)
	{
	}

	VectorIterator& operator++()
	{
		++ptr;
		return *this;
	}

	VectorIterator& operator++(int)
	{
		VectorIterator iterator = *this;
		++(*this);
		return iterator;
	}

	VectorIterator& operator--()
	{
		ptr--;
		return *this;
	}

	VectorIterator& operator--(int)
	{
		VectorIterator iterator = *this;
		--(*this);
		return iterator;
	}

	ReferenceType operator[](int index)
	{
		return *(ptr + index);
	}

	PointerType operator->()
	{
		return ptr;
	}

	ReferenceType operator*()
	{
		return *ptr;
	}

	bool operator==(const VectorIterator& other) const
	{
		return ptr == other.ptr;
	}

	bool operator!=(const VectorIterator& other) const
	{
		return !(*this == other);
	}

private:
	PointerType ptr;
};

// 템플릿은 같은 파일에서 선언 및 구현해야 함.

// 동적 배열
// 실행중에 크기가 변할 수 있는 배열
template<typename T>
class Vector
{
public:
	using ValueType = T;
	using Iterator = VectorIterator<Vector<ValueType>>;

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
			// 재할당은 2배로
			ReAllocate(capacity*2);
		}

		// 마지막 요소 다음 위치에 새로운 값 저장
		this->data[size] = data;
		// 저장된 요소의 크기 증가
		++size;
	}

	// R-Value Reference
	void PushBack(const T&& data)
	{
		if (size == capacity)
		{
			// 재할당은 2배로
			ReAllocate(capacity * 2);
		}

		// 마지막 요소 다음 위치에 새로운 값 저장
		// r value이므로 move semantic 사용
		this->data[size] = std::move(data);
		// 저장된 요소의 크기 증가
		++size;
	}

	// Getter
	int Size() const { return size; }
	int Capacity() const { return capacity; }
	T* Data() const { return data; }

	// 연산자 오버로딩
	const T& operator[](int index) const
	{
		// Out of Range
		assert(index > -1 && index < size);
		return data[index];
	}

	T& operator[](int index)
	{
		// Out of Range
		assert(index > -1 && index < size);
		return data[index];
	}

	// 접근 함수(at) , 설정함수(set)
	T& At(int index)
	{
		// Out of Range
		assert(index > -1 && index < size);
		return data[index];
	}

	void Set(int index, const T& value)
	{
		data[index] = value;
	}

	
	// 반복자
	Iterator begin()
	{
		return Iterator(data);
	}

	Iterator end()
	{
		return Iterator(data + size);
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

		memcpy_s(newBlock, sizeof(T) * newCapacity, data, sizeof(T) * capacity);

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