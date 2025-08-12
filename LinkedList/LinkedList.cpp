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
		// ���� ���� �̵�
		tail = current;
		current = current->next;

		// ���� ��� ����
		delete tail;
		tail = nullptr;

		// ����� ����
		--count;
	}
	

}

void LinkedList::AddToHead(int newData)
{
	Node* newNode = new Node(newData);

	// ��尡 ��� �ִ� ��� �� ��尡 ��尡 �ȴ�.
	if (head == nullptr)
	{
		head = newNode;
		++count;
		return;
	}

	// ��尡 ���� ��� �� ��尡 ��� ��� ������ �� ��,
	// ��� �����ͷ� �� ��带 ����Ų��.
	newNode->next = head;
	head = newNode;
	++count;
}

void LinkedList::Insert(int newData)
{
	// head�� ����ִ� ��� Head�� �߰��Ѵ�.
	if (head == nullptr)
	{
		AddToHead(newData);
		return;
	}

	Node* current = head;
	Node* trail = nullptr;

	// next ��尡 null�� ������ �˻�
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
		std::cout << "����Ʈ�� ��� �־ ������ �Ұ���";
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

		// ���� ���� �̵�
		trail = current;
		current = current->next;
	}

	// ����Ʈ�� �����Ϸ��� ������ ����
	if (current == nullptr)
	{
		std::cout << "Data : " << data << "�� ã�� ���߽��ϴ�.\n";
		return;
	}

	// �˻��� ������ ���
	// 1. current�� head �� ���
	if (current == head)
	{
		head = head->next;
	}
	// 2. head�� �ƴ� ���
	else
	{
		trail->next = current->next;
	}
	delete current;
	--count;
}

void LinkedList::Print()
{
	// ��� ��带 ����Ѵ�.

	// head ������ ��ȸ
	Node* current = head;
	
	// ���� ��尡 null �� ������ �ݺ� (��� ��� �湮)
	while (current != nullptr)
	{
		// ���� ��� ������ ���
		std::cout << *current << "\n";
		// ���� ���� �̵�
		current = current->next;
	}
}
