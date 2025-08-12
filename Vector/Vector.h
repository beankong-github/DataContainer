#pragma once
#include <cassert>


// �ݺ���
// ���� �����͸� ĸ��ȭ�� Ŭ����
// ��� �ڷᱸ���� �ݺ� ó���� �����ϱ� ���� STL���� ���
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

// ���ø��� ���� ���Ͽ��� ���� �� �����ؾ� ��.

// ���� �迭
// �����߿� ũ�Ⱑ ���� �� �ִ� �迭
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

	// ������ �߰� �Լ�
	void PushBack(const T& data)
	{
		if (size == capacity)
		{
			// ���Ҵ��� 2���
			ReAllocate(capacity*2);
		}

		// ������ ��� ���� ��ġ�� ���ο� �� ����
		this->data[size] = data;
		// ����� ����� ũ�� ����
		++size;
	}

	// R-Value Reference
	void PushBack(const T&& data)
	{
		if (size == capacity)
		{
			// ���Ҵ��� 2���
			ReAllocate(capacity * 2);
		}

		// ������ ��� ���� ��ġ�� ���ο� �� ����
		// r value�̹Ƿ� move semantic ���
		this->data[size] = std::move(data);
		// ����� ����� ũ�� ����
		++size;
	}

	// Getter
	int Size() const { return size; }
	int Capacity() const { return capacity; }
	T* Data() const { return data; }

	// ������ �����ε�
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

	// ���� �Լ�(at) , �����Լ�(set)
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

	
	// �ݺ���
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
		// todo ���Ҵ�
		// 1. ���ο� ���� �Ҵ�
		//int newCapacity = capacity * 2;
		T* newBlock = new T[newCapacity];
		memset(newBlock, 0, sizeof(T) * newCapacity);

		// 2. ���� �� ����/�̵�
		//for (int i = 0; i < capacity; ++i)
		//{
		//	newBlock[i] = data[i];
		//}

		memcpy_s(newBlock, sizeof(T) * newCapacity, data, sizeof(T) * capacity);

		// 3. �� �� �޸� ���� ���� �� ������Ʈ
		delete[] data;
		data = newBlock;
		capacity = newCapacity;
	}

private:
	// �ڷ� �����̳�
	T* data = nullptr;
	// �迭�� ����� ������ ��
	int size = 0;
	// �̸� Ȯ���ص� ���� ������ ũ��
	int capacity = 0;
};