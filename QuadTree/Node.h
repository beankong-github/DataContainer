#pragma once
#include "Bounds.h"
#include <vector>

template<typename T>
void SafeDelete(T*& pointer)
{
	if (pointer)
	{
		delete pointer;
		pointer = nullptr;
	}
}

// ���� ������ ���� ������
enum class NodeIndex
{
	// ������ �����ϴ� ���
	TopLeft,				// ���� ���
	TopRight,			// ������ ���
	BottomLeft,		// ���� �ϴ�
	BottomRight,	// ������ �ϴ�

	// �� ��
	Straddling,		// �� ������ ��ģ ���
	OutOfArea,		// ������ ��� ���
};

class Node
{
public:
	Node(const Bounds& bounds, int depth = 0);
	~Node();

	// ���� (Insert)
	void Insert(Node* node);

	// ����(Query)
	void Query(const Bounds& queryBounds, std::vector<Node*>& possibleNodes);

	// ����
	void Clear();

	//Getter
	Bounds GetBounds() const { return bounds; }
	const std::vector<Node*>& GetPoints() const { return points; }

	Node* GetTopLeft() const { return topLeft; };
	Node* GetTopRight() const { return topRight; };
	Node* GetBottomLeft() const { return bottomLeft; };
	Node* GetBottomRight()  const{ return bottomRight; };

private:
	// ��ġ���� �Ǵ� ���ԵǴ��� Ȯ���ϴ� �Լ�
	NodeIndex TestRegion(const Bounds& bounds);

	// ��û�� Bounds�� ��ġ�� 4�и� ��� ��ȯ �Լ�
	std::vector<NodeIndex> GetQuads(const Bounds& bounds);

	bool Subdivide();

	bool IsDevided();
private:
	// ����
	int depth = 0;

	// ����
	Bounds bounds;

	// ���� ��忡 ���Ե� ��� (�迭)
	std::vector<Node*> points;

	// �ڽ� ���
	Node* topLeft = nullptr;
	Node* topRight = nullptr;
	Node* bottomLeft = nullptr;
	Node* bottomRight = nullptr;
};
