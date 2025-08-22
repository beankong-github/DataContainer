#include "AStar.h"
#include "Node.h"

AStar::AStar()
{

}

AStar::~AStar()
{
	for (Node* n : openList)
	{
		SafeDelete(n);
	}
	openList.clear();

	for (Node* n : closeList)
	{
		SafeDelete(n);
	}
	closeList.clear();
}

vector<Node*> AStar::FindPath(Node* startNode, Node* goalNode, const vector<vector<int>>& grid)
{
	this->startNode = startNode;
	this->targetNode = goalNode;

	// 시작 노드를 열린 목록에 저장
	openList.emplace_back(startNode);

	while (!openList.empty())
	{
		// 가장 비용이 작은 노드 선택
		// 우선 순위 큐(힙)로 최적화 가능
		Node* lowestNode = openList[0];
		for (auto node : openList)
		{
			if (node->fCost < lowestNode->fCost)
			{
				lowestNode = node;
			}
		}

		Node* currentNode = lowestNode;

		// 현재 노드가 목표 노드인지 학인
		// 목표 노드라면 길을 생성해서 반환해준다.
		if (IsDestination(currentNode))
			return ConstructPath(currentNode);

		// 현재 노드->방문한 노드
		// 현재 노드를 열린 목록에서 제거
		for (int ix = 0; ix < (int)openList.size(); ++ix)
		{
			// 위치 비교
			if (*openList[ix] == *currentNode)
			{
				// 열린 목록에서 제거
				openList.erase(openList.begin() + ix);
				break;
			}
		}

		// 현재 노드를 닫힌 목록에 추가
		// 이미 있으면 추가 안하고 없으면 추가
		bool isNodeInList = false;
		for (Node* node : closeList)
		{
			if (*node == *currentNode)
			{
				isNodeInList = true;
				break;
			}
		}

		// 방문 했으면 아래 단계 건너 뛰기
		if (isNodeInList)
		{
			continue;
		}
		
		// 닫힌 리스트에 추가
		closeList.emplace_back(currentNode);

		// 이웃 노드들을 오픈 리스트에 넣는다.
		// 상하좌우 대각선 방향 및 비용
		static const vector<Direction> directions =
		{
			// 하상우좌
			{0, 1, 1.0f},  {0, -1, 1.f}, {1, 0, 1.f}, {-1, 0, 1.f},
			// 대각선
			{1, 1, 1.414f}, {1, -1, 1.414f}, {-1, 1, 1.414f}, {-1, -1, 1.414f}

		};
		for (const auto& dir : directions)
		{
			// 다음 이동할 위치
			int nextX = currentNode->pos.x + dir.x;
			int nextY = currentNode->pos.y + dir.y;

			//그리드 내에 유효한 인덱스 값인지 확인
			if (!IsInRange(nextX, nextY, grid))
				continue;

			// 값이 1이면 장애물이라고 약속
			// 장애물은 방문하지 않는다.
			if (grid[nextY][nextX] == 1)
				continue;

			// 이미 방문한 곳은 방문하지 않는다.
			float gCost = currentNode->gCost + dir.cost;
			if (HasVisited(nextX, nextY, gCost))
			{
				continue;
			}

			// 방문을 위한 노드 생성
			// 비용 계산
			Node* neighborNode = new Node(nextX, nextY, currentNode);
			neighborNode->gCost = gCost;
			// 휴리스틱 계산 
			neighborNode->hCost = CalculateHeuristic(neighborNode, targetNode);
			neighborNode->fCost = neighborNode->gCost + neighborNode->hCost;


			Node* openListNode = nullptr;
			for (Node* node : openList)
			{
				if (*node == *neighborNode)
				{
					openListNode = node;
					break;
				}
			}

			if (openListNode == nullptr
				|| openListNode->gCost > neighborNode->gCost
				|| openListNode->fCost > neighborNode->fCost)
			{
				openList.emplace_back(neighborNode);
			}
			else
			{
				SafeDelete(neighborNode);
			}
		}

	}
	return vector<Node*>();
}

void AStar::DisplayGridWithPath(std::vector<std::vector<int>>& grid, const std::vector<Node*>& path)
{
	for (const Node* node : path)
	{
		// 경로는 '2'로 표시.
		grid[node->pos.y][node->pos.x] = 2;
	}

	for (int y = 0; y < grid.size(); ++y)
	{
		for (int x = 0; x < grid[0].size(); ++x)
		{
			// 장애물.
			if (grid[y][x] == 1)
			{
				std::cout << "1 ";
			}

			// 경로.
			else if (grid[y][x] == 2)
			{
				std::cout << "* ";
			}

			// 빈 공간.
			else if (grid[y][x] == 0)
			{
				std::cout << "0 ";
			}
		}

		std::cout << "\n";
	}
}

vector<Node*> AStar::ConstructPath(Node* goalNode)
{
	// 경로를 반환하는 함수 로직 구현
	// 출력용 경로 배열 선언
	vector<Node*> path;

	Node* currentNode = goalNode;
	while (currentNode != nullptr)
	{
		path.emplace_back(currentNode);
		currentNode = currentNode->parent;
	}

	// 지금까지의 경로는 목표->시작 노드 방향
	// 시작->목표로 뒤집어야 한다.
	std::reverse(path.begin(), path.end());
	return path;
}

bool AStar::IsDestination(const Node* node)
{
	// 위치 비교 결과 반환
	return *node == *targetNode;
}

bool AStar::IsInRange(int x, int y, const vector<vector<int>>& grid)
{
	// x, y 범위가 벗어나면 false.
	if (x < 0 || y < 0 || x >= grid[0].size() || y >= (int)grid.size())
	{
		return false;
	}

	// 벗어나지 않으면 true
	return true;
}

bool AStar::HasVisited(int x, int y, float gCost)
{
	// 열린 리스트나 닫힌 리스트에 이미 해당 노드가 있으면 방문한 것으로 판단한다.

	// 열린 리스트에서 검색
	for (int ix = 0; ix < (int)openList.size(); ++ix)
	{
		Node* node = openList[ix];
		if (node->pos.x == x && node->pos.y == y)
		{
			// 위치가 같고, 비용도 더 크면 방문할 이유 없음
			if (node->gCost < gCost)
			{
				return true;
			}
			else if (node->gCost > gCost)
			{
				openList.erase(openList.begin() + ix);
				SafeDelete(node);
			}
		}
	}
	
	// 닫힌 리스트에서 검색
	for (int ix = 0; ix < (int)closeList.size(); ++ix)
	{
		Node* node = closeList[ix];
		// 위치가 같고, 비용도 더 크면 방문할 이유 없음
		if (node->pos.x == x && node->pos.y == y)
		{
			if (node->gCost < gCost)
			{
				return true;
			}
			else if(node->gCost > gCost)
			{
				closeList.erase(closeList.begin() + ix);
				SafeDelete(node);
			}
		}
	}

	// 목록에 없다고 확인되면 방문하지 않은 것으로 판단.
	return false;
}

float AStar::CalculateHeuristic(Node* currentNode, Node* targetNode)
{
	Position diff = *currentNode - *targetNode;
	// 대각선 길이 반환
	return (float)std::sqrt(diff.x*diff.x + diff.y*diff.y);
}
