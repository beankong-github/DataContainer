#pragma once

#include "Node.h"

class LinkedList
{
public:
	LinkedList();
	~LinkedList();

	// 첫 노드에 데이터 추가
	// 노드가 비어 있으면 head 생성
	// 노드가 있으면 head 교체
	void AddToHead(int newData);
	// 맨 뒤에 노드 추가
	void Insert(int newData);

	// 노드 삭제
	void Delete(int data);
	// 모두 정리
	void Clear();
	// 출력
	void Print();
private:
	// 첫 노드
	Node* head = nullptr;
	int count = 0;
};