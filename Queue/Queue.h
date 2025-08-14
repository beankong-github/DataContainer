#pragma once

#include <iostream>

const int maxQueueCount = 100;

class Queue
{
public:
	Queue()
	{
		memset(data, 0, sizeof(int) * maxQueueCount);
	}

	// 비었는지 확인
	bool IsEmpty() const
	{
		// 앞과 뒤를 가리키는 위치 값이 같으면 빈 상태
		return front == rear;
	}

	bool IsFull() const{
		return (rear + 1) % maxQueueCount == front;
	}

	//  출력

	// 큐에 데이터 추가
	bool Enqueue(int newData)
	{
		// 가득찼으면  데이터를 추가할 수 없다
		if (!IsFull())
		{
			return;
		}

		rear = (rear + 1) % maxQueueCount;
		data[rear] = newData;

		return true;
	}


	// 큐에서 데이터 추출
	bool Dequeue(int& outValue)
	{
		if (IsEmpty())
		{
			std::cout << "Error: 큐가 비어 있습니다. \n";
			return false;
		}
		front = (front + 1) % maxQueueCount;
		outValue = data[front];
		return true;
	}

	// 출력

private:
	int front = 0;
	int rear = 0; 
	int data[maxQueueCount] = {};
};