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
		// 시작 노드와 끝 노드 서로 연결
		first->next = last;
		last->prev = first;
	}
	~LinkedList()
	{
		Clear();
		// TODO : 삭제 함수 구현 후 호출 필요
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

	// 마지막 위치에 노드 추가
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
		// 비어있으면 아무것도 하지 않는다.
		if (first->next == nullptr)
		{
			return;
		}

		// 검색
		Node<T>* deleteNode = first->next;
		while (deleteNode && deleteNode != last)
		{
			// 데이터를 찾았으면 반복을 종료한다.
			if (deleteNode->data == deleteData)
			{
				break;
			}

			// 못 찾았으면 다음 노드를 이어간다
			deleteNode = deleteNode->next;
		}
		
		// 삭제
		if (!deleteNode || deleteNode == last)
		{
			std::cout << "삭제할 노드를 찾지 못했습니다.\n";
			return;
		}

		// 삭제 진행
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
	// 처음과 마지막을 가리키는 노드
	Node<T>* first = nullptr;
	Node<T>* last = nullptr;
	int count = 0;
};