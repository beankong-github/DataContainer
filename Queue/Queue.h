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

	// ������� Ȯ��
	bool IsEmpty() const
	{
		// �հ� �ڸ� ����Ű�� ��ġ ���� ������ �� ����
		return front == rear;
	}

	bool IsFull() const{
		return (rear + 1) % maxQueueCount == front;
	}

	//  ���

	// ť�� ������ �߰�
	bool Enqueue(int newData)
	{
		// ����á����  �����͸� �߰��� �� ����
		if (!IsFull())
		{
			return;
		}

		rear = (rear + 1) % maxQueueCount;
		data[rear] = newData;

		return true;
	}


	// ť���� ������ ����
	bool Dequeue(int& outValue)
	{
		if (IsEmpty())
		{
			std::cout << "Error: ť�� ��� �ֽ��ϴ�. \n";
			return false;
		}
		front = (front + 1) % maxQueueCount;
		outValue = data[front];
		return true;
	}

	// ���

private:
	int front = 0;
	int rear = 0; 
	int data[maxQueueCount] = {};
};