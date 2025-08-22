#pragma once

#include <vector>

using namespace std;

template<typename T>
void SafeDelete(T*& pointer)
{
	if (pointer)
	{
		delete pointer;
		pointer = nullptr;
	}
}

// A* ��ã�� �˰����� ó���ϴ� Ŭ����
class Node;
class AStar
{
	// ���� ó�� ����ü
	struct Direction
	{
		int x = 0;
		int y = 0;

		// �̵� ���
		float cost = 0.f;
	};

public:
	AStar();
	~AStar();

	vector<Node*> FindPath(
		Node* startNode,
		Node* goalNode,
		const vector<vector<int>>& grid
	);

	// �׸��� ��� �Լ�.
	void DisplayGridWithPath(std::vector<std::vector<int>>& grid, const std::vector<Node*>& path);


private:
	//Ž���� ��ģ �Ŀ� ��θ� ������ ��ȯ�ϴ� �Լ�
	// ��ǥ ��忡�� �θ� ��带 ������ ���� ������ ������ �ϸ鼭 ��θ� ���Ѵ�.
 	vector<Node*> ConstructPath(Node* goalNode);

	// Ž���Ϸ��� ��尡 ��ǥ ������� Ȯ��
	bool IsDestination(const Node* node);

	// �׸��� �ȿ� �ִ��� Ȯ��
	bool IsInRange(int x, int y, const vector<vector<int>>& grid);

	// �̹� �湮�ߴ��� Ȯ���Ѵ�.
	bool HasVisited(int x, int y, float gCost);

	// ���� �������� ��ǥ ���������� ���� ��� ��� �Լ�
	float CalculateHeuristic(Node* currentNode, Node* targetNode);

private:
	// ���� ����Ʈ (�湮�� ����� ���)
	vector<Node*> openList;

	// ���� ����Ʈ (�湮�� ����� ���)
	vector<Node*> closeList;

	// ���� ���
	Node* startNode = nullptr;

	// ��ǥ ���
	Node* targetNode = nullptr;
};