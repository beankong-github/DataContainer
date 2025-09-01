#pragma once

#include <vector>
#include "Node.h"


// ���� Ʈ�� Ŭ����
class QuadTree
{
public:
	QuadTree(const Bounds& bounds);
	~QuadTree();

	void Insert(Node* node);

	//  ������ ���� ��ġ�� ��带 ��ȯ�ϴ� �Լ� (����-Query)
	std::vector<Node*> Query(Node* queryNode);

public:
	static const int maxDepth = 5;


private:
	Node* root = nullptr;
};