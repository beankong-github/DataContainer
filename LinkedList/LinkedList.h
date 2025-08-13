#pragma once

#include "Node.h"

class LinkedList
{
public:
	LinkedList();
	~LinkedList();

	// ù ��忡 ������ �߰�
	// ��尡 ��� ������ head ����
	// ��尡 ������ head ��ü
	void AddToHead(int newData);
	// �� �ڿ� ��� �߰�
	void Insert(int newData);

	// ��� ����
	void Delete(int data);
	// ��� ����
	void Clear();
	// ���
	void Print();
private:
	// ù ���
	Node* head = nullptr;
	int count = 0;
};