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
	
	// 스택 비우기
	void Clear()
	{
		memset(data, 0, sizeof(T) * stackCount);
		count = 0;
	}

	// 스택이 비었는지 확인
	bool IsEmpty() const
	{
		return count == 0;
	}

	//스택이 가득찼는지 확인
	bool IsFull() const
	{
		return count == stackCount;
	}

	// 스택에 데이터 추가
	bool Push(const T& exp)
	{
		if (IsFull())
		{
			MessageBoxA(nullptr, "스택이 가득 차 있어서 추가가 불가능", "Stack Push Error", MB_OK);
			return false;
		}
		data[count] = exp;
		++count;

		std::cout << "Push!  " << data[count - 1] << std::endl;

		return true;
	}

	// 스택에서 데이터 추출
	T Pop()
	{
		if (IsEmpty())
		{
			MessageBoxA(nullptr, "스택이 비어 있어서 추출이 불가능", "Stack Pop Error", MB_OK);
			return false;
		}

		--count;
		std::cout << "Pop!  " << data[count] << std::endl;
		return data[count];
	}

	// 스택에 저장된 데이터 수 반환 
	int Count() const
	{
		return count;
	}

private:
	// 데이터 저장 공간
	T data[stackCount] = {};
	// 스택에 저장된 자료 수
	// count를 head(top)으로 활용
	// 새로운 데이터를 추가할 위치 인덱스
	int count = 0;

};