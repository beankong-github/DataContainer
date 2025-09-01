#include "Node.h"
#include "QuadTree.h"


Node::Node(const Bounds& bounds, int depth) 
	:bounds(bounds), depth(depth)
{
}


Node::~Node()
{
	// 노드를 모두 제거하는 함수 호출
	Clear();
}


void Node::Insert(Node* node)
{
	// 겹치는지 완전히 포함되는지 확인
	NodeIndex result = 	TestRegion(node->GetBounds());

	//여러 영영과 겹쳤는지
	if (result == NodeIndex::Straddling)
	{
		// 겹치는 경우에는 하위 노드 검색을 더이상 안하고, 현재 노드에 추가
		points.emplace_back(node);
	}
	// 겹치지 않은 경우
	else if(result != NodeIndex::OutOfArea)
	{
		// 분할
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
		// 더 이상 나눌 수 없는 경우
		else
		{
			points.emplace_back(node);
		}
	}
}

void Node::Query(const Bounds& queryBounds, std::vector<Node*>& possibleNodes)
{
	// 현재 노드 추가
	possibleNodes.emplace_back(this);

	// 하위 노드 검색 (영역이 분할된 경우)
	if (!IsDevided())
		return;

	std::vector<NodeIndex> quads = GetQuads(queryBounds);

	// 루프로 처리
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
	 // 현재 노드 정리
	 for (Node* node : points)
	 {
		 SafeDelete(node);
	 }
	 points.clear();

	 if (IsDevided())
	 {
		 // 자손 정리
		 topLeft->Clear();
		 topRight->Clear();
		 bottomLeft->Clear();
		 bottomRight->Clear();
		
		 // 정리
		 SafeDelete(topLeft);
		 SafeDelete(topRight);
		 SafeDelete(bottomLeft);
		 SafeDelete(bottomRight);
	 }

 }

 NodeIndex Node::TestRegion(const Bounds& bounds)
 {
	 // 전달된 bounds와 겹치는 4문면 목록 확인
	 std::vector<NodeIndex> quad = GetQuads(bounds);

	 // 겹치는 곳이 없다면
	 if (quad.size() == 0)
	 {
		 return NodeIndex::OutOfArea;
	 }

	 // 하나만 있는 경우
	 if (quad.size() == 1)
	 {
		 return quad[0];
	 }


	// 여러 영역과 겁치는 경우
	 return NodeIndex::Straddling;
 }

 std::vector<NodeIndex> Node::GetQuads(const Bounds& bounds)
 {
	 std::vector<NodeIndex> quads;

	 // 영역 계산에 필요한 변수
	 float x = this->bounds.GetX();
	 float y = this->bounds.GetY();
	 float halfWidth = this->bounds.GetWidth() / 2;
	 float halfHeight = this->bounds.GetHegith() / 2;
	 float centerX = x + halfWidth;
	 float centerY = y + halfHeight;

	 // 왼쪽 영역과 겹쳤는지 확인
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
	 // 최대깊이에 도달했는지 확인
	 //도달 했다면 더 이상 분할 안함
	 // TODO: 최대depth 값을 상수로 만들고 설정해애 함

	 if (depth == QuadTree::maxDepth)
		 return false;


	 if (!IsDevided())
	 {
		 // 영역 계산을위한 변수
		 float x = bounds.GetX();
		 float y = bounds.GetY();
		 float halfWidth = bounds.MaxX() / 2.f;
		 float halfHeight = bounds.MaxY() / 2.f;

		 // 분할 4분면 객체 생성
	
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
	 // 자손 노드 중 하나가 null이 아니면 분할 완료 상탠
	// 자손 노드는 모두 null이거나(분할 안됨),  모두 생성(분할 됨)
	 return topLeft != nullptr;
 }
