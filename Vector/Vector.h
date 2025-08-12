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

	// ������ �߰� �Լ�
	void PushBack(const T& data)
	{
		if (size == capacity)
		{
			ReAllocate(capacity*2);
			
		}

		// ������ ��� ���� ��ġ�� ���ο� �� ����
		data[size] = value;
		// ����� ����� ũ�� ����
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

		memcpy_s(newBlock, newCapacity, sizeof(T) * capacity);

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