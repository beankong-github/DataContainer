#pragma once


#include "Node.h"
#include <iostream>
#include <Windows.h>	

class RedBlackTree
{
public:
	RedBlackTree();
	~RedBlackTree();

	// �˻�
	bool Find(int data, Node*& outNode);

	// �߰�
	bool Insert(int data);

	// ��� �Լ�
	void Print(int depth = 0, int blackCount = 0);


	void Destroy();

private:
	// ��� ���� �Լ�
	Node* CreateNode(int data, Color color);
	// �˻� ��� �Լ�
	bool FindRecursive(int data, Node* node, Node*& outNode);
	// ��� �߰� ��� �Լ�
	void InsertRecursive(Node* node, Node* newNode);
	// ��� ���� �� ������ ó�� �Լ�
	void RestructureAfterInsert(Node* newNode);
	// ��� ��ȸ��
	void RotateToLeft(Node* node);
	// ��� ��ȸ��
	void RotateToRight(Node* node);
	// ��� ���
	void PrintRecursive(Node* node, int depth, int blackcount);
	// Ʈ�� �ı� ��� �Լ�.
	void DestroyRecursive(Node* node);

private:
	// ��Ʈ ��� (�ֻ�� �θ�)
	Node* root = nullptr;

	// NIL ���.
	static Node* nil;

};


enum class TextColor
{
	// �ܼ� ���� ����.
	Red = FOREGROUND_RED,
	Green = FOREGROUND_GREEN,
	Blue = FOREGROUND_BLUE,
	White = Red | Green | Blue,
};

void SetTextColor(TextColor color);