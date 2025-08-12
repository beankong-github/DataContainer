#include "LinkedList.h"

LinkedList::LinkedList()
{
}

LinkedList::~LinkedList()
{
	Node* current = head;
	Node* tail = nullptr;

	while (current != nullptr)
	{
		// 다음 노드로 이동
		tail = current;
		current = current->next;

		// 현재 노드 삭제
		delete tail;
		tail = nullptr;

		// 디버깅 목적
		--count;
	}
	

}

void LinkedList::AddToHead(int newData)
{
	Node* newNode = new Node(newData);

	// 헤드가 비어 있는 경우 새 노드가 헤드가 된다.
	if (head == nullptr)
	{
		head = newNode;
		++count;
		return;
	}

	// 헤드가 있을 경우 새 노드가 헤드 노드 앞으로 온 뒤,
	// 헤드 포인터로 새 노드를 가리킨다.
	newNode->next = head;
	head = newNode;
	++count;
}

void LinkedList::Insert(int newData)
{
	// head가 비어있는 경우 Head로 추가한다.
	if (head == nullptr)
	{
		AddToHead(newData);
		return;
	}

	Node* current = head;
	Node* trail = nullptr;

	// next 노드가 null일 때까지 검색
	while (current != nullptr)
	{
		trail = current;
		current = current->next;
	}

	Node* newNode = new Node(newData);
	trail->next = newNode;
	++count;
}

void LinkedList::Delete(int data)
{
	if (head == nullptr)
	{
		std::cout << "리스트가 비어 있어서 삭제가 불가능";
		return;
	}

	Node* current = head;
	Node* trail = nullptr;

	while (current != nullptr)
	{
		if (current->data == data)
		{
			break;
		}

		// 다음 노드로 이동
		trail = current;
		current = current->next;
	}

	// 리스트에 삭제하려는 데이터 없음
	if (current == nullptr)
	{
		std::cout << "Data : " << data << "를 찾지 못했습니다.\n";
		return;
	}

	// 검색에 성공한 경우
	// 1. current가 head 인 경우
	if (current == head)
	{
		head = head->next;
	}
	// 2. head가 아닌 경우
	else
	{
		trail->next = current->next;
	}
	delete current;
	--count;
}

void LinkedList::Print()
{
	// 모든 노드를 출력한다.

	// head 노드부터 순회
	Node* current = head;
	
	// 현재 노드가 null 일 때까지 반복 (모든 노드 방문)
	while (current != nullptr)
	{
		// 현재 노드 데이터 출력
		std::cout << *current << "\n";
		// 다음 노드로 이동
		current = current->next;
	}
}
