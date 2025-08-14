#pragma once

#include "Node.h"

class SingleLinkedList
{
public:
	SingleLinkedList();
	~SingleLinkedList();

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
	static void Print(const Node* head);

	void Sort();
	const Node* GetHead() const;

private:
	Node* MergeSort(Node* head);
	Node* SplitList(Node* head);						// 리스트를 반으로 나눠 두번째 리스트 head 노드를 반환한다.
	Node* MergeList(Node* a, Node* b);		// 두 리스트를 비교하여 합한다

private:
	// 첫 노드
	Node* head = nullptr;
	int count = 0;
};