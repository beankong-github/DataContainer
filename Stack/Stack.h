#pragma once
#include <iostream>

#define TEST 1

#if TEST 
const int stackCount = 1;
#else 
const int stackCount = 100;
#endif

template<typename T>
class Stack
{
public:
	Stack();
	~Stack() = default;
	
	// ���� ����
	void Clear()
	{
		memset(data, 0, sizeof(T) * stackCount);
		count = 0;
	}

	// ������ ������� Ȯ��
	bool IsEmpty() const
	{
		return count == 0;
	}

	//������ ����á���� Ȯ��
	bool IsFull() const
	{
		return count == stackCount;
	}

	// ���ÿ� ������ �߰�
	bool Push(const T& exp)
	{
		if (IsFull())
		{
			MessageBoxA(nullptr, "������ ���� �� �־ �߰��� �Ұ���", "Stack Push Error", MB_OK);
			return false;
		}
		data[count] = exp;
		++count;

		std::cout << "Push!  " << data[count - 1] << std::endl;

		return true;
	}

	// ���ÿ��� ������ ����
	T Pop()
	{
		if (IsEmpty())
		{
			MessageBoxA(nullptr, "������ ��� �־ ������ �Ұ���", "Stack Pop Error", MB_OK);
			return false;
		}

		--count;
		std::cout << "Pop!  " << data[count] << std::endl;
		return data[count];
	}

	// ���ÿ� ����� ������ �� ��ȯ 
	int Count() const
	{
		return count;
	}

private:
	// ������ ���� ����
	T data[stackCount] = {};
	// ���ÿ� ����� �ڷ� ��
	// count�� head(top)���� Ȱ��
	// ���ο� �����͸� �߰��� ��ġ �ε���
	int count = 0;

};