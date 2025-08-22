#pragma once


#include "Node.h"
#include <iostream>
#include <Windows.h>	

class RedBlackTree
{
public:
	RedBlackTree();
	~RedBlackTree();

	// 검색
	bool Find(int data, Node*& outNode);

	// 추가
	bool Insert(int data);

	// 출력 함수
	void Print(int depth = 0, int blackCount = 0);


	void Destroy();

private:
	// 노드 생성 함수
	Node* CreateNode(int data, Color color);
	// 검색 재귀 함수
	bool FindRecursive(int data, Node* node, Node*& outNode);
	// 노드 추가 재귀 함수
	void InsertRecursive(Node* node, Node* newNode);
	// 노드 삽입 후 재정렬 처리 함수
	void RestructureAfterInsert(Node* newNode);
	// 노드 좌회전
	void RotateToLeft(Node* node);
	// 노드 우회전
	void RotateToRight(Node* node);
	// 출력 재귀
	void PrintRecursive(Node* node, int depth, int blackcount);
	// 트리 파괴 재귀 함수.
	void DestroyRecursive(Node* node);

private:
	// 루트 노드 (최상단 부모)
	Node* root = nullptr;

	// NIL 노드.
	static Node* nil;

};


enum class TextColor
{
	// 콘솔 색상 정의.
	Red = FOREGROUND_RED,
	Green = FOREGROUND_GREEN,
	Blue = FOREGROUND_BLUE,
	White = Red | Green | Blue,
};

void SetTextColor(TextColor color);