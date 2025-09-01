#pragma once

#include <vector>
#include "Node.h"


// 쿼드 트리 클래스
class QuadTree
{
public:
	QuadTree(const Bounds& bounds);
	~QuadTree();

	void Insert(Node* node);

	//  전달한 노드와 겹치는 노드를 반환하는 함수 (질의-Query)
	std::vector<Node*> Query(Node* queryNode);

public:
	static const int maxDepth = 5;


private:
	Node* root = nullptr;
};