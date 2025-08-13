#pragma once

#include <iostream>
#include "Node.h"


template<typename T>
void SafeDelete(T*& target)
{
	if (target)
	{
		delete target;
		target = nullptr;
	}
}

template<typename T>
class LinkedList
{
public:
	LinkedList()
		: first(new Node<T>()), last(new Node<T>()), count(0)
	{
		// ���� ���� �� ��� ���� ����
		first->next = last;
		last->prev = first;
	}
	~LinkedList()
	{
		Clear();
		// TODO : ���� �Լ� ���� �� ȣ�� �ʿ�
		SafeDelete(first);
		SafeDelete(last);
	}


	void Clear()
	{
		Node<T>* current = first->next;
		while (current != nullptr && current != last)
		{
			Node<T>* next = current->next;
			SafeDelete(current);
			current = next;
		}

		count = 0;
		first->next = last;
		last->prev = first;
	}

	void PushFirst(const T& newData)
	{
		Node<T>* newNode = new Node<T>();
		newNode->data = newData;

		Node<T>* next = first->next;

		newNode->next = next;
		next->prev = newNode;

		first->next = newNode;
		newNode->prev = first;

		++count;
	}

	// ������ ��ġ�� ��� �߰�
	void PushLast(const T& newData)
	{
		Node<T>* newNode = new Node<T>();
		newNode->data = newData;

		Node<T>* prev = last->prev;
		prev->next = newNode;
		newNode->prev = prev;

		newNode->next = last;
		last->prev = newNode;

		++count;
	}
	
	void Delete(const T& deleteData)
	{
		// ��������� �ƹ��͵� ���� �ʴ´�.
		if (first->next == nullptr)
		{
			return;
		}

		// �˻�
		Node<T>* deleteNode = first->next;
		while (deleteNode && deleteNode != last)
		{
			// �����͸� ã������ �ݺ��� �����Ѵ�.
			if (deleteNode->data == deleteData)
			{
				break;
			}

			// �� ã������ ���� ��带 �̾��
			deleteNode = deleteNode->next;
		}
		
		// ����
		if (!deleteNode || deleteNode == last)
		{
			std::cout << "������ ��带 ã�� ���߽��ϴ�.\n";
			return;
		}

		// ���� ����
		deleteNode->prev->next = deleteNode->next;
		deleteNode->next->prev = deleteNode->prev;

		SafeDelete(deleteNode);
		--count;
	}


	void Print()
	{
		Node<T>* current = first->next;
		while (current != nullptr && current != last)
		{
			std::cout << "data: " << current->data << '\n';
			current = current->next;
		}
	}

private:
	// ó���� �������� ����Ű�� ���
	Node<T>* first = nullptr;
	Node<T>* last = nullptr;
	int count = 0;
};