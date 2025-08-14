#pragma once


#include <iostream>

class Node
{
	// ����� ���ϰ� ó���ϱ� ���� ������ �����ε�
	friend std::ostream& operator << (std::ostream& os, const Node& node);
	
	// Linked List�� Node Ŭ������ ���� �� ������ �� �ֵ��� ����.
	friend class SingleLinkedList;

private:
	Node();
	Node(int data);

private:
	int data;
	Node* next;
};