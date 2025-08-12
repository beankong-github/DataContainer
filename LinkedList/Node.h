#pragma once


#include <iostream>

class Node
{
	// ����� ���ϰ� ó���ϱ� ���� ������ �����ε�
	friend std::ostream& operator << (std::ostream& os, const Node& node);
	
	// Linked List�� Node Ŭ������ ���� �� ������ �� �ֵ��� ����.
	friend class LinkedList;

private:
	Node();
	Node(int data);

private:
	int data;
	Node* next;
};