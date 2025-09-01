#include "Node.h"
#include "QuadTree.h"


Node::Node(const Bounds& bounds, int depth) 
	:bounds(bounds), depth(depth)
{
}


Node::~Node()
{
	// ��带 ��� �����ϴ� �Լ� ȣ��
	Clear();
}


void Node::Insert(Node* node)
{
	// ��ġ���� ������ ���ԵǴ��� Ȯ��
	NodeIndex result = 	TestRegion(node->GetBounds());

	//���� ������ ���ƴ���
	if (result == NodeIndex::Straddling)
	{
		// ��ġ�� ��쿡�� ���� ��� �˻��� ���̻� ���ϰ�, ���� ��忡 �߰�
		points.emplace_back(node);
	}
	// ��ġ�� ���� ���
	else if(result != NodeIndex::OutOfArea)
	{
		// ����
		if (Subdivide())
		{
			if (result == NodeIndex::TopLeft)
			{
				topLeft->Insert(node);
			}
			if (result == NodeIndex::TopRight)
			{
				topRight->Insert(node);
			}
			if (result == NodeIndex::BottomLeft)
			{
				bottomLeft->Insert(node);
			}
			if (result == NodeIndex::BottomRight)
			{
				bottomLeft->Insert(node);
			}
		}
		// �� �̻� ���� �� ���� ���
		else
		{
			points.emplace_back(node);
		}
	}
}

void Node::Query(const Bounds& queryBounds, std::vector<Node*>& possibleNodes)
{
	// ���� ��� �߰�
	possibleNodes.emplace_back(this);

	// ���� ��� �˻� (������ ���ҵ� ���)
	if (!IsDevided())
		return;

	std::vector<NodeIndex> quads = GetQuads(queryBounds);

	// ������ ó��
	for (NodeIndex& index : quads)
	{
		if (index == NodeIndex::TopLeft)
		{
			topLeft->Query(queryBounds, possibleNodes);
		}
		else if (index == NodeIndex::TopRight)
		{
			topRight->Query(queryBounds, possibleNodes);
		}
		else if (index == NodeIndex::BottomLeft)
		{
			bottomLeft->Query(queryBounds, possibleNodes);
		}
		else if (index == NodeIndex::BottomRight)
		{
			bottomRight->Query(queryBounds, possibleNodes);
		}
	}
}



 void Node::Clear()
 {
	 // ���� ��� ����
	 for (Node* node : points)
	 {
		 SafeDelete(node);
	 }
	 points.clear();

	 if (IsDevided())
	 {
		 // �ڼ� ����
		 topLeft->Clear();
		 topRight->Clear();
		 bottomLeft->Clear();
		 bottomRight->Clear();
		
		 // ����
		 SafeDelete(topLeft);
		 SafeDelete(topRight);
		 SafeDelete(bottomLeft);
		 SafeDelete(bottomRight);
	 }

 }

 NodeIndex Node::TestRegion(const Bounds& bounds)
 {
	 // ���޵� bounds�� ��ġ�� 4���� ��� Ȯ��
	 std::vector<NodeIndex> quad = GetQuads(bounds);

	 // ��ġ�� ���� ���ٸ�
	 if (quad.size() == 0)
	 {
		 return NodeIndex::OutOfArea;
	 }

	 // �ϳ��� �ִ� ���
	 if (quad.size() == 1)
	 {
		 return quad[0];
	 }


	// ���� ������ ��ġ�� ���
	 return NodeIndex::Straddling;
 }

 std::vector<NodeIndex> Node::GetQuads(const Bounds& bounds)
 {
	 std::vector<NodeIndex> quads;

	 // ���� ��꿡 �ʿ��� ����
	 float x = this->bounds.GetX();
	 float y = this->bounds.GetY();
	 float halfWidth = this->bounds.GetWidth() / 2;
	 float halfHeight = this->bounds.GetHegith() / 2;
	 float centerX = x + halfWidth;
	 float centerY = y + halfHeight;

	 // ���� ������ ���ƴ��� Ȯ��
	 bool left = bounds.GetX() < centerX && bounds.MaxX() >= x;
	 bool right = bounds.MaxX() >= centerX && bounds.GetX() < this->bounds.MaxX();
	 bool top = bounds.GetY() < centerY && bounds.MaxY() >= y;
	 bool bottom = bounds.MaxY() >= centerY && bounds.GetY() < this->bounds.MaxY();

	 if (top && left)
	 {
		 quads.emplace_back(NodeIndex::TopLeft);
	 }
	 if (top && right)
	 {
		 quads.emplace_back(NodeIndex::TopRight);
	 }
	 if (bottom && left)
	 {
		 quads.emplace_back(NodeIndex::BottomLeft);
	 }
	 if (bottom && right)
	 {
		 quads.emplace_back(NodeIndex::BottomRight);
	 }


	 return std::vector<NodeIndex>();
 }

 bool Node::Subdivide()
 {
	 // �ִ���̿� �����ߴ��� Ȯ��
	 //���� �ߴٸ� �� �̻� ���� ����
	 // TODO: �ִ�depth ���� ����� ����� �����ؾ� ��

	 if (depth == QuadTree::maxDepth)
		 return false;


	 if (!IsDevided())
	 {
		 // ���� ��������� ����
		 float x = bounds.GetX();
		 float y = bounds.GetY();
		 float halfWidth = bounds.MaxX() / 2.f;
		 float halfHeight = bounds.MaxY() / 2.f;

		 // ���� 4�и� ��ü ����
	
		//  x			x + halfwidth		   x + width
		//* +------------+------------+ y
		//  |    0 (TL)		 |    1 (TR)		|
		//  |						 |						|
		//  +------------+------------+ y + halfHeight
		//  |    2 (BL)		|    3 (BR)		|
		//  |						|						|
		//  +------------+------------+ y + height
		// 
		 topLeft = new Node(Bounds(x, y, halfWidth, halfHeight), ++depth);
		 topRight = new Node(Bounds(x + halfWidth, y, halfWidth, halfHeight), ++depth);
		 bottomLeft = new Node(Bounds(x, y + halfHeight, halfWidth, halfHeight), ++depth);
		 bottomRight = new Node(Bounds(x+halfWidth, y + halfHeight, halfWidth, halfHeight), ++depth);
	 }

	 return true;
 }

 bool Node::IsDevided()
 {
	 // �ڼ� ��� �� �ϳ��� null�� �ƴϸ� ���� �Ϸ� ����
	// �ڼ� ���� ��� null�̰ų�(���� �ȵ�),  ��� ����(���� ��)
	 return topLeft != nullptr;
 }
