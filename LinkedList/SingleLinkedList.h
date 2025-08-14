#pragma once

#include "Node.h"

class SingleLinkedList
{
public:
	SingleLinkedList();
	~SingleLinkedList();

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
	static void Print(const Node* head);

	void Sort();
	const Node* GetHead() const;

private:
	Node* MergeSort(Node* head);
	Node* SplitList(Node* head);						// ����Ʈ�� ������ ���� �ι�° ����Ʈ head ��带 ��ȯ�Ѵ�.
	Node* MergeList(Node* a, Node* b);		// �� ����Ʈ�� ���Ͽ� ���Ѵ�

private:
	// ù ���
	Node* head = nullptr;
	int count = 0;
};